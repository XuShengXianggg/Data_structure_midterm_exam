#include <stdio.h>
#include <stdlib.h>

#define N 100010

char a[N], b[N];                // 存储待运算数字
int lena, lenb;

int A[N], B[N], C[N];           // C用于存储答案
int lenA, lenB, lenC;

int get_lenth(char s[]);        // 求字符数组长度
int cmp(int A[], int B[]);      // 比较待运算数字大小
int max(int a, int b);          // 求较大值
void swap(int* a, int* b);      // 交换数值
void sub(int *A, int *B);     // 减法

int main()
{
    printf("High precision minus high precision\nPlease input two high precision number:\ne.g. 123 123\n");
    scanf(" %s %s", a, b);      // 过滤空格与换行符
    
    lena = get_lenth(a), lenb = get_lenth(b);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储
    for(int j = lenb - 1; j >= 0; j --) B[lenB ++] = (b[j] - '0');

    if(!cmp(A, B))              // 如果A比B小，那么转变成-(B-A)
    {
        printf("-");
        for(int i = 0; i < max(lenA, lenB); i ++)
            swap(&A[i], &B[i]);
        swap(&lenA, &lenB);
    }
    sub(A, B);
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

int cmp(int A[], int B[])
{
	if(lenA != lenB)	return ((lenA > lenB) ? 1 : 0);
    for(int i = lenA - 1; i >= 0; i --)
    {
        if(A[i] != B[i])	return ((A[i] > B[i]) ? 1 : 0);
    }
    return 1;
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

void sub(int *A, int *B)
{
    int t = 0;
    for (int i = 0; i < lenA; i ++)
    {
        t = A[i] - t;                           // 处理进位
        if(i < lenB) t -= B[i];                 // 对位进行计算
        C[lenC ++] = (t + 10) % 10;             // 计算本位的数
        if(t < 0)   t = 1;                      // 确定是否进位
        else    t = 0;
    }

    while (lenC > 1 && C[lenC - 1] == 0) lenC --;           // 去除前导0
    return ;
}