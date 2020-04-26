#include <iostream>

using namespace std;
#define BUFF_SIZE 10000
#define ALPHABET 26


inline int char2int(char c) {
	return (int)(c - 'a');
}

int order = 0;

struct Trie {
	bool terminal;
	int v;
	Trie* child[ALPHABET];

	Trie() : terminal(false), v(-1) {
		for (register int i = 0; i < ALPHABET; ++i)
			child[i] = 0;
	}

	~Trie() {
		for (register int i = 0; i < ALPHABET; ++i) {
			if (child[i])
				delete child[i];
		}
	}

	void insert(char *key) {
		if (*key == 0) {
			terminal = true;
			v = order;
			order++;
		}
		else {
			int next = char2int(*key);
			if (child[next] == 0)
				child[next] = new Trie();
			child[next]->insert(key + 1);
		}
	}

	Trie* find(char *key) {
		if (*key == 0) return this;
		int next = char2int(*key);
		if (child[next] == 0)
			return 0;
		return child[next]->find(key + 1);

	}
};

int main() {
	char str[5][100] = { "absfsdf",
					"dafdafe",
					"iloveyou",
					"hungry",
					"baby" };

	Trie *root = new Trie();
	for (register int i = 0; i < 5; ++i) {
		root->insert(str[i]);
	}

	printf("%d\n", root->find(str[1])->v);
	return 0;
}