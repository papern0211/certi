#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

# define ALPHABET 26

int mstrlen(const char *key) {
	register int i;
	for (i = 0; key[i] != 0; ++i);
	return i;
}


int char2int(const char c) {
	return (int)(c - 'A');
}


struct Trie {
	int first;
	int terminal;
	Trie* child[ALPHABET];

	Trie() : first(-1), terminal(-1) {
		for (register int i = 0; i < ALPHABET; ++i)
			child[i] = 0;
	}

	~Trie() {
		for (register int i = 0; i < ALPHABET; ++i) {
			if (child[i])
				delete child[i];
		}
	}

	Trie* find(const char *key) {
		if (*key == 0) return this;
		int next = char2int(*key);
		if (child[next] == 0) return 0;
		return child[next]->find(key + 1);
	}
	
	void insert(const char *key, int id) {
		if (first == -1) first = id;
		if (*key == 0) {terminal = id;return;}
		int next = char2int(*key);
		if (child[next] == 0)
			child[next] = new Trie();
		child[next]->insert(key + 1, id);
	}

	int type(const char *key, int id) {
		if (*key == 0) return 0;
		if (first == id) return 1;
		int next = char2int(*key);
		return 1 + child[next]->type(key + 1, id);
	}
};


int countNumber(Trie* root, const char*key) {
	Trie* node = root->find(key);
	if (node == 0 || node->terminal == -1) 
		return mstrlen(key);
	return root->type(key, node->terminal);
}


int main() {
	int tc, N, M, freq;
	char buf[11];

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	
	scanf("%d", &tc);
	
	for (register int t = 1; t <= tc; ++t) {
	
		vector<pair<int, string> > input;
		scanf("%d %d", &N, &M);
		for (register int n = 0; n < N; ++n) {
			scanf("%s %d", buf, &freq);
			input.push_back(make_pair(-freq, buf));
		}

		sort(input.begin(), input.end());
	
		Trie* root = new Trie();
		for (register int n = 0; n < N; ++n) {
			root->insert(input[n].second.c_str(), n);
		}
		root->first = -1;

		int ret = M - 1; //add # of space
		for (register int m = 0; m < M; ++m) {
			scanf("%s", buf);
			ret += countNumber(root, buf);
		}
		printf("%d\n", ret);
		delete root;
	}

	return 0;
}