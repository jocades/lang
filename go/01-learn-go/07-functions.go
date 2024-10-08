package main

import (
	"errors"
	"fmt"
	"math"
)

func main() {
	result := sum(2, 3)
	fmt.Println(result)

	result2, err := sqrt(-1)
	if err != nil {
		fmt.Println(err)
        // panic(err)
	} else {
		fmt.Println(result2)
	}
}

func sum(x, y int) int {
	return x + y
}

func sqrt(x float64) (float64, error) {
	if x < 0 {
		return 0, errors.New("undefined for negative numbers")
	}

	return math.Sqrt(x), nil
}
