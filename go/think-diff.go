package main

import (
	"fmt"
	"time"
)

type Book struct {
    author string
    title string
    pages int
    saved bool
    savedAt time.Time
}

// 1. Read data
func saveBook(b *Book) {
    b.saved = true
    b.savedAt = time.Now()
}

// syntactic sugar
// func (b *Book) save() {
//     b.saved = true
//     b.savedAt = time.Now()
// }




// 2. Write data

func main() {
    b := Book{
        title: "Think different",
        author: "Steve Jobs",
        pages: 300,
    }

    saveBook(&b)

    // b.save()

    fmt.Println(b)
}


