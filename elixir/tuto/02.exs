# anonymous functions
add = fn a, b -> a + b end
result = add.(1, 2)
IO.puts result

# closures
double = fn a -> add.(a, a) end
IO.puts double.(2)

# clauses and guards
f = fn
  x, y when x > 0 -> x + y
  x, y -> x * y
end
IO.puts f.(1, 3)
IO.puts f.(-1, 3)

# capture operator
str_len = &String.length/1
IO.puts str_len.("hello")

sub = &-/2 # this is actually crazy (assigning the '-' operator)
IO.puts sub.(10, 2)

wow = &(&1 + 1)
IO.puts wow.(1)

wtf = &"Good #{&1}"
IO.puts wtf.("morning")

# keyword lists
ls = [name: "John", age: 23]
IO.inspect(ls)

IO.puts ls[:name]
IO.puts Keyword.get(ls, :name)

# map
map = %{name: "John", age: 23}
IO.inspect(map)

IO.puts map.name
IO.puts map[:name]
IO.puts Map.get(map, :name)

# pattern matching a map, it matches if any key is present
%{age: age} = map
IO.puts age

# updating, raises if the key is not present
new_map = %{map | name: "Jane"}
IO.inspect(new_map)

# nested data structures (keyword list with maps and lists)
users = [
  john: %{name: "John", age: 27, languages: ["Erlang", "Ruby", "Elixir"]},
  mary: %{name: "Mary", age: 29, languages: ["Elixir", "F#", "Clojure"]}
]

age = users[:john].age

# updating (remeber inmutability, always returns a new value instead of modifying the original)
users = put_in users[:john].age, 31
IO.puts age
IO.puts users[:john].age

users = update_in users[:mary].languages, fn languages -> List.delete languages, "Clojure" end
IO.inspect users[:mary].languages
