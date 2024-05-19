class Node:
    def __init__(self, val: int):
        self.val = val
        self.next: Node | None = None

    def __repr__(self):
        return f'Node({self.val})'


class LinkedList:
    def __init__(self):
        self.head: Node | None = None

    def __repr__(self):
        if self.head is None:
            return 'LinkedList()'
        else:
            return f'LinkedList({self.head.val}, ...)'

    def append(self, val: int):
        if self.head is None:
            self.head = Node(val)
        else:
            curr = self.head
            while curr.next is not None:
                curr = curr.next
            curr.next = Node(val)

    def prepend(self, val: int):
        new_head = Node(val)
        new_head.next = self.head
        self.head = new_head

    def insert(self, val: int, index: int):
        if index == 0:
            self.prepend(val)
        else:
            curr = self.head
            for _ in range(index - 1):
                curr = curr.next
            new_node = Node(val)
            new_node.next = curr.next
            curr.next = new_node

    def remove(self, index: int):
        if index == 0:
            self.head = self.head.next
        else:
            curr = self.head
            for _ in range(index - 1):
                curr = curr.next
            curr.next = curr.next.next

    def __iter__(self):
        curr = self.head
        while curr is not None:
            yield curr.val
            curr = curr.next

    def __getitem__(self, index: int):
        curr = self.head
        for _ in range(index):
            curr = curr.next
        return curr.val

    def __setitem__(self, index: int, val: int):
        curr = self.head
        for _ in range(index):
            curr = curr.next
        curr.val = val

    def __len__(self):
        curr = self.head
        length = 0
        while curr is not None:
            length += 1
            curr = curr.next
        return length

    def __contains__(self, val: int):
        curr = self.head
        while curr is not None:
            if curr.val == val:
                return True
            curr = curr.next
        return False


# Test
ll = LinkedList()
for i in range(1, 11):
    ll.append(i)

# append
ll.append(15)

# insert
ll.insert(20, 1)

# len
print('len: ', len(ll))

# __iter__
for node in ll:
    print(node)

# __getitem__
first = ll[0]
last = ll[len(ll) - 1]
print(first, last)

# __setitem__
ll[0] = 100
print(ll[0])

# __contains__
print(100 in ll)
