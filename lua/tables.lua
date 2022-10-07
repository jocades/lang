-- pairs() returns key-value pairs and is mostly used for associative tables.
-- Key order is unspecified.

-- ipairs() returns index-value pairs and is mostly used for numeric tables.
-- Non numeric keys in an array are ignored, while the index order is deterministic (in numeric order).

local t = {}
t[1] = "a"
t[3] = "b"
t[2] = "c"
t[4] = "d"
t.hello = "world"

for i, v in pairs(t) do
	print(i, v)
end
-- 1   a
-- hello   world
-- 3   b
-- 2   c
-- 4   d
print("")

for i, v in ipairs(t) do
	print(i, v)
end
-- 1   a
-- 2   c
-- 3   b
-- 4   d
print("")

local list = { "a", "b", "c", "d", "e" }

for i, value in ipairs(list) do
	print(i .. " " .. value)
end

print("")

local table = {
	name = "Jordi",
	age = 10,
	isAlive = true,
}

for _, value in pairs(table) do
	print(value)
end
