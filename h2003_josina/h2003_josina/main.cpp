#include <stdio.h>

int main(void){
	int test_case;
	int T;
	int N;
	int tmp;
	int expect;

	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case){
		expect = 0;
		scanf("%d", &N);
		for (register int i = 0; i < N; ++i) {
			scanf("%d", &tmp);
			if (tmp != i + 1)
				expect++;
		}
			
		printf("#%d %0.6lf\n", test_case, (double)expect);
	}
	

	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}