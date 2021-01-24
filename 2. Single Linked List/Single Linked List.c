#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node {	// Node ����
	int data;
	struct _Node* next;
} Node;

typedef struct _List {	// List ����
	Node* head;
	int length;
	int (*size)();
	bool (*empty)();
	void (*push_back)(int);
	void (*pop_back)();
	void (*insert)(int, int);
	void (*erase)(int);
} List;

List* list = NULL;	// ���� ���� ����

int _size() { return list->length; }

bool _empty() { return (list->head == NULL) ? true : false; }

void _push_back(const int data)
{
	if (list->empty()) {  // ����Ʈ�� �� ��� head ��� �Ҵ�
		list->head = calloc(1, sizeof(Node));
		list->head->data = data;
		list->length++;
		return;
	}
	for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
		if (pNode->next == NULL) {	// ������ ����� �� ���� �Ҵ�
			// calloc�� ��������Ƿ� pNode->next->next == NULL
			pNode->next = calloc(1, sizeof(Node));
			pNode->next->data = data;
			break;
		}
	}
	list->length++;
}

void _pop_back()
{
	switch (list->size()) {
	case 0:		// �� ����Ʈ�� ���
		printf("�� ����Ʈ �Դϴ�.");
		return;
	case 1:		// head�� ������ ���
		free(list->head);
		list->head = NULL;	// free()�� ��������Ƿ� NULL ����
		break;
	default:	// ��Ұ� 2�� �̻��� ���
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
			if (pNode->next->next == NULL) {	// pNode->next�� ������ ����� ���
				free(pNode->next);
				pNode->next = NULL;	// free()�� ��������Ƿ� NULL ����
				break;
			}
		}
	}
	list->length--;
}

void _insert(const int index, const int data)
{
	if (index >= list->size()) {
		printf("����Ʈ ������ ������ϴ�.");
		return;
	}
	switch (list->size()) {
	case 0:		// �� ����Ʈ�� ��� head �Ҵ�
		list->head = calloc(1, sizeof(Node));
		list->head->data = data;
		break;
	default:	// ��Ұ� 2�� �̻��� ���
		if (!index) {			// index == 0(head)�� ���
			Node* newNode = calloc(1, sizeof(Node));
			newNode->next = list->head;
			newNode->data = data;
			list->head = newNode;
			break;
		}
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
			int i = 0;
			if (i++ + 1 == index) {	// ���� ���(pNode->next)�� �ش� index�� ����� ���
				Node* newNode = calloc(1, sizeof(Node));
				newNode->next = pNode->next;
				newNode->data = data;
				pNode->next = newNode;
				break;
			}
		}
	}
	list->length++;
}

void _erase(const int index)	// index�� 0(head)�� ��� ���!!!
{
	if (index >= list->size()) {
		printf("����Ʈ ������ ������ϴ�.");
		return;
	}
	switch (list->size()) {
	case 0:		// �� ����Ʈ�� ���
		printf("�� ����Ʈ �Դϴ�.");
		return;
	case 1:		// head�� ������ ��� head�� ����
		free(list->head);
		list->head = NULL;	// free()�� ��������Ƿ� NULL ����
		break;
	default:	// ��Ұ� 2�� �̻��� ���
		if (!index) {			// index == 0(head)�� ���
			Node* temp = list->head->next;
			free(list->head);
			list->head = temp;	// head->next�� head�� ����
			break;
		}
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
			int i = 0;
			if (i++ + 1 == index) {	// ���� ���(pNode->next)�� �ش� index�� ����� ���
				Node* temp = pNode->next->next;
				free(pNode->next);
				pNode->next = temp;
				break;
			}
		}
	}
	list->length--;
}

List* initialize() {	// ���� �Ҵ����� �ʱ�ȭ �� �� ����� ��ȯ
	List* temp = calloc(1, sizeof(List));
	temp->length = 0;
	temp->size = _size;
	temp->empty = _empty;
	temp->push_back = _push_back;
	temp->pop_back = _pop_back;
	temp->insert = _insert;
	temp->erase = _erase;
	return temp;
}

int main(void)
{
	list = initialize();	// �Լ� ȣ���� �������� �Ұ��� �ϹǷ� main���� ����
	printf("%d\n", list->size());
	printf("%d\n", list->empty());
	
	list->push_back(3);
	list->push_back(6);
	list->push_back(4);
	
	printf("%d\n", list->size());
	printf("%d\n", list->empty());
	
	list->pop_back();
	list->pop_back();
	
	printf("%d\n", list->size());
	
	list->insert(0, 2);
	list->erase(0);
	list->erase(0);
	
	printf("%d\n", list->size());
	free(list);
	return 0;
}