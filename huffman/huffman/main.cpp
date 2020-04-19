#include <stdio.h>

#define MAX_SIZE 10000
#define NUM_CHAR 27

char buffer[MAX_SIZE];


struct TREE {
	int freq;
	char c;
	TREE* left;
	TREE* right;
}a[2 * MAX_SIZE];

int idx_tree = 0;
TREE* myAlloc(int freq) {
	TREE* tree = &a[idx_tree++];
	tree->freq = freq;
	tree->c = 0;
	tree->left = 0;
	tree->right = 0;
	return tree;
}


// 우선순위 큐
class PRIORITY_QUEUE {
public:
	int heapSize;
	TREE* heap[MAX_SIZE];
	
	PRIORITY_QUEUE() {
		heapSize = 0;
		for (register int i = 0; i < MAX_SIZE; ++i)
			heap[i] = 0;
	}

	void push(TREE* tree) {

		heap[heapSize] = tree;

		int current = heapSize;
		while (current > 0 && heap[current]->freq < heap[(current - 1) / 2]->freq) {
			TREE *temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}
		heapSize = heapSize + 1;
	}

	TREE* pop() {
		TREE* ret = heap[0];
		heapSize = heapSize - 1;

		heap[0] = heap[heapSize];

		int current = 0;
		while (current * 2 + 1 < heapSize) {
			int child;
			if (current * 2 + 2 == heapSize) {
				child = current * 2 + 1;
			}
			else {
				child = heap[current * 2 + 1]->freq < heap[current * 2 + 2]->freq ? current * 2 + 1 : current * 2 + 2;
			}

			if (heap[current]->freq < heap[child]->freq) {
				break;
			}

			TREE* temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;

			current = child;
		}
		return ret;
	}
};


PRIORITY_QUEUE pq;

TREE* makeTree() {

	while (pq.heapSize > 1) {
		TREE* tree1 = pq.pop();
		TREE* tree2 = pq.pop();

		TREE* new_tree = myAlloc(tree1->freq + tree2->freq);
		new_tree->left = tree1;
		new_tree->right = tree2;
		new_tree->c = '$';

		pq.push(new_tree);
	}
	return pq.pop();
}


unsigned int codes[NUM_CHAR];
int codes_size[NUM_CHAR];
int char2idx(char c) {
	if (c == ' ')
		return NUM_CHAR - 1;
	else
		return (int)(c - 'a');
}

unsigned int genBitCode(unsigned int code[], int idx) {
	unsigned int bitCode = 0;

	for (register int i = 0; i < idx; ++i) {
		bitCode <<= 1;
		bitCode |= code[i] & 1;
	}
	return bitCode;
}


void make_codes(TREE* tree, unsigned int code[], int idx) {
	if (!tree)
		return;

	char c = tree->c;
	if (c != '$') {
		codes[char2idx(c)] = genBitCode(code, idx);
		codes_size[char2idx(c)] = idx;
	}
		

	code[idx] = 0;
	make_codes(tree->left, code, idx + 1);
	code[idx] = 1;
	make_codes(tree->right, code, idx + 1);
	return;
}


int encoding(char str[]) {
	int idx = 0;
	int pos = 0;
	for (register int i = 0; str[i] != 0; ++i) {
		char c = str[i];
		int cidx = char2idx(c);
		unsigned int bitcode = codes[cidx];
		int bitSize = codes_size[cidx];

		for (register int j = bitSize - 1; j >= 0; --j) {
			buffer[idx] |= ((bitcode >> j) & 1) << pos;
			pos++;
			if (pos == 8) {
				idx++;
				pos = 0;
			}
		}
	}
	return idx;
}



int decoding(TREE* root, char result[]) {
	int idx = 0;
	int pos = 0;
	bool init = true;
	TREE* curr;
	int cnt = 0;

	while (1) {
		int bit = (buffer[idx] >> pos) & 1;
		if (init) {
			if (bit == 0)
				break;
			else {
				curr = root;
				init = false;
			}
		}
		else {
			if (bit == 0)
				curr = curr->left;
			else
				curr = curr->right;

			if (curr->c != '$') {
				result[cnt++] = curr->c;
				init = true;
			}
		}
		pos++;
		if (pos == 8) {
			idx++;
			pos = 0;
		}
	}

	return cnt;

}

void print_code() {
	for (register int i = 0; i < NUM_CHAR - 1; ++i) {
		printf("[%c]: ", i + 'a');
		unsigned int v = codes[i];
		int buffer[100];
		int cnt = 0;
		while (v > 0) {
			buffer[cnt++] = v & 1;
			v >>= 1;
		}

		for (register int j = cnt - 1; j >= 0; --j) {
			printf("%d", buffer[j]);
		}
		printf("\n");
	}

	printf("[ ]: ");
	unsigned int v = codes[NUM_CHAR - 1];
	int buffer[100];
	int cnt = 0;
	while (v > 0) {
		buffer[cnt++] = v & 1;
		v >>= 1;
	}

	for (register int j = cnt - 1; j >= 0; --j) {
		printf("%d", buffer[j]);
	}
	printf("\n");


}


int main() {
	int value[NUM_CHAR] = { 1, 23, 44, 552,22,
		223 ,22, 233, 44, 11,
		1, 23, 33, 441, 55,
		88, 139, 98, 22, 33,
		2, 26, 66, 99, 90,
		24, 900 };

	for (register int i = 0; i < NUM_CHAR; ++i) {
		TREE* tree = myAlloc(value[i]);
		if (i + 1 == NUM_CHAR)
			tree->c = ' ';
		else
			tree->c = (char)(i + 'a');
		pq.push(tree);
	}


	TREE *root = makeTree();
	unsigned int code[100] = { 0, };
	code[0] = 1;
	make_codes(root, code, 1);
	print_code();

	//int a = 1;

	//for (register int i = 0; i < NUM_CHAR; ++i) {
	//	TREE* tree = pq.pop();
	//	printf("%c, ", tree->c);
	//}
	char test[100] = "i am a king what are you doing i am very hungry";
	//char test[100] = "abc ";

	int bufidx = encoding(test);
	for (register int i = 0; i <= bufidx; ++i) {
		for (register int j = 0; j < 8; ++j) {
			printf("%d", (buffer[i] >> j) & 1);
		}
	}
	printf("\n");

	char test_result[100] = { 0, };
	int cnt = decoding(root, test_result);

	printf("test_resut: %s", test_result);

	return 0; 
}