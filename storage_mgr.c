#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dberror.h"
#include "storage_mgr.h"

int main(){
	
	initStorageManager();
	char file_Name[10] = TESTFILE;
    char *filePointer = &file_Name[0];
    SM_FileHandle *fHandle = (SM_FileHandle *)malloc(sizeof(SM_FileHandle));
	openPageFile(filePointer, fHandle);
	closePageFile(fHandle);
	destroyPageFile(fHandle->fileName);
	return 0;
	
} 	
extern void initStorageManager (void){
  
   char file_Name[10] = TESTFILE;
   char *filePointer = &file_Name[0];
   createPageFile(filePointer);
}

/***************************************************************
 * Function Name: createPageFile
 * 
 * Description: 
 *       Create a page file and write all '\0' in the first page.
 * 
 * Parameter:
 *       char *fileName: filename
 * 
 * Return: 
 *     RC:  return code(int error code)
 * 
 * Author:
 *     Dhruvit Modi (dmodi2@hawk.iit.edu)
 * 
 ****************************************************************/	
extern RC createPageFile (char *fileName){
  
  if(fileName == NULL){
	  return RC_FILE_NOT_FOUND;
  }
  
  FILE *fp;
  char *initChar = (char *)calloc(1, PAGE_SIZE);
  fp = fopen(fileName, "w+b");
  fwrite(initChar, PAGE_SIZE, 1, fp);
  if(ferror(fp)){
	  fclose(fp);
	  return RC_WRITE_FAILED;
  }
  fclose(fp);
  return RC_OK; 
}

/****************************************************************
 * Function Name: openPageFile
 * 
 ****************************************************************/
extern RC openPageFile (char *fileName, SM_FileHandle *fHandle){
  
  FILE *fp;
  int currentPos;
  fp = fopen(fileName, "r+b");
  if (fp == NULL){
    return RC_FILE_NOT_FOUND;
  }
  
  currentPos = ftell(fp);
  
  //Initializing the File Handle  
  fHandle->fileName = fileName;
  fHandle->mgmtInfo = (FILE *)fp;
  fHandle->curPagePos = currentPos/4096;
  fseek(fp, 0L, SEEK_END);
  fHandle->totalNumPages = ftell(fp)/4096;
  fseek(fp, currentPos, SEEK_SET);
  
  //printf("Filename: %s\n", fHandle->fileName);
  //printf("Current Page Pos: %d\n", fHandle->curPagePos);
  //printf("Total Page: %d\n", fHandle->totalNumPages);
  
  return RC_OK;
}

/****************************************************************
 * Function Name: closePageFile
 * 
 ****************************************************************/
extern RC closePageFile (SM_FileHandle *fHandle){
	
	if(fHandle == NULL){
		return RC_FILE_HANDLE_NOT_INIT;
	}
	fclose(fHandle->mgmtInfo);
	return RC_OK;
}

/****************************************************************
 * Function Name: destroyPageFile
 * 
 ****************************************************************/
extern RC destroyPageFile (char *fileName){
	
	int desRet;
	desRet = remove(fileName);
	if(desRet != 0){
		//error condition
	}
	return RC_OK;

}
