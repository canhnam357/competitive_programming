#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
const int sqr_mod = mod * mod;

int power(int a, int n) {
    if(n == 0)
        return 1;
    int ans = power(a, n/2);
    ans = ans * ans % mod;
    if(n & 1)
        return ans * a % mod;
    else
        return ans;
}
int inverse(int a) {
    return power(a, mod-2);
}

struct modint {
    int val;
    modint() {val = 0;}
    modint(int x) {val = (x + sqr_mod) % mod;}
    modint operator + (modint other) {
        return val + other.val;
    }
    modint operator - (modint other) {
        return val - other.val;
    }
    modint operator * (modint other) {
        return val * other.val;
    }
    modint operator / (modint other) {
        return val * inverse(other.val);
    }
};

istream& operator >> (istream& is, modint& p) {
    is >> p.val;
    return cin;
}
ostream& operator << (ostream& os, modint p) {
    cout << p.val;
    return cout;
}
// Ket qua la
// 6
// 998244351
// 8
// 499122177
int32_t main() {
    modint a = 2;
    modint b = 4;
    cout << a+b << "\n";
    cout << a-b << "\n";
    cout << a*b << "\n";
    cout << a/b << "\n";
}