#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
int Look(int Dx, int Dy, int D, int R, int x, int y);
double Distance(int x, int y);
double Cos(int Dx, int Dy, int x, int y);
int main()
{
	int Dx, Dy, D, R, Num, X, Y,mark; double P[1000];
	int N = 1;
	mark = 0;
 	cin >> Dx >> Dy >> D >> R;
	cin >> Num;
    for (int i=Num;i > 0;i--)
	{
		cin >> X;
		cin >> Y;
		if (Look(Dx, Dy, D, R, X, Y)==1)
		{
			P[N] = Distance(X,Y);
			N++;
		}
	}
	for (int i = 0;i < N;i++)
	{
		for (int l = i;l < N;l++)
		{
			if (P[mark] > P[l])
			{
				mark = l;
			}
		}
		cout << mark << " ";
	}
}
int Look(int Dx,int Dy,int D,int R,int x,int y)
{
	int cos = Cos(Dx, Dy, x, y);
    if (Distance(x, y) < D&&(cos<R))
	{
		return 1;
	}
	return 0;
}
double Distance(int x, int y)
{
	return sqrt(x * x + y * y);
}
double Cos(int Dx, int Dy, int x, int y)
{
	if (x == 0&&y==0)
	{
		return 0;
	}
	if (x == 0)
	{
		return 90;
	}
	if (y == 0)
	{
		return 0;
	}
	double a = Distance(Dx, Dy);
	double b = Distance(x, y);
	double c = Distance(abs(Dx - x), abs(Dy - y));
	double bcos = acos(abs((a * a + b * b - c * c) / (2*a*b)) * 180);
	return bcos;
}