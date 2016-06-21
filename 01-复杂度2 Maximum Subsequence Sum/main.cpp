#include <iostream>
using namespace std;

void MaxSubseqSum(int *, int, int*);

int main()
{
	int N;
	cin >> N;

	int *a = new int(N);

	for (int i = 0; i < N; ++i)
		cin >> a[i];

	int b[3];

	MaxSubseqSum(a, N, b);

	cout << b[0] << ' ' << b[1] << ' ' << b[2];

	return 0;

}

void MaxSubseqSum(int *a, int N, int *b)
{
	int thisSum, maxSum;
	b[0] = -1;
	b[1] = b[2] = 0;
	thisSum = maxSum = 0;

	int begin = 0;

	for (int i = 0; i < N; ++i)
	{
		thisSum += a[i];

		if (thisSum > b[0])
		{
			b[0] = thisSum;
			b[1] = a[begin];
			b[2] = a[i];
		}

		else if (thisSum < 0)
		{
			thisSum = 0;
			begin = i + 1;
		}

	}

	if (b[0] == -1)

		b[0] = 0, b[1] = a[0], b[2] = a[N - 1];

	return;
}
