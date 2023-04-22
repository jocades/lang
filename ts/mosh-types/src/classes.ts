class Account {
  // readonly id: number
  // owner: string
  // private _balance: number // only accessible from inside the class
  nickname?: string

  // parameter properties: they are automatically declared as properties
  constructor(
    public readonly id: number,
    public owner: string,
    private _balance: number
  ) {
    // this.id = id
    // this.owner = owner
    // this._balance = balance
  }

  deposit(amount: number): void {
    if (amount <= 0) throw new Error('Invalid amount')
    this._balance += amount
  }

  getBalance(): number {
    return this._balance
  }

  // making it a getter
  get balance(): number {
    return this._balance
  }

  // setter
  set balance(value: number) {
    if (value < 0) throw new Error('Invalid amount')
    this._balance = value
  }
}

let account = new Account(1, 'John', 0)
console.log(typeof account) // it wil allways return object
console.log(account instanceof Account) // it will return true

console.log(account.getBalance())
console.log(account.balance)
account.balance = 2 // possible because of the setter

// STATIC METHODS: they belong to the class, not to the instance (only a single copy in memory)
class Ride {
  private static _activeRides: number = 0

  sart() {
    Ride._activeRides++
  }

  stop() {
    Ride._activeRides--
  }

  static get activeRides(): number {
    return Ride._activeRides
  }
}

let ride1 = new Ride()
ride1.sart()

let ride2 = new Ride()
ride2.sart()

console.log(Ride.activeRides)

// ----------------------------
// INHERITANCE
class Person {
  constructor(public firstName: string, public lastName: string) {}

  get fullName() {
    return `${this.firstName} ${this.lastName}`
  }

  // protected: only accessible from inside the class or from the child classes
  // private: only accessible from inside the class
  protected sayHello() {
    console.log('Hello')
  }
}

class Student extends Person {
  constructor(public studentId: number, firstName: string, lastName: string) {
    super(firstName, lastName) // calling the constructor of the parent class will initialize the properties
  }

  takeExam() {
    this.sayHello()
    console.log(`${this.fullName} is taking an exam`)
  }
}

let student = new Student(1, 'John', 'Doe')
student.takeExam()

// overriding methods
class Teacher extends Person {
  // we inherit the constructor from the parent class

  override get fullName() {
    return `Professor ${super.fullName}`
  }
}

let teacher = new Teacher('Mary', 'Jane')
console.log(teacher.fullName)

// POLYMORPHISM (morph = form): the ability to treat objects of different types in the same way

function printNames(people: Person[]) {
  for (let person of people) {
    console.log(person.fullName)
  }
}

printNames([new Student(1, 'John', 'Doe'), new Teacher('Mary', 'Jane')])

// ----------------------------
// ABSTRACT CLASSES and METHODS:
// they cannot be instantiated, they are used as a base class for other classes
// abstract methods must be implemented in the child classes

abstract class Shape {
  constructor(public color: string) {}

  abstract render(): void
}

class Circle extends Shape {
  constructor(color: string, public radius: number) {
    super(color)
  }

  override render(): void {
    console.log('Rendering a circle')
  }
}

// let shape = new Shape('red') -> not possible
