#include <bits/stdc++.h>
#define int long long
using namespace std;

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx //
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
int inverse(int a, int mod) {
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
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx //

struct Congruence {
    int a, m;
};
int chinese_remainder(vector<Congruence> c) {
    int M = 1;
    for (Congruence x : c) {
        M *= x.m;
    }
    int ans = 0;
    for (Congruence x : c) {
        int a_i = x.a;
        int M_i = M / x.m;
        // inverse(a, mod) : nghich dao modulo cua a
        int N_i = inverse(M_i, x.m);
        ans = (ans + a_i * M_i % M * N_i) % M;
    }
    return ans;
}

// input (2, 3), (3, 4), (4, 5) (mod 3 = 2, mod 4 = 3, mod 5 = 4)
// output 59
// input (0, 1001), (2, 1003), (5, 1005)
// output 378508130
int32_t main() {
    vector<Congruence> a = { {0, 1001}, {2, 1003} , {5, 1005} };
    cout << chinese_remainder(a) << "\n";
}