#include <bits/stdc++.h>
#define int long long
using namespace std;

// y = a * x + b
struct Line {
    int a;
    int b;
};
bool operator < (Line a, Line b) {
    return true;
}

// Duoc dat trong comment la dao chieu hull
struct Hull {
    vector<pair<int, Line>> hull;
    Hull(Line first) {
        hull.emplace_back(INT_MIN, first);
//        hull.emplace_back(INT_MAX, first);
    }
    // Them duong thang voi a tang dan
    // Trong comment: them duong thang voi a giam dan
    void update(Line l) {
        int A = l.a;
        int B = l.b;
        while(true) {
            int A1 = hull.back().second.a;
            int B1 = hull.back().second.b;
            int X1 = hull.back().first;
            // A * X + B == A1 * X + B1
            int intersect = (B - B1) / (A1 - A);
//            int intersect = (B - B1 + (A1 - A - 1)) / (A1 - A);
            if(intersect <= X1) {
//            if(intersect >= X1) {
                hull.pop_back();
            }
            else {
                hull.push_back({intersect, {A, B}});
                break;
            }
        }
    }
    int query(int X) {
        int pos = upper_bound(hull.begin(), hull.end(), make_pair(X, Line()))
                - hull.begin() - 1;
//        int pos = upper_bound(hull.begin(), hull.end(), make_pair(X, Line()),
//                greater<pair<int, Line>>()) - hull.begin() - 1;
        Line l = hull[pos].second;
        return l.a * X + l.b;
    }
};

signed main() {
    
}