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
	int length;
public:
	List() : head(nullptr), length(0) { }

	int size() const { return length; }

	bool empty() const { return size() == 0 ? true : false; }

	void push_back(const int data) // next 순환
	{
		if (empty()) {	// 빈 경우 head 할당
			head = new Node(data);
			head->prev = head->next = head;
			length++;
			return;
		}
		auto* newNode = new Node(data);
		head->prev->next = newNode;
		newNode->prev = head->prev;
		head->prev = newNode;
		newNode->next = head;
		length++;
	}
	
	void pop_back()
	{
		switch (length) {
		case 0:
			std::cout << "빈 리스트 입니다." << '\n';
			return;
		case 1:	// head만 있는 경우
			delete head;
			head = nullptr;
			break;
		default:	// 마지막 노드는 head->prev
			auto* temp = head->prev;
			head->prev->prev->next = head;
			head->prev = head->prev->prev;
			delete temp;
			break;
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
			length++;
			break;
		default:
			auto* newNode = new Node(data);	// 공통된 newNode 선언을 맨 위로 옮김
			if (!index) {	// head에 insert 하는 경우 newNode 생성 후  head로 변경
				head->prev->next = newNode;
				newNode->prev = head->prev;
				
				head->prev = newNode;
				newNode->next = head;
				
				head = newNode;
				length++;
				break;
			}
			auto i = 0;
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (i++ == index - 1) {	// pNode->next가 해당 인덱스 노드인 경우
					newNode->next = pNode->next;
					newNode->prev = pNode;
					if (pNode->next != nullptr)	// 해당 인덱스가 nullptr이 아니라면
						pNode->next->prev = newNode;
					pNode->next = newNode;
					length++;
					break;
				}
			}
		}
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
			length--;
			break;
		default:
			if (!index) {	// head를 지우는 경우 head->next를 head로 설정
				auto* temp = head->next;
				head->prev->next = head->next;
				delete head;
				head = temp;
				length--;
				break;
			}
			auto i = 0;
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (i++ == index) {	// pNode가 해당 인덱스 노드인 경우
					pNode->prev->next = pNode->next;
					if (pNode->next != nullptr)	// pNode가 마지막 노드가 아닌경우
						pNode->next->prev = pNode->prev;
					delete pNode;
					length--;
					break;
				}
			}
		}
	}
};

int main(void)
{
	List list;
	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.pop_back();

	std::cout << list.size() << '\n';

	list.insert(1, 8);
	list.erase(0);
	list.erase(2);

	std::cout << list.size() << '\n';
	return 0;
}