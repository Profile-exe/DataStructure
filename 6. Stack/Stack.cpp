#include <iostream>
#include <climits>

template <typename T>
class Stack
{
private:
	int _top;
	T arr[30];
public:
	Stack() : _top(-1) { std::fill_n(arr, sizeof(arr) / sizeof(arr[0]), 0); }

	bool empty() const { return _top == -1; }

	void push(const T data) { arr[++_top] = data; }

	T top() const { return empty() ? 0 : arr[_top]; }

	T pop() { if (empty()) std::cout << "ºñ¾îÀÖ½À´Ï´Ù." << '\n'; return empty() ? INT_MIN : arr[_top--]; }
};

int main()
{
	Stack<int> stack;

	stack.pop();

	std::cout << stack.empty() << '\n';

	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);

	std::cout << stack.empty() << '\n';

	std::cout << stack.pop() << '\n';
	std::cout << stack.pop() << '\n';
	std::cout << stack.pop() << '\n';

	return 0;
}
