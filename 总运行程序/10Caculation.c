#include <stdio.h>
#include <stdlib.h>

#define N 100010

char op;

char a[N], b[N];                // 存储待运算数字
int lena, lenb;

int A[N], B[N], C[N], D[N];           // C用于存储答案
int lenA, lenB, lenC, lenD;

int get_lenth(char s[]);        // 求字符数组长度
int cmp(int A[], int B[]);      // 比较待运算数字大小
int max(int a, int b);          // 求较大值
void swap(int* a, int* b);      // 交换数值
void add(int *A, int *B);       // 加法
void sub(int *A, int *B);       // 减法
void mul(int *A, int *B);       // 乘法
int geq(int *a, int *b, int digit, int len);
void div(int A[], int B[]);

int main()
{
    printf("High precision divided high precision\nPlease input two high precision number and one option(+-*/):\ne.g. 123 * 123\n");
    scanf(" %s %c %s", a, &op, b);      // 过滤空格与换行符
    
    lena = get_lenth(a), lenb = get_lenth(b);

    for(int i = lena - 1; i >= 0; i --) A[lenA ++] = (a[i] - '0');      // 倒序存储
    for(int j = lenb - 1; j >= 0; j --) B[lenB ++] = (b[j] - '0');

    if(op == '+')
    {
        if(lenA < lenB)                 // 如果A的位数比B少，那么交换A和B的值
        {
            for(int i = 0; i < max(lenA, lenB); i ++)
                swap(&A[i], &B[i]);
            swap(&lenA, &lenB);
        }

        add(A, B);
        for(int i = lenC - 1; i >= 0; i --) printf("%d",C[i]);
        printf("\n");
    }
    else if(op == '-')
    {
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
    }
    else if(op == '*')
    {
        if(lenA < lenB)
        {
            for(int i = 0; i < max(lenA, lenB); i ++)
                swap(&A[i], &B[i]);
            swap(&lenA, &lenB);
        }

        mul(A, B);
        for(int i = lenC - 1; i >= 0; i --) printf("%d",C[i]);
        printf("\n");
    }
    else if(op == '/')
    {
        if(!cmp(A, B))
        {
            printf("0\n%s\n", a);
        }
        else
        {
            div(A, B);
            for(int i = lenC - 1; i >= 0; i --) printf("%d",C[i]);
            printf("\n");
            for(int i = lenD - 1; i >= 0; i --) printf("%d",D[i]);
            printf("\n");
        }
    }
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

// geq()用于判断被除数以下标digit为最低位，是否可以再减去除数而保持非负
// 此后对于商的每一位，不断调用 geq()，并在成立的时候用高精度减法从余数中减去除数
// 被除数 a 以下标 digit 为最低位，是否可以再减去除数b而保持非负
// len 是除数 b 的长度，避免反复计算
int geq(int *a, int *b, int digit, int len)
{
    // 有可能被除数剩余的部分比除数长，这个情况下最多多出 1 位，故如此判断即可
    if (a[digit + len] != 0) return 1;
    // 从高位到低位，逐位比较
    for(int i = len - 1; i >= 0; --i)
    {
        if(a[digit + i] > b[i]) return 1;
        if(a[digit + i] < b[i]) return 0;
    }
    // 相等的情形下也是可行的
    return 1;
}

void div(int A[], int B[])
{
    int la, lb, len = lenA + lenB + 1;
    for (la = len - 1; la > 0; -- la)
        if(A[la - 1] != 0)      break;
    for (lb = len - 1; lb > 0; -- lb)
        if(B[lb - 1] != 0)      break;
    if (lb == 0) 
    {
        // 除数不能为零
        printf("something wrong!\n");
        return;
    }
    // c 是商
    // d 是被除数的剩余部分，算法结束后自然成为余数
    for (int i = 0; i < la; ++ i) D[i] = A[i];
    for (int i = la - lb; i >= 0; -- i) 
    {
        // 计算商的第 i 位
        while(geq(D, B, i, lb))
        {
            // 若可以减，则减
            // 这一段是一个高精度减法
            for (int j = 0; j < lb; ++ j)
            {
                
                D[i + j] -= B[j];
                if(D[i + j] < 0) 
                {
                    D[i + j + 1] -= 1;
                    D[i + j] += 10;
                }
            }
            // 使商的这一位增加 1
            C[i] += 1;
            // 返回循环开头，重新检查
        }
    }
    lenC = lenA + lenB + 1;
    while (lenC > 1 && C[lenC - 1] == 0) lenC --;
    lenD = lenA + lenB + 1;
    while (lenD > 1 && D[lenD - 1] == 0) lenD --;
}
