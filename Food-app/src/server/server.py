import socket
import time
import os
from datetime import datetime

fileLines = []
clients = []

def zeroize(string, length=2):
    ret = ""
    if len(string) < length:
        for x in range(length - len(string)):
            ret += "0"
    else:
        return string
    return ret + string

def removeCRLF(string):
    ret = ""
    for b in string:
        if b != "\r" and b != "\n":
            ret += b
    return ret

class Date:
    def __init__(self, m=0, d=0, y=0):
        self.mon = m
        self.day = d
        self.year = y
        self.arr = [m, d, y]

    def array(self):
        return self.arr

    def getStr(self):
        return zeroize(str(self.mon)) + "/" + zeroize(str(self.day)) + "/" + zeroize(str(self.year))

    def isGreaterThan(self, comp):
        if comp.year == self.year:
            if comp.mon == self.mon:
                return self.day > comp.day
            else:
                return self.mon > comp.mon
        else:
            return self.year > comp.year
        return False

class Client:
    def __init__(self, tup):
        self.tup = tup
        self.tup[0].setblocking(False)
        self.greet = False
        self.commandState = False
        self.inputState = False
        self.buffer = ""
        self.currentData = ""
        self.lastFullData = ""
        self.lastSent = ""

    def sendTo(self, string):
        self.greet = True
        try:
            self.tup[0].send(bytes(string, 'utf-8'))
        except BrokenPipeError:
            pass

    def sendOnce(self, string):
        if self.lastSent == string:
            return
        self.lastSent = string
        self.sendTo(string)

    def get(self):
        return self.currentData

    def commandLine(self):
        if self.inputState:
            return self.lastFullData
        if not self.commandState:
            self.sendTo("-> ")
            self.commandState = True
        
        recvData = self.get()
        if recvData:
            self.commandState = False
        return recvData

    def update(self):
        try:
            add = self.tup[0].recv(1024).decode()
            self.buffer += add
            if not add:
                self.currentData = "NOPE"
            else:
                self.currentData = ""
        except BlockingIOError:
            for x in range(len(self.buffer)):
                if self.buffer[x] == "\r" or self.buffer[x]:
                    break
                if x == len(self.buffer)-1:
                    self.currentData = ""         
            ret = self.buffer
            if self.buffer and not self.inputState:
                self.lastFullData = self.buffer
            self.buffer = ""
            self.currentData = ret
        except UnicodeDecodeError:
            pass

    def leave(self):
        self.tup[0].close()

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setblocking(False)

def findUsableSocket():         # Finds an available port number starting at 8000
    currentPort = 8000
    noBind = True
    while noBind:
        noBind = False
        try:
            print("Server: ATTEMPT on port", currentPort)
            time.sleep(1)
            sock.bind(("", currentPort))
        except OSError:
            print("Server: FAILED on port", currentPort)
            print("Trying again in 3 seconds")
            time.sleep(3)
            noBind = True
        finally:
            if not noBind:
                print("Server: BOUND on port", currentPort)
            else:
                currentPort += 1


findUsableSocket()

def loadFoodInfo():
    foodFile = open("Food-file.txt", 'r+')
    global fileLines
    fileLines = foodFile.readlines()
    ret = []
    for x in range(len(fileLines)):
        fileLines[x] = removeCRLF(fileLines[x])
        ret.append(fileLines[x].split("  "))
        ret[x][1] = Date(int(fileLines[x].split("  ")[1].split("/")[0]), int(fileLines[x].split("  ")[1].split("/")[1]), int(fileLines[x].split("  ")[1].split("/")[2]))
    fileLines = ret
    foodFile.close()

def writeFoodInfo():
    foodFile = open("Food-file.txt", 'w+')
    for item in fileLines:
        ret = item[0] + "  " + item[1].getStr() + "  " + item[2] + "  " + item[3] + "\n"
        foodFile.write(ret)
        ret = ""

def getSortedFoodArray(arr):
    loadFoodInfo()
    sort = arr
    hasSorted = True
    while hasSorted:
        hasSorted = False
        for x in range(len(sort) - 1):
            if sort[x][1].isGreaterThan(sort[x+1][1]):
                tmp = sort[x+1]
                sort[x+1] = sort[x]
                sort[x] = tmp
                hasSorted = True
    return sort

def getHelp():
    ret = ""
    ret += "----------------------------------------------------\n"
    ret += "Commands: \n\nlist items: Lists all food items in order. \n\nadd item: Add an item to the list. \n\nremove item: Removes an item from the food list.\n"
    ret += "----------------------------------------------------\n"
    return ret

def getUnsortedFoodInfo():
    ret = ""
    loadFoodInfo()
    ret += "Name\t\t\t\tDate\t\t\t\tLocation\t\t\t\t\tAmount remaining\n"
    for line in arr:
        ret += "--------------------------------------------------------------------------------------------------------------------------------\n"
        ret += line[0]
        for y in range(32 - len(line[0])):
            ret += " "
        ret += line[1].getStr() + "\t\t\t"
        ret += line[2] + "\t\t\t\t\t\t"
        ret += line[3]
    return ret + "--------------------------------------------------------------------------------------------------------------------------------\n"

def getSortedFoodInfo(arr):
    ret = ""
    ret += "Name\t\t\t\tDate\t\t\t\tLocation\t\t\t\t\tAmount remaining\n"
    for line in getSortedFoodArray(arr):
        ret += "--------------------------------------------------------------------------------------------------------------------------------\n"
        ret += line[0]
        for y in range(32 - len(line[0])):
            ret += " "
        ret += line[1].getStr() + "\t\t\t"
        ret += line[2] + "\t\t\t\t\t\t"
        ret += line[3] + "\n"
    return ret + "--------------------------------------------------------------------------------------------------------------------------------\n"

def getAllGroup(g):
    global fileLines
    ret = fileLines
    for item in ret:
        if item[2] == removeCRLF(g):
            del item
    return getSortedFoodInfo(ret)

def getExpired():
    global fileLines
    currentDate = Date(datetime.now().month, datetime.now().day, int(str(datetime.now().year)[2:]))
    ret = []
    for item in getSortedFoodArray(fileLines):
        if not item[1].isGreaterThan(currentDate):
            ret.append(item)
    return getSortedFoodInfo(ret)

def addItem(n, d, l, a):
    f = open("Food-file.txt", 'a')
    f.write(n + "  " + d + "  " + l + "  " + a + "\n")
    f.close()

def removeItem(i, amt="1"):
    loadFoodInfo()
    fileLines[i][3] = str(int(fileLines[i][3]) - int(amt))
    if int(fileLines[i][3]) <= 0:
        del fileLines[i]
    writeFoodInfo()

def getAllPossible(name):
    loadFoodInfo()
    ret = []
    for item in fileLines:
        if item[0] == name:
            ret.append(item)
    return ret

def getItemPosition(name):
    for x in range(len(fileLines)):
        if removeCRLF(fileLines[x][0]) == removeCRLF(name):
            return x

def acceptClients():
    try:
        app = Client(sock.accept())
        clients.append(app)
    except BlockingIOError:
        pass


addName = ""
addDate = ""
addLoc = ""
addAmt = ""
removeName = ""
removeIndex = ""
removeAmt = ""
groupName = ""

def updateClients():
    global clients, addName, addDate, addLoc, addAmt, removeName, removeIndex, removeAmt, groupName, fileLines
    for cli in clients:
        if not cli.greet:
            cli.sendTo(getHelp())
            
        if cli.get() == "NOPE":
            del clients[clients.index(cli)]
            print("client removed")
        
        s = cli.commandLine()
        if s: 
            if removeCRLF(s) == "list items":
                loadFoodInfo()
                cli.sendTo(getSortedFoodInfo(fileLines))
            elif removeCRLF(s) == "add item":
                cli.inputState = True
                if not addName:
                    cli.sendOnce("Enter in the name:  ")
                    if removeCRLF(cli.get()) != "add item":
                        addName = cli.get()
                else:
                    if not addDate:
                        cli.sendOnce("Enter in the expiration date:  ")
                        addDate = cli.get()
                    else:
                        if not addLoc:
                            cli.sendOnce("Enter in the location:  ")
                            addLoc = cli.get()
                        else:
                            if not addAmt:
                                cli.sendOnce("Enter in the amount:  ")
                                addAmt = cli.get()
                            else:
                                cli.sendOnce("Added items.\n")
                                addItem(removeCRLF(addName), removeCRLF(addDate), removeCRLF(addLoc), removeCRLF(addAmt))
                                cli.inputState = False
                                addName = ""
                                addDate = ""
                                addAmt = ""
                                addLoc = ""
            elif removeCRLF(s) == "remove item":
                cli.inputState = True
                if not removeName or removeCRLF(removeName) == "remove item":
                    cli.sendOnce("Enter in the item name to delete:  ")
                    removeName = cli.get()
                else:
                    if not removeAmt:
                        cli.sendOnce("Enter in the amount of items to remove:  ")
                        removeAmt = cli.get()
                    else:
                        n = getAllPossible(removeCRLF(removeName))
                        if len(n) > 1:
                            send = "There are multiple items with that name. Select which one to delete:\n"
                            for x in range(len(n)):
                                send += "(" + str(x) + "): " + n[x][1].getStr() + "\n"
                            send += "Enter the number to delete: "
                            if not removeIndex:
                                cli.sendOnce(send)
                                removeIndex = cli.get()
                            else:
                                cli.sendOnce("Item(s) deleted.\n")
                                removeItem(fileLines.index(n[int(removeCRLF(removeIndex))]), removeCRLF(removeAmt))
                                cli.inputState = False
                                removeName = ""
                                removeIndex = ""
                                removeAmt = ""
                        elif not n:
                            cli.sendTo("There are no items with this name.\n")
                            cli.inputState = False
                            removeName = ""
                            removeIndex = ""
                            removeAmt = ""
                        else:
                            removeItem(getItemPosition(removeName), removeAmt)
                            cli.inputState = False
                            cli.sendTo("Item(s) deleted.\n")
                            removeName = ""
                            removeIndex = ""
                            removeAmt = ""
            elif removeCRLF(s) == "list expired":
                loadFoodInfo()
                cli.sendTo(getExpired())
            elif removeCRLF(s) == "list group":
                loadFoodInfo()
                cli.inputState = True
                if not groupName:
                    cli.sendOnce("Enter in a group:  ")
                    groupName = cli.get()
                else:
                    cli.sendTo(getAllGroup(groupName))
                    cli.inputState = False
            elif removeCRLF(s) == "quit":
                cli.sendOnce("Leaving!\n")
                cli.leave()
                del clients[clients.index(cli)]
            else:
                cli.sendTo("Command not found!\n")
                cli.sendTo(getHelp())

        if removeCRLF(s) != "quit":
            cli.update()

while 1:
    try:
        sock.listen(20)
        acceptClients()
        updateClients()
    except KeyboardInterrupt:
        print("\nKeyboard interrupt, leaving")
        break
sock.close()