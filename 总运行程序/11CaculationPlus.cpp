#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef vector<int> poly;

const int mod = 1004535809;
const int N = 1 << 19;
const int bas = 100;

int omg[2][N], rev[N];
char op;

template<class T> inline T read()
{
	T x = 0, w = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar())
		if(c == '-')
			w = -w;
	for(; isdigit(c); c = getchar())
		x = x * 10 + c - '0';
	return x * w;
}

template<class T> inline T&read(T&x)
{
	return x = read<T>();
}
 

inline int add(int a,int b)
{
	return (a += b) >= mod ? a - mod : a;
}

inline int mul(int a,int b)
{
	return (int64)a * b % mod;
}

inline int fpow(int a,int b)
{
	int ans = 1;
	for(; b; b >>= 1, a = mul(a,a))
		if(b & 1)	ans = mul(ans, a);
	return ans;
}

void NTT(poly&a, int dir)
{
	int lim = a.size(), len = log2(lim);
	for(int i = 0; i < lim; ++ i)
	{
		int r = rev[i] >> (19 - len);
		if(i < r) swap(a[i], a[r]);
	}
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0; j < lim; j += i << 1)
			for(int k = 0; k < i; ++ k)
			{
			int t = mul(omg[dir][N / (i << 1) * k], a[j + i + k]);
			a[j + i + k] = add(a[j + k], mod - t), a[j + k] = add(a[j + k], t);
			}
	if(dir)
	{
		int ilim = fpow(lim, mod - 2);
		for(int i = 0; i < lim; ++ i)
			a[i] = mul(a[i], ilim);
	}
}

template<> poly read<poly>()
{
	static char s[N];
	scanf("%s", s);
	int len = strlen(s);
	poly ans;
	for(int i = len - 1; i >= 0; i -= 2)
	{
		int sum = 0;
		for(int j = max(i - 1, 0); j <= i; ++ j)
			sum = sum * 10 + s[j] - '0';
		ans.push_back(sum);
	}
	return ans;
}

void write(const poly&a)
{
	int n = a.size() - 1;
	printf("%d", a.back());
	for(int i = n - 1; i >= 0; -- i)
		printf("%02d", a[i]);
}
 
bool operator<(const poly&a,const poly&b)
{
	if(a.size() != b.size()) return a.size() < b.size();
	int n = a.size() - 1;
	for(int i = n; i >= 0; -- i)
		if(a[i] != b[i])
			return a[i] < b[i];
	return 0;
}

bool operator<=(const poly&a,const poly&b)
{
	if(a.size() != b.size()) return a.size() < b.size();
	int n = a.size() - 1;
	for(int i = n; i >= 0; -- i)
		if(a[i] != b[i])
			return a[i] < b[i];
	return 1;
}

bool operator>(const poly&a,const poly&b)
{
	if(a.size() != b.size()) return a.size() > b.size();
	int n = a.size() - 1;
	for(int i = n; i >= 0; -- i)
		if(a[i] != b[i])
			return a[i] > b[i];
	return 0;
}

bool operator>=(const poly&a,const poly&b)
{
	return a > b or a == b;
}
 
poly operator<<(poly a,int m)
{
	int n = a.size() - 1;
	a.resize(n + m + 1);
	for(int i = n + m; i >= m; -- i)
		a[i] = a[i - m];
	fill(a.begin(), a.begin() + m, 0);
	return a;
}

poly operator>>(poly a,int m)
{
	int n = a.size() - 1;
	for(int i = 0; i <= n - m; ++ i)
		a[i] = a[i + m];
	a.resize(n - m + 1);
	return a;
}
 
poly operator+(poly a,const poly&b)
{
	int n = a.size() - 1, m = b.size() - 1;
	if(n < m)
	{
		n = m;
		a.resize(n + 1);
	}
	for(int i = 0; i <= m; ++ i)	a[i] += b[i];
	for(int i = 0; i < n; ++ i)
		if(a[i] >= bas)
		{
			++ a[i + 1];
			a[i] -= bas;
		}
	if(a[n] >= bas)
	{
		a.push_back(1);
		a[n] -= bas;
	}
	return a;
}

poly operator-(poly a,const poly&b)
{
	int n = a.size() - 1, m = b.size() - 1;
	for(int i = 0; i <= m; ++ i)	a[i] -= b[i];
	for(int i = 0; i <= n; ++ i)
		if(a[i] < 0)
		{
			-- a[i + 1];
			a[i] += bas;
		}
	while(a.size() > 1 and !a.back())	a.pop_back();
	return a;
}

poly operator*(poly a,poly b)
{
	if(a == poly{0} or b == poly{0})	return poly{0};
	if(a.size() <= 20 or b.size() <= 20)
	{
		int n = a.size() - 1, m = b.size() - 1;
		a.resize(n + m + 1);
		for(int i = n; i >= 0; -- i)
		{
			for(int j = m; j >= 1; -- j)
				a[i + j] += a[i] * b[j];
			a[i] *= b[0];
		}
		for(int i = 0; i < n + m; ++ i)
			if(a[i] >= bas)
			{
				a[i + 1] += a[i] / bas;
				a[i] %= bas;
			}	
		if(a[n + m] >= bas)
		{
			a.push_back(a[n + m] / bas);
			a[n + m] %= bas;
		}		
		return a;
	}
	int n = a.size() - 1 + b.size() - 1, lim = 1 << (int)ceil(log2(n + 1));
	a.resize(lim);
	NTT(a, 0);
	b.resize(lim);
	NTT(b, 0);
	for(int i = 0; i < lim; ++ i)
		a[i] = mul(a[i], b[i]);
	NTT(a, 1);
	a.resize(n + 1);
	for(int i = 0; i < n; ++ i)
		if(a[i] >= bas)
		{
			a[i + 1] += a[i] / bas;
			a[i] %= bas;
		}	
	if(a[n] >= bas)
	{
		a.push_back(a[n] / bas);
		a[n] %= bas;
	}
	return a;
}

poly operator~(poly a)
{
	int n = a.size();
	if(n == 1)
	{
		poly b;
		for(int x = bas * bas / a[0]; x; x /= bas)
			b.push_back(x % bas);
		return b;
	}
	if(n == 2)
	{
		poly b;
		for(int x = bas * bas * bas * bas / (a[0] + a[1] * bas); x; x /= bas)
			b.push_back(x % bas);
		return b;
	}
	int k = (n + 2) / 2;
	poly b = ~poly(a.end() - k, a.end());
	b = (poly{2} * b << (n - k)) - (a * b * b >> 2 * k);
	return b;
}

poly operator/(poly a,poly b)
{
	if(a < b) return poly{0};
	int n = a.size(), m = b.size();
	if(n > 2 * m)
	{
		a = a << (n - 2 * m);
		b = b << (n - 2 * m);
		n = a.size();
		m = b.size();
	}
	poly c = a * ~b >> 2 * m;
	if((c + poly{1}) * b <= a)
	{
		for(poly t = a - b * c; t >= b; t = t - b)
			c = c + poly{1};
	}
	else if(b * c > a)
	{
		for(poly t = b * c - a + b - poly{1}; t >= b; t = t - b)
			c = c - poly{1};
	}
	return c;
}

void init()
{
	omg[0][0] = 1;
	omg[0][1] = fpow(3, (mod - 1) / N);
	omg[1][0] = 1;
	omg[1][1] = fpow(omg[0][1], mod - 2);
	rev[0] = 0;
	rev[1] = 1 << 18;
	for(int i = 2; i < N; ++ i)
	{
		omg[0][i] = mul(omg[0][i - 1], omg[0][1]);
		omg[1][i] = mul(omg[1][i - 1], omg[1][1]);
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << 18;
	}
}

int main()
{
	printf("High precision divided high precision\nPlease input two high precision number and one option(+-*/):\ne.g. 123 * 123\n");
	init();
	poly a = read<poly>();
	cin >> op;
	poly b = read<poly>();
	if(op == '+')
	{
		write(a + b);
		cout << endl;
	}
	else if(op == '-')
	{
		if(a >= b)	write(a - b);
		else
		{
			cout << "-";
			write(b - a);
		}	
		cout << endl;
	}
	else if(op == '*')
	{
		write(a * b);
		cout << endl;
	}
	else if(op == '/')
	{
		write(a / b);
		cout << endl;
		write(a - a / b * b);
		cout << endl;
	}
	system("pause");
	return 0;
}