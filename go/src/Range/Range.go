package main

import "fmt"

func main() {

	nums := []int{2,3,4}

	fmt.Println("nums: ",nums)

	for joe := range nums {
		fmt.Println("Slice item ",joe," is ",nums[joe])
	}
	for _,bob := range nums {
		fmt.Println("Slice bob ", bob)
	}

	sum := 0

	for _,num := range nums {
		sum += num;
	}
	fmt.Println("sum of nums: ",sum)

	for i,num := range nums {
		if num == 3 {
			fmt.Println("index: ",i)
		}
	}

	kvs := map[string]string{"a":"apple", "b":"banana"}
	for k,v := range kvs {
		fmt.Println("key: ", k)
		fmt.Println("val: ", v)
		fmt.Printf("or %s -> %s\n",k,v)
	}

	for k := range kvs {
		fmt.Println("key: ", k)
	}

	fmt.Println("range of string go is: ")
	for i,c := range "go" {
		fmt.Println(i,c)
		fmt.Printf("or %d -> %d\n",i,c)
	}
}
