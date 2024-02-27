#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
const double pi = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    if(n == 1)
        return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n/2; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    // Chon w sao cho w ^ n = 1
    double angle = 2 * pi / n;
    if(invert)
        angle = -angle;
    cd w(cos(angle), sin(angle));
    cd wi(1);
    for(int i = 0; i < n/2; i++) {
        a[i] = a0[i] + wi*a1[i];
        a[i+n/2] = a0[i] - wi*a1[i];
        wi *= w;
        if(invert) {
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
    }
}

vector<double> multiply(const vector<double>& a, const vector<double>& b) {
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    int n = 1;
    int sz = a.size() + b.size() - 1;
    while(n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<double> res(sz);
    for(int i = 0; i < sz; i++)
        res[i] = fa[i].real();
    return res;
}

// 1 2 3 4 5 4 3 2 1
int main() {
    vector<double> a;
    vector<double> b;
    for(int i = 0; i < 5; i++) {
        a.push_back(1);
        b.push_back(1);
    }
    vector<double> c = multiply(a, b);
    for(int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    cout << "\n";
}