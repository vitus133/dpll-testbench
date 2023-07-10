package main

// #cgo LDFLAGS: -lmnl lib/ynl.a lib/protos.a
// #cgo CFLAGS: -I include/ -I ../../kernel-root/include/uapi/
// #include "ynl.h"
// #include "dpll-user.h"
import "C"

func main() {
	var ys *C.struct_ynl_sock

	ys = C.ynl_sock_create(&C.ynl_dpll_family, C.NULL)
}
