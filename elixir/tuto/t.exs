defmodule What do
  def add(a, b) when b > 0 do
    a * b
  end

  def add a, b do
    a + b
  end
end

IO.puts What.add(2,2)
IO.puts What.add(4,-2)
