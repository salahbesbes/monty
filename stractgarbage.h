
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

int delete_garbage_at_index(gc_t **head, unsigned int index);
size_t gc_len(const gc_t *h);
gc_t *add_garbage(gc_t **head, void *garbage);
gc_t *add_garbage_end(gc_t **head, void *garbage);
void free_gc(gc_t *head);
gc_t *insert_garbage_at_index(gc_t **h, unsigned int idx, void *garbage);
size_t print_gc(const gc_t *h);
int delete_garbage_at_index(gc_t **head, unsigned int index);
gc_t *add_garbage_end(gc_t **head, void *garbage);
gc_t *get_garbage_at_index(gc_t *head, unsigned int index);



#endif
