/*
 * Content: DVD 정보 저장/참조 함수들의 선언.
 */

#ifndef __DVDACCESS_H__
#define __DVDACCESS_H__

#include "dvdInfo.h"

int AddDVDInfo(char * ISBN, char * title, int genre);
dvdInfo * GetDVDPtrByISBN(char * ISBN);
int IsRegistISBN(char * ISBN);

/* 추가된 함수들의 선언 */
int SetDVDRented(char * ISBN);
int SetDVDReturned(char * ISBN);
int GetDVDRentState(char * ISBN);

void StoreDVDListToFile(void);
void LoadDVDListFromFile(void);

#endif
/* end of file */
