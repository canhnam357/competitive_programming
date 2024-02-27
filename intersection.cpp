#include <bits/stdc++.h>
#define sqr(a) ((a) * (a))
using namespace std;

struct Point {
    double x, y;
};
// ax + by = c
struct Line {
    double a;
    double b;
    double c;
};
// center (x, y), radius r
struct Circle {
    double x;
    double y;
    double r;
};

// Giao diem 2 duong thang
// Tra ve false neu 2 duong thang song song
// Nguoc lai tra ve true va giao diem
const double eps = 1e-9;
bool intersect(Line l1, Line l2, Point& ans) {
    double d = l1.a * l2.b - l1.b * l2.a;
    double dx = l1.b * l2.c - l1.c * l2.b;
    double dy = l1.c * l2.a - l1.a * l2.c;
    if(abs(d) < eps) {
        return false;
    }
    else {
        ans.x = -dx / d;
        ans.y = -dy / d;
        return true;
    }
}

// Giao diem duong thang va duong tron
vector<Point> intersect_line_circle(Line l, Circle c1) {
    double dx = c1.x;
    double dy = c1.y;
    vector<Point> ans;

    double a = l.a;
    double b = l.b;
    double c = l.c - l.a * dx - l.b * dy;
    double r = c1.r;
    double x0 = a*c / (sqr(a) + sqr(b));
    double y0 = b*c / (sqr(a) + sqr(b));
    if (sqr(c) > sqr(r) * (sqr(a) + sqr(b)) + eps) {
        return ans;
    }
    else if (abs (sqr(c) - sqr(r) * (sqr(a) + sqr(b))) < eps) {
        ans.push_back({x0 + dx, y0 + dy});
        return ans;
    }
    else {
        double d = sqr(r) - sqr(c) / (sqr(a) + sqr(b));
        double mult = sqrt (d / (sqr(a) + sqr(b)));
        double ax, ay, bx, by;
        ax = x0 + b * mult + dx;
        bx = x0 - b * mult + dx;
        ay = y0 - a * mult + dy;
        by = y0 + a * mult + dy;
        
        ans.push_back({ax, ay});
        ans.push_back({bx, by});
    }
    return ans;
}

// Giao diem 2 duong tron
vector<Point> intersect_circle_circle(Circle c1, Circle c2) {
    double dx = c1.x;
    double dy = c1.y;
    c2.x -= c1.x;
    c2.y -= c1.y;
    c1.x = 0;
    c1.y = 0;

    Line l;
    l.a = -2 * c2.x;
    l.b = -2 * c2.y;
    l.c = -(sqr(c2.x) + sqr(c2.y) + sqr(c1.r) - sqr(c2.r));
    vector<Point> ans = intersect_line_circle(l, c1);
    for(Point& p : ans) {
        p.x += dx;
        p.y += dy;
    }
    return ans;
}

// Ket qua la
// 0.666667 0.333333
// -1
// -1
// 2 0 | 0 2 | 
// 0.211146 2.89443 | 3.78885 1.10557 |
int main() {
    Line a = {1, 1, 1};
    Line b = {-1, 2, 0};
    Line c = {1, 1, 2};
    Circle d {2, 2, 2};
    Circle e {3, 4, 3};
    Point ans;
    if(intersect(a, b, ans))
        cout << ans.x << " " << ans.y << "\n";
    else
        cout << "-1\n";
    if(intersect(a, c, ans))
        cout << ans.x << " " << ans.y << "\n";
    else
        cout << "-1\n";
    if(intersect(a, a, ans))
        cout << ans.x << " " << ans.y << "\n";
    else
        cout << "-1\n";
    for(Point p : intersect_line_circle(c, d))
        cout << p.x << " " << p.y << " | ";
    cout << "\n";
    for(Point p : intersect_circle_circle(d, e))
        cout << p.x << " " << p.y << " | ";
    cout << "\n";
}