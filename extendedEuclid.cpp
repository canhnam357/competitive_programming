#include <bits/stdc++.h>
#define int long long
using namespace std;

// Dung extended euclid de tim nghiem cua phuong trinh
// a*x + b*y = gcd(a, b)
// return gcd va 2 tham chieu x, y
// Phuong trinh tong quat co nghiem khi d chia het cho gcd(a, b)
int extended_euclid(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Tinh nghich dao su dung extended euclid
int inverse_extended_euclid(int a, int mod) {
    int x, y;
    int g = extended_euclid(a, mod, x, y);
    if(g == 1) {
        x = (x % mod + mod) % mod;
        return x;
    }
    else {
        // No solution
        return -1;
    }
}

// Kiem tra ham
int32_t main() {
    for(int a = 1; a <= 100; a++) {
        for(int b = 1; b <= 100; b++) {
            int x, y;
            int g = extended_euclid(a, b, x, y);
            for(int c = -1000; c <= 1000; c++) {
                if(c % g == 0) {
                    int x2 = x * (c / g);
                    int y2 = y * (c / g);
                    if(a * x2 + b * y2 != c) {
                        cout << "Fail at " << a << " " << b << " " << c << "\n";
                        return 0;
                    }
                }
            }
        }
    }
    int mod = 1e9+7;
    for(int i = 10; i <= 100; i++) {
        if(inverse_extended_euclid(i, mod) * i % mod != 1) {
            cout << "Fail at invese " << i << "\n";
            break;
        }
    }
    cout << "OK\n";
}