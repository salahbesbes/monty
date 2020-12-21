#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H


#include <stdio.h>


void *create_obj(size_t size);
void destroy_obj(void *ptr);
void *copy_obj(size_t size, void *ptr);
void clear_gc(void);
void *save_at_first(size_t size);
#endif
