
#ifndef __ASAN_H__

size_t vasan_buffer_size(void* buffer);
char* vasan_buffer_hex_string(void* buffer);
void vasan_free_saved_buffer(void* saved_buffer);
void* vasan_save_buffer_copy(void *buffer);

#define __ASAN_H__
#endif
