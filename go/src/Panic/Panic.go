package main

import "os"
import "fmt"

func main() {
	panic("a problem")

	fmt.Println("did't panic")

	_,err := os.Create("/tmp/file")
	if err != nil {
		panic(err)
	}
}
