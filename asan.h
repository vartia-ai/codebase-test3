
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
