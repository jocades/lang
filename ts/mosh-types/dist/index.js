"use strict";
var _a;
let age = 25;
if (age < 50) {
    age += 10;
}
let numbers = [1, 2, 3];
numbers.forEach((n) => n.toString());
let user = [1, 'John'];
user.push(2);
let mySize = 1;
console.log(mySize);
function calcTax(income, taxYear = 2022) {
    if (taxYear < 2022)
        return income * 1.2;
    return income * 1.4;
}
calcTax(10000);
let employee = {
    id: 1,
    name: 'John',
    retire: (date) => {
        console.log(date);
    },
};
let employee2 = {
    id: 1,
    name: 'John',
    retire: (date) => {
        console.log(date);
    },
};
function kgToPounds(weight) {
    if (typeof weight === 'number')
        return weight * 2.2;
    else
        return parseInt(weight) * 2.2;
}
kgToPounds(10);
kgToPounds('10kg');
let widget = {
    drag: () => { },
    resize: () => { },
};
let quantity = 10;
function greet(name) {
    if (name)
        console.log(`Hello ${name.toUpperCase()}`);
    else
        console.log('Hola!');
}
greet(null);
function getCustomer(id) {
    return id === 0 ? null : { birthday: new Date() };
}
let customer = getCustomer(0);
console.log((_a = customer === null || customer === void 0 ? void 0 : customer.birthday) === null || _a === void 0 ? void 0 : _a.getFullYear());
let log1 = null;
log1 === null || log1 === void 0 ? void 0 : log1('a');
let log = (message) => console.log(message);
let speed = null;
let ride = {
    speed: speed || 30,
    speed1: speed !== null ? speed : 30,
    speedCorrect: speed !== null && speed !== void 0 ? speed : 30,
};
let phone = document.getElementById('phone');
phone.value = '123456789';
function reject(message) {
    throw new Error(message);
}
function processEvents() {
    while (true) {
    }
}
reject('something went wrong');
//# sourceMappingURL=index.js.map