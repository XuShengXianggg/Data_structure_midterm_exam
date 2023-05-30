#include <stdio.h>
#include <stdlib.h>

#define N 100010

char a[N];
int lena;

int b;
int A[N], C[N];           // C用于存储答案
int lenA, lenC;

int get_lenth(char s[]);        // 求字符数组长度
void mul(int A[], int b);       // 乘法

int main()
{
    printf("High precision multiply low precision\nPlease input one high precision number and one low precision number:\ne.g. 123 123\n");
    scanf(" %s %d", a, &b);      // 过滤空格与换行符

    lena = get_lenth(a);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储

    mul(A, b);
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

void mul(int A[], int b)
{
    int t = 0;
    for (int i = 0; i < lenA || t; i ++ )
    {
        if (i < lenA) t += A[i] * b;
        C[lenC ++] = t % 10;                            // 留下个位
        t /= 10;                                        // 进位信息
    }

    while (lenC > 1 && C[lenC - 1] == 0) lenC --;       // 去除前导0
    return ;
}