#include <iostream>

using namespace std;

template <typename T>
class vector {
private:
	int _size;
	int _capacity;
	T* _vc;

public:
	vector(int size = 1) {
		_size = 0;
		_capacity = size;
		_vc = new T[_capacity];
	}

	~vector() {
		delete[] _vc;
	}

	int size() {return _size;}
	int capacity() { return _capacity; };
	bool empty() { return !_size; }

	void resize(int size) {
		_capacity = size;
		T* _vct = new T[_capacity];
		for (register int i = 0; i < _size; ++i) {
			_vct[i] = _vc[i];
		}
		
		delete[] _vc;
		_vc = _vct;
	}

	void clear() {
		_size = 0;
		_capacity = 1;
		delete[] _vc;
		_vc = new T[_capacity];
	}

	void push_back(T v) {
		if (_size == _capacity)
			resize(2 * _capacity);
		_vc[_size++] = v;
	}
	
	void pop_back() {
		if (_size == 0)
			return;
		_vc[--_size] = 0;
	}

	void reverse() {
		for (register int i = 0; i < _size / 2; ++i) {
			T temp = _vc[i];
			_vc[i] = _vc[_size - 1 - i];
			_vc[_size - 1 - i] = temp;
		}
	}

	T& operator[](int i) {
		return _vc[i];
	}

	void operator=(vector<T> &newV) {
		_capacity = newV.capacity();
		_size = newV.size();
		delete[] _vc;
		_vc = new T[_capacity];
		for (register int i = 0; i < _size; ++i)
			_vc[i] = newV[i];
	}
};


int main() {
	vector<int> a;

	printf("%d %d\n", a.size(), a.capacity());

	a.push_back(1);
	a.push_back(100);

	for (register int i = 0; i < a.size(); ++i) {
		printf("%d\n", a[i]);
	}

	vector<int> b;
	b = a;
	for (register int i = 0; i < b.size(); ++i) {
		printf("%d\n", b[i]);
	}

	a.reverse();
	for (register int i = 0; i < a.size(); ++i) {
		printf("%d\n", a[i]);
	}


	return 0;
}