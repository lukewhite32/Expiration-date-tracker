/* Javascript for the food app */

var names          = [];
var dates          = [];
var place          = [];
var amount         = [];
var current_length = 0;

function zeroize(num, goTo=2) {
    let ret = num;
    if (num.length < goTo) {
        for (var x = 0; x < goTo - num.length; x ++) {
            ret = "0" + num;
        }
    }
    return ret;
}

function datitize(date) {
    /*if (!(date.split("-") > 0)) {
        return date;
    }*/
    var m, d, y;
    m = date.split("-")[1];
    d = date.split("-")[2];
    y = date.split("-")[0];
    return m + "/" + d + "/" + y;
}

class Info {
    constructor(n, d, p, a) {
        this.name = n;
        this.date = d;
        this.place = p;
        this.amount = a;
    }
};

class Date {
    constructor(m=0, d=0, y=0) {
        this.m = zeroize("" + m);
        this.d = zeroize("" + d);
        this.y = zeroize("" + y);
    }

    get_str() {
        return ("" + this.m) + "/" + ("" + this.d) + "/" + ("" + this.y);
    }
};

function infoMatches(info1, info2) {
    return (info1.name == info2.name) && (info1.date == info2.date) && (info1.place == info2.place) && (info1.amount == info2.amount);
}

function getList() {
    return Array.from(document.getElementById("the-table").childNodes);
}

function removeItem(ind) {
    names.splice(ind);
    dates.splice(ind);
    place.splice(ind);
    amount.splice(ind);
    updateTable();
    current_length -= 1;
}

function wipeTable() {
    document.getElementById("the-table").innerHTML = "";
}

function addItem(name_text, date_text, loc_text, amt_text) {
    let tr = document.createElement('TR');
    tr.innerHTML += "<th>" + name_text + "</th>";
    tr.innerHTML += "<th>" + date_text + "</th>";
    tr.innerHTML += "<th>" + loc_text + "</th>";
    tr.innerHTML += "<th>" + amt_text + "</th>";
    let delButton = document.createElement('BUTTON');
    delButton.innerHTML = "Delete";
    delButton.onclick = () => { removeItem(getList().indexOf(tr)) };
    tr.appendChild(delButton);
    document.getElementById("the-table").appendChild(tr);
    current_length += 1;
}

function updateTable() {
    wipeTable();
    for (let x = 0; x < current_length; x ++) {
        console.log(dates[x]);
        addItem(names[x], dates[x].get_str(), place[x], amount[x]);
    }
}

function wipeArray() {
    names = [];
    dates = [];
    place = [];
    amount = [];
    current_length = 0;
}

function load() {
    names.push("test1");
    names.push("test2");
    names.push("test3");
    dates.push(new Date (1, 2, 3));
    dates.push(new Date (4, 5, 6));
    dates.push(new Date (7, 8, 9));
    place.push(1);
    place.push(2);
    place.push(3);
    amount.push(4);
    amount.push(5);
    amount.push(6);

    updateTable();
}

load();

document.getElementById("button-add-item").onclick = () => {
    addItem(
        document.getElementById("item-name").value,
        datitize(document.getElementById("item-date").value),
        document.getElementById("item-loc").value,
        document.getElementById("item-amt").value
    ) 
};