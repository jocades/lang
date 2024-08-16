defmodule User do
  defstruct name: "John", age: 27
end

# protocols

# defmodule Utility do
#   def type(value) when is_binary(value), do: "string"
#   def type(value) when is_integer(value), do: "integer"
#   # ... other implementations ...
# end

# Not extensible at all, make use of protocols to allow for extensibility

defprotocol Utility do
  @spec type(t) :: String.t()
  def type(value)
end

defimpl Utility, for: BitString do
  def type(_value), do: "string"
end

defimpl Utility, for: Integer do
  def type(_value), do: "integer"
end

# two idioms for checking how many items there are in a data structure: length 
# and size. length means the information must be computed.

defprotocol Size do
  @doc "Calculates the size (and not the lenght!) of a data structure"
  def size(data)
end

defimpl Size, for: BitString do
  def size(string), do: byte_size(string)
end

defimpl Size, for: Map do
  def size(map), do: map_size(map)
end

defimpl Size, for: Tuple do
  def size(tuple), do: tuple_size(tuple)
end

IO.puts(Size.size("foo"))
IO.puts(Size.size({:ok, "hello"}))
IO.puts(Size.size(%{key: "value"}))
