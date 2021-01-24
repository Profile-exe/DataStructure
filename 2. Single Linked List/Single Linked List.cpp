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
			length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->next) {	// 리스트 순환
			if (pNode->next == nullptr) {	// 마지막 노드인 경우 새로 할당
				pNode->next = new Node(data);
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
				if (pNode->next->next == nullptr) {	// pNode->next가 마지막 노드인 경우 삭제
					delete pNode->next;
					pNode->next = nullptr;
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
			break;
		default:
			if (!index) {	// head에 insert 하는 경우 newNode 생성 후  head로 변경
				auto* newNode = new Node(data);
				newNode->next = head;
				head = newNode;
				break;
			}
			auto i = 0;
			for (auto* pNode = head; ; pNode = pNode->next) {
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
				delete head;
				head = temp;
				break;
			}
			auto i = 0;
			for (auto* pNode = head; ; pNode = pNode->next) {
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
