/*
I referred to https://github.com/stevenhalim/cpbook-code
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class segtree {
private:
	vll A, st;
	int n;
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }
	ll build(int p, int L, int R) {
		if(L == R) {
			return st[p] = A[L];
		} else {
			return st[p] = build(left(p), L, (L+R)/2) + build(right(p), (L+R)/2+1, R);
		}
	}
	ll rsq(int p, int L, int R, int i, int j) {
		if(L > j || R < i) return 0;
		if(L >= i && R <= j) return st[p];
		
		ll p1 = rsq(left(p), L, (L+R)/2, i, j);
		ll p2 = rsq(right(p), (L+R)/2+1, R, i, j);
		
		if(p1 == -1) return p2;
		if(p2 == -1) return p1;
		
		return p1 + p2;
	}
	ll update(int p, int L, int R, int i, int val) {
		if(i < L || i > R) return st[p];
		if(L == i && R == i) {
			A[i] = val;
			return st[p] = A[L];
		}
		if(L != R) {
			ll p1 = update(left(p), L, (L+R)/2, i, val);
			ll p2 = update(right(p), (L+R)/2+1, R, i, val);
			return st[p] = p1 + p2;
		}
	}
public:
	segtree(const vll &A) : A(A) {
		n = (int)A.size();
		st.assign(4 * n, 0);
		build(1, 0, n-1);
	}
	ll rsq(int i, int j) {
		return rsq(1, 0, n-1, i, j);
	}
	ll update(int i, int val) {
		return update(1, 0, n-1, i, val);
	}
};
