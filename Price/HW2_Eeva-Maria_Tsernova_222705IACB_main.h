#ifndef HW2_EEVA_MARIA_TSERNOVA_222705IACB_MAIN_H
#define HW2_EEVA_MARIA_TSERNOVA_222705IACB_MAIN_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LEN 100
#define LOG_MAX 300

// paths to the data file
#define FILE_PRODUCTS "HW2_Eeva-Maria_Tsernova_222705IACB_products.txt"
#define FILE_QUOTES "HW2_Eeva-Maria_Tsernova_222705IACB_quotes.txt"

typedef struct {
    char mark[LEN];           // mark
    char model[LEN];          // model
} name;

typedef struct {
    char p_code[LEN];         // product code (PK)
    name mark_model[LEN];     // product name (mark + model)
    int RAM;                  // RAM (MB)
    double screen_size;       // size of screen (inches)
    char op_sys[LEN];         // operating system
} products;

typedef struct {
    char quote_ID[LEN];       // quote ID (PK)
    char product_code[LEN];   // product code (FK)
    char retailer[LEN];       // retailer
    double price;             // price of product
    char availability[LEN];   // availability (in stock / order)
} quotes;

// Funktsioonid
int GetMenuInput(void);
void Log(char *txt);
int ReadProducts(products **pData);
int ReadQuotes(quotes **qData);
void DisplayData(products *pData, quotes *qData, int pCount, int qCount);
int EditScreenSize(products *pData, int pCount);
int EditAvailability(quotes *qData, int qCount);
void Search(products *pData, quotes *qData, int pCount, int qCount);
void Printout(products *pData, quotes *qData, int pCount, int qCount, char param1[], char param2[]);
#endif // HW2_EEVA_MARIA_TSERNOVA_222705IACB_MAIN_H
