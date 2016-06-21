#include <iostream>
#include <vector>

using namespace std;

int MaxSubseqSum(vector<int> &ivet);

int main()
{
	int N;
	cin >> N;
	vector<int> ivet(N);

	for (auto &it : ivet)
		cin >> it;

	cout << MaxSubseqSum(ivet) << endl;

	return 0;
}

int MaxSubseqSum(vector<int> &ivet)
{
	int thisSum, maxSum;
	thisSum = maxSum = 0;
	for (auto it = ivet.begin(); it != ivet.end(); ++it)
	{
		thisSum += *it;
		if (thisSum > maxSum)
			maxSum = thisSum;
		else  if (thisSum < 0)
			thisSum = 0;

	}
	return maxSum;
}
