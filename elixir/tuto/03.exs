# modules and functions

defmodule Math do
  # public
  def sum(a, b) do
    a + b
  end

  # private
  defp do_sum(a, b) do
    a + b
  end

  # multiple clauses
  # def zero?(0) do
  #   true
  # end

  # def zero?(x) when is_integer(x) do
  #   false
  # end

  # a more concise way using keyword lists
  def zero?(0), do: true
  def zero?(x) when is_integer(x), do: false
end

IO.puts Math.sum 1, 2
# IO.puts Math.do_sum 1, 2

IO.puts Math.zero?(0)         #=> true
IO.puts Math.zero?(1)         #=> false
# IO.puts Math.zero?([1, 2, 3]) #=> ** (FunctionClauseError)
# IO.puts Math.zero?(0.0)       #=> ** (FunctionClauseError)


defmodule Concat do
  # def join(a, b, sep \\ " ") do
  #   a <> sep <> b
  # end

  # If a function with default values has multiple clauses, it is required to
  # create a function head (a function definition without a body) for declaring defaults:
  def join(a, b \\ nil, sep \\ " ")

  def join(a, b, _sep) when is_nil(b) do
    a
  end

  def join(a, b, sep) do
    a <> sep <> b
  end
end


IO.puts Concat.join("Hello", "world")      #=> Hello world
IO.puts Concat.join("Hello", "world", "_") #=> Hello_world

