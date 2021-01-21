#include <stdio.h>
#include <stdlib.h>

typedef struct calc
{
	int a, b;
	int (*add) (const int a, const int b);
	int (*substract) (const int a, const int b);
	int (*multiple) (const int a, const int b);
	int (*divide) (const int a, const int b);
} Calculator;

int add(const int a, const int b) {	return a + b; }

int sub(const int a, const int b) {	return a - b; }

int mul(const int a, const int b) {	return a * b; }

int divide(const int a, const int b) { return a / b; }

Calculator calculator(const int a, const int b)
{
	Calculator* newNode = calloc(1, sizeof(Calculator));
	newNode->a = a;
	newNode->b = b;
	newNode->add = add;
	newNode->substract = sub;
	newNode->multiple = mul;
	newNode->divide = divide;
	return *newNode;
}

int main() {
	int A, B;
	scanf_s("%d %d", &A, &B);

	const Calculator calc = calculator(A, B);

	printf("Add : %d\n", calc.add(A, B));
	printf("Subtract : %d\n", calc.substract(A, B));
	printf("Multiple : %d\n", calc.multiple(A, B));
	printf("Divide : %d", calc.divide(A, B));
	return 0;
}