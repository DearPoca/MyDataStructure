class SegmentTree {
public:
#define ls node * 2 + 1  // 左儿子
#define rs node * 2 + 2  // 右儿子

	const static int MaxN = 1e5 + 7;
	int n;
	int tree[MaxN * 4], lazy[MaxN * 4];

	void PushUp(int node) { tree[node] = tree[ls] + tree[rs]; }

	// node表示当前节点，ln,rn分别表示左右子树的节点数量
	void PushDown(int node, int ln, int rn) {
		if (lazy[node]) {
			lazy[ls] += lazy[node];  // 下推标记
			lazy[rs] += lazy[node];
			tree[ls] += lazy[node] * ln;  // 修改子节点的Sum使之与对应的lazy相对应
			tree[rs] += lazy[node] * rn;
			lazy[node] = 0;  // 清除本结点标记
		}
	}

	void _Build(int a[], int l, int r, int node) {
		if (l == r) {
			tree[node] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		_Build(a, l, mid, ls);
		_Build(a, mid + 1, r, rs);
		PushUp(node);  // 左右子树建好以后就可以求当前节点的值了
	}

	void Build(int a[], int n) {
		this->n = n;
		_Build(a, 0, n - 1, 0);
	}

	void _UpdateSection(int L, int R, int val, int start, int end, int node) {
		if (L <= start && end <= R) {
			tree[node] += val * (end - start + 1);  // 更新数字和，向上保持正确
			lazy[node] += val;  // 增加lazy标记，表示本区间的Sum正确，子区间的Sum仍需要根据lazy的值来调整
			return;
		}
		int mid = (start + end) / 2;
		PushDown(node, mid - start + 1, end - mid);
		if (L <= mid)  // 这里判断左右子树跟[L,R]有无交集，有交集才递归
			_UpdateSection(L, R, val, start, mid, ls);
		if (R > mid) _UpdateSection(L, R, val, mid + 1, end, rs);
		PushUp(node);
	}

	void UpdateSection(int L, int R, int val) { _UpdateSection(L, R, val, 0, n - 1, 0); }

	int _Query(int L, int R, int start, int end, int node) {
		if (R < start || L > end)  // 没有交集
			return 0;
		else if (start == end)  // 区间缩小到1时
			return tree[node];
		else if (L <= start && end <= R)  // 完全在区间内
			return tree[node];
		int mid = (start + end) / 2;

		PushDown(node, mid - start + 1, end - mid);
		int ans = 0;
		ans += _Query(L, R, start, mid, ls);
		ans += _Query(L, R, mid + 1, end, rs);
		return ans;
	}

	int Query(int L, int R) { return _Query(L, R, 0, n - 1, 0); }
};