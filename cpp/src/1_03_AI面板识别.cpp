#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*
 * Tips:
 * 1. 使用 emplace_back 而不是 push_back，可以避免创建临时对象，拷贝构造
 * 2. 此处使用 emplace_back，需要定义一个构造函数
 *  a. push_back
 *      需要一个已经构造好的对象，然后会复制或移动这个对象到 vector 中
 *  b. emplace_back
 *      则直接在 vector 中构造对象，它接受的参数是将要构造的对象的构造函数的参数
 */

struct Light {
    int id; // 灯id
    int x;  // 圆心横坐标
    int y;  // 圆心纵坐标
    int r;  // 半径
    Light(int id, int x1, int y1, int x2, int y2)
        : id(id)
        , x((x1 + x2) / 2)
        , y((y1 + y2) / 2)
        , r(abs(x2 - x1) / 2) {}
};

bool compareY(const Light &a, const Light &b) {
    return a.y < b.y;
}

bool compareX(const Light &a, const Light &b) {
    return a.x < b.x;
}

string getResult(vector<Light> lights) {
    sort(lights.begin(), lights.end(), compareY);

    stringstream ret;

    vector<Light> sameRowLights;
    Light         base = lights[0];
    sameRowLights.emplace_back(base); // 1

    for (int i = 1; i < lights.size(); i++) {
        Light light = lights[i];

        if (light.y - base.y <= base.r) {
            sameRowLights.emplace_back(light); // 1
        } else {
            sort(sameRowLights.begin(), sameRowLights.end(), compareX);
            for (const auto &a : sameRowLights) {
                ret << a.id << " ";
            }

            vector<Light>().swap(sameRowLights);
            sameRowLights.clear();

            base = light;
            sameRowLights.emplace_back(base); // 1
        }
    }

    if (!sameRowLights.empty()) {
        sort(sameRowLights.begin(), sameRowLights.end(), compareX);
        for (const auto &a : sameRowLights)
            ret << a.id << " ";
    }

    return ret.str();
}

void test() {
    {
        vector<Light> lights = {Light{1, 0, 0, 2, 2}, Light{2, 2, 2, 4, 4}, Light{3, 4, 4, 6, 6}};
        string        result = getResult(lights);
        assert(result == "1 2 3 ");
    }
    {
        vector<Light> lights = {Light{1, 0, 0, 2, 2}, Light{2, 2, 2, 3, 3}, Light{3, 4, 4, 6, 6}};
        string        result = getResult(lights);
        assert(result == "1 2 3 ");
    }
    {
        vector<Light> lights = {Light{1, 0, 0, 2, 2}, Light{2, 0, 2, 2, 4}, Light{3, 4, 4, 6, 6}};
        string        result = getResult(lights);
        assert(result == "1 2 3 ");
    }
    {
        vector<Light> lights = {Light{1, 2, 2, 4, 4}, Light{2, 0, 0, 2, 2}, Light{3, 4, 4, 6, 6}};
        string        result = getResult(lights);
        assert(result == "2 1 3 ");
    }
    {
        vector<Light> lights = {Light{1, 0, 0, 2, 2}, Light{2, 2, 2, 4, 4}, Light{3, 2, 2, 4, 4}};
        string        result = getResult(lights);
        assert(result == "1 2 3 ");
    }
    {
        vector<Light> lights = {Light{1, 0, 0, 2, 2}};
        string        result = getResult(lights);
        assert(result == "1 ");
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    int n;
    cout << "Enter the number of lights" << endl;
    cin >> n;

    cout << "Enter the coordinate information for the light" << endl;
    vector<Light> lights;
    for (int i = 0; i < n; i++) {
        int id, x1, y1, x2, y2;
        cin >> id >> x1 >> y1 >> x2 >> y2;
        lights.emplace_back(Light{id, x1, y1, x2, y2}); // 2
    }

    cout << "Result: " << endl;
    cout << getResult(lights) << endl;
    return 0;
}