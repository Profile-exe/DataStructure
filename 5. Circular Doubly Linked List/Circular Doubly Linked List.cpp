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
	int length;
public:
	List() : head(nullptr), length(0) { }

	int size() const { return length; }

	bool empty() const { return size() == 0 ? true : false; }

	void push_back(const int data) // next ��ȯ
	{
		if (empty()) {	// �� ��� head �Ҵ�
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
			std::cout << "�� ����Ʈ �Դϴ�." << '\n';
			return;
		case 1:	// head�� �ִ� ���
			delete head;
			head = nullptr;
			break;
		default:	// ������ ���� head->prev
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
			std::cout << "����Ʈ ������ ������ϴ�." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// �� ����Ʈ�� head ����
			head = new Node(data);
			length++;
			break;
		default:
			auto* newNode = new Node(data);	// ����� newNode ������ �� ���� �ű�
			if (!index) {	// head�� insert �ϴ� ��� newNode ���� ��  head�� ����
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
				if (i++ == index - 1) {	// pNode->next�� �ش� �ε��� ����� ���
					newNode->next = pNode->next;
					newNode->prev = pNode;
					if (pNode->next != nullptr)	// �ش� �ε����� nullptr�� �ƴ϶��
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
			length--;
			break;
		default:
			if (!index) {	// head�� ����� ��� head->next�� head�� ����
				auto* temp = head->next;
				head->prev->next = head->next;
				delete head;
				head = temp;
				length--;
				break;
			}
			auto i = 0;
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (i++ == index) {	// pNode�� �ش� �ε��� ����� ���
					pNode->prev->next = pNode->next;
					if (pNode->next != nullptr)	// pNode�� ������ ��尡 �ƴѰ��
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