CC = gcc
OGFLAGS = -Og
O1FLAGS = -O1
CFLAGS = $(OGFLAGS) -Wall -g

CINC =
F64 =-m64

%.s: %.c
	$(CC) $(OGFLAGS) $(CINC) -S $(F64) $<

%_opt01.s: %.c
	$(CC) $(O1FLAGS) $(CINC) -S $(F64) $< -o $*_optO1.s

%.d: %.c
	$(CC) $(CFLAGS) $(CINC) $(F64) $< -o $*
	objdump -d $* > $@
	# rm -f $* 

files:	array_indexing array_indexing.s 2D_array 2D_array.s 

array_indexing: array_indexing.c
	$(CC) $(CFLAGS) $(CINC) -o array_indexing array_indexing.c
	
2D_array: 2D_array.c
	$(CC) $(CFLAGS) $(CINC) -o 2D_array 2D_array.c


clean:
	rm -f *.s *.d *~ array_indexing 2D_array
