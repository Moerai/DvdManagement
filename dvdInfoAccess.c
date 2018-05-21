/* 
 * Content: DVD 정보 저장/참조 함수들의 정의.
 */

#include "common.h"
#include "screenOut.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"

#define MAX_DVD  100
#define DVD_BAKCUP_FILE   "dvdInfo.dat"

static dvdInfo * dvdList[MAX_DVD];
static int numOfDVD=0;


int AddDVDInfo(char * ISBN, char * title, int genre)
{
    dvdInfo * pDVD;
    
    if(numOfDVD>=MAX_DVD)
        return 0;  // 입력 실패

    pDVD=(dvdInfo *)malloc(sizeof(dvdInfo));
    strcpy(pDVD->ISBN, ISBN);
    strcpy(pDVD->title, title);
    pDVD->genre=genre;

    pDVD->rentState=RETURNED;
    dvdList[numOfDVD++]=pDVD;

    /* 파일에 데이터 저장 */
    StoreDVDListToFile();

    return numOfDVD;   // 입력 성공
}


dvdInfo * GetDVDPtrByISBN(char * ISBN)
{
    int i;

    for(i=0; i<numOfDVD; i++)
    {
        if(!strcmp(dvdList[i]->ISBN, ISBN))
            return dvdList[i];
    }
    
    return (dvdInfo *)0;
}

int IsRegistISBN(char * ISBN)
{
    dvdInfo * pDVD = GetDVDPtrByISBN(ISBN);
    
    if(pDVD==0)
        return 0;  // 가입 안된 경우.
    else
        return 1;  // 가입 된 경우.
}


int SetDVDRented(char * ISBN)
{
	dvdInfo * pDVD = GetDVDPtrByISBN(ISBN);
    if(pDVD==0)
        return 0;  // 등록 안된 경우.
            
    pDVD->rentState=RENTED;

    /* 파일에 데이터 저장 */
    StoreDVDListToFile();

    return 1;
}

int SetDVDReturned(char * ISBN)
{
    dvdInfo * pDVD = GetDVDPtrByISBN(ISBN);
    
    if(pDVD==0)
        return 0;  // 등록 안된 경우.

    pDVD->rentState=RETURNED;

	/* 파일에 데이터 저장 */
	StoreDVDListToFile();

    return 1;
}

int GetDVDRentState(char * ISBN)
{
    dvdInfo * pDVD = GetDVDPtrByISBN(ISBN);

    if(pDVD==0)
        return -1;  // 등록 안된 경우.

    return pDVD->rentState;
}

void StoreDVDListToFile(void)
{
    int i;
    FILE * fp=fopen(DVD_BAKCUP_FILE, "wb");
    if(fp==NULL)
        return;
    
    fwrite(&numOfDVD, sizeof(int), 1, fp);
    
    for(i=0; i<numOfDVD; i++)
        fwrite(dvdList[i], sizeof(dvdInfo), 1, fp);
    
    fclose(fp);
}

void LoadDVDListFromFile(void)
{
    int i;
    FILE * fp=fopen(DVD_BAKCUP_FILE, "rb");
    if(fp==NULL)
        return;
    
    fread(&numOfDVD, sizeof(int), 1, fp);

    for(i=0; i<numOfDVD; i++)
    {
        dvdList[i]=(dvdInfo *)malloc(sizeof(dvdInfo));
        fread(dvdList[i], sizeof(dvdInfo), 1, fp);
    }
 
    fclose(fp);
}
/* end of file */
