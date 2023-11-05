# 设置编译器和编译选项
CXX      := g++
CXXFLAGS := -Wall -O0 -std=c++2a -g

# 源文件和目标文件路径
SRC_DIR = src
# 将每个.cpp文件对应的可执行文件放在bin目录下
BINS = $(SRCS:src/%.cpp=bin/%)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# 默认规则
all: $(BINS)

# 链接规则
bin/%: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# 创建bin目录
$(BINS): | bin

bin:
	mkdir -p bin

# 清理生成的文件
clean:
	rm -rf bin

.PHONY: all clean