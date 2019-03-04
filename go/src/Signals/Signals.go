package main

import "fmt"
import "os"
import "os/signal"
import "syscall"

func main() {

	sigs := make(chan os.Signal,1)
	done := make(chan bool,1)

	signal.Notify(sigs,syscall.SIGINT,syscall.SIGTERM)

	go func() {
		sigs := <-sigs
		fmt.Println()
		fmt.Println(sigs)
		done <-true
	}()

	fmt.Println("awaiting signal")
	<-done
	fmt.Println("exiting")
}
