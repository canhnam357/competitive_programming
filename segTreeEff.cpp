int n;
// 1-indexed
vector<int> st(1 << 20);
void update(int idx, int val) {
    st[idx += n] += val;
    for (idx /= 2; idx; idx /= 2)
        st[idx] = st[2 * idx] + st[2 * idx + 1];
}

int get(int lo, int hi) {
    int ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
        if (lo & 1)
            ra += st[lo++];
        if (hi & 1)
            rb += st[--hi];
    }
    return ra + rb;
}