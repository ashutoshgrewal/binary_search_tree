#include <stdio.h>

void
my_func(int my_int, int *my_pointer, int **ptr_to_ptr) 
{
	printf("%s my_int = %d && &my_int = %p\n", __FUNCTION__, my_int, &my_int);
	printf("%s my_pointer = %p and ptr_to_ptr - %p\n", __FUNCTION__, my_pointer, ptr_to_ptr);
}

int
main()
{
	int my_int;
	int *my_pointer;
	int **ptr_to_ptr;

	my_int = 5;

	printf("my_int = %d && &my_int = %p\n", my_int, &my_int);

	my_pointer = &my_int;
	ptr_to_ptr = &my_pointer;
	printf("my_pointer = %p and ptr_to_ptr = %p\n", my_pointer, ptr_to_ptr);

	*my_pointer = 6;
	printf("my_pointer (unchanged) = %p\n", my_pointer);
	printf("my_int (changed) = %d && &my_int (unchanged) = %p\n", my_int, &my_int);

	my_func(my_int, my_pointer, ptr_to_ptr);
}
