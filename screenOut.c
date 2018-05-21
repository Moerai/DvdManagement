/* 
 * Content: 콘솔 입출력을 위한 함수들의 정의.
 */

#include "common.h"
#include "cusInfo.h"
#include "dvdInfo.h"
#include "rentInfo.h"
#include "screenOut.h"

/* 프로그램 사용을 위한 메뉴 */
void ShowMenu(void)
{
    system("clear");   //stdlib.h
    
    printf("━━━━━ 메  뉴 ━━━━━━━ \n");
    printf(" 1. 신규가입 \n");
    printf(" 2. 고객검색 \n");
    printf("──────────────── \n");
    printf(" 3. DVD 등록 \n");
    printf(" 4. DVD 검색 \n");
    printf("──────────────── \n");
    printf(" 5. DVD 대여 \n");
    printf(" 6. DVD 반납 \n");
    printf("──────────────── \n");
    printf(" 7. DVD 대여고객 전체 조회\n");
    printf(" 8. 고객 대여 DVD 전체 조회\n");
    printf("──────────────── \n");
    printf(" 9. 종료 \n");
    printf("━━━━━━━━━━━━━━━━ \n");
    printf("선택》 ");
}


/* 고객 개인의 기본 정보 출력 */
void ShowCustomerInfo(cusInfo * pCus)
{
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ID: %s \n", pCus->ID);
    printf("┃ ▶ 이름: %s \n", pCus->name);
    printf("┃ ▶ 전화번호: %s \n", pCus->phoneNum);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
    
    getchar();
}

/* 고객 개인의 기본 정보 출력(연속 출력용) */
void ShowCustomerInfoContinue(cusInfo * pCus)
{
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ID: %s \n", pCus->ID);
    printf("┃ ▶ 이름: %s \n", pCus->name);
    printf("┃ ▶ 전화번호: %s \n", pCus->phoneNum);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
}

/* DVD 기본 정보 출력 */
void ShowDVDInfo(dvdInfo * pDVD)
{
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ISBN: %s \n", pDVD->ISBN);
    printf("┃ ▶ 타이틀: %s \n", pDVD->title);
    printf("┃ ▶ 쟝르:  "), ShowGenre(pDVD->genre), puts("");
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
    
    getchar();
}

/* DVD의 장르 정보 출력 */
void ShowGenre(int gen)
{
    switch(gen)
    {
    case ACTION:
        fputs("액션", stdout);
        break;
    case COMIC:
        fputs("코믹", stdout);
        break;
    case SF:
        fputs("SF", stdout);
        break;
    case ROMANTIC:
        fputs("로맨스", stdout);
        break;
    }
}

/* 대여 DVD 기본 정보 출력 */
void ShowDVDRentInfo(dvdRentInfo dvd)
{
    printf("┏━━━━━━━━━━━━━━━━ \n");
    printf("┃ ▶ ISBN: %s \n", dvd.ISBN);
    printf("┃ ▶ 대여일: %u \n", dvd.rentDay);
    printf("┗━━━━━━━━━━━━━━━━ \n\n");
}

/* end of file */
