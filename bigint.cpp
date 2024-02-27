#include <bits/stdc++.h>
using namespace std;

const int BASE_DIGITS = 9;
const int BASE = round(pow(10, BASE_DIGITS));

int int_comp(int a, int b) {
    if(a > b)
        return 1;
    if(a < b)
        return -1;
    return 0;
}
struct BigInt {
    int sign;
    vector<int> d;
    // Constructor
    BigInt() {
        sign = 0;
    }
    BigInt(long long x) {
        if(x == 0) {
            sign = 0;
            return;
        }
        if(x < 0) {
            sign = -1;
            x = -x;   
        }
        else {
            sign = 1;
        }
        while(x) {
            d.push_back(x % BASE);
            x /= BASE;
        }
    }
    // Ham ho tro
    int length() const {
        return d.size();
    }
    int internal_cmp(const BigInt& a, const BigInt& b) const {
        if(a.length() != b.length()) {
            return int_comp(a.length(), b.length());
        }
        else {
            for(int i = a.length()-1LL; i >= 0; i--) {
                if(a.d[i] != b.d[i])
                    return int_comp(a.d[i], b.d[i]);
            }
        }
        return 0;
    }
    bool comp(const BigInt& a, const BigInt& b) const {
        if(a.sign != b.sign) {
            return int_comp(a.sign, b.sign);
        }
        else
            return internal_cmp(a, b);
    }
    void norm() {
        while(!d.empty() && d.back() == 0) {
            d.pop_back();
        }
        if(d.empty()) {
            sign = 0;
        }
    }
    int full_adder(int x, int y, int& carry) {
        int sum = x + y + carry;
        if(sum >= BASE) {
            carry = 1;
            sum -= BASE;
        }
        else if(sum < 0) {
            carry = -1;
            sum += BASE;
        }
        else {
            carry = 0;
        }
        return sum;
    }
    long long full_multiply(long long x, long long y, int cur, int& carry) {
        long long mul = x * y + cur + carry;
        carry = mul / BASE;
        mul %= BASE;
        return mul;
    }
    // Ham tinh toan
    BigInt operator * (BigInt other) {
        BigInt ans;
        int n = length();
        int m = other.length();
        ans.d.resize(n + m);
        ans.sign = other.sign * sign;
        for(int i = 0; i < n; i++) {
            int carry = 0;
            for(int j = 0; j < m; j++) {
                ans.d[i+j] = full_multiply(d[i], other.d[j], ans.d[i+j], carry);
            }
            ans.d[i+m] = full_adder(ans.d[i+m], 0, carry);
        }
        ans.norm();
        return ans;
    }
    void add(BigInt other) {
        d.resize(max(d.size(), other.d.size()) + 1);
        int carry = 0;
        for(int i = 0; i < length(); i++) {
            if(i < other.length())
                d[i] = full_adder(d[i], other.d[i], carry);
            else
                d[i] = full_adder(d[i], 0, carry);
        }
        norm();
    }
    void sub(BigInt other) {
        int carry = 0;
        for(int i = 0; i < length(); i++) {
            if(i < other.length())
                d[i] = full_adder(d[i], -other.d[i], carry);
            else
                d[i] = full_adder(d[i], 0, carry);
        }
        norm();
    }
    BigInt operator + (BigInt other) {
        if(sign == 0)
            return other;
        else if(other.sign == 0)
            return *this;
        else {
            BigInt ans = *this;
            if(ans.sign * other.sign == 1) {
                ans.add(other);
                return ans;
            }
            else {
                if(internal_cmp(ans, other) >= 0) {
                    ans.sub(other);
                    return ans;
                }
                else {
                    other.sub(ans);
                    return other;
                }
            }
        }
    }
    BigInt operator - (BigInt other) {
        other.sign = -other.sign;
        return operator + (other);
    }
    BigInt operator / (int x) {
        int carry = 0;
        BigInt ans = *this;
        for(int i = length()-1; i >= 0; i--) {
            carry = carry * BASE + ans.d[i];
            ans.d[i] = carry / x;
            carry %= x;
        }
        ans.norm();
        return ans;
    }
    // Ham so sanh
#define COMPARE(x) bool operator x (const BigInt& other) const {return comp(*this, other) x 0;}
    COMPARE(==) COMPARE(!=) COMPARE(>) COMPARE(<) COMPARE(>=) COMPARE(<=)
#undef COMPARE
};

ostream& operator << (ostream& os, const BigInt& a) {
    if(a.sign == 0) {
        os << 0;
        return os;
    }
    else if(a.sign == -1)
        os << "-";
    os << a.d.back();
    for(int i = a.d.size() - 2LL; i >= 0; i--)
        os << setw(BASE_DIGITS) << setfill('0') << right << a.d[i];
    return os;
}

int main() {
    // a = 1e18 - 1
    // b = 1
    // c = 123456789123456789
    // Ket qua
    // 1000000000000000000
    // 999999999999999999
    // 999999999999999998000000000000000001
    // 499999999999999999
    // 0
    // 0
    // 0
    // 1
    // 1
    // 1
    BigInt a = 999999999999999999LL;
    BigInt b = 1;
    BigInt c = 123456789123456789LL;
    cout << (a + b) << "\n";
    cout << (a + b - b) << "\n";
    cout << (a * a) << "\n";
    cout << (a / 2) << "\n";
    cout << (a < b) << "\n";
    cout << (a > a) << "\n";
    cout << (a <= b) << "\n";
    cout << (a >= a) << "\n";
    cout << (a == a) << "\n";
    cout << (a != b) << "\n";
}
