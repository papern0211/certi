#include <stdio.h>
#include <time.h>
#include <stdlib.h>



//int main() {
//
//	// 시간 측정
//	clock_t start, end;
//	long long result;
//	int sum = 0;
//
//	start = clock();
//	for (register int i = 0; i < 1000; ++i)
//		for (register int j = 0; j < 1000; ++j)
//			sum++;
//
//	end = clock();
//	result = end - start;
//
//	printf("%lldms \n", result);
//
//
//	// Random 함수 작성
//	srand(time(NULL));
//	for (register int i = 0; i < 10; ++i)
//		printf("%d ", rand() % 100);
//
//	return 0;
//}


// ########### bit shift in char buffer
// #1. naive
void shift_right(unsigned char *arr, int size, int shift) {
	unsigned char carry = 0;
	while (shift--) {
		for (register int i = size - 1; i >= 0; --i) {
			unsigned char next = (arr[i] & 1) ? 0x80 : 0;
			arr[i] = carry | arr[i] >> 1;
			carry = next;
		}
	}
}

// #2. one shot way (but we have to fix the shift size)
// for example, shift is 3,
void shift_right3(unsigned char *arr, int size) {
	unsigned char bits1 = 0;
	unsigned char bits2 = 0;

	for (register int i = size - 1; i >= 0; --i) {
		bits2 = arr[i] & 0x07;
		arr[i] >>= 3;
		arr[i] |= bits1 << 5;
		bits1 = bits2;
	}
}

void print_buf(unsigned char *arr, int size) {
	for (register int i = size - 1; i >= 0; --i) {
		for (register int j = 7; j >= 0; --j) {
			printf("%d", (arr[i] >> j) & 1);
		}
		printf(" ");
	}
	printf("\n\n");
}


void copy_buffer(unsigned char *dst, unsigned char *src, int size) {
	for (register int i = 0; i < size; ++i)
		dst[i] = src[i];
}



int main() {
	unsigned char buf[10] = { 0, 233, 2, 3, 0, 100, 12, 50, 22 ,178 };
	unsigned char buf2[10];
	clock_t start, end;

	//1. original
	print_buf(buf, 10);

	//2. naive
	copy_buffer(buf2, buf, 10);
	start = clock();
	shift_right(buf2, 10, 3);
	end = clock();
	print_buf(buf2, 10);
	printf("elapsed time : %lldms\n", end - start);

	// 3. one-shot
	copy_buffer(buf2, buf, 10);
	start = clock();
	shift_right3(buf2, 10);
	end = clock();
	print_buf(buf2, 10);
	printf("elapsed time : %lldms\n", end - start);

}


