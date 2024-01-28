#include "HW2_Eeva-Maria_Tsernova_222705IACB_main.h"

void Search(products *pData, quotes *qData, int pCount, int qCount)
{    
    char param1[LEN], param2[LEN];
    char log[LEN];
    
    printf("Sisestage esimene parameeter (tootekood, mark, mudel,");
    printf("operatsioonisüsteem, RAM või ekraanisuurus): ");
    scanf("%s", param1);
    
    printf("Sisestage teine parameeter(tootekood, mark, mudel,");
    printf("operatsioonisüsteem, RAM või ekraanisuurus): ");
    scanf("%s", param2);
    
    Printout(pData, qData, pCount, qCount, param1, param2);
    
    snprintf(log, sizeof(log), "Parameetrid sisestati");
    Log(log);
}

// prindib kõik tooted, mis on laos:
void Printout(products *pData, quotes *qData, int pCount, int qCount, char param1[], char param2[])
{
    int i, j;
    char laos[LEN] = "Laos";
    int count = 0;
    int found = 0;
    
    for (i = 0; i < pCount; i++)
    {
        products *p = (pData + i);
        for (j = 0; j < qCount; j++)
        {
            quotes *q = (qData + j);
            if (strcmp(pData[i].p_code, param1) == 0 ||
            strcmp(p->mark_model->mark, param1) == 0 ||
            strcmp(p->mark_model->model, param1) == 0 ||
            strcmp(p->op_sys, param1) == 0 ||
            p->screen_size == atof(param1) || p->RAM == atoi(param1))
            {
                if (strcmp(p->p_code, param2) == 0 ||
                strcmp(p->mark_model->mark, param2) == 0 ||
                strcmp(p->mark_model->model, param2) == 0 ||
                strcmp(p->op_sys, param2) == 0 ||
                p->screen_size == atof(param2) || p->RAM == atoi(param2))
                {
                    if (strcmp(p->p_code, q->product_code) == 0 &&
                    strcmp(q->availability, laos) == 0) 
                    {
                        printf("\n%d. Tootekood: %s\n   Mark ja mudel: %s %s\n",
                        count + 1, p->p_code, p->mark_model->mark,
                        p->mark_model->model);
                        printf("   RAM: %d\n   Ekraani suurus(tollides): %.2lf\n",
                        p->RAM, p->screen_size);
                        printf("   Operatsioonisüsteem: %s\n\n", p->op_sys);
                        
                        printf("   Tarnija: %s\n", q->retailer);
                        printf("   Saadavus: %s\n\n", q->availability);
                        
                        count++;
                        found = 1;
                    }    
                }
            }
        }
    }
    if (!found)
    {
        printf("\nSelliste parameetritega toodet pole laos.\n");
    }
}
