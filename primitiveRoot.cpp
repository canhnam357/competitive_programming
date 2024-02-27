#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;

int powmod (int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1)
            res = int (res * 1ll * a % p),  --b;
        else
            a = int (a * 1ll * a % p),  b >>= 1;
    return res;
}

int generator (int p) {
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
// root^(p-1) = 1
// root^(p-1) = root^(7*17*2^23) = root(7*17*2^23)
int32_t main() {
    int mod = 998244353;
    int root = powmod(generator(mod), 7*17, mod);
    int inv_root = powmod(root, mod-2, mod);
    cout << root << " " << inv_root << "\n";
}
