// test.h
#ifndef TEST_H
#define TEST_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int svg_to_png_binary(const char* input_file, unsigned char** output_data, size_t* output_size);

#ifdef __cplusplus
}
#endif

#endif // TEST_H