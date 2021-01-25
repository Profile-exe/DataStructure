#include <iostream>

enum class ForB { FRONT = 0, BACK = 1 };

struct Node
{
	int data;
	Node* prev;
	Node* next;
	Node(const int data) : data(data), prev(nullptr), next(nullptr) { }	// 생성시 data와 next 초기화
};

class List
{
private:
	Node* head;
	int front_length, back_length;
public:
	List() : head(nullptr), front_length(0), back_length(0) { }

	int size() const { return front_length + back_length; }

	bool empty() const { return size() == 0 ? true : false; }

	void push_front(const int data)	// prev 순환
	{
		if (empty()) {	// 빈 경우 head 할당
			head = new Node(data);
			front_length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->prev) {	// 리스트 순환
			if (pNode->prev == nullptr) {	// 마지막 노드인 경우 새로 할당
				pNode->prev = new Node(data);
				pNode->prev->next = pNode;	// 양쪽으로 연결
				break;
			}
		}
		front_length++;
	}
	
	void push_back(const int data) // next 순환
	{
		if (empty()) {	// 빈 경우 head 할당
			head = new Node(data);
			back_length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->next) {	// 리스트 순환
			if (pNode->next == nullptr) {	// 마지막 노드인 경우 새로 할당
				pNode->next = new Node(data);
				pNode->next->prev = pNode;	// 양쪽으로 연결
				break;
			}
		}
		back_length++;
	}
	// delete는 nullptr로 초기화해주지 않는다. 직접 nullptr로 초기화 필요

	void pop_front()
	{
		switch (front_length) {
		case 0:
			std::cout << "빈 리스트 입니다." << '\n';
			return;
		case 1:	// head만 있는 경우
			delete head;
			head = nullptr;
			break;
		default:
			for (auto* pNode = head; ; pNode = pNode->prev) {
				if (pNode->prev == nullptr) {
					pNode->next->prev = pNode->prev;
					delete pNode;
					break;
				}
			}
		}
		front_length--;
	}
	
	void pop_back()
	{
		switch (back_length) {
		case 0:
			std::cout << "빈 리스트 입니다." << '\n';
			return;
		case 1:	// head만 있는 경우
			delete head;
			head = nullptr;
			break;
		default:
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (pNode->next == nullptr) {
					pNode->prev->next = pNode->next;
					delete pNode;
					break;
				}
			}
		}
		back_length--;
	}

	void insert(const int index, const int data, const ForB option)
	{
		if (index >= size()) {
			std::cout << "리스트 범위를 벗어났습니다." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// 빈 리스트면 head 생성
			head = new Node(data);
			front_length++;
			break;
		default:
			auto* newNode = new Node(data);	// 공통된 newNode 선언을 맨 위로 옮김
			if (!index) {	// head에 insert 하는 경우 newNode 생성 후  head로 변경
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
				front_length++;
				break;
			}
			auto i = 0;
			switch (option) {
			case ForB::FRONT:
				for (auto* pNode = head; ; pNode = pNode->prev) {
					if (i++ == index - 1) {	// pNode->prev가 해당 인덱스 노드인 경우
						newNode->prev = pNode->prev;
						newNode->next = pNode;
						pNode->prev->next = newNode;
						pNode->prev = newNode;
						break;
					}
				}
				front_length++;
				break;
			case ForB::BACK:
				for (auto* pNode = head; ; pNode = pNode->next) {
					if (i++ == index - 1) {	// pNode->next가 해당 인덱스 노드인 경우
						newNode->next = pNode->next;
						newNode->prev = pNode;
						pNode->next->prev = newNode;
						pNode->next = newNode;
						break;
					}
				}
				back_length++;
				break;
			}
		}
	}

	void erase(const int index, const ForB option)
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
			front_length--;
			break;
		default:
			if (!index) {	// head를 지우는 경우 head->next를 head로 설정
				auto* temp = head->next;
				delete head;
				head = temp;
				front_length--;
				break;
			}
			auto i = 0;
			switch (option) {
			case ForB::FRONT:
				for (auto* pNode = head; ; pNode = pNode->next) {
					if (i++ == index) {	// pNode가 해당 인덱스 노드인 경우
						pNode->prev->next = pNode->next;
						if (pNode->next != nullptr)
							pNode->next->prev = pNode->prev;
						delete pNode;
						front_length--;
						break;
					}
				}
				break;
			case ForB::BACK:
				for (auto* pNode = head; ; pNode = pNode->prev) {
					if (i++ == index) {	// pNode가 해당 인덱스 노드인 경우
						pNode->next->prev = pNode->prev;
						if (pNode->next != nullptr)
							pNode->prev->next = pNode->next;
						delete pNode;
						back_length--;
						break;
					}
				}
				break;
			}
		}
	}
};

int main(void)
{
	List list;
	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.push_front(1);
	list.push_front(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.pop_back();
	list.pop_front();

	std::cout << list.size() << '\n';

	list.insert(1, 8, ForB::BACK);
	list.erase(0, ForB::FRONT);
	list.erase(2, ForB::FRONT);

	std::cout << list.size() << '\n';
	return 0;
}