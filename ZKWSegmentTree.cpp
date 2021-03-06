#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class SegmentTree {
public:
#define ls node * 2 + 1  // left son
#define rs node * 2 + 2  // right son

	using ll = long long;
	const static int MaxN = 2e5 + 7;
	int n;
	ll tree[MaxN * 4];

	static inline ll _Add(const ll& a, const ll& b) { return a + b; }
	static inline ll _Max(const ll& a, const ll& b) { return max(a, b); }
	static inline ll _Min(const ll& a, const ll& b) { return min(a, b); }
	typedef ll(*SegmentTreeFunc)(const ll& a, const ll& b);
	SegmentTreeFunc ThisSegmentTreeFunc = _Add;
	map<SegmentTreeFunc, ll> Func2DefaultNum;

	SegmentTree() {
		Func2DefaultNum[_Add] = 0;
		Func2DefaultNum[_Max] = LLONG_MIN / 2;
		Func2DefaultNum[_Min] = LLONG_MAX / 2;
	}

	void Build(ll a[], int n) {
		this->n = n;
		_Build(a, 0, n - 1, 0);
	}

	void Build(int n) {
		this->n = n;
		_Build(0, n - 1, 0);
	}

	void Updata(int idx, ll val) { _Updata(idx, val, 0, n - 1, 0); }

	ll Query(int L, int R) {
		if (L > R)
			return Func2DefaultNum[ThisSegmentTreeFunc];
		return _Query(L, R, 0, n - 1, 0);
	}

private:
	void _PushUp(int node) { tree[node] = ThisSegmentTreeFunc(tree[ls], tree[rs]); }

	void _Build(int l, int r, int node) {
		if (l == r) {
			tree[node] = Func2DefaultNum[ThisSegmentTreeFunc];
			return;
		}
		int mid = (l + r) / 2;
		_Build(l, mid, ls);
		_Build(mid + 1, r, rs);
		_PushUp(node);  // 左右子树建好以后就可以求当前节点的值了
	}

	void _Build(ll a[], int l, int r, int node) {
		if (l == r) {
			tree[node] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		_Build(a, l, mid, ls);
		_Build(a, mid + 1, r, rs);
		_PushUp(node);  // 左右子树建好以后就可以求当前节点的值了
	}

	void _Updata(int idx, ll val, int start, int end, int node) {
		if (start == end) {
			tree[node] = val;  // 修改树中的节点
			return;
		}
		int mid = (start + end) / 2;
		if (start <= idx && idx <= mid)
			_Updata(idx, val, start, mid, ls);
		else
			_Updata(idx, val, mid + 1, end, rs);
		_PushUp(node);
	}

	ll _Query(int L, int R, int start, int end, int node) {
		if (R < start || L > end)  // 没有交集
			return Func2DefaultNum[ThisSegmentTreeFunc];
		else if (start == end)  // 区间缩小到1时
			return tree[node];
		else if (L <= start && end <= R)  // 完全在区间内
			return tree[node];
		int mid = (start + end) / 2;

		ll ans = Func2DefaultNum[ThisSegmentTreeFunc];
		ans = ThisSegmentTreeFunc(ans, _Query(L, R, start, mid, ls));
		ans = ThisSegmentTreeFunc(ans, _Query(L, R, mid + 1, end, rs));
		return ans;
	}
};
