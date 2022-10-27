#include <stdio.h>
#include "Huffman.h"

int main()
{
    symbol_prob all[10];
    int count = 0;
    int temp;
    all[0].symbol = 'A';
    all[0].prob = 0.5;
    all[0].codeword = StrNew();
    all[0].left = NULL;
    all[0].right = NULL;
    //
    all[1].symbol = 'B';
    all[1].prob = 0.3;
    all[1].codeword = StrNew();
    all[1].left = NULL;
    all[1].right = NULL;
    //
    all[2].symbol = 'C';
    all[2].prob = 0.2;
    all[2].codeword = StrNew();
    all[2].left = NULL;
    all[2].right = NULL;
    //
    /*
    all[3].symbol = 'D';
    all[3].prob = 0.1;
    all[3].codeword = StrNew();
    all[3].left = NULL;
    all[3].right = NULL;
    */
    //
    count = 3;
    /*
    while (scanf("%d", &temp) != EOF)
    {
        scanf("%c %lf", &all[count].symbol, &all[count].prob);
        all[count].codeword = StrNew();
        all[count].left = NULL;
        all[count].right = NULL;
        all[count].id = count;
        printf("%c\t%lf\n", all[count].symbol, all[count].prob);

        count++;
    }
    */
    Huffman(all, count);
    printAll(all, count);
    if (check_prob(all, count) == true)
    {
        Huffman(all, count);
        printAll(all, count);
        printf("prob Good\n");
    }
    else
    {
        printf("prob Error!\n");
    }
}
