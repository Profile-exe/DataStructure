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
	void (*reverse)();
} List;

List* list = NULL;	// ���� ���� ����

int _size() { return list->length; }

bool _empty() { return (list->head == NULL) ? true : false; }

void _push_back(const int data)
{
	if (list->empty()) {  // ����Ʈ�� �� ��� head ��� �Ҵ� head->next�� head�̴�.
		list->head = calloc(1, sizeof(Node));
		list->head->next = list->head;
		list->head->data = data;
		list->length++;
		return;
	}
	for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
		if (pNode->next == list->head) {	// ������ ����� �� ���� �Ҵ�
			// calloc�� ��������Ƿ� pNode->next->next == NULL
			pNode->next = calloc(1, sizeof(Node));
			pNode->next->next = list->head;
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
			if (pNode->next->next == list->head) {	// pNode->next�� ������ ����� ���
				free(pNode->next);
				pNode->next = list->head; // ������ ���� head�� ����Ų��.
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
		list->head->next = list->head;
		list->head->data = data;
		break;
	default:	// ��Ұ� 2�� �̻��� ���
		if (!index) {			// index == 0(head)�� ���
			Node* newNode = calloc(1, sizeof(Node));

			Node* lastNode = list->head;	// ������ ��尡 ���ο� head�� ����Ű�� �ؾ���
			// ������ node ���ϱ�
			for (lastNode; lastNode->next != list->head; lastNode = lastNode->next);
			lastNode->next = newNode;	// head�� �� newNode�� ����Ų��.

			newNode->next = list->head;
			newNode->data = data;
			list->head = newNode;
			break;
		}
		int i = 0;
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
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

void _erase(const int index)	// index�� 0(head)�� ��� ����!!!
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

			Node* lastNode = list->head;	// ������ ��尡 ���ο� head�� ����Ű�� �ؾ���
			// ������ node ���ϱ�
			for (lastNode; lastNode->next != list->head; lastNode = lastNode->next);
			lastNode->next = temp;	// head�� �� temp�� ����Ų��.

			free(list->head);
			list->head = temp;	// head->next�� head�� ����
			break;
		}
		int i = 0;
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
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

void _reverse()
{
	switch(list->size()) {
	case 0:
	case 1:
		break;
	case 2:
		list->head = list->head->next;
		break;
	default: {	// C���� ���� ������ ���̺��� ������� �ʴ� ������ �ذ��ϱ� ���� ����'{}'�� �߰���
		Node* front_lastNode = list->head; for (; front_lastNode->next->next != list->head; front_lastNode = front_lastNode->next);
		front_lastNode->next->next = front_lastNode;	// ���������� �ٷ� �� ��带 ����Ű���Ѵ�.

		Node* tempLast = front_lastNode->next;			// head�� ������ ��尡 �Ǿ���ϹǷ� ������ ��带 tempLast�� �����ϰ� ����Ű����

		while (list->head->next->next != list->head) {
			for (Node* pNode = list->head; ; pNode = pNode->next) {
				if (pNode->next == pNode->next->next->next) {
					pNode->next->next = pNode;
					break;
				}
			}
		}
		list->head->next = tempLast;	// head�� ������ ��尡 �Ǿ� head�� �� tempLast�� ����Ű�� �Ѵ�.
		list->head = tempLast;
	}
	}
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
	temp->reverse = _reverse;
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
	list->push_back(9);

	// list : 3 -> 6 -> 4 -> 9 -> 3 -> 6 -> ...
	list->reverse();
	// list : 9 -> 4 -> 6 -> 3 -> 9 -> 4 -> ...	

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