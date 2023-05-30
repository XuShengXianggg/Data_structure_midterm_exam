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
void add(int *A, int *B);       // 加法

int main()
{
    printf("High precision plus high precision\nPlease input two high precision number:\ne.g. 123 123\n");
    scanf(" %s %s", a, b);      // 过滤空格与换行符
    
    lena = get_lenth(a), lenb = get_lenth(b);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储
    for(int j = lenb - 1; j >= 0; j --) B[lenB ++] = (b[j] - '0');

    if(lenA < lenB)                 // 如果A的位数比B少，那么交换A和B的值
    {
        for(int i = 0; i < max(lenA, lenB); i ++)
            swap(&A[i], &B[i]);
        swap(&lenA, &lenB);
    }

    add(A, B);
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

void swap(int* a, int* b)           // 交换a与b的值
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void add(int *A, int *B)
{
    int t = 0;                      // 存储进位信息
    for (int i = 0; i < lenA; i ++ )
    {
        t += A[i];
        if (i < lenB) t += B[i];
        C[lenC ++] = t % 10;        // 处理进位信息
        t /= 10;
    }

    if (t) C[lenC ++] = t;          // 处理最高位的进位
    return ;
}