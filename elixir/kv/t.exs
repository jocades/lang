defmodule What do
 #  testing guard expressions
 def what_is(x) when x < 0 do
   IO.puts "It's negative"
 end

 # can i use my own fn as a guard?
 # def is_even?(x) do
 #   rem(x, 2) == 0
 # end
 # not possible is has to be defined as a macro
 
 defguard is_even?(x) when rem(x, 2) == 0

 def what_is(x) when is_even?(x) do
   IO.puts "It's even"
 end
end

What.what_is(2)
What.what_is(-2)
