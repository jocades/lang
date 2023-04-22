let age: number = 25

if (age < 50) {
  age += 10
}

let numbers = [1, 2, 3]
numbers.forEach((n) => n.toString())

// TUPLE (don't use for arrays with more than 2 items, what is the point?)

let user: [number, string] = [1, 'John']
user.push(2)

// ----------------------------
// ENUM: used to represent a list of constants

// const small = 0
// const medium = 1
// const large = 2

const enum Size {
  // 0, 1, 2 (default) we could also: Small = 's', Medium = 'm'...
  Small,
  Medium,
  Large,
}

let mySize: Size = Size.Medium
console.log(mySize)

// ----------------------------
// FUNCTIONS

function calcTax(income: number, taxYear = 2022): number {
  // numbers in ts can be written with '_' for readability
  if (taxYear < 2022) return income * 1.2
  return income * 1.4
}

calcTax(10_000)

// ----------------------------
// OBJECTS

// nasty syntax
let employee: {
  readonly id: number
  name: string
  retire: (date: Date) => void
} = {
  id: 1,
  name: 'John',
  retire: (date: Date) => {
    console.log(date)
  },
}

// DRY.
// We can use type aliases to avoid repeating the same type
type Employee = {
  readonly id: number
  name: string
  retire: (date: Date) => void
}

let employee2: Employee = {
  id: 1,
  name: 'John',
  retire: (date: Date) => {
    console.log(date)
  },
}

// COMBINING TYPES
// union types
function kgToPounds(weight: number | string): number {
  // narrowing down the type
  if (typeof weight === 'number') return weight * 2.2
  else return parseInt(weight) * 2.2
}

kgToPounds(10)
kgToPounds('10kg')

// intersection types
type Draggable = {
  drag: () => void
}

type Resizable = {
  resize: () => void
}

type UIWidget = Draggable & Resizable

let widget: UIWidget = {
  drag: () => {},
  resize: () => {},
}

// literal types
type Quantity = 10 | 20
let quantity: Quantity = 10

// nullable types
function greet(name: string | null | undefined) {
  if (name) console.log(`Hello ${name.toUpperCase()}`)
  else console.log('Hola!')
}

greet(null)

// while working with nullable or unefinded values, we often need to use null checks
// we can use the optional chaining operator instead

type Customer = {
  birthday?: Date
}
function getCustomer(id: number): Customer | null | undefined {
  return id === 0 ? null : { birthday: new Date() }
}

// optional property access operator (?.) - optional chaining
let customer = getCustomer(0)
console.log(customer?.birthday?.getFullYear())

// optional element access operator (arrays)
// customers?.[0]

// optional call operator (functions)
let log1: any = null
log1?.('a')

let log: any = (message: string) => console.log(message)

// nullish coalescing operator
let speed: number | null = null
let ride = {
  // falsy values: 0, '', null, undefined, false, NaN
  // since 0 is a falsy value but is a number this will fail our expectations
  speed: speed || 30,
  // we could do something like this
  speed1: speed !== null ? speed : 30,
  // or we could use the nullish coalescing operator
  // if value is not null or undefined use it, otherwise use the default value
  speedCorrect: speed ?? 30,
}

// If we know a bit more about the type we can make a type assertion
// (we are telling the compiler that we know better)
// in this case if the element is not an input it won't find the value property and will throw an error

let phone = document.getElementById('phone') as HTMLInputElement
phone.value = '123456789'

// The NEVER type - to represent values that never occur
function reject(message: string) {
  // never
  throw new Error(message)
}

function processEvents(): never {
  while (true) {
    // do something
  }
}

reject('something went wrong')

// processEvents() // inifite loop
// console.log('done') // this will never be reached because the function never returns
