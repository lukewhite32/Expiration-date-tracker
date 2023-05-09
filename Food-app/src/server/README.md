# Server
A telnet food app in Python. It is capable of handling multiple clients.

# To use
Download `server.py` on a computer and run:
`python3 server.py`.
There should be a prompt asking for a port number, enter in the desired port number.

To use, on a seperate computer, run this at the terminal:
`telnet (ip of server computer) (port number)`

# Features
* Names: The name of the food item.
* Dates: When prompted `Enter in the expiration date:  `, it is expecting a `mm/dd/yy` format (don't forget the '/'!) The items are sorted by the date you pass in.
* Location: The location of the item (i.e. shelf, cabinet, etc). If you are not intending to use a group, just leave it blank.
* Amount: The amount of the item you have. For example, if you had a 4 or 8-pack of beans.