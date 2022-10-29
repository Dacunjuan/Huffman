#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0

typedef struct Str Str;
typedef struct symbol_prob symbol_prob;

struct Str
{
    int len, size;
    char *s;
    char radix;
};

struct symbol_prob
{
    char symbol;
    double prob;
    struct Str *codeword;
    struct symbol_prob *left, *right;
};

Str *StrNew();
void StrAppend(Str *str, char *s);
int max(int a, int b);
int check_prob(symbol_prob list[], int count);
void Huffman(symbol_prob allTask[], int count);
void sortTask(symbol_prob allTask[], int count);
symbol_prob *createTask(symbol_prob *allTask, int count);
void returnBack_Symbol(symbol_prob *allTask);
void printAll(symbol_prob *allTask, int count);
//-------------------
int check_prob(symbol_prob list[], int count)
{
    int i = 0;
    unsigned long long int temp = 0.0, max = 1.0;
    for (i = 0; i < count; i++)
    {
        temp += list[i].prob;
    }

    int flag = (temp - 1.0) <= 0.0 ? true : false;
    return flag;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Str *StrNew()
{
    Str *str = (Str *)malloc(sizeof(Str));
    str->s = (char *)malloc(1);
    str->s[0] = '\0';
    str->len = 0;
    str->size = 1;
    return str;
}

void StrAppend(Str *str, char *s)
{
    int newLen = str->len + strlen(s);
    if (newLen + 1 > str->size)
    {
        int newSize = max(str->size * 2, newLen + 1);
        char *t = (char *)malloc(newSize);
        sprintf(t, "%s%s", str->s, s);
        free(str->s);
        str->s = t;
        str->len = newLen;
        str->size = newSize;
    }
    else
    {
        strcat(&str->s[str->len], s);
        str->len += strlen(s);
    }
}
// Huffman main
void Huffman(symbol_prob *allTask, int count)
{
    if (count == 1 && allTask[0].prob == 1.0)
    {
        returnBack_Symbol(allTask);
        return;
    }
    else if (count == 1 || allTask[0].prob == 1.0)
    {
        printf("Error!\n");
        return;
    }

    sortTask(allTask, count);
    symbol_prob *new_allSymbol = createTask(allTask, count);
    Huffman(new_allSymbol, count - 1);
}

void swapTask(symbol_prob main[], int a, int b)
{
    symbol_prob temp;
    temp.symbol = main[a].symbol;
    temp.prob = main[a].prob;
    temp.codeword = main[a].codeword;
    temp.left = main[a].left;
    temp.right = main[a].right;
    //
    main[a].symbol = main[b].symbol;
    main[a].prob = main[b].prob;
    main[a].codeword = main[b].codeword;
    main[a].left = main[b].left;
    main[a].right = main[b].right;
    //
    main[b].symbol = temp.symbol;
    main[b].prob = temp.prob;
    main[b].codeword = temp.codeword;
    main[b].left = temp.left;
    main[b].right = temp.right;
}

void sortTask(symbol_prob allTask[], int count)
{
    int i, j, max;
    for (i = 0; i < count; i++)
    {
        max = i;
        for (j = i + 1; j < count; j++)
        {
            if (allTask[j].prob > allTask[max].prob)
            {
                max = j;
            }
        }
        swapTask(allTask, i, max);
    }
}

symbol_prob *createTask(symbol_prob *allTask, int count)
{
    int i;
    symbol_prob *temp = (symbol_prob *)malloc(sizeof(symbol_prob) * (count - 1));
    for (i = 0; i < count - 1; i++)
    {
        // temp[i].symbol = NULL;
        temp[i].codeword = StrNew();

        if (i == count - 2)
        {
            temp[i].left = &allTask[i];
            temp[i].right = &allTask[i + 1];
            temp[i].prob = allTask[i].prob + allTask[i + 1].prob;
            break;
        }
        else
        {
            temp[i].prob = allTask[i].prob;
            temp[i].left = &allTask[i];
            temp[i].right = NULL;
        }
    }
    return temp;
}

void returnBack_Symbol(symbol_prob *allTask)
{
    symbol_prob *left_temp = allTask->left;
    symbol_prob *right_temp = allTask->right;
    Str *strTemp = allTask->codeword;
    if (left_temp != NULL && right_temp != NULL)
    {
        StrAppend(left_temp->codeword, strTemp->s);
        StrAppend(right_temp->codeword, strTemp->s);

        StrAppend(left_temp->codeword, "0");
        StrAppend(right_temp->codeword, "1");

        returnBack_Symbol(left_temp);
        returnBack_Symbol(right_temp);
    }
    else if (left_temp == NULL && right_temp != NULL)
    {
        returnBack_Symbol(right_temp);
    }
    else if (left_temp != NULL && right_temp == NULL)
    {
        StrAppend(left_temp->codeword, strTemp->s);
        returnBack_Symbol(left_temp);
    }
    else
    {
        return;
    }
}

void printAll(symbol_prob *allTask, int count)
{
    int i = 0;
    printf("Symbol\tProb\tCodeWord\n");
    for (i = 0; i < count; i++)
    {
        Str *temp = allTask[i].codeword;
        printf("%c\t%0.3lf\t%s\n", allTask[i].symbol, allTask[i].prob, temp->s);
    }
}
// code len
double calculateLav(symbol_prob *allTask, int count)
{
    int i;
    double Lav = 0;
    for (i = 0; i < count; i++)
    {
        Str *temp = allTask[i].codeword;
        Lav += allTask[i].prob * temp->len;
    }
    return Lav;
}
// Entropy
double calculateEntropy(symbol_prob *allTask, int count)
{
    int i;
    double Hr = 0;
    for (i = 0; i < count; i++)
    {
        Str *temp = allTask[i].codeword;
        Hr += allTask[i].prob * (log(1 / allTask[i].prob) / log(2));
    }
    return Hr;
}