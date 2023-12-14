# 接收一个字符串 s 作为输入
def custom_sort(s):
    # 将字符串划分为两部分来进行排序
    return (s[:2], int(s[4:]))


# 读取一行输入并保存在变量s
s = input()
# 将输入的字符串按逗号分隔成一个列表 input_data
input_data = s.split(",")
# 调用自定义排序函数 custom_sort，对 input_data 列表进行排序
sorted_data = sorted(input_data, key=custom_sort)
# 将排序后的列表转换为一个字符串，每个元素之间用逗号分隔打印输出
print(",".join(map(str, sorted_data)))
