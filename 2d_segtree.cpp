int st[1 << 12][1 << 12] = {};
const int inf = 123456789;
int get_child(int id_par, int y1, int y2, int id = 1, int l = 1, int r = 1 << 11) {
    if (r < y1 || l > y2) return -inf;
    if (l >= y1 && r <= y2)
        return st[id_par][id];
    int mid = (l + r) >> 1;
    return max(get_child(id_par, y1, y2, id << 1, l, mid), get_child(id_par, y1, y2, id << 1 | 1, mid + 1, r));
}

int get(int x1, int x2, int y1, int y2, int id = 1, int l = 1, int r = 1 << 11) {
    if (r < x1 || l > x2) return -inf;
    if (l >= x1 && r <= x2)
        return get_child(id, y1, y2);
    int mid = (l + r) >> 1;
    return max(get(x1, x2, y1, y2, id << 1, l, mid), get(x1, x2, y1, y2, id << 1 | 1, mid + 1, r));
}
void update_y(int id_par, int l_par, int r_par, int y, int val, int id = 1, int l = 1, int r = 1 << 11) {
    if (l == r) {
        if (l_par == r_par)
            st[id_par][id] = val;
        else
            st[id_par][id] = max(st[id_par << 1][id], st[id_par << 1 | 1][id]);
    }
    else {
        int mid = (l + r) >> 1;
        if (y <= mid)
            update_y(id_par, l_par, r_par, y, val, id << 1, l, mid);
        else
            update_y(id_par, l_par, r_par, y, val, id << 1 | 1, mid + 1, r);
        st[id_par][id] = max(st[id_par][id << 1], st[id_par][id << 1 | 1]);
    }
}
void update(int x, int y, int val, int id = 1, int l = 1, int r = 1 << 11) {
    if (l != r) {
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(x, y, val, id << 1, l, mid);
        else
            update(x, y, val, id << 1 | 1, mid + 1, r);
    }
    update_y(id, l, r, y, val);
}

