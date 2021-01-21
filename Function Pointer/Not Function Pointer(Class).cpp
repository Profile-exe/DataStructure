#include <iostream>

class Calculator
{
private:
	int a, b;
public:
	Calculator(const int a, const int b) : a{a}, b{b} { }
	int add() const { return a + b; }
	int substract() const { return a - b; }
	int multiple() const { return a * b; }
	int divide() const { return a / b; }
};

void main() {
	int A, B;
	scanf_s("%d %d", &A, &B);

	auto* calc = new Calculator{ A, B };

	printf("Add : %d\n", calc->add());
	printf("Subtract : %d\n", calc->substract());
	printf("Multiple : %d\n", calc->multiple());
	printf("Divide : %d", calc->divide());
	delete calc;
}