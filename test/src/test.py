def devideLR(post, mid,queue,ans):
    # 后序遍历的最后一个元素就是根
    root = post[-1]
    # 将根加入题解
    ans.append(root)# 牛啊。每一层都是根啦
    # 在中序遍历中找到根的位置 rootIdx，那么该位置左边就是左子树，右边就是右子树
    rootIdx = mid.find(root)
    # 左子树 因为是从0开始的嘛
    leftLen = rootIdx
    if leftLen>0:
        leftPost = post[:leftLen] # 从后续遍历，截取得到左子树的后续遍历
        leftMid = mid[:rootIdx] # 从中序遍历中，截取得到左子树的中序遍历
        queue.append([leftPost, leftMid]) # 将左子树的后、中遍历序列加入执行队列
    # 如果存在右子树，即右子树长度大于 0
    if len(post) - 1 - leftLen>0: # 减去1是减去root这个数量1
        rightPost = post[leftLen:-1] # 倒数第一个是根啦。则从后序遍历中，截取出右子树的后序遍历 
        rightMid = mid[rootIdx+1:] # 从中序遍历中，截取出右子树的中序遍历
        queue.append([rightPost, rightMid]) # 将右子树的后、中遍历序列加入执行队列
def result(post, mid):
    # 广度优先搜索的执行队列，先加入左子树，再加入右子树
    queue = []
    # 层序遍历出来的元素存放在 ans 中
    ans = []
    devideLR(post,mid, queue, ans) # 得到左右子树
    while len(queue)>0:
        post, mid = queue.pop(0)
        devideLR(post, mid, queue,ans)
    return "".join(ans)
# 输入获取
post, mid = input().split()
print(result(post,mid))