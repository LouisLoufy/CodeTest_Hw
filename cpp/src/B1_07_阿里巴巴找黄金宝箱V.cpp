#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int maxSlideWindow(vector<int> &arr, int k) {
    int sum = 0;

    for (int i = 0; i < k; i++) {
        sum += arr[i];
    }

    int res = sum;

    for (int i = k; i < arr.size(); i++) {
        sum += arr[i] - arr[i - k];
        res = max(res, sum);
    }

    return res;
}

void test() {
    {
        vector<int> arr{2, 10, -3, -8, 40, 5};
        int         k          = 4;
        int         firstIndex = maxSlideWindow(arr, k);
        assert(firstIndex == 39);
    }

    {
        vector<int> arr{8};
        int         k          = 1;
        int         firstIndex = maxSlideWindow(arr, k);
        assert(firstIndex == 8);
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    cout << "Enter the arr" << endl;
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int>  arr;
    string       str;

    while (getline(ss, str, ',')) {
        arr.push_back(stoi(str));
    }

    cout << "Enter the k" << endl;
    int k;
    cin >> k;

    cout << "Result: " << endl;
    cout << maxSlideWindow(arr, k) << endl;

    return 0;
}