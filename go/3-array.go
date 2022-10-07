/* Different ways to initialiaze an array in Go */
package main

import (
	"fmt"
)

// Go arrays only allow the storage of only one data type.

func main() {
	var seasons [4]string // String array of length 4

	seasons[0] = "Spring" // Adding elements individually
	seasons[1] = "Summer"
	seasons[2] = "Autumn"
	seasons[3] = "Winter"

	// Shorthand declarations
	myseasons := [4]string{
		"Spring",
		"Summer",
		"Autumn",
		"Winter"}

	fmt.Println(seasons, myseasons)

	// Compiler determines the length of array

	grades := [...]string{
		"A+", "A", "A-",
		"B+", "B", "B-",
		"C+", "C", "C-",
		"D+", "D", "D-",
		"F"}
	fmt.Println(grades, len(grades))
}
