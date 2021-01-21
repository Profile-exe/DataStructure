#include <iostream>

struct Node
{
	int data;
	Node* next;
	Node(const int data) : data(data), next(nullptr) { }	// 생성시 data와 next 초기화
};

class List
{
private:
	Node* head;
	int length;
public:
	List() : head(nullptr), length(0) { }

	int size() const { return length; }

	bool empty() const { return (head == nullptr) ? true : false; }

	void push_back(const int data)
	{
		if (empty()) {	// 빈 경우 head 할당
			head = new Node(data);
			head->next = head;
			length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->next) {	// 리스트 순환
			if (pNode->next == head) {	// 마지막 노드인 경우 새로 할당
				pNode->next = new Node(data);
				pNode->next->next = head;
				break;
			}
		}
		length++;
	}
	// delete는 nullptr로 초기화해주지 않는다. 직접 nullptr로 초기화 필요
	void pop_back()
	{
		switch (size()) {
		case 0:
			std::cout << "빈 리스트 입니다." << '\n';
			return;
		case 1:	// head만 있는 경우
			delete head;
			head = nullptr;
			break;
		default:
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (pNode->next->next == head) {	// pNode->next가 마지막 노드인 경우 삭제
					delete pNode->next;
					pNode->next = head;
					break;
				}
			}
		}
		length--;
	}

	void insert(const int index, const int data)
	{
		if (index >= size()) {
			std::cout << "리스트 범위를 벗어났습니다." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// 빈 리스트면 head 생성
			head = new Node(data);
			head->next = head;
			break;
		default:
			if (!index) {	// 원형 연결리스트는 마지막 노드가 head를 가리키므로 newNode를 가리키게 설정
				auto* newNode = new Node(data);
				auto* lastNode = head;	// 마지막 노드를 구하여 새로운 head를 가리키게 해야함
				for (lastNode; lastNode->next != head; lastNode = lastNode->next);
				lastNode->next = newNode; // head가 될 newNode를 가리킨다.

				newNode->next = head;
				head = newNode;
				break;
			}
			for (auto* pNode = head; ; pNode = pNode->next) {
				auto i = 0;
				if (i++ + 1 == index) {	// pNode->next가 해당 인덱스 노드인 경우
					auto* newNode = new Node(data);
					newNode->next = pNode->next;
					pNode->next = newNode;
					break;
				}
			}
		}
		length++;
	}

	void erase(const int index)
	{
		if (index >= size()) {
			std::cout << "리스트 범위를 벗어났습니다." << '\n';
			return;
		}
		switch (size()) {
		case 0:		// 빈 리스트인 경우
			printf("빈 리스트 입니다.");
			return;
		case 1:		// head만 존재할 경우 delete 사용하므로 nullptr 대입
			delete head;
			head = nullptr;
			break;
		default:
			if (!index) {	// head를 지우는 경우 head->next를 head로 설정
				auto* temp = head->next;
				
				auto* lastNode = head;	// 마지막 노드를 구하여 새로운 head를 가리키게 해야함
				for (lastNode; lastNode->next != head; lastNode = lastNode->next);
				lastNode->next = temp; // head가 될 temp를 가리킨다.
				
				delete head;
				head = temp;
				break;
			}
			for (auto* pNode = head; ; pNode = pNode->next) {
				auto i = 0;
				if (i++ + 1 == index) {
					auto* temp = pNode->next->next;
					delete pNode->next;
					pNode->next = temp;
					break;
				}
			}
		}
		length--;
	}
};

int main(void)
{
	List list;
	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.push_back(3);
	list.push_back(7);
	list.push_back(2);

	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.pop_back();
	list.pop_back();

	std::cout << list.size() << '\n';

	list.insert(0, 2);
	list.erase(0);
	list.erase(0);

	std::cout << list.size() << '\n';
	return 0;
}
