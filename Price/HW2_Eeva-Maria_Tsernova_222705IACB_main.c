#include "HW2_Eeva-Maria_Tsernova_222705IACB_main.h"

int main(void)
{
    Log("Programm avati");
    products *p = NULL;
    quotes *q = NULL;
    
    int pCount = ReadProducts(&p);
    int qCount = ReadQuotes(&q);
    
    int menu;
    
    while (1)
    {
        menu = GetMenuInput();
        switch (menu)
        {
            case 0:
                /* case 0 - destroy the list and exits the program */
                free(p);
                free(q);
                
                Log("Mälu vabastatud");
                Log("Programm sulgus");
                exit(EXIT_SUCCESS);
                break;
            case 1:
                /* case 1 - kuva tooted ja nende andmed*/ 
                
                Log("Tooted kuvatakse");
                DisplayData(p, q, pCount, qCount);
                break;
            case 2:
                /* case 2 - küsi tootekoodi ja lase muuta ekraani suurust*/
                Log("Ekraani suuruse muutmine");
                EditScreenSize(p, pCount);
                break;
            case 3:
                /* case 3 - küsi pakkumise ID-d ja lase muuta toote saadavust*/
                
                Log("Toote saadavuse muutmine");
                EditAvailability(q, qCount);
                break;
            case 4:
                /* case 4 - otsing 2 parameetri alusel*/
                
                Log("Toote otsimine");
                Search(p, q, pCount, qCount);
                break;
            default:
                printf("Sisestasite vale numbri!");
                Log("Error! Sisestus on vale");
                break;
        }
    }
    return EXIT_SUCCESS;
}

int GetMenuInput(void)
{
    int input;
    puts("");
    while (1)
    {
        printf("Menüü:\n");
        printf("1 - Kuva andmed\n");
        printf("2 - Muuda toote ekraani suurust\n");
        printf("3 - Muuda toote saadavust\n");
        printf("4 - Otsing\n");
        printf("0 - Exit\n");
        printf("> ");
        scanf("%d", &input);
        printf("\n\n");
        if (input <= 4 && input >= 0)
        {
            return input;
        }
        else
        {
            fprintf(stderr, "Vale sisestus, proovi uuesti!\n");
            return input;
        }
    }
}

void Log(char *txt)
{
    time_t t = time(NULL);
    char *time = ctime(&t);
    
    strtok(time, "\n");
    
    FILE *f = fopen("HW2_Eeva-Maria_Tsernova_222705IACB_log.txt", "a");
    
    if (f == NULL)
    {
        perror("Error! Logi faili ei saanud avada!\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    
    fprintf(f, "%s\t%s \n", time, txt);
    fclose(f);
}
