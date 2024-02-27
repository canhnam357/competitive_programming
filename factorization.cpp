#include <bits/stdc++.h>
using namespace std;
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);

long long pollardRho(long long n) {
    if (n % 2 == 0)
        return 2;
    long long x, y, g = 1, a;
    x = mt() % n + 1;
    y = x;
    a = mt() % n + 1;
    while (g == 1 || g == n) {
        if (g == n)
        {
            x = mt() % n + 1;
            y = x;
            a = mt() % n + 1;
        }
        x = (((__int128)x * x) + a) % n;
        y = (((__int128)y * y) + a) % n;
        y = (((__int128)y * y) + a) % n;
        g = gcd(abs(x - y), n);
    }
    return g;
}
inline uint64_t mod_mult64(uint64_t a, uint64_t b, uint64_t m)
{
    return __int128_t(a) * b % m;
}
uint64_t mod_pow64(uint64_t a, uint64_t b, uint64_t m)
{
    uint64_t ret = (m > 1);
    for (;;)
    {
        if (b & 1) ret = mod_mult64(ret, a, m);
        if (!(b >>= 1)) return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool is_prime(uint64_t n)
{
    if (n <= 3) return (n >= 2);
    static const uint64_t small[] =
    {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(uint64_t); ++i)
    {
        if (n % small[i] == 0) return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const uint64_t millerrabin[] =
    {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    };
    static const uint64_t A014233[] =    // From OEIS.
    {
        2047LL, 1373653LL, 25326001LL, 3215031751LL, 2152302898747LL,
        3474749660383LL, 341550071728321LL, 341550071728321LL,
        3825123056546413051LL, 3825123056546413051LL, 3825123056546413051LL, 0,
    };
    uint64_t s = n - 1, r = 0;
    while (s % 2 == 0)
    {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(uint64_t); i++)
    {
        uint64_t md = mod_pow64(millerrabin[i], s, n);
        if (md != 1)
        {
            for (j = 1; j < r; j++)
            {
                if (md == n - 1) break;
                md = mod_mult64(md, md, n);
            }
            if (md != n - 1) return false;
        }
        if (n < A014233[i]) return true;
    }
    return true;
}
vector<pair<long long, int>> factorize(long long n)
{
    assert(n > 1);
    vector<pair<long long, int>> res;
    for (long long i = 2; i * i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res.emplace_back(i, 0);
            while (n % i == 0)
            {
                res.back().second++;
                n /= i;
            }
        }
    }
    if (n == 1) return res;
    if (is_prime(n))
    {
        res.emplace_back(n, 1);
        return res;
    }
    long long k = pollardRho(n);
    if (k > n / k) k = n / k;
    res.emplace_back(k, 1);
    if (k * k == n) res.back().second++;
    else res.emplace_back(n / k, 1);
    sort(res.begin(), res.end());
    return res;
}
int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        long long n;
        cin >> n;
        if (n == 1)
        {
            cout << 0 << '\n';
            continue;
        }
        auto f = factorize(n);
        int cnt = 0;
        for (auto [p, o] : f) cnt += o;
        cout << cnt << ' ';
        for (auto [p, o] : f)
        {
            for (int i = 0; i < o; i++) cout << p << ' ';
        }
        cout << '\n';
    }
    return 0;
}
