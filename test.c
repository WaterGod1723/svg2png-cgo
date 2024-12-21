#include <vips/vips.h>
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int svg_to_png_binary(const char *input_file, unsigned char **output_data, size_t *output_size) {
    if (!input_file || !output_data || !output_size) {
        fprintf(stderr, "Invalid input or output parameters\n");
        return 1;
    }

    vips_init(NULL);

    VipsImage *in_image = NULL;
    VipsImage *out_image = NULL;

    // Load the SVG file
    int result = vips_svgload(input_file, &in_image, NULL);
    if (result != 0) {
        fprintf(stderr, "VIPS SVG load failed: %s\n", vips_error_buffer());
        vips_shutdown();
        return 1;
    }

    // Get the dimensions of the loaded image
    int width = in_image->Xsize;
    int height = in_image->Ysize;

    // Calculate the new dimensions with minimum size and padding
    int min_size = 64;
    int min_padding = 4;
    int new_width = width + 2 * min_padding;
    int new_height = height + 2 * min_padding;

    if (new_width < min_size) {
        new_width = min_size;
    }
    if (new_height < min_size) {
        new_height = min_size;
    }

    // Embed the image with padding
    result = vips_embed(in_image, &out_image, min_padding, min_padding, new_width, new_height, "extend", VIPS_EXTEND_WHITE, NULL);
    if (result != 0) {
        fprintf(stderr, "VIPS embed failed: %s\n", vips_error_buffer());
        g_object_unref(in_image);
        vips_shutdown();
        return 1;
    }

    // Write the output image to a memory buffer
    size_t data_size;
    void *data;
    result = vips_image_write_to_buffer(out_image, ".png", &data, &data_size, NULL);
    if (result != 0) {
        fprintf(stderr, "VIPS image write to buffer failed: %s\n", vips_error_buffer());
        g_object_unref(in_image);
        g_object_unref(out_image);
        vips_shutdown();
        return 1;
    }

    // Assign the output data and size
    *output_data = (unsigned char *)data;
    *output_size = data_size;

    // Use g_object_unref to release the image resources
    g_object_unref(in_image);
    g_object_unref(out_image);
    vips_shutdown();
    return 0;
}