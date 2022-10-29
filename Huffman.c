#include <stdio.h>
#include "Huffman.h"

int main(int argc, char *argv[])
{
    symbol_prob all[10];
    int count = 0;
    int temp;
    printf("Symbol\tProb\t\n");
    while (scanf("%d", &temp) != EOF)
    {
        all[count].codeword = StrNew();
        all[count].left = NULL;
        all[count].right = NULL;
        scanf("%c %lf", &all[count].symbol, &all[count].prob);
        printf("%c\t%lf\n", all[count].symbol, all[count].prob);
        count++;
    }
    printf("----------------\n");
    if (check_prob(all, count) == true)
    {
        Huffman(all, count);
        printAll(all, count);
        printf("Lav =\t%lf\n", calculateLav(all, count));
        printf("Hr(2) =\t%lf\n", calculateEntropy(all, count));
    }
    else
    {
        printf("prob Error!\n");
    }
}
