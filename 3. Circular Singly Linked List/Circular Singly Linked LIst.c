#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node {	// Node 구조
	int data;
	struct _Node* next;
} Node;

typedef struct _List {	// List 구조
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

List* list = NULL;	// 전역 변수 선언

int _size() { return list->length; }

bool _empty() { return (list->head == NULL) ? true : false; }

void _push_back(const int data)
{
	if (list->empty()) {  // 리스트가 빈 경우 head 노드 할당 head->next는 head이다.
		list->head = calloc(1, sizeof(Node));
		list->head->next = list->head;
		list->head->data = data;
		list->length++;
		return;
	}
	for (Node* pNode = list->head; ; pNode = pNode->next) {	// 리스트 순환
		if (pNode->next == list->head) {	// 마지막 노드일 때 새로 할당
			// calloc을 사용했으므로 pNode->next->next == NULL
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
	case 0:		// 빈 리스트인 경우
		printf("빈 리스트 입니다.");
		return;
	case 1:		// head만 존재할 경우
		free(list->head);
		list->head = NULL;	// free()를 사용했으므로 NULL 대입
		break;
	default:	// 요소가 2개 이상인 경우
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// 리스트 순환
			if (pNode->next->next == list->head) {	// pNode->next가 마지막 노드인 경우
				free(pNode->next);
				pNode->next = list->head; // 마지막 노드는 head를 가리킨다.
				break;
			}
		}
	}
	list->length--;
}

void _insert(const int index, const int data)
{
	if (index >= list->size()) {
		printf("리스트 범위를 벗어났습니다.");
		return;
	}
	switch (list->size()) {
	case 0:		// 빈 리스트인 경우 head 할당
		list->head = calloc(1, sizeof(Node));
		list->head->next = list->head;
		list->head->data = data;
		break;
	default:	// 요소가 2개 이상인 경우
		if (!index) {			// index == 0(head)인 경우
			Node* newNode = calloc(1, sizeof(Node));

			Node* lastNode = list->head;	// 마지막 노드가 새로운 head를 가리키게 해야함
			// 마지막 node 구하기
			for (lastNode; lastNode->next != list->head; lastNode = lastNode->next);
			lastNode->next = newNode;	// head가 될 newNode를 가리킨다.

			newNode->next = list->head;
			newNode->data = data;
			list->head = newNode;
			break;
		}
		int i = 0;
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// 리스트 순환
			if (i++ + 1 == index) {	// 다음 노드(pNode->next)가 해당 index의 노드인 경우
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

void _erase(const int index)	// index가 0(head)인 경우 고려!!!
{
	if (index >= list->size()) {
		printf("리스트 범위를 벗어났습니다.");
		return;
	}
	switch (list->size()) {
	case 0:		// 빈 리스트인 경우
		printf("빈 리스트 입니다.");
		return;
	case 1:		// head만 존재할 경우 head만 지움
		free(list->head);
		list->head = NULL;	// free()를 사용했으므로 NULL 대입
		break;
	default:	// 요소가 2개 이상인 경우
		if (!index) {			// index == 0(head)인 경우
			Node* temp = list->head->next;

			Node* lastNode = list->head;	// 마지막 노드가 새로운 head를 가리키게 해야함
			// 마지막 node 구하기
			for (lastNode; lastNode->next != list->head; lastNode = lastNode->next);
			lastNode->next = temp;	// head가 될 temp를 가리킨다.

			free(list->head);
			list->head = temp;	// head->next를 head로 변경
			break;
		}
		int i = 0;
		for (Node* pNode = list->head; ; pNode = pNode->next) {	// 리스트 순환
			if (i++ + 1 == index) {	// 다음 노드(pNode->next)가 해당 index의 노드인 경우
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
	default: {	// C언어에서 변수 선언이 레이블에 적용되지 않는 문제를 해결하기 위해 블럭'{}'을 추가함
		Node* front_lastNode = list->head; for (; front_lastNode->next->next != list->head; front_lastNode = front_lastNode->next);
		front_lastNode->next->next = front_lastNode;	// 마지막노드는 바로 전 노드를 가리키게한다.

		Node* tempLast = front_lastNode->next;			// head가 마지막 노드가 되어야하므로 마지막 노드를 tempLast에 저장하고 가리키게함

		while (list->head->next->next != list->head) {
			for (Node* pNode = list->head; ; pNode = pNode->next) {
				if (pNode->next == pNode->next->next->next) {
					pNode->next->next = pNode;
					break;
				}
			}
		}
		list->head->next = tempLast;	// head가 마지막 노드가 되어 head가 될 tempLast를 가리키게 한다.
		list->head = tempLast;
	}
	}
}

List* initialize() {	// 동적 할당으로 초기화 후 값 복사로 반환
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
	list = initialize();	// 함수 호출은 전역에서 불가능 하므로 main에서 수행

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