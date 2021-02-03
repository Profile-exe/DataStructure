#include <iostream>
#include <cmath>

template<typename T>
int is_compos(T n);

template<typename T>
void swap(T& a, T& b);

template<typename T>
class Queue
{
private:
	int head, tail;     // head : 첫번째 요소의 바로 앞 인덱스, tail : 마지막 요소의 인덱스
	T arr[10001];
public:
	Queue() : head(-1), tail(-1) { std::fill_n(arr, sizeof(arr) / sizeof(T), 0); }

	int size() const { return tail - head; }

	bool empty() const { return size() == 0; }

	void push(const T data) {
	    arr[++tail] = data;
	    for (auto i = head + 1; i < tail; i++) {    // 삽입 정렬 - 모든 소수를 앞으로
            for (auto j = i + 1; j <= tail; j++) {
                if (is_compos(arr[i]) && !is_compos(arr[j]))
                    swap(arr[i], arr[j]);
            }
	    }
		for (auto i = head + 1; i < tail; i++) {    // 삽입 정렬 - 소수끼리, 합성수끼리 정렬
			for (auto j = i + 1; j <= tail; j++) {
				switch(is_compos(arr[i]) + is_compos(arr[j])) {
				case 0: if (arr[i] > arr[j]) swap(arr[i], arr[j]); break;    // 소수끼리 정렬
				case 2: if (arr[i] > arr[j]) swap(arr[i], arr[j]); break;    // 합성수끼리 정렬
				}
			}
		}
	}

	T pop() {
		if (empty()) std::cout << "비어있음" << '\n';
		const auto temp = arr[++head];
		arr[head] = 0;
		return temp;
	}

	void print() const {    // 큐에 담겨진 요소 출력
	    for (auto i = head + 1; i <= tail; i++)
	        std::cout << arr[i] << ' ';
	}
};

Queue<int> queue;
int main()
{
	for (auto i = 100; i > 0; i--)
		queue.push(i);
	
    queue.print();
}

template<typename T>
int is_compos(T n) {
	if (n == 1) return 1;
	if (n == 2) return 0;
	for (auto i = 2; i <= sqrt(n); i++)
		if (n % i == 0) return 1;
	return 0;
}

template<typename T>
void swap(T& a, T& b) {
    auto temp = a;
    a = b;
    b = temp;
}