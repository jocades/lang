.global  my_function
.type    my_function, "function"
.p2align 4

my_function:
	sub  x1, x1, #1
	sub  x2, x0, x1
	cmp  x2, #0
	b.ne my_function
	ret
