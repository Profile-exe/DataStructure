class Node:
	def __init__(self, data):
		self.data = data
		self.next = None


class List:
	def __init__(self):
		self.head = None
		self.length = 0

	def size(self):
		return self.length

	def empty(self):
		return True if self.head is None else False

	def push_back(self, data):
		if self.empty():  # 리스트가 빈 경우 head 노드 할당
			self.head = Node(data)
			self.length += 1
			return
		node = self.head
		while True:
			if node.next is self.head:  # 마지막 node인 경우
				node.next = Node(data)
				node.next.next = self.head
				break
			node = node.next
		self.length += 1

	def pop_back(self):
		size = self.size()  # 크기 얻기
		if size == 0:
			print("빈 리스트 입니다.")
			return
		elif size == 1:
			del self.head
			self.head = None
		else:
			node = self.head
			while True:
				if node.next.next is self.head:
					del node.next
					node.next = self.head
					break
				node = node.next
		self.length -= 1

	def insert(self, index, data):
		size = self.size()
		if index >= size:
			print("리스트 범위를 벗어났습니다.")
			return
		if size == 0:  # 빈 리스트면 head 생성
			self.head = Node(data)
		else:
			if index == 0:  # head에 insert하는 경우
				newNode = Node(data)
				lastNode = self.head
				while True:
					if lastNode.next == self.head:
						break
					lastNode = lastNode.next
				lastNode.next = newNode     # 마지막 노드의 next는 head가 될 newNode다

				newNode.next = self.head
				self.head = newNode
			else:
				node = self.head
				i = 0
				while True:
					if i + 1 == index:  # node.next가 해당 인덱스 노드인 경우
						newNode = Node(data)
						newNode.next = node.next
						node.next = newNode
						break
					i += 1
					node = node.next
		self.length += 1

	def erase(self, index):
		size = self.size()
		if index >= size:
			print("리스트 범위를 벗어났습니다.")
			return
		if size == 0:
			print("빈 리스트 입니다.")
			return
		elif size == 1:
			del self.head
			self.head = None  # empty()때문에 None을 대입해주어야한다.
		else:
			if index == 0:  # head를 지우는 경우
				node = self.head.next

				lastNode = self.head
				while True:
					if lastNode.next == self.head:
						break
					lastNode = lastNode.next
				lastNode.next = node  # 마지막 노드의 next는 head가 될 node다

				del self.head
				self.head = node
			else:
				node = self.head
				i = 0
				while True:
					if i + 1 == index:  # node.next가 해당 인덱스 노드인 경우
						temp = node.next.next
						del node.next
						node.next = temp
						break
		self.length -= 1


if __name__ == '__main__':
	_list = List()

	print(_list.size())
	print(_list.empty())

	_list.push_back(3)
	_list.push_back(4)
	_list.push_back(6)

	_list.erase(1)

	print(_list.size())
	print(_list.empty())

	_list.pop_back()
	_list.pop_back()

	print(_list.size())

	_list.insert(0, 2)
	_list.erase(0)
	_list.erase(0)

	print(_list.size())
