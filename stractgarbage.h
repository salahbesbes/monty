
#ifndef STRACT_GARBAGE_H
#define STRACT_GARBAGE_H
#include "stdio.h"


/**
 * struct garbageCollector_s - collect garbage and free them
 * @garbage: garbage to be freed
 * @next: next node
 * @prev: prev node
 */
typedef struct garbageCollector_s
{
	void *garbage;
	struct garbageCollector_s *next;
	struct garbageCollector_s *prev;
} gc_t;

size_t gc_len(const gc_t *h);
gc_t *add_garbage(gc_t **head, void *garbage);
gc_t *add_garbage_end(gc_t **head, void *garbage);
void free_gc(gc_t *head);
gc_t *get_garbage_at_index(gc_t *head, unsigned int index);







void destroy_all(void);
void *copy_obj(size_t size, void *ptr);
void *create_obj(size_t size);
void *save_at_first(size_t size);
void destroy_obj(void *ptr);





#endif
