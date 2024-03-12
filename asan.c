
#include <sanitizer/asan_interface.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __ASAN_H__
struct vasan_saved_buffer {
    void* buffer;
    size_t size;
};
typedef struct vasan_saved_buffer vasan_saved_buffer_t;


size_t vasan_buffer_size(void* buffer);
char* vasan_buffer_hex_string(void* buffer);
void vasan_free_saved_buffer(vasan_saved_buffer_t* saved_buffer);
vasan_saved_buffer_t* vasan_save_buffer_copy(void *buffer);

#define __ASAN_H__
#endif

size_t vasan_buffer_size(void* buffer) {
    char* name = NULL;
    size_t name_size = 0;
    void* region_address = NULL;
    size_t region_size = 0;

    const void* alloc_info = __asan_locate_address(buffer, name, name_size, &region_address, &region_size);
    if (alloc_info) {
        return region_size;
    }

    return -1;
}

char* vasan_buffer_hex_string(void* buffer) {
    size_t size = vasan_buffer_size(buffer);
    if (size == -1) {
        return NULL;
    }

    const unsigned char* bytes = (const unsigned char*)buffer;
    char* hex_string = (char*)malloc((size * 2) + 1);
    if (hex_string == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        snprintf(hex_string + (i * 2), 3, "%02x", bytes[i]);
    }
    hex_string[size * 2] = '\0';

    return hex_string;
}

void vasan_free_saved_buffer(vasan_saved_buffer_t* saved_buffer) {
    free(saved_buffer->buffer);
    free(saved_buffer);
}

vasan_saved_buffer_t* vasan_save_buffer_copy(void *buffer) {
    size_t size = vasan_buffer_size(buffer);
    if (size == -1) {
        return NULL;
    }

    void* copy = malloc(size);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, buffer, size);

    vasan_saved_buffer_t *saved_buffer = (vasan_saved_buffer_t*)malloc(sizeof(vasan_saved_buffer_t));
    if (saved_buffer == NULL) {
        return NULL;
    }

    saved_buffer->buffer = copy;
    saved_buffer->size = size;

    return saved_buffer;
}
