/*
 * Content: DVD 대여 관리 프로그램 main 
 */

#include "common.h"
//#include "cusManager.h"
//#include "dvdManager.h"
#include "blManager.h"
#include "screenOut.h"

enum{
  CUS_REGIST=1, CUS_SEARCH, DVD_REGIST, DVD_SEARCH, 
  DVD_RENT, DVD_RETURN, DVD_RENT_ALLCUS, DVD_CUS_ALLRENT, QUIT};

int main(void)
{
    int inputMenu = 0;
    InitData();  // 새로 추가된 문장
    
    while(1)
    {
        ShowMenu();
        scanf("%d", &inputMenu);
   		 getchar();
  		        
        switch(inputMenu)
        {
        case CUS_REGIST:
            RegistCustomer();
            break;
        
        case CUS_SEARCH:
            SearchCusInfo();
            break;

        case DVD_REGIST:
            RegistDVD();
            break;

        case DVD_SEARCH:
            SearchDVDInfo();
            break;

        case DVD_RENT:
            RentDVD();
            break;

        case DVD_RETURN:
            ReturnDVD();
            break;

        case DVD_RENT_ALLCUS:
            ShowDVDRentAllCusInfo();
            break;

        case DVD_CUS_ALLRENT:
            ShowDVDCusAllRentInfo();
            break;
        }
        
        if(inputMenu==QUIT)
        {
            puts("이용해 주셔서 고마워요~");
            break;
        }
    }    

    return 0;
}

/* end of file */
