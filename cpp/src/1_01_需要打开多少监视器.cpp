#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右四个方向的偏移量

int numOfMonitors(int &m, int &n, vector<vector<int>> &matrix) {
    int count = 0; // 记录需要打开的监控器数量
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 如果元素值为1，对应位置的监控器就要打开
            if (matrix[i][j] == 1) {
                ++count;
                continue;
            }

            // 如果元素值为0，则需要进一步检查其上下左右4个位置
            for (int i = 0; i < 4; i++) {
                int offsetX = offsets[i][0];
                int offsetY = offsets[i][1];

                int X = i + offsetX;
                int Y = j + offsetY;

                // 只要这四个位置有一个元素值为1，则当前位置的监控器需要打开
                if (X >= 0 && X < m && Y >= 0 && Y < n && matrix[X][Y] == 1) {
                    ++count;
                    break;
                }
            }
        }
    }
    return count;
}

void test() {
    {
        int                 m = 0, n = 0;
        vector<vector<int>> matrix;
        assert(numOfMonitors(m, n, matrix) == 0);
    }

    {
        int                 m = 2, n = 3;
        vector<vector<int>> matrix = {{0, 0, 0}, {0, 0, 0}};
        assert(numOfMonitors(m, n, matrix) == 0);
    }

    {
        int                 m = 2, n = 2;
        vector<vector<int>> matrix = {{1, 1}, {1, 1}};
        assert(numOfMonitors(m, n, matrix) == 4);
    }

    {
        int                 m = 3, n = 3;
        vector<vector<int>> matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        assert(numOfMonitors(m, n, matrix) == 5);
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    int m, n; // 输入长宽

    cout << "Enter the length and width of the parking lot: " << endl;
    cin >> m >> n;

    if (m != 0 && n != 0) {
        cout << "Enter the distribution of parking lot cars: " << endl;
    }

    vector<vector<int>> matrix(m, vector<int>(n)); // 停车场分布
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    // 输出结果打印
    cout << "result: " << numOfMonitors(m, n, matrix) << endl;

    return 0;
}