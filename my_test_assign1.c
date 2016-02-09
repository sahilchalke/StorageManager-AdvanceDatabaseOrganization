#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// test name
char *testName;

/* test output files */
#define TESTPF "test_pagefile.bin"

/* prototypes for test functions */
static void myTestAssign1(void);

/* main function running all tests */
int
main (void)
{
  testName = "";
  
  initStorageManager();
  myTestAssign1();
  return 0;
}

/* Try to create, open, and close a page file */
void
myTestAssign1(void)
{
  SM_FileHandle fh;
  SM_PageHandle ph;
  int i;
}
