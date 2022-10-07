// Constructor Function
// pascal case not camel case like in factory functions

function Circle(radius) {
    this.radius = radius;
    this.draw = function() {
        console.log('draw');
    }
}

// 'new' creates and empty object which points to the constructor function
const circle = new Circle(1);


// we can add or remove properties and functions
circle.color = 'yellow';
circle.hipo = 3
circle.draw = function() {}

delete circle.hipo;


console.log(circle);

//constructor porperty return the function used to create that object
circle.constructor


// both ways of creating objects are valid
// the constructor function it's more familiar to me so i will stick with that one