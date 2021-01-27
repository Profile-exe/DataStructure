#include <iostream>
#include <climits>

class Stack
{
private:
	int top;
	int array[20];
public:
	Stack() : top(-1) { }

	bool empty() const { return top == -1 ? true : false; }

	void push(const int data) { array[++top] = data; }

	int pop() { if (empty()) std::cout << "비어있습니다." << '\n'; return empty() ? INT_MIN : array[top--]; }
};

int main(void)
{
	Stack stack;
	
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