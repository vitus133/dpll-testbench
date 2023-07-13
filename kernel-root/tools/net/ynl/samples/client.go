package main

import (
	"fmt"
	"log"
	"net"
)

const (
	protocol = "unixpacket"
	sockAddr = "/tmp/us_xfr"
)

func main() {
	conn, err := net.Dial(protocol, sockAddr)
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	buf := make([]byte, 1024)
	for {
		_, err = conn.Read(buf)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(string(buf))
	}
}
