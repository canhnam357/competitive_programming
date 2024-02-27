#include <bits/stdc++.h>
#define sqr(x) ((x) * (x))
using namespace std;

int eulerPhi(int n) { // = n (1-1/p1) ... (1-1/pn)
    if (n == 0) return 0;
    int ans = n;
    for (int x = 2; x*x <= n; ++x) {
        if (n % x == 0) {
            ans -= ans / x;
            while (n % x == 0) n /= x;
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}

// Phi ham euler dung sang
vector<int> buildEulerPhi(int N)
{
    vector<int> phi(N+1);
    for (int i = 1; i <= N; i++) 
        phi[i] = i;
    for (int i = 2; i <= N; i++)
        if (phi[i] == i)
            for (int j = i; j <= N; j += i) 
                phi[j] -= phi[j]/i;
    return phi;
}

// Kiem tra phi(x)
// input:  123456 100000
// output:  41088  40000
int32_t main() {
    cout << eulerPhi(123456) << "\n";
    cout << eulerPhi(100000) << "\n";
    auto phi = buildEulerPhi(123456);
    cout << phi[123456] << "\n";
    cout << phi[100000] << "\n";
}