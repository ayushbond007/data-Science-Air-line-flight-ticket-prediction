#ifndef SAMPLE_H_INCLUDED
#define SAMPLE_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
typedef struct node {
	struct node *next;
	int size;
	bool free;
	void *ptr;
} Node;

   Node *head;
static uintptr_t fsbrk;
static int count;
static uintptr_t fsize;
int pagesize_multiple (int requiredsize, int pageSize);
void *ptrmodeight (void *ptr);
void memdiv (Node * crr, int size);
void *malloc (size_t size);
void * calloc (size_t no_of_element, size_t size);
void *realloc (void *ptr, size_t newsize);
void free (void *ptr);
int debug (int a);
#endif // SAMPLE_H_INCLUDED
