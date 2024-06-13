# enumerables and streams
# enum cheatsheet: https://hexdocs.pm/elixir/enum-cheat.html

# ranges are also enumerables

IO.inspect Enum.reduce 1..3, 0, &+/2
IO.inspect Enum.map 1..3, fn x -> x * 2 end

# eager vs lazy

# all the functions in the Enum module are eager. 
odd? = fn x -> rem(x, 2) != 0 end

IO.inspect Enum.filter 1..3, odd?

# this means that when performing multiple operations with Enum, each operation
# is going to generate an intermediate list until we reach the result:

IO.puts 1..100_000 |> Enum.map(&(&1 * 3)) |> Enum.filter(odd?) |> Enum.sum() # => 7500000000

# This first operation will now create and return a list with 100_000 items. 
# Then we keep all odd elements from the list, generating a new list, now with
# 50_000 items, and then we sum all entries.

# same without the pipe operator 
IO.puts Enum.sum(Enum.filter(Enum.map(1..100_000, &(&1 * 3)), odd?))

# streams are lazy, composable enumerables
# Instead of generating intermediate lists, streams build a series of computations
# that are invoked only when we pass the underlying stream to the Enum module.
