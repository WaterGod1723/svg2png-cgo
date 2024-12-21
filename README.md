##以下均为 Windows 环境配置

c 环境配置（go 环境略过）:

- 安装 MSYS2（网上有教程）主要用于编译 C 代码，C 的三方库管理。
- 安装使用 MSYS2 中的 **pacman（c 的包管理工具，感觉比 vcpkg 的包要齐全）** 安装 gcc、vips、glib、pkg-config 等工具
- 配置 **pkg-config（c 的包索引工具）** 环境变量，注意 MSYS2 中可能有多个 pkg-config，但 windows 环境用 mingw64 的最多，所以将 MSYS2 安装目录下的 mingw64 下的 pkg-config 路径添加到系统环境变量中，如：D:\program\MSYS2\mingw64\bin，一般**安装所有包时都需要带有 mingw64 前缀的**

**重点:**
msys2 环境下，主要使用的 mingw64 所以所有的包都应该下载 mingw64 的版本，包括 gcc、vips、glib 等

main.go 中需要正确导入 vips 和 libtest.a

/_
#cgo pkg-config: vips
#cgo LDFLAGS: -L. -ltest
#include <stdlib.h>
#include "test.h"
_/

1、编译 gcc -c -Wall test.c $(pkg-config --cflags vips) -o test.o
2、链接 ar rcs libtest.a test.o
3、在 go 中调用
