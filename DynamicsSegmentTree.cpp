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

class Node {
public:
	Node* left;
	Node* right;
	int l;
	int r;
	int mid;
	int v;
	int add;

	Node(int l, int r) {
		this->l = l;
		this->r = r;
		this->mid = (l + r) >> 1;
		this->left = this->right = nullptr;
		v = add = 0;
	}
};

class SegmentTree {
private:
	Node* root;

public:
	SegmentTree() {
		root = new Node(1, 1e9);
	}

	void modify(int l, int r, int v) {
		modify(l, r, v, root);
	}

	void modify(int l, int r, int v, Node* node) {
		if (l > r) return;
		if (node->l >= l && node->r <= r)
		{
			node->v = v;
			node->add = v;
			return;
		}
		pushdown(node);
		if (l <= node->mid) modify(l, r, v, node->left);
		if (r > node->mid) modify(l, r, v, node->right);
		pushup(node);
	}

	int query(int l, int r) {
		return query(l, r, root);
	}

	int query(int l, int r, Node* node) {
		if (l > r) return 0;
		if (node->l >= l && node->r <= r) return node->v;
		pushdown(node);
		int v = 0;
		if (l <= node->mid) v = max(v, query(l, r, node->left));
		if (r > node->mid) v = max(v, query(l, r, node->right));
		return v;
	}

	void pushup(Node* node) {
		node->v = max(node->left->v, node->right->v);
	}

	void pushdown(Node* node) {
		if (!node->left) node->left = new Node(node->l, node->mid);
		if (!node->right) node->right = new Node(node->mid + 1, node->r);
		if (node->add)
		{
			Node* left = node->left;
			Node* right = node->right;
			left->v = node->add;
			right->v = node->add;
			left->add = node->add;
			right->add = node->add;
			node->add = 0;
		}
	}
};


