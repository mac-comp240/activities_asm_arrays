#include <stdio.h>  // printf
#include <stdlib.h>  // malloc
#include <assert.h>

#define N 10

/*
 * Computes and returns the sum of the elements in the array
 * pointed to by arr_ptr.
 *
 */
int sum_p(int *arr_ptr) {
	int sum = 0;
    int i;
	int * next = arr_ptr;  // points to zeroth element
	
	printf("The pointer values (memory addresses) \nfor each element of array are:\n");
	// for loop using pointer addition goes here
	for (i = 0; i < N; i++) {
		//  TODO: you compute the sum by adding one line here
		
		next = next + 1;       // increment pointer goes to next element
		printf("%p ", next);
	}
	printf("\n"); 
    
    return sum;
}


/*
 * Computes and returns the sum of the elements in the array A.
 *
 */
int sum_index(int *A) {
    int sum = 0;
    int i;
    
	// TODO: write the for loop to sum up the elements of A
	
    
    return sum;
}

int main() {
    // To declare A statically, uncomment the line below and comment out the 
    // two lines in the next section (and the "free" line below)
    //int A[N];    // array of length N

    // To declare A dynamically, uncomment the two lines below and comment out
    // the line above (also uncomment the "free" line below)
    int * A;    // set the pointer to the beginning (only a single pointer now)
	A = (int *) malloc(N * sizeof(int));  // creates contiguous array of ints in the heap
    
    // fill A with dummy data values, using indexing
    for (int i = 0; i<N; i++) {
        A[i] = i;
    }
    
    ///// Using the functions
    
    //using A here as the argument to the function means that we are passing the
    // pointer to the zeroth element of the array
    int arraySum = sum_p(A);  
    
    printf("sum of elements in A is: %d\n", arraySum);
    // 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
    assert(arraySum == 45);
    
    arraySum = sum_index(A);
    assert(arraySum == 45);
    
    free(A);
    return 0;
}