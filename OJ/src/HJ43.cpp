#include "dbg.h"

#include <deque>
#include <iostream>
#include <vector>

struct Node {
    int x;
    int y;
    int fatherNode;
};

std::vector<Node> bfs(int row, int col, std::vector<std::vector<int>> &maze) {
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));
    std::deque<std::vector<Node>>  route;
    std::vector<Node>              first = {{0, 0, 0}};
    visited[0][0]                        = true;
    route.push_back(first);

    while (!route.empty()) {
        std::vector<Node> current = route.front();
        route.pop_front();

        Node last_node = current.back();
        int  x[4]      = {last_node.x - 1, last_node.x + 1, last_node.x, last_node.x};
        int  y[4]      = {last_node.y, last_node.y, last_node.y - 1, last_node.y + 1};

        for (int i = 0; i < 4; i++) {
            if (x[i] >= 0 && x[i] < row && y[i] >= 0 && y[i] < col && maze[x[i]][y[i]] == 0 &&
                !visited[x[i]][y[i]]) {
                visited[x[i]][y[i]]         = true;
                std::vector<Node> new_route = current;
                new_route.push_back({x[i], y[i], static_cast<int>(current.size()) - 1});
                route.push_back(new_route);

                if (x[i] == row - 1 && y[i] == col - 1) {
                    return new_route;
                }
            }
        }
    }

    return {};
}

std::vector<Node> buildRoute(std::vector<std::vector<Node>> &route) {
    std::vector<Node> final_route;
    for (int i = route.size() - 1; i >= 0; i--) {
        if (final_route.empty()) {
            final_route.emplace_back(route[i][route[i].size() - 1]);
        } else {
            final_route.emplace_back(route[i][final_route[final_route.size() - 1].fatherNode]);
        }
    }

    std::reverse(final_route.begin(), final_route.end());
    return final_route;
}

int main() {
    int rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 0));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::cin >> maze[row][col];
        }
    }
    // dbg(maze);

    std::vector<Node> route = bfs(rows, cols, maze);

    for (const auto &cell : route) {
        std::cout << "(" << cell.x << "," << cell.y << ")\n";
    }

    return 0;
}