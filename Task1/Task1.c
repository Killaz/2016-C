#include <stdio.h>
#include <stdlib.h>

typedef long long lld;

int len(int i)
{
	int ans = 0;
	while (i != 0)
		i /= 10, ans++;
	return ans;
}

int main(void)
{
	lld **a;
	int i, j, k, n, x1, x2, y1, y2, nowLen, mxLen;
	scanf("%d", &n);
	a = (lld **)malloc(n * sizeof(lld *));
	for (i = 0; i < n; i++)
		a[i] = (lld *)malloc(n * sizeof(lld));
	while (1)
	{
		scanf("%d", &x1);
		if (x1 == 0)
			break;
		scanf("%d%d%d", &y1, &x2, &y2);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				a[i][j] = (i + 1) * (j + 1);
		mxLen = len(a[x2 - 1][y2 - 1]);
		for (i = y1 - 1; i < y2; i++, printf("\n"))
			for (j = x1 - 1; j < x2; j++)
			{
				nowLen = printf("%I64d", a[i][j]);
				for (k = nowLen - 1; k < mxLen; k++)
				printf(" ");
			}
	}
	for (i = 0; i < n; i++) {
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
}
