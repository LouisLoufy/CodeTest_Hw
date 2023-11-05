#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右四个方向的偏移量

int Caculate(int &m, int &n, vector<vector<int>> &matrix) {
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

int main() {
    int m, n; // 输入长宽
    cout << "Enter: " << endl;
    cin >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    // 输出结果打印
    cout << "result: " << Caculate(m, n, matrix) << endl;
    return 0;
}