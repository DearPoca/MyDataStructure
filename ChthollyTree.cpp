#include <set>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long type; // 设定珂朵莉树的数据类型

struct NODE {
	int l, r;
	mutable type val;
	NODE(int l_ = -1, int r_ = -1, type val_ = 0) {
		l = l_, r = r_, val = val_;
	}
	bool operator < (const NODE& a) const {
		return l < a.l;
	}
};
typedef set<NODE>::iterator IT;

class ChthollyTree {
	set<NODE> st;
	IT split(int pos) {
		IT it = st.lower_bound(NODE(pos));
		if (it != st.end() && it->l == pos) return it;
		--it;
		NODE tmp = *it;
		st.erase(it);
		st.insert(NODE(tmp.l, pos - 1, tmp.val));
		return st.insert(NODE(pos, tmp.r, tmp.val)).first;
	}

	void assign(int l, int r, type val) {
		IT itr = split(r + 1), itl = split(l);
		st.erase(itl, itr);
		st.insert(NODE(l, r, val));
	}

	void add(int l, int r, type val) {
		IT itr = split(r + 1), itl = split(l);
		for (IT it = itl; it != itr; ++it) {
			it->val += val;
		}
	}

	type querySum(int l, int r) {
		IT itr = split(r + 1), itl = split(l);
		type res = 0;
		for (IT it = itl; it != itr; ++it) {
			res += (it->r - it->l + 1) * it->val;
		}
		return res;
	}

	type queryKth(int l, int r, int k) {
		vector<pair<type, int>> vec(0);
		IT itr = split(r + 1), itl = split(l);
		for (IT it = itl; it != itr; ++it) {
			vec.push_back(make_pair(it->val, it->r - it->l + 1));
		}
		sort(vec.begin(), vec.end());
		for (vector<pair<type, int>>::iterator it = vec.begin(); it != vec.end(); ++it) {
			if ((k -= it->second) <= 0) return it->first;
		}
		return -1;
	}
};

int main(void) {

}