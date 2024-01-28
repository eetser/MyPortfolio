#include "HW2_Eeva-Maria_Tsernova_222705IACB_main.h"

void DisplayData(products *pData, quotes *qData, int pCount, int qCount)
{
    int i, j;
    //int c = 0;
                                                                
    for (i = 0; i < pCount; i++)
    {
        printf("\n%d. Tootekood:\t\t      %s\n", i + 1, pData[i].p_code);
        printf("   Mark ja mudel:\t      %s %s\n", pData[i].mark_model->mark,
                                            pData[i].mark_model->model);
        printf("   RAM:\t\t\t      %d\n   Ekraani suurus (tollides): %.2lf\n",
                                    pData[i].RAM, pData[i].screen_size);
        printf("   Operatsioonisüsteem:\t      %s\n\n", pData[i].op_sys);
                         
        for (j = 0; j < qCount; j++)
        {
            if (strcmp(pData[i].p_code, qData[j].product_code) == 0)
            {
                printf("\tPakkumise ID: %s\n", qData[j].quote_ID);
                printf("\tTootekood:    %s\n", qData[j].product_code);
                printf("\tTarnija:      %s\n", qData[j].retailer);
                printf("\tHind:         %.2lf\n", qData[j].price);
                printf("\tSaadavus:     %s\n\n", qData[j].availability);
            }
        }
    }
}
