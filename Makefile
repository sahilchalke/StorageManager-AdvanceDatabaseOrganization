CC=gcc

default: assign1_1

assign1_1: test_assign1_1.o storage_mgr.o dberror.o
		$(CC) -o assign1_1 test_assign1_1.o storage_mgr.o dberror.o -I.
		
my_assign1: my_test_assign1.o storage_mgr.o dberror.o
		$(CC) -o my_assign1 my_test_assign1.o storage_mgr.o dberror.o -I.		
		
dberror.o: dberror.c
	$(CC) -o dberror.o -c dberror.c

storage_mgr.o: storage_mgr.c
	$(CC) -o storage_mgr.o -c storage_mgr.c

test_assign1_1.o: test_assign1_1.c
	$(CC) -o test_assign1_1.o -c test_assign1_1.c	

my_test_assign1.o: my_test_assign1.c
	$(CC) -o my_test_assign1.o -c my_test_assign1.c
    
clean:
	rm assign1_1 my_assign1 *.o
