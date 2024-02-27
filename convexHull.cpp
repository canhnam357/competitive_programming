#include <bits/stdc++.h>
#define int long long
using namespace std;

#define sqr(x) ((x) * (x))

struct Point {
    int x;
    int y;
    void input() {
        cin >> x >> y;
    }
};

bool operator < (Point a, Point b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}
int ccw(Point a, Point b, Point c) {
    int a1 = b.x-a.x;
    int a2 = b.y-a.y;
    int b1 = c.x-b.x;
    int b2 = c.y-b.y;
    int d = a1*b2 - a2*b1;
    if(d == 0)
        return 0;
    else if(d > 0)
        return 1;
    else
        return -1;
}

// Can su dung ham ccw
// Bao loi khong tinh diem thang hang, theo chieu kim dong ho
// Neu tinh ca diem thang hang thi thay < thanh <= trong doan ccw
// New muon doi thanh nguoc chieu kim dong ho thi doi < thanh >
void convex_hull(vector<Point> p, vector<Point>& hull) {
    int n = p.size();
    hull.clear();
    sort(p.begin(), p.end());
    vector<Point> up;
    /// (1)
    up.push_back(p[0]);
    for(int i = 1; i < n-1; i++) {
        if(ccw(up.back(), p[i], p.back()) < 0) {
            while(up.size() >= 2 && ccw(up[up.size()-2], up[up.size()-1], p[i]) >= 0) {
                up.pop_back();
            }
            up.push_back(p[i]);
        }
    }
    hull.insert(hull.end(), up.begin(), up.end());
    ///
    up.clear();
    reverse(p.begin(), p.end());
    /// (2) copy paste cua 1
    up.push_back(p[0]);
    for(int i = 1; i < n-1; i++) {
        if(ccw(up.back(), p[i], p.back()) < 0) {
            while(up.size() >= 2 && ccw(up[up.size()-2], up[up.size()-1], p[i]) >= 0) {
                up.pop_back();
            }
            up.push_back(p[i]);
        }
    }
    hull.insert(hull.end(), up.begin(), up.end());
    ///
}

// Kiem tra bao loi ngiem ngat, neu ket qua la
// 1 -> bao loi nguoc chieu kim dong ho
// -1 -> bao loi cung chieu kim dong ho
// 0 -> khong phai bao loi hoac khong phai da giac
int is_convex_hull(vector<int> p) {
    int n = p.size();
    int max_ccw = 2;
    int min_ccw = -2;
    for(int i = 0; i < n; i++) {
        int p1 = p[i];
        int p2 = p[(i+1) % n];
        int p3 = p[(i+2) % n];
    }
    if(max_ccw == min_ccw)
        return max_ccw;
    else
        return 0;
}
// Ket qua la
// 5
// 0 0
// 0 2
// 1 2
// 2 1
// 2 0
int32_t main() {
    vector<Point> a = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 1}, {2, 1}, {2, 0}, {1, 0}};
    vector<Point> hull;
    convex_hull(a, hull);
    cout << hull.size() << "\n";
    for(Point p : hull) {
        cout << p.x << " " << p.y << "\n";
    }
    return 0;
}
