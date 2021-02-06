#include <iostream>
#include <iomanip>  // 함수의 형식 조정을 위한 헤더
#include <cmath>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(const int value = 0) : value(value), left(nullptr), right(nullptr) {}
    bool isLeaf() const { return (left == nullptr) && (right == nullptr); }
};

class BST {     // 이진 탐색 트리
private:
    int _size;
    int _index;
    static int _depth;
    static Node* root;

public:
    BST* divide;     // 모든 크기의 노드를 담는 포인터배열
    Node* subroot;   // divide에 담은 것들을 실행시켜주기 위해 (root가 static멤버라서 traversal에 subroot넣고 실행)

    BST() : _size(0), _index(0), divide(nullptr) { }

    int getLen() const {    // 쪼갠 노드들을 담을 배열의 길이를 구하는 함수
        auto len = 0;
        for (auto i = 2; i <= _depth; i++)
            len += static_cast<int>(pow(2, _depth - i + 1) - 1);
        return len;
    }

    bool search(Node*& pNode, const int value) {    // 포인터 필드를 참조자로 받는다.
        return pNode->value < value;                // 넣을 값이 기존 값보다 크면 true
    }

    void add(const int value, Node*& pNode = root) {    // 포인터 필드를 참조자로 받는다.
        static auto level = 1;              // 트리의 깊이를 구하기 위해 각 단계의 레벨을 구한다.
        if (pNode == nullptr) {             // root 부터 시작하여 nullptr인 경우 새로 할당
            pNode = new Node(value);
            _size++;
            if (level > _depth) _depth = level; // 새로 할당하는 경우 깊이를 재설정
            level = 1;                      // 다음 노드의 깊이를 계산하기 위해 초기화
            return;
        }
        if (pNode->value == value) {        // 중복된 값을 넣는 경우 오류 메시지 출력 후 반환
            cout << "중복된 값을 넣을 수 없습니다." << '\n';
            return;
        }
        if (search(pNode, value)) {
            level++;
            add(value, pNode->right);
        }
        else {
            level++;
            add(value, pNode->left);
        }
    }

    void remove(Node*& pNode = root) {      // 포인터 필드를 참조자로 받는다.
        if (pNode->right != nullptr)        // 오른쪽부터 시작
            remove(pNode->right);
        else if (pNode->left != nullptr)    // 오른쪽 비면 왼쪽 탐색
            remove(pNode->left);
        else {                              // 양쪽 다 빈 경우(isLeaf == true) 제거
            delete pNode;
            pNode = nullptr;
            _size--;
        }
    }

    void traversal(Node*& pNode = root) const {	// 중위 순회 (inorder traversal)
        if (pNode->isLeaf()) {                  // 끝 노드인 경우 출력 후 return
            cout << setw(2) << pNode->value << ' ';
            return;
        }

        // cout << pNode->value << ' ';     // preorder traversal : 전위 순회

        if (pNode->left != nullptr)         // 왼쪽이 있는 경우 들어간다.
            traversal(pNode->left);

        cout << setw(2) << pNode->value << ' ';        // inorder traversal : 중위 순회

        if (pNode->right != nullptr)        // 오른쪽이 있는 경우 들어간다.
            traversal(pNode->right);

        // cout << pNode->value << ' ';     // postorder traversal : 후위 순회
    }

    Node* copy(const int limit, Node*& pNode = root) const {    // 입력한 레벨만큼 트리를 복사한다. root 반환
        if (pNode == nullptr || limit == 0) return NULL;

        auto temp = new Node;
        temp->left = copy(limit - 1, pNode->left);
        temp->right = copy(limit - 1, pNode->right);
        temp->value = pNode->value;
        return temp;
    }

    void getTree(const int size, Node*& pNode = root, const int depth = _depth) {  // 입력한 크기(레벨) 만큼의 모든 트리를 구한다.
        auto maxLv = depth - size + 1;  // 해당 크기의 노드를 구할 수 있는 최대 레벨(root 기준) : 이 이상 내려가면 안됨
        if (maxLv == 1) {               // 최소 레벨까지 도달하면 복제 후 반환
            divide[_index++].subroot = copy(size, pNode);
            return;
        }
        // 현재 노드
        divide[_index++].subroot = copy(size, pNode);
        // 왼쪽 노드
        getTree(size, pNode->left, depth - 1);
        // 오른쪽 노드
        getTree(size, pNode->right, depth - 1);
    }

    void getDivide() {      // 레벨 2부터 최대 크기(_depth)의 노드까지 구하는 함수
        divide = new BST[getLen()];             // 배열 할당
        for (auto lv = 2; lv <= _depth; lv++)    // 레벨 2 트리(노드 3개로 이루어짐)부터 가장 큰 크기의 트리까지
            getTree(lv);
    }
};

// 스태틱 멤버 초기화
Node* BST::root = nullptr;
int BST::_depth = 1;

int main() {
    BST tree;
    // 완전 이진 트리 데이터 입력
    tree.add(16);

    tree.add(8);
    tree.add(24);

    tree.add(4);
    tree.add(12);
    tree.add(20);
    tree.add(28);

    tree.add(2);
    tree.add(6);
    tree.add(10);
    tree.add(14);
    tree.add(18);
    tree.add(22);
    tree.add(26);
    tree.add(30);

    tree.add(1);
    tree.add(3);
    tree.add(5);
    tree.add(7);
    tree.add(9);
    tree.add(11);
    tree.add(13);
    tree.add(15);
    tree.add(17);
    tree.add(19);
    tree.add(21);
    tree.add(23);
    tree.add(25);
    tree.add(27);
    tree.add(29);
    tree.add(31);

    tree.getDivide();   // 크기 2 이상의 모든 완전 이진 트리를 구한다. : tree->divide에 저장

    for (auto i = 0; i < tree.getLen(); i++) {
        tree.divide[i].traversal(tree.divide[i].subroot);
        cout << endl;
    }

    cout << "-------------------- 아래는 트리의 중위 순회 --------------------" << endl;
    tree.traversal();

    cout << endl;
    return 0;
}