#include <iostream>

struct Node
{
	int data;
	Node* next;
	Node(const int data) : data(data), next(nullptr) { }	// ������ data�� next �ʱ�ȭ
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
		if (empty()) {	// �� ��� head �Ҵ�
			head = new Node(data);
			head->next = head;
			length++;
			return;
		}
		for (auto* pNode = head; ; pNode = pNode->next) {	// ����Ʈ ��ȯ
			if (pNode->next == head) {	// ������ ����� ��� ���� �Ҵ�
				pNode->next = new Node(data);
				pNode->next->next = head;
				break;
			}
		}
		length++;
	}
	// delete�� nullptr�� �ʱ�ȭ������ �ʴ´�. ���� nullptr�� �ʱ�ȭ �ʿ�
	void pop_back()
	{
		switch (size()) {
		case 0:
			std::cout << "�� ����Ʈ �Դϴ�." << '\n';
			return;
		case 1:	// head�� �ִ� ���
			delete head;
			head = nullptr;
			break;
		default:
			for (auto* pNode = head; ; pNode = pNode->next) {
				if (pNode->next->next == head) {	// pNode->next�� ������ ����� ��� ����
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
			std::cout << "����Ʈ ������ ������ϴ�." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// �� ����Ʈ�� head ����
			head = new Node(data);
			head->next = head;
			break;
		default:
			if (!index) {	// ���� ���Ḯ��Ʈ�� ������ ��尡 head�� ����Ű�Ƿ� newNode�� ����Ű�� ����
				auto* newNode = new Node(data);
				auto* lastNode = head;	// ������ ��带 ���Ͽ� ���ο� head�� ����Ű�� �ؾ���
				for (lastNode; lastNode->next != head; lastNode = lastNode->next);
				lastNode->next = newNode; // head�� �� newNode�� ����Ų��.

				newNode->next = head;
				head = newNode;
				break;
			}
			for (auto* pNode = head; ; pNode = pNode->next) {
				auto i = 0;
				if (i++ + 1 == index) {	// pNode->next�� �ش� �ε��� ����� ���
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
			break;
		default:
			if (!index) {	// head�� ����� ��� head->next�� head�� ����
				auto* temp = head->next;
				
				auto* lastNode = head;	// ������ ��带 ���Ͽ� ���ο� head�� ����Ű�� �ؾ���
				for (lastNode; lastNode->next != head; lastNode = lastNode->next);
				lastNode->next = temp; // head�� �� temp�� ����Ų��.
				
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
