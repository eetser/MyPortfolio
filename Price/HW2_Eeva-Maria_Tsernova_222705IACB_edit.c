#include "HW2_Eeva-Maria_Tsernova_222705IACB_main.h"

int EditScreenSize(products *pData, int pCount)
{
    FILE *fp;
    char pCode[LEN];
    double new_screen_size;
    int found = 0;
    int i;
    char log[LEN];
    
    printf("Sisesta tootekood, mille ekraani suurust soovid muuta:\n");
    for (i = 0; i < pCount; i++)
    {
        printf("\t%s\n", pData[i].p_code);
    }
    printf("\n> ");
    
    if (scanf("%s", pCode) != 1)
    {
        printf("Vale sisestus!\n");
        Log("Error! Vale sisestus!");
        
        fflush(stdin);
        int a;
        // loetakse kuni tuleb reavahetus ja fail lõppeb
        while ((a = getchar()) != '\n' && a != EOF);

        return EXIT_FAILURE;
    }

    printf("Sisesta uus ekraani suurus tollides: ");
    printf("\n");
    
    if (scanf("%lf", &new_screen_size) != 1)
    {
        printf("Vale sisestus!\n");
        Log("Error! Vale sisestus!");
        
        fflush(stdin);
        int b;
        // loetakse kuni tuleb reavahetus ja fail lõppeb
        while ((b = getchar()) != '\n' && b != EOF);

        return EXIT_FAILURE;
    }
    
    for (i = 0; i < pCount; i++)
    {
        if (strcmp(pData[i].p_code, pCode) == 0)
        {
            pData[i].screen_size = new_screen_size;
            printf("Ekraani suurus edukalt muudetud!\n");
            printf("Uus ekraani suurus on %.2lf tolli.\n\n", pData[i].screen_size);
            snprintf(log, sizeof(log), "Toote ekraani suurus muudeti");
            Log(log);
            
            found++;
        }
    }
    
    if (found == 0)
    {
        printf("Sellist toodet ei leitud.\n");
        Log("Error! Sellist toodet ei leitud");
    }
    
    fp = fopen(FILE_PRODUCTS, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR! Faili avamine ebaõnnestus.\n");
        Log("ERROR: Toodete faili avamine ebaõnnestus");
        return EXIT_FAILURE;
    }
    // Muudatused salvestatakse faili
    for (i = 0; i < pCount; i++)
    {
        fprintf(fp, "%s %s %s %d %lf %s\n", pData[i].p_code,
                    pData[i].mark_model->mark, pData[i].mark_model->model,
                    pData[i].RAM, pData[i].screen_size, pData[i].op_sys);
    }

    fclose(fp);
    Log("Toodete fail uuendatud.");
    
    return EXIT_SUCCESS;
}    

int EditAvailability(quotes *qData, int qCount)
{
    FILE *fp;
    char ID[LEN];
    char new_availability[LEN];
    int found = 0;
    int i;
    char log[LEN];
    char laos[] = "Laos";
    char order[] = "Order";
    
    printf("Sisesta pakkumise ID, mille staatust soovid muuta:\n");
    for (i = 0; i < qCount; i++)
    {
        printf("\t%s\n", qData[i].quote_ID);
    }
    printf("\n> ");
    
    if (scanf("%s", ID) != 1)
    {
        printf("Vale sisestus!\n");
        Log("Error! Vale sisestus!");
        
        int a;
        while ((a = getchar()) != '\n' && a != EOF);

        return EXIT_FAILURE;
    }

    printf("Sisesta uus staatus (Laos / Order): ");
    printf("\n");
    
    if (scanf("%s", new_availability) != 1 || strcmp(new_availability, laos) != 0 && strcmp(new_availability, order) != 0)
    {
        printf("Vale sisestus!\n");
        Log("Error! Vale sisestus!");
        
        int b;
        // loetakse kuni tuleb reavahetus ja fail lõppeb
        while ((b = getchar()) != '\n' && b != EOF);

        return EXIT_FAILURE;
    }
    
    for (i = 0; i < qCount; i++)
    {
        if (strcmp(qData[i].quote_ID, ID) == 0)
        {
            strcpy(qData[i].availability, new_availability);
            printf("Staatus edukalt muudetud!\n");
            printf("Uus staatus on %s.\n\n", qData[i].availability);
            Log("Pakkumise staatus muudeti");
            
            snprintf(log, sizeof(log), "Toote saadavust muudeti");
            Log(log);
            
            found++;
        }
    }
    
    if (found == 0)
    {
        printf("Sellist pakkumist ei leitud.\n");
        Log("Error! Sellist pakkumist ei leitud");
    }
    
    fp = fopen(FILE_QUOTES, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR! Faili avamine ebaõnnestus.\n");
        Log("ERROR: Pakkumiste faili avamine ebaõnnestus");
        return EXIT_FAILURE;
    }
    // Muudatused salvestatakse faili
    for (i = 0; i < qCount; i++)
    {
        fprintf(fp, "%s %s %s %lf %s\n", qData[i].quote_ID,
                    qData[i].product_code, qData[i].retailer, qData[i].price,
                    qData[i].availability);
    }

    fclose(fp);
    Log("Pakkumiste fail uuendatud.");
    
    return EXIT_SUCCESS;
}
