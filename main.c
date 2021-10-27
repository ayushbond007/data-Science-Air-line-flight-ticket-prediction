#include "sample.h"


int main()
{

	 
        // This pointer will hold the
    // base address of the block created
    int *ptr, *ptr1;
    int a, n, i;
    a =sizeof(int);
 printf("ayush%d\n",a);
    n = 0;
    a=sizeof(Node);
    
    printf("\n%d",a);
    printf("Enter number of elements: %d\n", n);
 
   
    ptr = (int*)malloc(n * sizeof(int));
 
    
    ptr1 = (int*)calloc(n, sizeof(int));
 
    //
    if (ptr == NULL || ptr1 == NULL) {  // Check if the memory has been successfully
                                         // allocated by malloc or not
        printf("Memory not allocated.\n");
        
    }
    else {
 
     
        printf("Memory successfully allocated using malloc.\n");
 
      
        free(ptr);
        printf("Malloc Memory successfully freed.\n");
 
   
        printf("\nMemory successfully allocated using calloc.\n");
 
      
        free(ptr1);
        printf("Calloc Memory successfully freed.\n");
    }
    
        n = 0;
        printf("\n\nEnter the new size of the array: %d\n", n);
 
       
        ptr = realloc(ptr, n * sizeof(int));
 
        
        printf("Memory successfully re-allocated using realloc.\n");
 
        // Get the new elements of the array
        for (i = 5; i < n; ++i) {
            ptr[i] = i + 1;
        }
 
        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d, ", ptr[i]);
        }
          
        free(ptr);
        printf("\n\t\n\tTo see the memory info press 1 %lu",ptr);
        
        printf("\n\t\n\tTo see the memory info press 1\n");
        scanf("%d",&a);
        a= debug(a);
        printf("%d",a);
    
    return 0;
    
    
}
 
