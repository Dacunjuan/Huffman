#include <stdio.h>
#include "Huffman.h"

int main(int argc, char *argv[])
{
    symbol_prob all[10];
    int count = 0;
    while (scanf(" %c %lf", &all[count].symbol, &all[count].prob) != EOF)
    {
        all[count].codeword = StrNew();
        all[count].left = NULL;
        all[count].right = NULL;
        count++;
        if (count == 10)
        {
            printf("Symbol count = 10 , Stop read\n");
            break;
        }
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
        printf("Probability Error! Sum not equal 1.0\n");
    }
}
