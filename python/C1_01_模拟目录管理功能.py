class TreeNode:
    def __init__(self, curDicName, father):
        self.curDicName = curDicName
        self.father = father
        self.children = {}
 
 
class Tree:
    def __init__(self):
        # root是根目录，根目录 / 作为初始目录
        self.root = TreeNode("/", None)
        # cur用于指向当前正在操作的目录
        self.cur = self.root
 
    def mkdir(self, dicName):
        # mkdir 目录名称，如 mkdir abc 为在当前目录创建abc目录，如果已存在同名目录则不执行任何操作
        self.cur.children.setdefault(dicName, TreeNode(dicName + "/", self.cur))  # 目录符号为 /
 
    def cd(self, dicName):
        if dicName == "..":
            # cd .. 为返回上级目录，如果目录不存在则不执行任何操作
            if self.cur.father is not None:
                # cur 变更指向上级目录
                self.cur = self.cur.father
        else:
            # cd 目录名称，如 cd abc 为进入abc目录，如果目录不存在则不执行任何操作
            if self.cur.children.get(dicName) is not None:
                # cur 变更指向下级目录
                self.cur = self.cur.children[dicName]
 
    def pwd(self):
        # 输出当前路径字符串
        lst = []
 
        # 倒序路径，即不停向上找父目录
        cur = self.cur
        while cur is not None:
            lst.append(cur.curDicName)
            cur = cur.father
 
        # 反转后拼接
        lst.reverse()
 
        return "".join(lst)
 
 
# 算法逻辑
# 初始化目录结构
tree = Tree()
 
# 记录最后一条命令的输出
lastCommandOutput = ""
 
while True:
    try:
        line = input()
 
        # 本地测试解开此行
        # if line == "":
        #     break
 
        tmp = line.split()
        cmd_key = tmp[0]
 
        if cmd_key == "pwd":
            # pwd 命令不需要参数
            if len(tmp) != 1:
                continue
            lastCommandOutput = tree.pwd()
        elif cmd_key == "mkdir" or cmd_key == "cd":
            # 约束：mkdir 和 cd 命令的参数仅支持单个目录，如：mkdir abc 和 cd abc
            if len(tmp) != 2:
                continue
 
            # 目录名
            cmd_val = tmp[1]
 
            # 目录名约束校验
            # 约束：目录名称仅支持小写字母
            # 约束：不支持嵌套路径和绝对路径，如 mkdir abc/efg，cd abc/efg，mkdir /abc/efg，cd /abc/efg 是不支持的。
            # 关于嵌套路径和绝对路径，我简单理解就是cmd_val含有'/'字符，可以被小写字母判断涵盖住
            if not cmd_val.isalpha() or not cmd_val.islower():
                continue
 
            if cmd_key == "mkdir":
                tree.mkdir(cmd_val)
                # 题目进要求输出最后一个命令的运行结果，因此，对于无输出的命令，我认为需要覆盖掉前面的命令的输出结果
                lastCommandOutput = ""
            else:
                tree.cd(cmd_val)
                # 题目进要求输出最后一个命令的运行结果，因此，对于无输出的命令，我认为需要覆盖掉前面的命令的输出结果
                lastCommandOutput = ""
    except:
        break
 
print(lastCommandOutput)