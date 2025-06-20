# Makefile is essential for C/C++ coding

# It behaves like a recipe book, lead all ingredients (headers and C files) to build
# the final dish(program)

CC = clang	# Compiler
CFALGS = -Wall - Werror	# Complier flags

# all: we will build all the files
all: gen \
     selectionSort bubbleSort insertionSort \
     mergeSort naiveQuickSort medianOfThreeQuickSort randomisedQuickSort

# gen: the name of the file we complied
gen: gen.c
	$(CC) $(CFLAGS) -o gen gen.c

selectionSort: sorter.c
	$(CC) "-DSORT='s'" $(CFLAGS) -o selectionSort sorter.c

bubbleSort: sorter.c
	$(CC) "-DSORT='b'" $(CFLAGS) -o bubbleSort sorter.c

insertionSort: sorter.c
	$(CC) "-DSORT='i'" $(CFLAGS) -o insertionSort sorter.c

shellSort: sorter.c
	$(CC) "-DSORT='h'" $(CFLAGS) -o shellSort sorter.c

mergeSort: sorter.c
	$(CC) "-DSORT='m'" $(CFLAGS) -o mergeSort sorter.c

naiveQuickSort: sorter.c
	$(CC) "-DSORT='N'" $(CFLAGS) -o naiveQuickSort sorter.c

medianOfThreeQuickSort: sorter.c
	$(CC) "-DSORT='M'" $(CFLAGS) -o medianOfThreeQuickSort sorter.c

randomisedQuickSort: sorter.c
	$(CC) "-DSORT='R'" $(CFLAGS) -o randomisedQuickSort sorter.c

# remove the complied files
clean:
	rm -f gen \
	      selectionSort bubbleSort insertionSort shellSort mergeSort \
	      naiveQuickSort medianOfThreeQuickSort randomisedQuickSort

