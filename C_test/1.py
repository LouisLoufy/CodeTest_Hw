# 定义了一个Node类，表示 Huffman 树的节点
class Node:
    def __init__(self, weight):
        self.weight = weight  # 权重
        self.left = None  # 左子节点
        self.right = None  # 右子节点


# 构建Huffman树
def huffman_tree(data):  # 接收一个整数列表 data 作为输入，表示各个叶子节点的权重
    # 根据 data 列表创建一个 Node 对象列表 nodes
    nodes = [Node(weight) for weight in data]
    while len(nodes) > 1:  # 直到只剩下一个最后一个节点
        # 按照权重对 nodes 列表进行升序排序
        nodes.sort(key=lambda x: x.weight)

        # 从 nodes 列表中移除权重最小的两个节点，分别记为 left 和 right
        left = nodes.pop(0)
        right = nodes.pop(0)

        # 创建一个新的节点 merged_node，其权重为left和right节点的权重之和
        merged_node = Node(left.weight + right.weight)
        # 将 left 设为 merged_node 的左子节点
        merged_node.left = left
        # 将 right 设为 merged_node 的右子节点
        merged_node.right = right
        # 将 merged_node 添加回 nodes 列表中
        nodes.append(merged_node)
    # 返回 nodes 列表中唯一剩下的节点，即Huffman树的根节点
    return nodes[0]


# 广度优先搜索，用于进行Huffman树的前序遍历
def bfs(root, result):  # 接收两个参数：root为当前节点，result为存储结果的列表
    if root:  # 如果当前节点存在
        # 递归遍历左子树
        bfs(root.left, result)
        # 将当前节点的权重添加到result列表中
        result.append(root.weight)
        # 递归遍历右子树
        bfs(root.right, result)


# python YYDS 忽略第一行输入的个数
_ = input()
# 将第二行输入的整数数据转换为一个整数列表
input_data = list(map(int, input().split()))
# 构建 Huffman 树，将根节点保存在变量 root 中
root = huffman_tree(input_data)
# 创建一个空列表result用于存储前序遍历结果
result = []
# 广度优先搜索，得到前序遍历结果
bfs(root, result)
# 将结果列表中的元素转换为字符串，并以空格分隔打印
print(" ".join(map(str, result)))
