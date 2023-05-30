#include <stdio.h>
#include <stdlib.h>

#define N 100010

char a[N], b[N];                // 存储待运算数字
int lena, lenb;

int A[N], B[N], C[N];           // C用于存储答案
int lenA, lenB, lenC;

int get_lenth(char s[]);        // 求字符数组长度
int max(int a, int b);          // 求较大值
void swap(int* a, int* b);      // 交换数值
void mul(int *A, int *B);       // 乘法

int main()
{
    printf("High precision multiply high precision\nPlease input two high precision number:\ne.g. 123 123\n");
    scanf(" %s %s", a, b);      // 过滤空格与换行符
    
    lena = get_lenth(a), lenb = get_lenth(b);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储
    for(int j = lenb - 1; j >= 0; j --) B[lenB ++] = (b[j] - '0');

    if(lenA < lenB)
    {
        for(int i = 0; i < max(lenA, lenB); i ++)
            swap(&A[i], &B[i]);
        swap(&lenA, &lenB);
    }

    mul(A, B);
    for(int i = lenC - 1; i >= 0; i --) printf("%d",C[i]);
    printf("\n");
	system("pause");
    return 0;
}

int get_lenth(char s[])
{
    int len = 0;
    for(int i = 0; s[i] != '\0'; i ++)  len ++;
    return len;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void swap(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void mul(int *A, int *B)
{
    // 两个数相乘，结果的位数不会多于两数位数之和+1
    for (int i = 0; i < lenA + lenB + 1; ++i) 
    {
        for (int j = 0; j <= i; ++j)
            C[i] += A[j] * B[i - j];        // 加上所有满足p+q=i的元素的乘积之和

        if(C[i] >= 10)
        {
            C[i + 1] += C[i] / 10;
            C[i] %= 10;
        }
        lenC ++;
    }

    while (lenC > 1 && C[lenC - 1] == 0) lenC --;       // 去除前导0
    return ;
}