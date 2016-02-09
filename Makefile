CC=gcc

dberror.o: dberror.c
	$(CC) -o dberror.o -c dberror.c

storage_mgr.o: storage_mgr.c
	$(CC) -o storage_mgr.o -c storage_mgr.c

test_assign1_1.o: test_assign1_1.c
	$(CC) -o test_assign1_1.o -c test_assign1_1.c

assign1_1: test_assign1_1.o storage_mgr.o dberror.o
		$(CC) -o assign1_1 test_assign1_1.o storage_mgr.o dberror.o -I.

clean:
	rm assign1_1 test_assign1_1.o storage_mgr.o dberror.o
