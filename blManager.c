/*
 * Content:  비즈니스 로직 처리 함수들의 정의
 */
#include "common.h"
#include "cusInfo.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"
#include "cusInfoAccess.h"
#include "rentInfoAccess.h"
#include "screenOut.h"


void InitData(void)
{
    LoadCusListFromFile();    // cusInfoAccess.c에 정의된 함수
    LoadDVDListFromFile();    // dvdInfoAccess.c에 정의된 함수
    LoadRentListFromFile();    // rentInfoAccess.c에 정의된 함수
}


void RegistCustomer(void)
{
    char ID[ID_LEN];
    char name[NAME_LEN];
    char phoneNum[PHONE_LEN];
    
    /* ID 입력 과정 */
    fputs("ID 입력: ", stdout);
    gets(ID);
    
    if(IsRegistID(ID))
    {
        puts("해당 ID는 사용 중에 있습니다. 다른 ID를 선택해 주세요");
        getchar();
        return;
    }

    /* 이름 입력 */
    fputs("이름 입력: ", stdout);
    gets(name);
    
    /* 전화번호 입력 */
    fputs("전화번호 입력: ", stdout);
    gets(phoneNum);
    
    if(!AddCusInfo(ID, name, phoneNum))
    {
        puts("정상적인 데이터 저장에 실패하였습니다.");
        getchar();
        return;
    }
    
    puts("가입이 완료되었습니다.");
    getchar();
}


void SearchCusInfo(void)
{
    char ID[ID_LEN];
    cusInfo * cusPtr;
    
    /* 찾을 대상의 ID 입력 */
    fputs("찾는 ID 입력: ", stdout);
    gets(ID);

    cusPtr=GetCusPtrByID(ID); 
    if(cusPtr==0)
    {
        puts("존재하지 않는 ID입니다.");
        getchar();
        return;
    }

    ShowCustomerInfo(cusPtr);
}


void RegistDVD(void)
{
    char ISBN[ISBN_LEN];
    char title[TITLE_LEN];
    int genre;
    
    /* ISBN 입력 과정 */
    fputs("ISBN 입력: ", stdout);
    gets(ISBN);
    
    if(IsRegistISBN(ISBN))
    {
        puts("해당 ISBN은 이미 등록되었습니다.");
        getchar();
        return;
    }

    /* 제목 입력 */
    fputs("제목 입력: ", stdout);
    gets(title);
    
    /* 장르 입력 */
    fputs("장르 입력 (액션 1, 코믹 2, SF 3, 로맨틱 4): ", stdout);
    scanf("%d", &genre);
    getchar();

    if(!AddDVDInfo(ISBN, title, genre))
    {
        puts("정상적인 데이터 저장에 실패하였습니다.");
        getchar();
        return;
    }
    
    puts("등록이 완료되었습니다.");
    getchar();
}

void SearchDVDInfo(void)
{
    char ISBN[ISBN_LEN];
    dvdInfo * dvdPtr;
    
    /* 찾을 대상의 ISBN 입력 */
    fputs("찾는 ISBN 입력: ", stdout);
    gets(ISBN);

    dvdPtr=GetDVDPtrByISBN(ISBN); 
    if(dvdPtr==0)
    {
        puts("등록되지 않은 ISBN입니다.");
        getchar();
        return;
    }

    ShowDVDInfo(dvdPtr);
}

void RentDVD(void)
{
    char ISBN[ISBN_LEN];
    int registDVD;
    int registCus;
    int rentSte;

    char cusID[ID_LEN];      // 대여 고객 ID
    unsigned int rentDay;     // 대여일

    // 1. 대여할 DVD ISBN 입력 및 검증.
    fputs("대여 DVD ISBN 입력: ", stdout);
    gets(ISBN);
    
    registDVD=IsRegistISBN(ISBN);
    if(registDVD==0)
    {
        puts("등록되지 않은 ISBN 입니다.");
        getchar();
        return;
    }
    
    // 2. 대여 가능한 상태인지 확인.
    rentSte=GetDVDRentState(ISBN);
    if(rentSte==RENTED) 
    {
        puts("대여 중이라 대여가 불가능합니다.");
        getchar();
        return;
    }
    
    // 3. 대여 절차 진행.
    puts("대여가 가능합니다. 대여 과정을 진행합니다.");
    fputs("대여 고객 ID 입력: ", stdout);
    gets(cusID);
    
    registCus=IsRegistID(cusID);
    if(registCus==0)
    {
        puts("가입 고객이 아닙니다.");
        getchar();
        return;
    }
    
    fputs("대여 날짜 입력: ", stdout);
    scanf("%u", &rentDay);
    getchar();

    SetDVDRented(ISBN);
    AddRentList(ISBN, cusID, rentDay);

    puts("대여가 완료되었습니다.");
    getchar();
}


void ReturnDVD(void)
{
    char ISBN[ISBN_LEN];
    int registDVD;
    int rentSte;
    
    // 1. 반납할 DVD ISBN 입력 및 검증.
    fputs("반납 DVD ISBN 입력: ", stdout);
    gets(ISBN);
    
    registDVD=IsRegistISBN(ISBN);
    if(registDVD==0)
    {
        puts("등록되지 않은 ISBN 입니다.");
        getchar();
        return;
    }    
    
    // 2. 반납이 가능한 대상인지 확인.
    rentSte=GetDVDRentState(ISBN);
    if(rentSte==RETURNED)  // 대여 중이라면..
    {
        puts("대여되지 않은 DVD 입니다.");
        getchar();
        return;
    }
    
    // 3. 반납 절차 진행.
    SetDVDReturned(ISBN);
    puts("반납이 완료되었습니다.");
    getchar();
}


void ShowDVDRentAllCusInfo(void)
{
    char ISBN[ISBN_LEN];
    dvdInfo * ptrDVDInfo;
    
    /* 찾을 대상의 ISBN 입력 */
    fputs("찾는 ISBN 입력: ", stdout);
    gets(ISBN);
    
    ptrDVDInfo = GetDVDPtrByISBN(ISBN);
    if(ptrDVDInfo==0)
    {
        puts("존재하지 않는 ISBN 입니다.");
        getchar();
        return;
    }
    
    PrintOutRentAllCusInfo(ISBN);

    puts("조회를 완료하였습니다.");
    getchar();         
}

void ShowDVDCusAllRentInfo(void)
{
    char ID[ID_LEN];
    unsigned int rentStart;
    unsigned int rentEnd;
    cusInfo * ptrCusInfo;

    /* 찾을 대상의 ID 입력 */
    fputs("찾는 ID 입력: ", stdout);
    gets(ID);

    ptrCusInfo = GetCusPtrByID(ID);
    if(ptrCusInfo==0)
    {
        puts("가입되지 않은 ID 입니다.");
        getchar();
        return;
    }
 
    fputs("대여 기간 입력: ", stdout);
    scanf("%u %u", &rentStart, &rentEnd);
    getchar();
    
    if(rentStart>rentEnd)
    {
        puts("기간 정보가 잘못 입력되었습니다.");
        getchar();
        return;
    }
    
    PrintOutCusAllRentInfo(ID, rentStart, rentEnd);
    puts("조회를 완료하였습니다.");
    getchar();
}

/* end of file */
