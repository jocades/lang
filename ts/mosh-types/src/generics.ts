// GENERICS: passing types as parameters to a class, interface or function

// ----------------------------
// GENERIC CLASSES

class KeyValuePair<K, V> {
  constructor(public key: K, public value: V) {}
}

// the compiler will infer the types, sometimes we need to specify them: KeyValuePair<string, string>
let pair = new KeyValuePair('1', 'Apple')
pair.key.endsWith('x')

// ----------------------------
// GENERIC FUNCTIONS

function wrapInArray<T>(value: T) {
  return [value]
}

let nums = wrapInArray(10)
let strs = wrapInArray('Hello')

// or in a method
class ArrayUtils {
  static wrapInArray<T>(value: T) {
    return [value]
  }
}

let nums2 = ArrayUtils.wrapInArray(10)

// ----------------------------
// GENERIC INTERFACES

// mysite.com/users
// mysite.com/products

interface Result<T> {
  data: T | undefined
  error: string | undefined
}

function fetch<T>(url: string): Result<T> {
  console.log(url)
  return { data: undefined, error: undefined }
}

interface User {
  id: number
  name: string
}

let res = fetch<User>('url.com/users')
res.data?.name

// ----------------------------
// GENERIC CONSTRAINTS
// we can use generic constraints to limit the types that can be used with a generic type

function echo<T extends number | string>(value: T): T {
  return value
}

echo('Hello')

// ----------------------------
// EXTENDING GENERIC CLASSES

interface Product {
  name: string
  price: number
}

// passing the generic type as a parameter through the class hierarchy (multiple levels)
class Store<T> {
  private _objects: T[] = []

  add(obj: T) {
    this._objects.push(obj)
  }
  // keyof operator: to get the keys of an object
  // T is Product, so keyof T => 'name' | 'price'
  find(property: keyof T, value: unknown): T | undefined {
    return this._objects.find((obj) => obj[property] === value)
  }

  get objects(): T[] {
    return this._objects
  }
}

let store1 = new Store<Product>()
store1.add({ name: 'Apple', price: 10 })
store1.find('name', 'Apple')
store1.find('price', 10)
// store1.find('non-existing-property', 10) // to fix this we can use keyof

class CompStore<T> extends Store<T> {
  compress() {}
}

let store = new CompStore<Product>()
store.add({ name: 'Apple', price: 10 })

// restricting the generic type parameter
class SearchStore<T extends { name: string }> extends Store<T> {
  findOne(name: string): T | undefined {
    return this.objects.find((obj) => obj.name === name)
  }
}

// fixing / terminating the generic type parameter
class ProductStore extends Store<Product> {
  filterByCategory(category: string): Product[] {
    console.log(category)
    return []
  }
}

// ----------------------------
// TYPE MAPPING
// we can use the type mapping to map the properties of a type to another type

interface Product1 {
  name: string
  price: number
}

type ReadOnlyProduct = {
  readonly [K in keyof Product1]: Product1[K] // Product1['name'] = string
}

// make it reuasable
type ReadOnly<T> = {
  readonly [K in keyof T]: T[K]
}

// we can make it optional
type Optional<T> = {
  [K in keyof T]?: T[K]
}

type PartialProduct = Optional<Product1>

// TS comes with some built-in type mappings like Partial<T>, Required<T>, Readonly<T>, etc.
// i.e: Parial<T>
interface Product2 {
  name: string
  price: number
}

function updateProduct(product: Product2, fieldsToUpdate: Partial<Product2>) {
  return { ...product, ...fieldsToUpdate }
}

// we can make it nullable
type Nullable<T> = {
  [K in keyof T]: T[K] | null
}
