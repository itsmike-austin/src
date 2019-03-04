package main

import "fmt"

func vals() (int,int) {
	return 3,7
}

func main() {
	a,b := vals()
	fmt.Println("a,b = vals(): a: ",a)
	fmt.Println("a,b = vals(): b: ",b)

	_,c := vals()
	fmt.Println("_,c = vals(): c: ",c);
}

	
