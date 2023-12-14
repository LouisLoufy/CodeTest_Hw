from collections import deque


# 定义了一个 TreeNode 类，表示二叉树的节点
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val  # 值
        self.left = left  # 左子节点
        self.right = right  # 右子节点


def bfs(root):
    if not root:  # 判断根节点是否为空
        return
    queue = deque([root])  # 创建一个双向队列，并将根节点加入队列中
    while queue:
        level_size = len(queue)  # 记录当前层的节点个数level_size
        temp = []
        for _ in range(level_size):  # 循环level_size次
            current_node = queue.popleft()  # 从队列中取出当前节点current_node
            temp.append(current_node.val)
            if current_node.left:  # 如果当前节点存在左子节点，则将左子节点加入队列中
                queue.append(current_node.left)
            if current_node.right:  # 如果当前节点存在右子节点，则将右子节点加入队列中
                queue.append(current_node.right)
        for i in temp:  # 循环结束后，将temp列表中的节点值依次打印出来。循环继续直到队列为空
            print(i, end="")


# 用于构建二叉树
def buildTree(inorder, postorder):  # 该函数接受两个参数inorder和postorder，分别表示中序遍历和后序遍历的结果
    if not inorder and not postorder:
        return
    root = TreeNode(postorder[-1])  # 根节点root，为后序遍历结果的最后一个元素
    idx = inorder.index(postorder[-1])  # 找到根节点在中序遍历结果中的索引idx

    # 递归调用buildTree函数构建左子树和右子树
    root.left = buildTree(inorder[:idx], postorder[:idx])
    root.right = buildTree(inorder[idx + 1 :], postorder[idx : len(postorder) - 1])
    return root


a, b = input().split()
postorder = list(a)
inorder = list(b)

root = buildTree(inorder, postorder)

bfs(root)
