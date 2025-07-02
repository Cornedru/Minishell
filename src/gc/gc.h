// src/gc/gc.h
#ifndef GC_H
#define GC_H

#include <stddef.h>

void *gc_malloc(size_t size);
void gc_free_all(void);
void gc_addback(void *ptr);
void gc_init(void);

#endif
