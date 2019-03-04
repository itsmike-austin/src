package main

import "fmt"
import "os"

type point struct {
	x,y int
}

func main() {
	p := point{1,2}

	// Print out the struct data
	fmt.Printf("%v\n",p)

	// Print out the struct data with struct field names
	fmt.Printf("%+v\n",p)

	// Print a Go syntax representation
	fmt.Printf("%#v\n",p)

	// Print the type of the value
	fmt.Printf("%T\n",p)

	// Output a boolean
	fmt.Printf("%t\n",true);

	// Output a generic integer
	fmt.Printf("%d\n",123)

	// Output a binary representation
	fmt.Printf("%b\n",14)

	// Print the character representation of a number
	fmt.Printf("%c\n",33);

	// Print the hexadecimal representation of a number
	fmt.Printf("0x%x\n",456)

	// Format scientific notation variants
	fmt.Printf("%e\n",123400000.0)
	fmt.Printf("%E\n",123400000.0)

	// Basic string print
	fmt.Printf("%s\n","\"string\"")

	// For double quote string use %q
	fmt.Printf("%q\n","\"string\"")

	// Hex reprentation of odd things
	fmt.Printf("%x\n","hex this")

	// Print a point
	fmt.Printf("%p\n",&p)

	// Numeric with with and precision control
	fmt.Printf("|%6d|%6d|\n",12,345)
	fmt.Printf("|%6.2f|%6.2f|\n",1.2,3.45)

	// To left justify the number
	fmt.Printf("|%-6.2f|%-6.2f|\n",1.2,3.45)

	// Control the string width and alignment on these
	fmt.Printf("|%6s|%6s|\n","foo","b")
	fmt.Printf("|%-6s|%-6s|\n","foo","b")

	s :=fmt.Sprintf("a %s","string")
	fmt.Println(s)

	fmt.Fprintf(os.Stderr,"an %s\n","error");
}
