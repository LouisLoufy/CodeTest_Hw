#include "dbg.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> getSparseInfo(int m, int n, vector<vector<int>> &matrix) {
    int         sparseRows = 0, sparseCols = 0;
    vector<int> M(m), N(n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                M[i]++;
                N[j]++;
                // dbg(i, j, M, N);
            }
        }
        if (M[i] >= n / 2) { // 这样更高效，可读性下降，但方便调试
            sparseRows++;
            // dbg(sparseRows, m);
        }
    }

    for (int j = 0; j < n; ++j) {
        if (N[j] >= m / 2) {
            sparseCols++;
        }
    }

    return {sparseRows, sparseCols};
}

void test() {
    {
        vector<vector<int>> matrix    = {{-1, 0, 1}, {0, 0, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, 0}};
        auto [sparseRows, sparseCols] = getSparseInfo(5, 3, matrix);
        assert(sparseRows == 5);
        assert(sparseCols == 3);
    }

    {
        vector<vector<int>> matrix    = {{1, 0, 0}, {0, 0, 1}, {1, 1, 1}};
        auto [sparseRows, sparseCols] = getSparseInfo(3, 3, matrix);
        assert(sparseRows == 2);
        assert(sparseCols == 3);
    }

    {
        vector<vector<int>> matrix    = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        auto [sparseRows, sparseCols] = getSparseInfo(3, 3, matrix);
        assert(sparseRows == 0);
        assert(sparseCols == 0);
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    int m, n;
    cout << "Enter m x n" << endl;
    cin >> m >> n;

    if (m != 0 && n != 0) {
        cout << "Enter the matrix: " << endl;
    }

    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Result: " << endl;
    auto [sparseRows, sparseCols] = getSparseInfo(m, n, matrix);
    cout << "Sparse Rows: " << sparseRows << endl;
    cout << "Sparse Cols: " << sparseCols << endl;
    return 0;
}