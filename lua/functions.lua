-- Defined function
local function square(h)
	local l = 5
	return h * l
end

-- Anonymous function assigned to variable
local fun = function(txt, n)
	print(txt .. n)
end

-- Call function
local funcReturn = square(2)
print(funcReturn)

fun("hello", 1)
