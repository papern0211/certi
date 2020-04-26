#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>

using namespace std;



#define MAX_DEPTH 10
#define MAX_BREADTH 1000


struct NODE {
	int key, priority, size;
	NODE *left, *right;
	
	NODE(): key(0), priority(rand()), size(1), left(0), right(0) {}
	NODE(int _key) : key(_key), priority(rand()), size(1), left(0), right(0) {}
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}

	void setRight(NODE* new_node) { right = new_node; calcSize(); }
	void setLeft(NODE* new_node) { left = new_node; calcSize(); }
}node_set[1000];

int idx_node = 0;
NODE* myAlloc(int key) {
	NODE* node = &node_set[idx_node++];
	node->key = key;

	return node;
}



typedef pair<NODE*, NODE*> NODE_PAIR;

NODE_PAIR split(NODE* root, int key) {
	if (root == NULL) return NODE_PAIR(NULL, NULL);

	// rootÀÇ ¿À¸¥ÂÊÀ» ÂÉ°µ´Ù
	if (root->key < key) {
		NODE_PAIR rs = split(root->right, key);
		root->setRight(rs.first);
		return NODE_PAIR(root, rs.second);
	}
	// rootÀÇ ¿ÞÂÊÀ» ÂÉ±ü´Ù
	NODE_PAIR ls = split(root->left, key);
	root->setLeft(ls.second);
	return NODE_PAIR(ls.first, root);
}

NODE* insert(NODE* root, NODE* node) {
	if (root == NULL) return node;
	if (root->priority < node->priority) {
		NODE_PAIR pr = split(root, node->key);
		node->setLeft(pr.first);
		node->setRight(pr.second);
		return node;
	}
	else if (root->key < node->key)
		root->setRight(insert(root->right, node));
	else
		root->setLeft(insert(root->left, node));
	return root;
}

// max(a) < min(b) ÀÏ¶§,
NODE* merge(NODE *a, NODE* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

NODE* erase(NODE* root, int key) {
	if (root == NULL) return NULL;
	if (root->key == key) {
		NODE* ret = merge(root->left, root->right);
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else 
		root->setRight(erase(root->right, key));
	return root;
}

typedef unsigned int uint;
typedef pair<int, NODE*> qNODE;


int max_idx = 1;
qNODE* queue[10000];
NODE* heap[10000];
int front = 0;
int rear = 0;

void print_node(NODE* root) {
	qNODE* qNode = new qNODE();
	qNode->first = 1;
	qNode->second = root;
	queue[front++] = qNode;
	heap[qNode->first] = root;

	while (front != rear) {
		qNode = queue[rear++];
		rear = rear % 10000;
		int idx = qNode->first;
		if (idx > max_idx) {
			max_idx = idx;
		}
		NODE* curr = qNode->second;
		heap[qNode->first] = curr;

		if (curr->left) {
			qNode = new qNODE();
			qNode->first = 2 * idx;
			qNode->second = curr->left;
			queue[front++] = qNode;
			front = front % 10000;
		}
		if (curr->right) {
			qNode = new qNODE();
			qNode->first = 2 * idx + 1;
			qNode->second = curr->right;
			queue[front++] = qNode;
			front = front % 10000;
		}

		int kk = 1;
	}
	
	int max_idx_tmp = max_idx;
	int maxDepth = 0;
	while (max_idx_tmp) {
		max_idx_tmp >>= 1;
		maxDepth++;
	}
	int num_space = 1 << (maxDepth-1);

	int curr_max = 2;
	for (register int i = 1; i <= max_idx; ++i) {
		if (i == curr_max) {
			curr_max <<= 1;
			num_space >>= 1;
			printf("\n");
		}

		if (heap[i]) {
			printf("%5d(%5d)*", heap[i]->key, heap[i]->priority);

			for (register int j = 0; j < num_space - 1; ++j) {
				printf("             ");
			}
		}
		else {
			for (register int j = 0; j < num_space; ++j) {
				printf("             ");
			}
		}
		
	}
}

void print_node2(NODE* root) {
	if (root == NULL) return;
	printf("%d(%d)\t", root->key, root->priority);
	print_node2(root->left);
	print_node2(root->right);
	return;
}


int main() {
	system("mode con cols=300 lines=50");
	int key[10] = { 23, 44, 12, 323, 22, 11, 2, 1 ,44, 55 };

	NODE* root = myAlloc(key[0]);
	for (register int i = 1; i < 10; ++i) 
		root = insert(root, myAlloc(key[i]));
	
	print_node(root);

	printf("\n\n\n");
	print_node2(root);





	return 0;
}