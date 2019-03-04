package main

import "encoding/json"
import "fmt"
import "os"

// Two structs to demonstrateencoding and decoding of custom types

type response1 struct {
	Page   int
	Fruits []string
}

type response2 struct {
	Page   int      `json:"page"`
	Fruits []string `json:"fruits"`
}

func main() {

	// Encode some basic JSON types

	bolB,_ := json.Marshal(true)
	fmt.Println(string(bolB))

	intB,_ := json.Marshal(1)
	fmt.Println(string(intB))

	fltB,_ := json.Marshal(2.34)
	fmt.Println(string(fltB))

	strB,_ := json.Marshal("gopher")
	fmt.Println(string(strB))

	// Encode some examples of slices and maps

	slcD   := []string{"apple","peach","pear"}
	slcB,_ := json.Marshal(slcD)
	fmt.Println(string(slcB))

	mapD   := map[string]int{"apple": 5,"lettuce": 7}
	mapB,_ := json.Marshal(mapD)
	fmt.Println(string(mapB))

	// Automatically encode custom data types. Only include exported
	// fields in the encoded output and use those names as JSON keys

	res1D := &response1{
		Page: 1,
		Fruits: []string{"apple","peach","pear"}}
	res1B,_ := json.Marshal(res1D)
	fmt.Println(string(res1B))

	// Use tags on struct field declarations to customize JSON key names
	// Check the definitions of response2 to see an example

	res2D := &response2{
		Page: 1,
		Fruits: []string{"apple","peach","pear"}}
	res2B,_ := json.Marshal(res2D)
	fmt.Println(string(res2B))

	// Decode JSON into Go values from this generic data structure

	byt := []byte(`{"num":6.3,"strs":["a","b"]}`)

	// Provide a variable where JSON can put the decoded data
	// This map[string]interface{} will hold a map of strings to
	// arbitrary data types.

	var dat map[string]interface{}

	// Decode the data

	if err := json.Unmarshal(byt,&dat); err != nil {
		panic(err)
	}

	fmt.Println(dat)

	// You need to cast the data to the appropriate type in order to
	// decode them. This example casts the values to an expected float64

	num := dat["num"].(float64)
	fmt.Println(num)

	// Accessing nested data requires a series of casts

	strs := dat["strs"].([]interface{})
	str1 := strs[0].(string)
	fmt.Println(str1)

	// We can decode JSON into custom data types. This has the advantage
	// of adding type-safety to our programs and eliminating the
	// need for type assertions when accessing decoded data

	str := `{"page": 1, "fruits": ["apple","peach"]}`
	res := response2{}
	json.Unmarshal([]byte(str),&res)
	fmt.Println(res)
	fmt.Println(res.Fruits[0])

	// JSON encoded strings can be directly decoded to streams
	// like os.Writers such as os.Stdout

	enc := json.NewEncoder(os.Stdout)
	d := map[string]int{"apple": 5,"lettuce": 7}
	enc.Encode(d)
}
