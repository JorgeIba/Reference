const int SZ_BLOCK = 1100;
const int MAXN = 5e5 + SZ_BLOCK + 1;
const int BLOCKS = MAXN / SZ_BLOCK;

void update(int l, int r, int x) {
    int block_l = l / SZ_BLOCK;
    int block_r = r / SZ_BLOCK;

    push(block_l);
    push(block_r);

    for (int i = l; i < SZ_BLOCK * (block_l + 1) && i <= r; i++) {
        // Update in l range
    }

    for (int i = block_l + 1; i < block_r; i++) {
        // Update in block
    }

    for (int i = r; i >= SZ_BLOCK * (block_r) && i >= l; i--) {
        // Update in R range
    }
}

int query(int l, int r) {

    int block_l = l / SZ_BLOCK;
    int block_r = r / SZ_BLOCK;

    push(block_l);
    push(block_r);

    int ans = 0;
    for (int i = l; i < SZ_BLOCK * (block_l + 1) && i <= r; i++) {
        // Query in l range
    }

    for (int i = block_l + 1; i < block_r; i++) {
        // Query in blocks
    }

    for (int i = r; i >= SZ_BLOCK * (block_r) && i >= l; i--) {
        // Query in r range
    }

    return ans;
}