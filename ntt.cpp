#include <bits/stdc++.h>
//#define int long long
using namespace std;

// phai chinh neu thay doi mod
const int mod = 998244353; // 1 + 7*17*2^23
const int inv_2 = (mod+1) / 2;
const int root = 15311432;
const int inv_root = 469870224;
const int root_pw = 1 << 23;

void fft(vector<int>& a, bool invert) {
    int n = a.size();
    if(n == 1)
        return;
    vector<int> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n/2; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);
    
    // Chon w sao cho w ^ n = 1, w ^ n-1 != 1
    int w = invert ? inv_root : root;
    for(int i = n; i < root_pw; i <<= 1)
        w = 1LL * w * w % mod;
    int wi(1);
    for(int i = 0; i < n/2; i++) {
        int odd = 1LL * wi * a1[i] % mod;
        int even = a0[i];
        a[i] = (even + odd) % mod;
        a[i+n/2] = (even - odd + mod) % mod;
        wi = 1LL * wi * w % mod;
        if(invert) {
            a[i] = 1LL * a[i] * inv_2 % mod;
            a[i+n/2] = 1LL * a[i+n/2] * inv_2 % mod;
        }
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> fa(a.begin(), a.end());
    vector<int> fb(b.begin(), b.end());
    int n = 1;
    int sz = a.size() + b.size() - 1;
    while(n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] = 1LL * fa[i] * fb[i] % mod;
    fft(fa, true);
    fa.resize(sz);
    return fa;
}
// 1 2 3 4 5 4 3 2 1
int32_t main() {
    vector<int> a;
    vector<int> b;
    for(int i = 0; i < 5; i++) {
        a.push_back(1);
        b.push_back(1);
    }
    vector<int> c = multiply(a, b);
    for(int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    cout << "\n";
}
