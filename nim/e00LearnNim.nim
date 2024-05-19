# Single-line commnets start with a #

#[
    This is a miulti-line comment.
    It starts with a #[ and ends with a ]#
]#


# Declare (and assign) variables, with or without type
var 
    letter: char = 'n'
    lang = "N" & "im"
    nLength: int = len(lang)
    boat: float
    truth: bool = false


# Use 'let' to declare and bind variables *once*.
let
    legs = 400 # legs is now immutable
    arms = 2_000 # _ is ignored in numbers
    aboutPi = 3.14


# Constants are computed at compile time. This provides performance and is useful in compile time expressinos.
const
    debug = true
    compileBadCode = false


when compileBadCode:              # `when` is a compile time `if`
    legs = legs + 1               # This error will never be compiled.
    const input = readline(stdin) # Const values must be known at compile time. 

discard 1 > 2 # Note: The compiler will complain if the result of an expression
              # is unused. `discard` bypasses this.


#
# Data Structures
#

# Tuples
var
    child: tuple[name: string, age: int] # Tuples have *both* field names *and* order.
    today: tuple[sun: string, temp: float]

child = (name: "Jordi", age: 2) # Assing all at once with literal '()'
today.sun = "Overcast"          # or individual fields
today.temp = 70.1

# Sequences
var
    drinks: seq[string]

drinks = @["Water", "Juice", "Chocolate"] # @[V1,...,Vn] is a sequence literal

drinks.add("Milk")

if "Milk" in drinks:
    echo "We have Milk and ", drinks.len - 1, " other drinks."
