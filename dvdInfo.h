/* 
 * Content: 영화 DVD 관리 구조체
 */

#ifndef __DVDINFO_H__
#define __DVDINFO_H__

#include "cusInfo.h"

#define ISBN_LEN   30
#define TITLE_LEN  30

enum {ACTION=1, COMIC, SF, ROMANTIC};    // 장르 정보
enum {RENTED, RETURNED};    // 대여 상태를 나타내는 상수!

typedef struct __dvdInfo 
{
    char ISBN[ISBN_LEN];
    char title[TITLE_LEN];
    int genre;
    int rentState;
}dvdInfo;

#endif
/* end of file */
