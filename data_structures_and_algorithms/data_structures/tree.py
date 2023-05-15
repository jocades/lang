class Node:
    def __init__(self, data):
        self.data = data
        self.left: Node | None = None
        self.right: Node | None = None

    def __repr__(self):
        return f'Node({self.data})'


# Create a tree
#  1
# / \
# 2   3
# / \ / \
# 4  5 6  7

root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)
root.right.left = Node(6)
root.right.right = Node(7)


# Find the sum of all the nodes in the tree, recursively
# O(n) time complexity

def sum_tree(root: Node | None) -> int:
    if root is None:
        return 0
    return root.data + sum_tree(root.left) + sum_tree(root.right)


print(sum_tree(root))


# Print the tree, recursively
# O(n) time complexity

def print_tree(root: Node | None):
    if root is None:
        return
    print(root.data)
    print_tree(root.left)
    print_tree(root.right)


print_tree(root)


# Find the height of the tree, recursively
# O(n) time complexity

def height(root: Node | None) -> int:
    if root is None:
        return 0
    return 1 + max(height(root.left), height(root.right))


print('Height', height(root))
