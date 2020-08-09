#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INT_MAX = numeric_limits<int>::max();

struct RMQ {
	int n;
	vector<int> range_min;
	RMQ(const vector<int>& arr) {
		n = arr.size();
		range_min = vector<int>(4 * n, 0);
		init(arr, 0, n-1, 1);
	}

	int init(const vector<int>& arr, int left, int right, int node) {
		if (left == right)
			return range_min[node] = arr[left];
		int mid = (left + right) / 2;
		int left_min = init(arr, left, mid, 2 * node);
		int right_min = init(arr, mid + 1, right, 2 * node + 1);
		return range_min[node] = min(left_min, right_min);
	}

	int query(int left, int right, int node, int node_left, int node_right) {
		if (node_left > right || node_right < left)
			return INT_MAX;
		if (node_left >= left && node_right <= right)
			return range_min[node];
		int node_mid = (node_left + node_right) / 2;
		int left_min = query(left, right, 2 * node, node_left, node_mid);
		int right_min = query(left, right, 2 * node + 1, node_mid + 1, node_right);
		return min(left_min, right_min);
	}

	// 외부에서 호출하기 위한
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int update(int index, int new_value, int node, int node_left, int node_right) {
		if (index < node_left || index > node_right)
			return range_min[node];
		if (node_left == node_right)
			return range_min[node] = new_value;
		int node_mid = (node_left + node_right) / 2;
		int left_min = update(index, new_value, 2 * node, node_left, node_mid);
		int right_min = update(index, new_value, 2 * node + 1, node_mid + 1, node_right);
		return range_min[node] = min(left_min, right_min);
	}

	// 외부에서 호출하기 위한
	int update(int index, int new_value) {
		return update(index, new_value, 1, 0, n - 1);
	}
	
};




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);


	return 0;
}