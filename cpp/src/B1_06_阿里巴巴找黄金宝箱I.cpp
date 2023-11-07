#include "dbg.h"

#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int findIndex(const vector<int> &arr) {
    int leftSum = 0, rightSum = accumulate(arr.begin(), arr.end(), 0) - arr[0];
    if (leftSum == rightSum) {
        return 0;
    }
    for (int i = 1; i < arr.size(); ++i) {
        leftSum += arr[i - 1];
        rightSum -= arr[i];
        // dbg(leftSum, rightSum);
        if (leftSum == rightSum) {
            return i;
        }
    }
    return -1;
}

void test() {
    {
        vector<int> arr{2, 5, -1, 8, 6};
        int         firstIndex = findIndex(arr);
        assert(firstIndex == 3);
    }

    {
        vector<int> arr{8, 9};
        int         firstIndex = findIndex(arr);
        assert(firstIndex == -1);
    }

    {
        vector<int> arr{11};
        int         firstIndex = findIndex(arr);
        assert(firstIndex == 0);
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    cout << "Enter the arr" << endl;
    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> arr;
    string      temp;
    while (getline(ss, temp, ',')) {
        arr.emplace_back(stoi(temp));
    }

    cout << "Result: " << findIndex(arr) << endl;

    return 0;
}