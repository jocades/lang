-- Different types
local x = 10 --number
local name = "john doe" --string
local isAlive = false -- boolean
local a = nil --no value or invalid value

-- Dictionary / Table
local table = {
	name = "Jordi",
	age = "20",
	isAlive = true,
}

-- Access table
print(table["first_key"])
print(table.first_key)

-- List / Array
local list = { "a", "b,", "c", "d", "e" } -- Under the hood it is still an associative array / dictionary in python
