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

	const static int MaxN = 1e5 + 7;
	int n;
	int tree[MaxN * 4];

	static inline int _Add(const int& a, const int& b) { return a + b; }
	static inline int _Max(const int& a, const int& b) { return max(a, b); }
	static inline int _Min(const int& a, const int& b) { return min(a, b); }
	int (*SegmentTreeFunc)(const int& a, const int& b) = _Add;

	void Build(int a[], int n) {
		this->n = n;
		_Build(a, 0, n - 1, 0);
	}

	void Updata(int idx, int val) { _Updata(idx, val, 0, n - 1, 0); }

	int Query(int L, int R) { return _Query(L, R, 0, n - 1, 0); }

private:
	void _PushUp(int node) { tree[node] = SegmentTreeFunc(tree[ls], tree[rs]); }

	void _Build(int a[], int l, int r, int node) {
		if (l == r) {
			tree[node] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		_Build(a, l, mid, ls);
		_Build(a, mid + 1, r, rs);
		_PushUp(node);  // 左右子树建好以后就可以求当前节点的值了
	}

	void _Updata(int idx, int val, int start, int end, int node) {
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

	int _Query(int L, int R, int start, int end, int node) {
		if (R < start || L > end)  // 没有交集
			return 0;
		else if (start == end)  // 区间缩小到1时
			return tree[node];
		else if (L <= start && end <= R)  // 完全在区间内
			return tree[node];
		int mid = (start + end) / 2;

		int ans = 0;
		ans = SegmentTreeFunc(ans, _Query(L, R, start, mid, ls));
		ans = SegmentTreeFunc(ans, _Query(L, R, mid + 1, end, rs));
		return ans;
	}
};
