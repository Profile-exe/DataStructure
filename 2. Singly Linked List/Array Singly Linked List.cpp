#include <iostream>

#define DATA 0
#define NEXT 1

class List	
{
private:
	int head[100][2];	// head의 위치 즉, 첫번째 노드의 위치는 head[0]으로 고정하고 구현한다.
	int length;
public:
	List() : length(0) { }

	int size() const { return length; }

	bool empty() const { return (size() == 0) ? true : false; }

	void push_back(const int data)
	{
		if (empty()) {	// 빈 경우 head 할당
			head[0][DATA] = data;
			head[0][NEXT] = -1;
			length++;
			return;
		}
		auto empty_idx = 1;	// head를 제외하고 (0은 안된다) 추가될 노드가 들어갈 빈 인덱스 구하기
		for (; empty_idx < size(); empty_idx++)	// 빈 인덱스는 erase, pop_back에서 지울 때 NEXT를 -1로 설정하여 판별할 수 있도록함
			if (head[empty_idx][DATA] == -1 && head[empty_idx][NEXT] == -1) break;
		// break없이 벗어나면 empty는 꽉찬 리스트의 바로 다음 인덱스가 된다.
		
		for (auto* pNode = head[0]; ; pNode = head[pNode[NEXT]]) {	// 리스트 순환
			if (pNode[NEXT] == -1) {	// 마지막 노드인 경우 새로 할당
				pNode[NEXT] = empty_idx;
				head[empty_idx][DATA] = data;
				head[empty_idx][NEXT] = -1;
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
		case 1:	// head만 있는 경우는 data도 삭제해주어야한다.
			head[0][DATA] = -1;
			head[0][NEXT] = -1;
			break;
		default:
			for (auto* pNode = head[0]; ; pNode = head[pNode[NEXT]]) {
				if (head[pNode[NEXT]][NEXT] == -1) {	// pNode->next (head[pNode[NEXT]])가 마지막 노드인 경우 삭제
					head[pNode[NEXT]][DATA] = -1;		// DATA를 -1로 만들어 빈공간으로 만들어주고
					pNode[NEXT] = -1;					// 연결을 끊는다.
					break;
				}
			}
		}
		length--;
	}

	void insert(const int index, const int data)
	{	// 빈 자리에 원래의 노드(index에 위치했던 노드)를 위치시키고 새로운 노드가 index자리에서 빈자리에 들어간 노드를 가리키게 한다.
		if (index >= size()) {
			std::cout << "리스트 범위를 벗어났습니다." << '\n';
			return;
		}
		switch (size()) {
		case 0:	// 빈 리스트면 head 생성
			head[0][DATA] = data;
			head[0][NEXT] = -1;
			break;
		default:
			auto empty_idx = 1;	// head를 제외하고 (0은 안된다) 추가될 노드가 들어갈 빈 인덱스 구하기
			for (; empty_idx < size(); empty_idx++)	// 빈 인덱스는 erase, pop_back에서 지울 때 NEXT를 -1로 설정하여 판별할 수 있도록함
				if (head[empty_idx][DATA] == -1 && head[empty_idx][NEXT] == -1) break;
			// break없이 벗어나면 empty는 꽉찬 리스트의 바로 다음 인덱스가 된다.

			if (!index) {	// head에 insert 할 경우 head를 옮겨주고 head자리 [0]에 노드를 추가한다.
				head[empty_idx][DATA] = head[0][DATA];
				head[empty_idx][NEXT] = head[0][NEXT];
				head[0][DATA] = data;
				head[0][NEXT] = empty_idx;
			}
			else {
				auto i = 0;
				auto* front_idx = head[0];	// 해당 index 바로 전 노드 구하기
				for (; i++ != index - 1; front_idx = head[front_idx[NEXT]]);

				const auto temp_next = front_idx[NEXT];	// index번째 노드 저장
				front_idx[NEXT] = empty_idx;			// 추가될 노드를 가리킨다.

				head[empty_idx][DATA] = data;
				head[empty_idx][NEXT] = temp_next;		// 원래의 index 번째 노드 위치를 가리킨다.
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
		case 1:	// 위 선언에도 나와있지만 head의 위치(첫번째 노드의 위치)는 head[0]이다. 그러므로 head[0][NEXT] = -1이면 아무것도 접근 불가
			head[0][DATA] = -1;	// head이므로 데이터도 삭제해준다.
			head[0][NEXT] = -1;
			break;
		default:
			if (!index) {	// head를 지우는 경우 head->next를 head자리에 덮어씌우면 끝
				head[0][DATA] = head[head[0][NEXT]][DATA];	// 무조건 DATA를 먼저 덮어씌워야한다.
				head[0][NEXT] = head[head[0][NEXT]][NEXT];	// NEXT먼저 덮어쓸 경우 data는 head의 다음 다음 노드의 data를 덮어씌우게됨
			} else {
				auto i = 0;
				auto* front_idx = head[0];	// 해당 index 바로 전 노드 구하기 -> 지울 노드 : head[front_idx[NEXT]]
				for (; i++ != index - 1; front_idx = head[front_idx[NEXT]]);

				const auto temp_next = head[front_idx[NEXT]][NEXT];	// 연결이 끊기지 않기 위해 저장
				head[front_idx[NEXT]][DATA] = -1;
				head[front_idx[NEXT]][NEXT] = -1;
				front_idx[NEXT] = temp_next;		// 다음 노드를 연결
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
