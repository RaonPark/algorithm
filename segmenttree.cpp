/*
implement segment tree to solve range sum query.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class segtree {
private:
	vll A, st, lazy;
	int n;
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }
	void propagate(int p, int L, int R) {
		st[p] += lazy[p] * (R-L+1);
		if(lazy[p] != 0) {
			if(L != R) {
				lazy[left(p)] += lazy[p];
				lazy[right(p)] += lazy[p];
			}
			lazy[p] = 0;
		}
	}
	ll build(int p, int L, int R) {
		if(L == R) {
			return st[p] = A[L];
		} else {
			return st[p] = build(left(p), L, (L+R)/2) + build(right(p), (L+R)/2+1, R);
		}
	}
	ll rsq(int p, int L, int R, int i, int j) {
		propagate(p, L, R);
		if(i > j) return 0;
		if(L >= i && R <= j) return st[p];
		int M = (L+R) / 2;
		ll p1 = rsq(left(p), L, M, i, min(j, M));
		ll p2 = rsq(right(p), M+1, R, max(i, M+1), j);
		return p1 + p2;
	}
	void update(int p, int L, int R, int i, int j, ll val) {
		propagate(p, L, R);
		if(i > j) return;
		if(L >= i && R <= j) {
			lazy[p] = val;
			propagate(p, L, R);
		} else {
			int M = (L+R) / 2;
			update(left(p), L, M, i, min(M, j), val);
			update(right(p), M+1, R, max(i, M+1), j, val);
			ll lsubtree = (lazy[left(p)] != 0) ? lazy[left(p)] : st[left(p)];
			ll rsubtree = (lazy[right(p)] != 0) ? lazy[right(p)] : st[right(p)];
			st[p] = lsubtree + rsubtree;
		}
	}
public:
	segtree(const vll &A) : A(A) {
		n = (int)A.size();
		st.assign(4 * n, 0);
		build(1, 0, n-1);
		lazy.assign(4 * n, 0);
	}
	ll rsq(int i, int j) {
		return rsq(1, 0, n-1, i, j);
	}
	void update(int i, int j, ll val) {
		update(1, 0, n-1, i, j, val);
	}
};
