#include <stdio.h>
#include <stdlib.h>

FILE *vytvor_soubor()
{
    FILE *f = fopen("postup_reseni.txt", "w");
    return f;
}

void nacti(FILE *f, float matice[11][10], int *x, int *y)
{
    int n, m;
    printf("Napis pocet neznamych v soustave rovnic (max. 10): ");
    scanf("%d", x);
    if(*x>10)
    {
        printf("Neumis pocitat do desiti?!\n");
        return;
    }
    *y = *x;
    (*x)++;
    fprintf(f, "Zadana soustava rovnic: \n");
    for(n=0; n<*y; n++)
    {
        for(m=0; m<*x; m++)
        {
            if(m!=*x-1)printf("Zadejte koeficent promenne x%d %d. rovnice (musi se jednat o realne cislo): ", m+1, n+1);
            else printf("Zadejte vysledek %d. rovnice (musi se jednat o realne cislo): ", n+1);
            scanf("%f", &matice[n][m]);
            if(m!=*x-1)
            {
                if(m>0)
                {
                    if(matice[n][m]>=0) fprintf(f, " + %f*x%d", matice[n][m], m+1);
                    else fprintf(f, " - %f*x%d", matice[n][m]*(-1), m+1);
                }
                else fprintf(f, "%f*x%d", matice[n][m], m+1);
            }
            else
            {
                if(matice[n][m]>=0) fprintf(f, " = %f", matice[n][m]);
                else fprintf(f, " = -%f", matice[n][m]*(-1));
            }
        }
        printf("\n");
        fprintf(f, "\n");
    }
}

void prubezny_vypis(FILE *f, float matice[11][10], int x)
{
    int n, m;
    for(n=0; n<x-1; n++)
    {
        for(m=0; m<x; m++)
        {
            if(m!=x-1)
            {
                if(m>0)
                {
                    if(matice[n][m]>=0) fprintf(f, " + %f*x%d", matice[n][m], m+1);
                    else fprintf(f, " - %f*x%d", matice[n][m]*(-1), m+1);
                }
                else fprintf(f, "%f*x%d", matice[n][m], m+1);
            }
            else
            {
                if(matice[n][m]>=0) fprintf(f, " = %f", matice[n][m]);
                else fprintf(f, " = -%f", matice[n][m]*(-1));
            }
        }
        fprintf(f, "\n");
    }
}

void primy_chod(FILE *f, float matice[11][10], int x)
{
    int i, j, k;
    for(k=0; k<x-2; k++)
    {
        fprintf(f, "\n%d. pruchod soustavami rovnic primym chodem GEM:\n", k+1);
        for(i=k+1; i<x+1; i++)
        {
            for(j=k+1; j<x; j++)
            {
                if(matice[k][k]!=0)
                {
                    matice[i][j] = matice[i][j] - (matice[i][k] / matice[k][k]) * matice[k][j];
                }
                else
                {
                    matice[x-2][x-2] = 0;
                    matice[x-2][x-1] = 0;
                    k = x;
                }
            }
            matice[i][k]=0;
        }
        prubezny_vypis(f, matice, x);
    }
}

void zpetny_chod(FILE *f, float matice[11][10], int x)
{
    int i, k;
    for(k=x-1; k>=0; k--)
    {
        for(i=k+1; i<x; i++)
        {
            matice[k][x] = matice[k][x] - matice[k][i] * matice[i][x];

        }
        matice[k][x] = matice[k][x] / matice[k][k];
    }
    fprintf(f, "\nVysledky:\n");
    printf("\nVysledky:\n");
    int n;
    for(n=0; n<x; n++)
    {
        printf("x%d = %f\n", n+1, matice[n][x]);
        fprintf(f, "x%d = %f\n", n+1, matice[n][x]);
    }
}

void resitelnost(FILE *f, float matice[11][10], int x)
{
    x--;
    if(matice[x-2][x-2]!=0)
    {
        zpetny_chod(f, matice, x);
    }
    else
        if(matice[x-2][x-1]==0)
        {
            printf("\nSoustava rovnic ma nekonecne mnoho reseni.\n\n");
            fprintf(f, "\nSoustava rovnic ma nekonecne mnoho reseni.\n\n");
        }
        else
        {
            printf("\nSoustava rovnic nema zadne reseni.\n\n");
            fprintf(f, "\nSoustava rovnic nema zadne reseni.\n\n");
        }
}

int main()
{
    printf("Program na pocitani soustavy rovnic Gaussovou Eliminaèní Metodou (pouze sumarizacniho typu):\n\n");
    float matice[11][10];
    int x, y;
    FILE *f = vytvor_soubor();
    if(f == 0)
    {
        printf("Nepodarilo se vytvorit soubor.\n");
        getchar();
    }
    nacti(f, matice, &x, &y);
    primy_chod(f, matice, x);
    resitelnost(f, matice, x);
    fclose(f);
    printf("\nOtevira se soubor s postupem reseni...\n");
    system("notepad postup_reseni.txt");
    return 0;
}
