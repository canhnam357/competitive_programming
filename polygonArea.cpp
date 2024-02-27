#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};
// Tra ve 2 lan dien tich da giac
int polygon_area(vector<Point>& p) {
    int n = p.size();
    p.push_back(p.front());
    int s = 0;
    for(int i = 0; i < n; i++) {
        Point p1 = p[i];
        Point p2 = p[i+1];
        s += p1.x*p2.y - p1.y*p2.x;
    }
    p.pop_back();
    return abs(s);
}

int main() {
    vector<Point> p = {{0, 0}, {0, 2}, {1, 2}, {1, 1}, {2, 1}, {2, 0}};
    // Ket qua la 6
    cout << polygon_area(p) << "\n";
}