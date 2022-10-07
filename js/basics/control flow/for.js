// for (<initial expression; condition; increment expression>) {statement}
for (let i = 0; i < 5; i++) {
  if (i % 2 !== 0) console.log(i)
}

// for..in
// used to iterate over objects(dictionries) or arrays but for arrys it's better to use a for..of loop
const person = {
  name: "Jordi",
  age: 25,
} // dictionary in python, object in js

// similiar to python just diff syntax
for (let key in person) console.log(key, person[key])

const colors = ["red", "blue", "green"]
// for..in works only with indexes in arrays
for (let index in colors) console.log(index, colors[index])

// for..of
// better way to iterate over an arary since it iterates over the value not the index
for (let color of colors) console.log(color)
