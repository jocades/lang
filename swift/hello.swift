print("Hello, World!")

let apples = 3
let summary = "I have \(apples) apples."

var fruits = ["strawberries", "limes", "tangerines"]
fruits[1] = "grapes"
fruits.append("blueberries")

var occupations = [
  "Malcolm": "Captain",
  "Kaylee": "Mechanic"
]
occupations["Jayne"] = "Public Relations"
print(occupations)

for (k, v) in occupations {
  // print("\(pair.key) -> \(pair.value)")
  print("\(k) -> \(v)")
}

let optionalName: String? = "Jordi"
print(optionalName == nil)
var greeting = "Hello!"
if let name = optionalName {
  greeting = "Hello, \(name)"
}
print(greeting)

func greet(person: String, day: String) -> String {
  return "Hello \(person), today is \(day)."
}

greet(person: "Bob", day: "Tuesday")

func bye(_person: String) {
  print("Goodbye \(_person)")
}

bye("Jordi")
