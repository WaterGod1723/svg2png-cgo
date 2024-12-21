重点:
主要使用的mingw64所以所有的包都应该下载mingw64的版本，包括gcc、vips、glib等

main.go中需要正确导入vips和libtest.a

/*
#cgo pkg-config: vips
#cgo LDFLAGS: -L. -ltest
#include <stdlib.h>
#include "test.h"
*/

1、编译gcc -c -Wall test.c $(pkg-config --cflags vips) -o test.o
2、链接ar rcs libtest.a test.o
3、在go中调用