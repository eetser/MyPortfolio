#include "HW2_Eeva-Maria_Tsernova_222705IACB_main.h"

// Avab faili ja loeb andmed sisse
// Tagastab arvu, kui palju loeti
int ReadProducts(products **pData)
{   
    products *db = (products*)malloc(sizeof(products));
    products *temp = NULL;
    char log[LEN];

    int i = 0;
    
    char productCode[LEN];
    char mark[LEN];
    char model[LEN];
    int ram;
    double screenSize;
    char opSys[LEN];
    
    FILE *f = fopen(FILE_PRODUCTS, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error! Toodete faili ei saanud avada!\n");
        Log("Error! Toodete faili ei saanud avada!");
        return EXIT_FAILURE;
    }
    
    while (fscanf(f, "%s %s %s %d %lf %s", productCode, mark, model, &ram,
                                    &screenSize, opSys) == 6)
    {
        temp = realloc(db, sizeof(products) * (i + 1));
        
        if (temp == NULL)
        {
            fprintf(stderr, "Error! Mälu küsimine ebaõnnestus!\n");
            Log("Error! Mälu küsimine ebaõnnestus!");
            break;
        }
        
        db = temp;
        strcpy(db[i].p_code, productCode);
        strcpy(db[i].mark_model->mark, mark);
        strcpy(db[i].mark_model->model, model);
        db[i].RAM = ram;
        db[i].screen_size = screenSize;
        strcpy(db[i].op_sys, opSys);
        i++;
    }
    *pData = db;
    snprintf(log, sizeof(log), "Andmete lugemine oli edukas!");
    
    fclose(f);
    Log(log);
    return i;
}

// Avab faili ja loeb andmed sisse
// Tagastab arvu, kui palju loeti
int ReadQuotes(quotes **qData)
{
    quotes *db = (quotes*)malloc(sizeof(quotes));
    quotes *temp = NULL;
    char log[LEN];
    
    int i = 0;
    
    char quoteID[LEN];
    char productCode[LEN];
    char retailer[LEN];
    double price;
    char availability[LEN];
    
    
    FILE *f = fopen(FILE_QUOTES, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error! Hinnapakkumiste faili ei saanud avada!\n");
        Log("Error! Hinnapakkumiste faili ei saanud avada!");
        return EXIT_FAILURE;
    }
    
    while (fscanf(f, "%s %s %s %lf %s", quoteID, productCode, retailer,
                                    &price, availability) == 5)
    {
        temp = realloc(db, sizeof(quotes) * (i + 1));
        
        if (temp == NULL)
        {
            fprintf(stderr, "Error! Mälu küsimine ebaõnnestus!\n");
            Log("Error! Mälu küsimine ebaõnnestus!");
            break;
        }
        
        db = temp;
        strcpy(db[i].quote_ID, quoteID);
        strcpy(db[i].product_code, productCode);
        strcpy(db[i].retailer, retailer);
        db[i].price = price;
        strcpy(db[i].availability, availability);
        i++;
    }
    *qData = db;
    snprintf(log, sizeof(log), "Andmete lugemine oli edukas!");
    
    fclose(f);
    Log(log);
    return i;
}
