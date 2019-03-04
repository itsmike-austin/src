package main

import "fmt"
import "net"
import "net/url"

func main() {

	s := "postgres://user:pass@host.com:5432/path?k=v#f"

	u,err := url.Parse(s)
	if  err != nil {
		panic(err)
	}

	fmt.Println("FullUrl:    ",u)

	fmt.Println("Scheme:     ",u.Scheme)
	fmt.Println("User:       ",u.User)
	fmt.Println("Username:   ",u.User.Username())
	p,_ := u.User.Password()
	fmt.Println("Password:   ",p)

	fmt.Println("Host:       ",u.Host)
	host,port,_ := net.SplitHostPort(u.Host)
	fmt.Println("SplitHost:  ",host)
	fmt.Println("SplitPort:  ",port)

	fmt.Println("Path:       ",u.Path)
	fmt.Println("Fragment:   ",u.Fragment)

	fmt.Println("RawQuery:   ",u.RawQuery)
	m,_ := url.ParseQuery(u.RawQuery)
	fmt.Println("ParseQuery: ",m)
	fmt.Println("MapOfK:     ",m["k"][0])

}
