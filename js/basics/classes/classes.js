// IMPORT FROM MODULE 
class Person {
    constructor(name) {
        this.name = name;
    }

    walk() {
        console.log('walk');
    }
}

const person = new Person('Jordi');
person.walk();


// Inheritance
class Teacher extends Person {
    constructor(name, degree) {
        // we have to call the parent constructor and pass in the name argument
        super(name);
        this.degree = degree;
    }

    teach() {
        console.log('teach');
    }
}

const teacher = new Teacher('Julia', 'MSc');
teacher.teach();