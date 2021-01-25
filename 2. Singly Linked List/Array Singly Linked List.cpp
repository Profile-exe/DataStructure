#include <iostream>

#define DATA 0
#define NEXT 1

class List	
{
private:
	int head[100][2];	// head�� ��ġ ��, ù��° ����� ��ġ�� head[0]���� �����ϰ� �����Ѵ�.
	int length;
public:
	List() : length(0) { }

	int size() const { return length; }

	bool empty() const { return (size() == 0) ? true : false; }

	void push_back(const int data)
	{
		if (empty()) {	// �� ��� head �Ҵ�
			head[0][DATA] = data;
			head[0][NEXT] = -1;
			length++;
			return;
		}
		auto empty_idx = 1;	// head�� �����ϰ� (0�� �ȵȴ�) �߰��� ��尡 �� �� �ε��� ���ϱ�
		for (; empty_idx < size(); empty_idx++)	// �� �ε����� erase, pop_back���� ���� �� NEXT�� -1�� �����Ͽ� �Ǻ��� �� �ֵ�����
			if (head[empty_idx][DATA] == -1 && head[empty_idx][NEXT] == -1) break;
		// break���� ����� empty�� ���� ����Ʈ�� �ٷ� ���� �ε����� �ȴ�.
		
		for (auto* pNode = head[0]; ; pNode = head[pNode[NEXT]]) {	// ����Ʈ ��ȯ
			if (pNode[NEXT] == -1) {	// ������ ����� ��� ���� �Ҵ�
				pNode[NEXT] = empty_idx;
				head[empty_idx][DATA] = data;
				head[empty_idx][NEXT] = -1;
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
		case 1:	// head�� �ִ� ���� data�� �������־���Ѵ�.
			head[0][DATA] = -1;
			head[0][NEXT] = -1;
			break;
		default:
			for (auto* pNode = head[0]; ; pNode = head[pNode[NEXT]]) {
				if (head[pNode[NEXT]][NEXT] == -1) {	// pNode->next (head[pNode[NEXT]])�� ������ ����� ��� ����
					head[pNode[NEXT]][DATA] = -1;		// DATA�� -1�� ����� ��������� ������ְ�
					pNode[NEXT] = -1;					// ������ ���´�.
					break;
				}
			}
		}
		length--;
	}

	void insert(const int index, const int data)
	{	// �� �ڸ��� ������ ���(index�� ��ġ�ߴ� ���)�� ��ġ��Ű�� ���ο� ��尡 index�ڸ����� ���ڸ��� �� ��带 ����Ű�� �Ѵ�.
		if (index >= size()) {
			std::cout << "����Ʈ ������ ������ϴ�." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// �� ����Ʈ�� head ����
			head[0][DATA] = data;
			head[0][NEXT] = -1;
			break;
		default:
			auto empty_idx = 1;	// head�� �����ϰ� (0�� �ȵȴ�) �߰��� ��尡 �� �� �ε��� ���ϱ�
			for (; empty_idx < size(); empty_idx++)	// �� �ε����� erase, pop_back���� ���� �� NEXT�� -1�� �����Ͽ� �Ǻ��� �� �ֵ�����
				if (head[empty_idx][DATA] == -1 && head[empty_idx][NEXT] == -1) break;
			// break���� ����� empty�� ���� ����Ʈ�� �ٷ� ���� �ε����� �ȴ�.

			if (!index) {	// head�� insert �� ��� head�� �Ű��ְ� head�ڸ� [0]�� ��带 �߰��Ѵ�.
				head[empty_idx][DATA] = head[0][DATA];
				head[empty_idx][NEXT] = head[0][NEXT];
				head[0][DATA] = data;
				head[0][NEXT] = empty_idx;
			}
			else {
				auto i = 0;
				auto* front_idx = head[0];	// �ش� index �ٷ� �� ��� ���ϱ�
				for (; i++ != index - 1; front_idx = head[front_idx[NEXT]]);

				const auto temp_next = front_idx[NEXT];	// index��° ��� ����
				front_idx[NEXT] = empty_idx;			// �߰��� ��带 ����Ų��.

				head[empty_idx][DATA] = data;
				head[empty_idx][NEXT] = temp_next;		// ������ index ��° ��� ��ġ�� ����Ų��.
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
		case 1:	// �� ���𿡵� ���������� head�� ��ġ(ù��° ����� ��ġ)�� head[0]�̴�. �׷��Ƿ� head[0][NEXT] = -1�̸� �ƹ��͵� ���� �Ұ�
			head[0][DATA] = -1;	// head�̹Ƿ� �����͵� �������ش�.
			head[0][NEXT] = -1;
			break;
		default:
			if (!index) {	// head�� ����� ��� head->next�� head�ڸ��� ������ ��
				head[0][DATA] = head[head[0][NEXT]][DATA];	// ������ DATA�� ���� ��������Ѵ�.
				head[0][NEXT] = head[head[0][NEXT]][NEXT];	// NEXT���� ��� ��� data�� head�� ���� ���� ����� data�� �����Ե�
			} else {
				auto i = 0;
				auto* front_idx = head[0];	// �ش� index �ٷ� �� ��� ���ϱ� -> ���� ��� : head[front_idx[NEXT]]
				for (; i++ != index - 1; front_idx = head[front_idx[NEXT]]);

				const auto temp_next = head[front_idx[NEXT]][NEXT];	// ������ ������ �ʱ� ���� ����
				head[front_idx[NEXT]][DATA] = -1;
				head[front_idx[NEXT]][NEXT] = -1;
				front_idx[NEXT] = temp_next;		// ���� ��带 ����
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
	list.push_back(5);

	std::cout << list.size() << '\n';
	std::cout << list.empty() << '\n';

	list.pop_back();
	list.pop_back();

	std::cout << list.size() << '\n';

	list.insert(1, 8);
	list.erase(0);
	list.erase(0);

	std::cout << list.size() << '\n';
	return 0;
}
