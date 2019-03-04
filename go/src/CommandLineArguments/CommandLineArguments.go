package main

import "os"
import "fmt"

func main() {
	argsWithProg    := os.Args
	argsWithoutProg := os.Args[1:]

	arg := os.Args[3]

	fmt.Println("argsWithProg:    ",argsWithProg)
	fmt.Println("argsWithoutProg: ",argsWithoutProg)
	fmt.Println("os.Args[3]:      ",arg)
}
