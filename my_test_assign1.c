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

/****************************************************************
 * Function Name: myTestAssign1
 *  
 * Description: Additional tests for Storage Manager.
 * 
 * Parameter: void
 * 
 * Return: void
 * 
 * Author: Dhruvit Modi (dmodi2@hawk.iit.edu)
 *         Monika Priyadarshani (mpriyad1@hawk.iit.edu)
 ****************************************************************/
void
myTestAssign1(void)
{
  SM_FileHandle fh;
  SM_PageHandle ph;
  int i;
  
  ph = (SM_PageHandle) malloc(PAGE_SIZE);

  // create a new page file
  TEST_CHECK(createPageFile (TESTPF));
  TEST_CHECK(openPageFile (TESTPF, &fh));
  printf("created and opened file\n");
  
    
  for (i=0; i < PAGE_SIZE; i++)
    ph[i] = (i % 10) + '0';
  
  // write on the first block  
  TEST_CHECK(writeCurrentBlock (&fh, ph));
  printf("writing first block\n");
  
  // append empty block
  TEST_CHECK(appendEmptyBlock(&fh));
  printf("append Empty block\n");
   
   // write on the second block 
  TEST_CHECK(writeBlock (1, &fh, ph));
  printf("writing second block\n");
  
  TEST_CHECK(appendEmptyBlock(&fh));
  printf("append Empty block\n");
  
    // write to the third block
  TEST_CHECK(writeBlock (2, &fh, ph));
  printf("writing third block\n");
  
  // read back the page containing the string and check that it is correct
  printf("reading first block\n");
  TEST_CHECK(readFirstBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  
  
  // read back the page containing the string and check that it is correct
  printf("reading last block\n");
  TEST_CHECK(readLastBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  
  
  // read back the page containing the string and check that it is correct
  printf("reading previous block\n");
  TEST_CHECK(readPreviousBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  
  
  // read back the page containing the string and check that it is correct
  printf("reading current block\n");
  TEST_CHECK(readCurrentBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  
  
  // read back the page containing the string and check that it is correct
  printf("reading next block\n");
  TEST_CHECK(readNextBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  
  // append empty block
  TEST_CHECK(appendEmptyBlock(&fh));
  printf("append Empty block\n");
  
  // ensure capacity
  TEST_CHECK(ensureCapacity(6, &fh));
  printf("ensure capacity\n");
  
    // destroy new page file
  TEST_CHECK(destroyPageFile (TESTPF));  
  
  TEST_DONE();
}
