int solve(int l, int r, int opt_l, int opt_r) {
    if(l > r)
        return INT_MIN;
    int m = l + r >> 1;
    pair<int, int> best = {-1, -1};
    for(int k = opt_l; k <= min(m, opt_r); k++) {
//        best = max(best, {dp_before[k-1] + cost(k, m), k});
    }
    int opt = best.second;
    int res = best.first;
//  dp_cur[mid] = res;
    solve(l, m-1, opt_l, opt);
    solve(m+1, r, opt, opt_r);
}