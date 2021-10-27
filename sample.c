#include "sample.h"


int pagesize_multiple (int requiredsize, int pageSize){ 
    int i = 1;
    int finalmem= pageSize;

  while (finalmem < requiredsize) finalmem = pageSize * ++i;	     //this condition violate at 4096< required size//
  return finalmem;
}

void *ptrmodeight (void *ptr){
  while ((uintptr_t) ptr % 8 != 0)ptr++;
    return ptr;
}

void memdiv (Node * crr, int size){
  int remainingSize = crr->size - size - sizeof (Node);	//calculating the above next free area excluding the header//
  if (remainingSize > 8){				                                 //minimum size we need is 8 for holding 2 integer atleast//
      Node *new = (Node *) (crr->ptr + size);	    //new pointer will point to previous header + size or start of new herder //     
      new->next = crr->next;	                    //new header next will point to null//
      new->size = remainingSize;	                       //above free area//
      new->free = true;		                       // true says atea is still free  for allocation//
      new->ptr = ptrmodeight (crr->ptr + size + sizeof (Node));	// rounding of tyhe pointer//
      count++;
      printf("\n%d",count);
      fsize= (uintptr_t )new->ptr;
      crr->next = new;		                       //previous header will point to start ofnew header//
      crr->size = size;		                       //previous header keep track the size allocated by malloc//
    }
}


void free (void *ptr){
  Node *crr = head;

  count--;
  printf("\nabcdefg%d",count);
 
  while (crr != NULL){
      if (crr->ptr == ptr){
	  crr->free = true;
	  return;
	}
	 crr = crr->next;
	 fsize= (uintptr_t )crr;
	 
    }
      return;
}


void *malloc (size_t size){				                               //call malloc with size required//
  Node *crr = head;		                            //cnt value is zero because memeory allocation not one now//
  Node *prev = NULL;
  int pageSize = sysconf (_SC_PAGESIZE);	//pagesize =4096bytes//
  int totalSize = size + sizeof (Node);

  while (crr != NULL)
    {				         // first time call malloc this condition fail,condition only true when we call malloc for the second time//
      if (crr->free)
	{
	  if (crr->size >= size)
	    {
	      if (crr->size > size) memdiv (crr, size);
	     crr->free = false;
          return crr->ptr;
	    }
	}

      prev = crr;
      crr = crr->next;
    }				                     //loc will get 4096 if page size > total size//
                                           //loc will get value in multiple of page size when page size < total size//
  int loc = pagesize_multiple (totalSize, pageSize);
  void *ptr = sbrk (loc);//sbrk(loc) will increment program break by loc but return pointer to previous//
        fsbrk = (uintptr_t ) ptr;                           //program break i.e before incrementing the programe break// 
    printf("fsbrk\n%lu",fsbrk);
    if (ptr != (void *) -1)
    {				                          //(void *)-1  typically refer to 0xff....ffff or the area occupied by kernel and not allowed//
                                              //by user program and more over to handel the error//
      crr = (Node *) ptr;
                                                    //printf ("first ptr= %lu\n", ptr);//
      crr->next = NULL;
      crr->free = false;
      crr->size = loc - sizeof (Node);
       crr->ptr = ptrmodeight (ptr + sizeof (Node));
       if (pageSize > totalSize) memdiv (crr, size);
       else count++;
      if (head == NULL)head = crr;
      else prev->next = crr;

      return crr->ptr;  //returning the memory address where we have to write the data //
    }

  errno = ENOMEM;
  return NULL;
}

void * calloc (size_t no_of_element, size_t size){
    if (no_of_element > 0 && size > 0)
    {
      int total = no_of_element * size;
      void *ptr = malloc (total);
      if (ptr != NULL)                       //just initializing the memory with the 0 with help of memset//
	return memset (ptr, 0, total);             //total telss about the no. of bytes to copy//
    }
    return NULL;
}

void *realloc (void *ptr, size_t newsize)           
{
  if (ptr == NULL)                       //pointer is pointing to null the call malloc (size)//
    return malloc (newsize);

  if (newsize == 0)                  //if the new size is 0 then pree up the pointer//
    {
      free (ptr);
      return ptr;
    }

  Node *crr = head;               

  while (crr != NULL)
    {
      if (crr->ptr == ptr)       //if previous node pointing to address and the address given by malloc is sme then we break //
	{                            //from while loop//
	  break;
	}

      crr = crr->next;       
    }


  if (crr != NULL)
    {
      if (crr->size > newsize && crr->size - newsize > 8)    //size > new required size and size -new size > 8 hten we do the allocation//
	{                                                        //greater than 8 is just for pointer rounding of//
	  memdiv (crr, newsize);
	}

      else if (crr->size < newsize)             //if size < new size than we have to call malloc for new allocation with malloc//
	{                                           //have the paramenter as new required size//
	  void *new = malloc (newsize);
	  return memcpy (new, crr->ptr, crr->size);  // now we will going to first copy the data to new memeory and the return the pointer//
	}

      else return ptr;
    }

  return NULL;
}
int debug(int a )
{ 
    int totmeuse;
    if (a==1){
        totmeuse= fsize-(24*count)-fsbrk;
        printf("\n%lu\n",fsize);
        
    }
    return totmeuse;
}

