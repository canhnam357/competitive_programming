#include<bits/stdc++.h>
using namespace std;

#define sqr(x) ((x) * (x))
const double pi = acos(-1);

struct Point {
    int x, y;
};
struct Line {
    int a, b, c;
};
// Tra ve d^2
int sqr_distance(Point a, Point b) {
    return sqr(a.x-b.x) + sqr(a.y-b.y);
}
// Tra ve 2*S tam giac
int triangle_area(Point a, Point b, Point c) {
    int a1 = b.x-a.x;
    int a2 = b.y-a.y;
    int b1 = c.x-b.x;
    int b2 = c.y-b.y;
    return abs(a1*b2 - a2*b1);
}
// Tra ve 1 neu a, b, c nguoc chieu kim dong ho (re trai)
//       -1 neu a, b, c cung chieu kim dong ho (re phai)
//        0 neu a, b, c thang hang
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

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}
bool operator <= (Point a, Point b) {
    return a.x < b.x || a.x == b.x && a.y <= b.y;
}
// Tra ve A <= B <= C
bool between(Point a, Point b, Point c) {
    return a <= b && b <= c || c <= b && b <= a;
}
// Kiem tra 2 doan thang AB va CD co diem chung khong
bool is_intersect(Point a, Point b, Point c, Point d) {
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    
    if(!c1 && between(a, c, b))
        return true;
    if(!c2 && between(a, d, b))
        return true;
    if(!c3 && between(c, a, d))
        return true;
    if(!c4 && between(c, b, d))
        return true;
    return c1*c2 < 0 && c3*c4 < 0;
}
// in ra so luong giao diem 2 doan thang
// tra ve 2 neu co 1 doan chung
int number_intersect(Point a, Point b, Point c, Point d) {
    if(!(a <= b))
        swap(a, b);
    if(!(c <= d))
        swap(c, d);
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    int cnt = 0;
    if(!c1 && between(a, c, b))
        cnt++;
    if(!c2 && between(a, d, b))
        cnt++;
    if(!c3 && between(c, a, d))
        cnt++;
    if(!c4 && between(c, b, d))
        cnt++;
    
    if(cnt > 0) {
        if(a == c || b == d || a == d || b == c) {
            return min(cnt-1, 2);
        }
        else
            return min(cnt, 2);
    }
    else {
        return c1*c2 < 0 && c3*c4 < 0;
    }
}
// Tra ve cos(AOB)
double angle(Point a, Point o, Point b) {
    int x1 = a.x - o.x;
    int y1 = a.y - o.y;
    int x2 = b.x - o.x;
    int y2 = b.y - o.y;
    int dot = x1 * x2 + y1 * y2;
    return sqrt(sqr_distance(o, a)) * sqrt(sqr_distance(o, b)) / dot;
}
// Tra ve duong thang AB
bool to_line(Point a, Point b, Line& res) {
    if(a == b) {
        return false;
    }
    res.a = a.y - b.y;
    res.b = b.x - a.x;
    res.c = res.a * a.x + res.b * a.y;
    return true;
}
// Tra ve khoang cach giua diem va duong thang
double distance_to_line(Point p, Line l) {
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(sqr(l.a) + sqr(l.b));
}
// Tra ve goc cuc
double polar_angle(Point p) {
    if(p.x == 0) {
        if(p.y > 0) {
            return pi/2;
        }
        else {
            return pi*3/2;
        }
    }
    else if(p.x > 0) {
        if(p.y >= 0)
            return atan((double)p.y / p.x);
        else
            return atan((double)p.y / p.x) + pi * 2;
    }
    else {
        return atan((double)p.y / p.x) + pi;
    }
}

int main() {

}