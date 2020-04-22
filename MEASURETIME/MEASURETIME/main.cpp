#include <iostream>
#include <vector>

using namespace std;
int arr[50001];

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		int ret = 0;
		pos++;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int value) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += value;
			pos += (pos & -pos);
		}
	}
};

long long count_with_FenwickTree(int arr[], int N) {
	FenwickTree tree(1000000);

	long long ret = 0;
	for (register int i = 0; i < N; ++i) {
		ret += tree.sum(999999) - tree.sum(arr[i]);
		tree.add(arr[i], 1);
	}
	return ret;

}

long long count_with_mergeSort(int arr[], int left, int right) {
	if (left == right) return 0;
	int mid = (left + right) / 2;
	long long ret = count_with_mergeSort(arr, left, mid) + count_with_mergeSort(arr, mid + 1, right);

	int N = right - left + 1;
	int* temp = new int[N];

	int i = left;
	int j = mid + 1;
	int k = 0;

	while (i <= mid || j <= right) {
		if (i <= mid && (j > right || arr[i] <= arr[j]))
			temp[k++] = arr[i++];
		else {
			ret += mid - i + 1;
			temp[k++] = arr[j++];
		}
	}

	for (register int n = 0; n < N; ++n)
		arr[left + n] = temp[n];
	
	delete[] temp;

	return ret;
}


int main() {
	int tc, N;

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &tc);
	for (int t = 1; t <= tc; ++t) {
		scanf("%d", &N);
		for (int n = 0; n < N; ++n)
			scanf("%d", arr + n);

		long long ret1 = count_with_FenwickTree(arr, N);
		long long ret2 = count_with_mergeSort(arr, 0, N - 1);

		if (ret1 == ret2)
			printf("%lld\n", ret1);
		else {
			printf("%lld, %lld: it's different!\n", ret1, ret2);
			break;
		}
	}
	return 0;

}