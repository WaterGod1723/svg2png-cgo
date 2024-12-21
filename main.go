package main

/*
#cgo pkg-config: vips
#cgo LDFLAGS: -L. -ltest
#include <stdlib.h>
#include "test.h"
*/
import "C"
import (
	"fmt"
	"os"
	"unsafe"
)

//export freeMemory
func freeMemory(ptr unsafe.Pointer) {
	C.free(ptr)
}

func SvgToPngBinary(inputFile string) ([]byte, error) {
	cInputFile := C.CString(inputFile)
	defer C.free(unsafe.Pointer(cInputFile))

	var outputData *C.uchar
	var outputSize C.size_t

	result := C.svg_to_png_binary(cInputFile, &outputData, &outputSize)
	if result != 0 {
		return nil, fmt.Errorf("SVG to PNG conversion failed")
	}

	// Convert C byte array to Go byte slice
	goData := C.GoBytes(unsafe.Pointer(outputData), C.int(outputSize))

	// Free the memory allocated by the C function
	freeMemory(unsafe.Pointer(outputData))

	return goData, nil
}

func main() {
	inputFile := "input.svg"
	pngData, err := SvgToPngBinary(inputFile)
	if err != nil {
		fmt.Println(err)
		return
	}

	// Save the PNG data to a file for verification
	outputFile := "output.png"
	err = os.WriteFile(outputFile, pngData, 0644)
	if err != nil {
		fmt.Println("Failed to write PNG file:", err)
		return
	}

	fmt.Println("Conversion successful, PNG saved as", outputFile)
}
