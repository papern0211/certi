#include <stdio.h>
#include <vector>

using namespace std;
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define N_MAX 100001
#define INF 987654321

struct RMQ {
	int n;
	vector<int> rangeMin;

	RMQ(vector<int>& array) {
		n = array.size();
		rangeMin.resize(4 * n);
		init(array, 0, n - 1, 1);
	}

	int init(vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];

		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = MIN(leftMin, rightMin);
	}

	int query(int left, int right, int nodeleft, int noderight, int node) {
		if (right < nodeleft || left > noderight)
			return INF;
		if (left <= nodeleft && noderight <= right)
			return rangeMin[node];

		int midnode = (nodeleft + noderight) / 2;
		int leftMin = query(left, right, nodeleft, midnode, 2 * node);
		int rightMin = query(left, right, midnode + 1, noderight, 2 * node + 1);
		return MIN(leftMin, rightMin);
	}

	int query(int left, int right) {
		return query(left, right, 0, n - 1, 1);
	}

	int update(int index, int newValue, int nodeleft, int noderight, int node) {
		if (index < nodeleft || index > noderight)
			return rangeMin[node];
		if (nodeleft == noderight)
			return rangeMin[node] = newValue;

		int midnode = (nodeleft + noderight) / 2;
		int leftMin = update(index, newValue, nodeleft, midnode, 2 * node);
		int rightMin = query(index, newValue, midnode + 1, noderight, 2 * node + 1);
		return rangeMin[node] = MIN(leftMin, rightMin);
	}

	int update(int index, int newValue) {
		return update(index, newValue, 0, n - 1, 1);
	}
};

vector<int> child[N_MAX];
int no2serial[N_MAX], serial2no[N_MAX];
int locInTrip[N_MAX], depth[N_MAX];
int nextSerial;

void traverse(int here, int d, vector<int>& trip) {
	serial2no[nextSerial] = here;
	no2serial[here] = nextSerial;
	nextSerial++;

	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	depth[here] = d;

	for (register int i = 0; i < (int)child[here].size(); ++i) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(no2serial[here]);
	}
	return;
}

void swap(int& a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int distance(RMQ* rmq, int a, int b) {
	int	a1 = locInTrip[a];
	int b1 = locInTrip[b];
	if (b1 < a1) swap(a1, b1);
	int q = rmq->query(a1, b1);
	return depth[a] + depth[b] - 2 * depth[serial2no[q]];
}



int main() {
	int tc;
	int N, Q;

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &tc);

	for (register int t = 1; t <= tc; ++t) {
		scanf("%d %d", &N, &Q);
		
		// 부모 자식 관계 완성
		for (register int n = 1; n < N; ++n) {
			int p;
			scanf("%d", &p);
			child[p].push_back(n);
		}

		// Traverse을 통해 배열 생성
		nextSerial = 0;
		vector<int> trip;
		traverse(0, 0, trip);

		// RMQ 생성
		RMQ rmq(trip);

		// depth 계산
		for (register int q = 0; q < Q; ++q) {
			int a, b;
			scanf("%d %d", &a, &b);
			printf("%d\n", distance(&rmq, a, b));
		}
	}

	return 0;
}