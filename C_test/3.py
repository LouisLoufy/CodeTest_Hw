from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def bfs(root):
    if not root:
        return
    queue = deque([root])
    while queue:
        level_size = len(queue)
        temp = []
        for _ in range(level_size):
            current_node = queue.popleft()
            temp.append(current_node.val)
            if current_node.left:
                queue.append(current_node.left)
            if current_node.right:
                queue.append(current_node.right)
        for i in temp:
            print(i, end="")


def buildTree(inorder, postorder):
    if not inorder and not postorder:
        return
    root = TreeNode(postorder[-1])
    idx = inorder.index(postorder[-1])
    root.left = buildTree(inorder[:idx], postorder[:idx])
    root.right = buildTree(inorder[idx + 1 :], postorder[idx : len(postorder) - 1])
    return root


a, b = input().split()
postorder = list(a)
# print(inorder)
inorder = list(b)
root = buildTree(inorder, postorder)
bfs(root)
