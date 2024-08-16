# A comprehension is made of three parts: generators, filters, and collectables.

for n <- [1, 2, 3, 4], do: n * n

# generators and filters

# `n <- [1, 2, 3, 4]` is the generator
# any enumerable can be passed on the right-hand side of the generator expression:
for n <- 1..4, do: n * n

# pattern matching
values = [good: 1, good: 2, bad: 3, good: 4]
for {:good, n} <- values, do: n * n

# filtering
for n <- 0..5, rem(n, 3) == 0, do: n * n

# bitstring generators
pixels = <<213, 45, 132, 64, 76, 32, 76, 0, 0, 234, 32, 15>>
for <<r::8, g::8, b::8 <- pixels>>, do: {r, g, b}
