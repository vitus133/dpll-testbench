package main

// #cgo LDFLAGS: -lmnl lib/ynl.a lib/protos.a
// #cgo CFLAGS: -I include/ -I ../../kernel-root/include/uapi/
// #include "ynl.h"
// #include "dpll-user.h"
import "C"
import (
	"fmt"
	"log"
)

// Note - this doesn't work. Hits segfault on line 26
func main() {
	//var ys *C.struct_ynl_sock
	var dpll_family C.struct_ynl_family
	var yse C.struct_ynl_error

	dpll_family.name = C.CString("dpll")
	ys := C.ynl_sock_create(&dpll_family, &yse)
	if yse.code != 0 {
		log.Fatal("can't allocate ynl socket", yse.msg)
	}
	var devs *C.struct_dpll_device_get_list
	devs = C.dpll_device_get_dump(ys)
	ls := devs.obj._present
	fmt.Println(ls)
}
