#include <stdio.h>
#include <stdlib.h>

#define N 100010
typedef long long ll;

char a[N];
int lena;

ll b, r;
int A[N], C[N], tmp[N];           // C用于存储答案
int lenA, lenC;

int get_lenth(char s[]);        // 求字符数组长度
void div(int *A, ll b);     // 除法

int main()
{
    printf("High precision divided low precision\nPlease input one high precision number and one low precision number:\ne.g. 123 123\n");
    scanf(" %s %lld", a, &b);      // 过滤空格与换行符

    lena = get_lenth(a);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储

    div(A, b);

    for(int i = lenC - 1; i >= 0; i --) printf("%d",C[i]);
    printf("\n%lld\n", r);
    system("pause");
    return 0;
}

int get_lenth(char s[])
{
    int len = 0;
    for(int i = 0; s[i] != '\0'; i ++)  len ++;
    return len;
}

void div(int *A, ll b)
{
    r = 0;
    for(int i = lenA - 1; i >= 0; i --)
    {
        r = r * 10 + A[i];              // 计算当前位
        C[lenC ++] = r / b;             // 用商作为当前结果
        r %= b;                         // 余数乘10加入到下一位的运算中
    }
    // 此时答案为正序，倒转为逆序，方便下一步去除前导0
    for(int i = 0; i < lenC; i ++)  tmp[i] = C[i];
    for(int i = 0; i < lenC; i ++)  C[i] = tmp[lenC - 1 - i];

    
    while (lenC > 1 && C[lenC - 1] == 0) lenC --;                // 去除前导0
    return ;
}