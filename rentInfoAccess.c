/* 
 * Content: DVD 대여 정보 저장/참조 함수들의 정의
 */

#include "common.h"
#include "rentInfo.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"
#include "rentInfoAccess.h"
#include "screenOut.h"

#define RENT_LEN  100
#define RENT_BAKCUP_FILE   "rentInfo.dat"

static dvdRentInfo rentList[RENT_LEN];
static int numOfRentCus=0;

void AddRentList(char * ISBN, char * cusID, int rentDay)
{
    strcpy(rentList[numOfRentCus].ISBN, ISBN);
    strcpy(rentList[numOfRentCus].cusID, cusID);
    rentList[numOfRentCus].rentDay = rentDay;

    numOfRentCus++;
    
    StoreRentListToFile();
}


void PrintOutRentAllCusInfo(char * ISBN)   // CusInfo, 고객 정보 출력
{
    int i;
    cusInfo * ptrCusInfo;
    
    for(i=0; i<numOfRentCus; i++)
    {
        if(!strcmp(rentList[i].ISBN, ISBN))
        {
            printf("대여일: %d \n", rentList[i].rentDay);
            ptrCusInfo=GetCusPtrByID(rentList[i].cusID);
            ShowCustomerInfoContinue(ptrCusInfo);
        }
    }
}


void PrintOutCusAllRentInfo   //RentInfo, 대여 정보 출력
    (char * ID, unsigned int start, unsigned int end)
{
    int i;
    
    for(i=0; i<numOfRentCus; i++)
    {
        /* 해당 ID의 정보라면. */
        if(!strcmp(rentList[i].cusID, ID))
        {
            /* 기간 내의 정보라면. */
            if(start<=rentList[i].rentDay && rentList[i].rentDay<=end)
                ShowDVDRentInfo(rentList[i]);
        }
    }
}


void StoreRentListToFile(void)
{
    FILE * fp=fopen(RENT_BAKCUP_FILE, "wb");
    if(fp==NULL)
        return;

    fwrite(&numOfRentCus, sizeof(int), 1, fp);
    fwrite(rentList, sizeof(dvdInfo), numOfRentCus, fp);

    fclose(fp);
}
 
void LoadRentListFromFile(void)
{
    FILE * fp=fopen(RENT_BAKCUP_FILE, "rb");
    if(fp==NULL)
        return;
 
    fread(&numOfRentCus, sizeof(int), 1, fp);
    fread(rentList, sizeof(dvdInfo), numOfRentCus, fp);

    fclose(fp);
}

/* end of file */
