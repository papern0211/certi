#define MAX_PICTURE_SIZE 1000
#define MAX_PIECE_SIZE 100
#define MAXN 1500
#define MAX_TABLE 4096
#define HORIZONTAL 0
#define VERTICAL 1
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

extern bool setPicture(int id, int x, int y);

struct PICTURE {
	int id;
	int x;
	int y;
	bool used;
	bool enable[4];
}pics[MAXN];


struct PIECE {
	int pid;
	int x;
	int y;
	int hash;
	int dir;
	PIECE* next;
}a[4 * MAXN];


int idx_pieces;
PIECE* hash_table[2][MAX_TABLE];

int idx_stack;
PICTURE* stack[MAXN];

PIECE* myAlloc(int pid, int x, int y, int dir) {
	PIECE* piece = &a[idx_pieces++];
	piece->pid = pid;
	piece->x = x;
	piece->y = y;
	piece->dir = dir;
	piece->next = 0;
	return piece;
}

int myHash(char pictures[MAX_PIECE_SIZE][MAX_PIECE_SIZE], int x, int y, int dir){
	int hash = 0;
	int ex, ey;

	if (dir == HORIZONTAL) {
		ex = x + 3;
		ey = y + 2;
	}
	else {
		ex = x + 2;
		ey = y + 3;
	}

	for (register int c = x; c < ex; c++) {
		for (register int r = y; r < ey; r++) {
			hash += (int)pictures[r][c];
			hash <<= 4;
		}
	}
	return hash % MAX_TABLE;
}

void init() {
	idx_pieces = 0;
	idx_stack = 0;

	for (register int i = 0; i < MAX_TABLE; ++i) {
		hash_table[0][i] = 0;
		hash_table[1][i] = 0;
	}
}


void insertPiece(PIECE* piece,  int hash, int dir) {
	if (hash_table[dir][hash] == 0) {
		hash_table[dir][hash] = piece;
	}
	else {
		piece->next = hash_table[dir][hash];
		hash_table[dir][hash] = piece; 
	}
}


void mergePictures(int N, int M, int K, char pictures[MAXN][MAX_PIECE_SIZE][MAX_PIECE_SIZE]) {

	// 초기화
	init();

	// PIC hash 
	int hash;
	for (register int n = 0; n < N; ++n) {
		pics[n].id = n;
		pics[n].used = false;
		for (register int i = 0; i < 4; ++i) {
			pics[n].enable[i] = true;
		}

		hash = myHash(pictures[n], 0, 0, HORIZONTAL);
		PIECE* piece = myAlloc(n, 0, 0, HORIZONTAL);
		insertPiece(piece, hash, HORIZONTAL);

		hash = myHash(pictures[n], 0, M-2, HORIZONTAL);
		piece = myAlloc(n, 0, M-2, HORIZONTAL);
		insertPiece(piece, hash, HORIZONTAL);

		hash = myHash(pictures[n], 0, 0, VERTICAL);
		piece = myAlloc(n, 0, 0, VERTICAL);
		insertPiece(piece, hash, VERTICAL);
			
		hash = myHash(pictures[n], M-2, 0, VERTICAL);
		piece = myAlloc(n, M-2, 0, VERTICAL);
		insertPiece(piece, hash, VERTICAL);
	}


	// 배치
	pics[0].x = pics[1].y = 0;
	pics[0].enable[LEFT] = pics[0].enable[UP] = false;
	pics[0].used = false;
	stack[idx_stack++] = &pics[0];

	while (idx_stack > 0) {
		PICTURE *pic = stack[--idx_stack]; 
		int id = pic->id;
		int x0 = pic->x;
		int y0 = pic->y;
		int hash;

		// left right check
		for (register int x = 0; x < M - 1; ++x) {
			hash = myHash(pictures[id], x, 0, VERTICAL);

			register PIECE* curr = hash_table[VERTICAL][hash];
			while (curr != 0) {
				int id_next = curr->pid;
				if (!pics[id_next].used) {
					if (pics[id].enable[LEFT] && setPicture(id_next, x0 + x - M + 2, y0)) {
						pics[id].enable[LEFT] = false;
						pics[id_next].enable[RIGHT] = false;
						pics[id_next].used = true;
						pics[id_next].x = x0 + x - M + 2;
						pics[id_next].y = y0;
						stack[idx_stack++] = &pics[id_next];
						continue;
					}
					else if (pics[id].enable[RIGHT] && setPicture(id_next, x0 + x, y0)) {
						pics[id].enable[RIGHT] = false;
						pics[id_next].enable[LEFT] = false;
						pics[id_next].used = true;
						pics[id_next].x = x0 + x;
						pics[id_next].y = y0;
						stack[idx_stack++] = &pics[id_next];
					}
				}
				curr = curr->next;
			}
			
			if (!pic->enable[LEFT] && !pic->enable[RIGHT])
				break;
		}

		// up down check
		for (register int y = 0; y < M - 1; ++y) {
			hash = myHash(pictures[id], 0, y, HORIZONTAL);

			register PIECE* curr = hash_table[HORIZONTAL][hash];
			while (curr != 0) {
				int id_next = curr->pid;
				if (!pics[id_next].used) {
					if (pics[id].enable[UP] && setPicture(id_next, x0, y0 + y - M + 2)) {
						pics[id].enable[UP] = false;
						pics[id_next].enable[DOWN] = false;
						pics[id_next].used = true;
						pics[id_next].x = x0;
						pics[id_next].y = y0 + y - M + 2;
						stack[idx_stack++] = &pics[id_next];
						continue;
					}
					else if (pics[id].enable[DOWN] && setPicture(id_next, x0, y0 + y)) {
						pics[id].enable[DOWN] = false;
						pics[id_next].enable[UP] = false;
						pics[id_next].used = true;
						pics[id_next].x = x0;
						pics[id_next].y = y0 + y;
						stack[idx_stack++] = &pics[id_next];
					}
				}
				curr = curr->next;
			}

			if (!pic->enable[UP] && !pic->enable[DOWN])
				break;
		}
	}

	
	return;
	

}
