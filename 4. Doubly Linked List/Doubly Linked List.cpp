#include <iostream>

enum class ForB { FRONT = 0, BACK = 1 };

struct Node
{
	int data;
	Node* prev;
	Node* next;
	Node(const int data) : data(data), prev(nullptr), next(nullptr) { }	// ������ data�� next �ʱ�ȭ
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

	void push_front(const int data)	// prev ��ȯ
	{
		if (empty()) {	// �� ��� head �Ҵ�
			head = new Node(data);
			front_length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->prev) {	// ����Ʈ ��ȯ
			if (pNode->prev == nullptr) {	// ������ ����� ��� ���� �Ҵ�
				pNode->prev = new Node(data);
				pNode->prev->next = pNode;	// �������� ����
				break;
			}
		}
		front_length++;
	}
	
	void push_back(const int data) // next ��ȯ
	{
		if (empty()) {	// �� ��� head �Ҵ�
			head = new Node(data);
			back_length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
			if (pNode->next == nullptr) {	// ������ ����� ��� ���� �Ҵ�
				pNode->next = new Node(data);
				pNode->next->prev = pNode;	// �������� ����
				break;
			}
		}
		back_length++;
	}
	// delete�� nullptr�� �ʱ�ȭ������ �ʴ´�. ���� nullptr�� �ʱ�ȭ �ʿ�

	void pop_front()
	{
		switch (front_length) {
		case 0:
			std::cout << "�� ����Ʈ �Դϴ�." << '\n';
			return;
		case 1:	// head�� �ִ� ���
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
			std::cout << "�� ����Ʈ �Դϴ�." << '\n';
			return;
		case 1:	// head�� �ִ� ���
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
			std::cout << "����Ʈ ������ ������ϴ�." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// �� ����Ʈ�� head ����
			head = new Node(data);
			front_length++;
			break;
		default:
			auto* newNode = new Node(data);	// ����� newNode ������ �� ���� �ű�
			if (!index) {	// head�� insert �ϴ� ��� newNode ���� ��  head�� ����
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
					if (i++ == index - 1) {	// pNode->prev�� �ش� �ε��� ����� ���
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
					if (i++ == index - 1) {	// pNode->next�� �ش� �ε��� ����� ���
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
			std::cout << "����Ʈ ������ ������ϴ�." << '\n';
			return;
		}
		switch (size()) {
		case 0:		// �� ����Ʈ�� ���
			printf("�� ����Ʈ �Դϴ�.");
			return;
		case 1:		// head�� ������ ��� delete ����ϹǷ� nullptr ����
			delete head;
			head = nullptr;
			front_length--;
			break;
		default:
			if (!index) {	// head�� ����� ��� head->next�� head�� ����
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
					if (i++ == index) {	// pNode�� �ش� �ε��� ����� ���
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
					if (i++ == index) {	// pNode�� �ش� �ε��� ����� ���
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