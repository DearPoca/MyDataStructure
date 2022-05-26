#include <set>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

struct NODE {
	int l, r;
	mutable ll val;
	NODE(int l_ = -1, int r_ = -1, ll val_ = 0) {
		l = l_, r = r_, val = val_;
	}
	bool operator < (const NODE& a) const {
		return l < a.l;
	}
};

class ChthollyTree {
public:
	typedef set<NODE>::iterator IT;
	set<NODE> st;

	ChthollyTree() {
		st.insert(NODE(INT_MIN, INT_MIN, LLONG_MAX)); // INT_MIN 一般用不到, 因此插入该节点, 防止首次split时越界
	}

	IT split(int pos) {
		IT it = st.lower_bound(NODE(pos));
		if (it != st.end() && it->l == pos) return it;
		--it;
		NODE tmp = *it;
		st.erase(it);
		st.insert(NODE(tmp.l, pos - 1, tmp.val));
		return st.insert(NODE(pos, tmp.r, tmp.val)).first;
	}

	void assign(int l, int r, ll val) {
		IT itr = split(r + 1), itl = split(l);
		st.erase(itl, itr);
		st.insert(NODE(l, r, val));
	}

	void add(int l, int r, ll val) {
		IT itr = split(r + 1), itl = split(l);
		for (IT it = itl; it != itr; ++it) {
			it->val += val;
		}
	}

	ll querySum(int l, int r) {
		IT itr = split(r + 1), itl = split(l);
		ll res = 0;
		for (IT it = itl; it != itr; ++it) {
			res += (it->r - it->l + 1) * it->val;
		}
		return res;
	}

	ll queryKth(int l, int r, int k) {
		vector< pair<ll, int> > vec(0);
		IT itr = split(r + 1), itl = split(l);
		for (IT it = itl; it != itr; ++it) {
			vec.push_back(make_pair(it->val, it->r - it->l + 1));
		}
		sort(vec.begin(), vec.end());
		for (vector< pair<ll, int> >::iterator it = vec.begin(); it != vec.end(); ++it) {
			if ((k -= it->second) <= 0) return it->first;
		}
		return -1;
	}
};