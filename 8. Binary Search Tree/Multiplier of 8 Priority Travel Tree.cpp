#include <iostream>

using namespace std;

struct Node {
    const int value;
    Node* left;
    Node* right;
    Node(const int value) : value(value), left(nullptr), right(nullptr) {}
    bool isLeaf() const { return (left == nullptr) && (right == nullptr); }
};

class BST {	// 이진 탐색 트리가 아닌 8의 배수 우선 순회 트리이다.
private:
    int _size;
    static Node* root;

    // _add()는 이진 탐색 트리의 add()와 동일
    void _add(const int value, Node*& pNode) {    // 포인터 필드를 참조자로 받는다.
        if (pNode == nullptr) {             // root 부터 시작하여 nullptr인 경우 새로 할당
            pNode = new Node(value);
            _size++;
            return;
        }
        if (pNode->value == value) {        // 중복된 값을 넣는 경우 오류 메시지 출력 후 반환
            cout << "중복된 값을 넣을 수 없습니다." << '\n';
            return;
        }
        if (search(pNode, value))
            _add(value, pNode->right);
        else
            _add(value, pNode->left);
    }

public:
    BST() : _size(0) { }

    int size() const { return _size; }

    bool search(Node*& pNode, const int value) {    // 포인터 필드를 참조자로 받는다.
        return pNode->value < value;                // 넣을 값이 기존 값보다 크면 true
    }

    // 호출된 _add()는 이진탐색트리의 기본적인 add()함수랑 동일
    void add(const int value) {
        if (root == nullptr) {  // root가 비어있으면 생성 후 return
            root = new Node(value);
            _size++;
            return;
        }
        if (value % 8)          // 8의 배수가 아닌 경우 오른쪽에서 _add() 실행
            _add(value, root->right);
        else                    // 8의 배수인 경우 왼쪽에서 _add() 실행
            _add(value, root->left);
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

    void traversal(Node*& pNode = root) const {    // 8의 배수 우선 순회
        if (pNode->isLeaf()) {              // 끝 노드인 경우 출력 후 return
            cout << pNode->value << ' ';
            return;
        }

        if (pNode->left != nullptr)         // 왼쪽이 있는 경우 들어간다.
            traversal(pNode->left);

        cout << pNode->value << ' ';        // 자기 자신을 출력

        if (pNode->right != nullptr)        // 오른쪽이 있는 경우 들어간다.
            traversal(pNode->right);
    }
};

Node* BST::root = nullptr;  // 스태틱 멤버 초기화

int main() {
    BST tree;

    tree.add(5);
    tree.add(45);
    tree.add(24);
    tree.add(16);
    tree.add(33);
    tree.add(32);
    tree.add(8);
    tree.add(73);
    tree.add(40);
    tree.add(6);
    tree.add(65);
    tree.add(89);

    cout << tree.size() << endl;    // 12

    tree.traversal();  // 8 16 24 32 40 5 6 33 45 65 73 89
    cout << endl;

    tree.remove();
    tree.remove();
    tree.remove();

    cout << tree.size() << endl;    // 9

    tree.traversal();  // 8 16 24 32 40 5 6 33 45
    cout << endl;
    return 0;
}