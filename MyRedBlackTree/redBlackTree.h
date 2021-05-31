#pragma once
#include<vector>
#include<string>
#include<iostream>

using namespace std;
namespace treeNodeColor {
	enum Enum {
		Red,
		Black
	};
	vector<string> strs = { "Red","Black" };
}

template<class T>
class redBlackTree {
public:
	T val;
	redBlackTree* left;
	redBlackTree* right;
	treeNodeColor::Enum color;

	redBlackTree(T val = INT_MIN, treeNodeColor::Enum color = treeNodeColor::Black) {
		this->val = val;
		this->color = color;
		this->left = nullptr;
		this->right = nullptr;
	}

	void insert(T val) {
		this->right = insert(this->right, val);
		if (this->right)
			this->right->color = treeNodeColor::Black;
	}

	void inorderTraversal() {
		inorderTraversal(this->right);
	}

	void preorderTraversal() {
		preorderTraversal(this->right);
	}

	void erase(T val) {
		bool flag = false;
		redBlackTree* N = nullptr;
		redBlackTree* t = this;
		this->right = erase(t->right, val, t, N, flag);
		if (this->right)
			this->right->color = treeNodeColor::Black;
	}
private:
	redBlackTree* singleRotateWithLeft(redBlackTree* K2) {
		redBlackTree* K1 = K2->left;
		K2->left = K1->right;
		K1->right = K2;
		return K1;
	}

	redBlackTree* singleRotateWithRight(redBlackTree* K2) {
		redBlackTree* K1 = K2->right;
		K2->right = K1->left;
		K1->left = K2;
		return K1;
	}

	redBlackTree* LRRotate(redBlackTree* K3) {
		K3->left = singleRotateWithRight(K3->left);
		return singleRotateWithLeft(K3);
	}

	redBlackTree* RLRotate(redBlackTree* K3) {
		K3->right = singleRotateWithLeft(K3->right);
		return singleRotateWithRight(K3);
	}


	redBlackTree* insert(redBlackTree* curNode, T val) {
		using namespace treeNodeColor;

		if (curNode == nullptr) {
			return new redBlackTree(val, Red);
		}
		if (curNode->left != nullptr && curNode->left->color == Red &&
			curNode->right != nullptr && curNode->right->color == Red) {
			curNode->color = Red;
			curNode->right->color = Black;
			curNode->left->color = Black;
		}
		if (val < curNode->val) {
			curNode->left = insert(curNode->left, val);
			if (curNode->left != nullptr && curNode->left->color == Red) {
				if (curNode->left->left != nullptr && curNode->left->left->color == Red) {
					curNode = singleRotateWithLeft(curNode);
					curNode->color = Black;
					curNode->right->color = Red;
					curNode->left->color = Red;
				}
				else if (curNode->left->right != nullptr && curNode->left->right->color == Red) {
					curNode = LRRotate(curNode);
					curNode->color = Black;
					curNode->right->color = Red;
					curNode->left->color = Red;
				}
			}
		}
		else if (val > curNode->val) {
			curNode->right = insert(curNode->right, val);
			if (curNode->right != nullptr && curNode->right->color == Red) {
				if (curNode->right->right != nullptr && curNode->right->right->color == Red) {
					curNode = singleRotateWithRight(curNode);
					curNode->color = Black;
					curNode->right->color = Red;
					curNode->left->color = Red;
				}
				else if (curNode->right->left != nullptr && curNode->right->left->color == Red) {
					curNode = RLRotate(curNode);
					curNode->color = Black;
					curNode->right->color = Red;
					curNode->left->color = Red;
				}
			}
		}
		return curNode;
	}

	void inorderTraversal(redBlackTree* node) {
		if (node == nullptr)
			return;
		inorderTraversal(node->left);
		cout << node->val << " " << treeNodeColor::strs[node->color] << endl;
		inorderTraversal(node->right);
	}

	void preorderTraversal(redBlackTree* node) {
		if (node == nullptr)
			return;
		cout << node->val << " " << treeNodeColor::strs[node->color] << endl;
		preorderTraversal(node->left);
		preorderTraversal(node->right);
	}

	redBlackTree* erase(redBlackTree* curNode, T val, redBlackTree*& parent, redBlackTree*& grandParent, bool& flag) {

		bool needProcess = false;
		using namespace treeNodeColor;

		auto Process = [&]() {
			// 1
			if (grandParent == nullptr) {
				return;
			}
			auto silbing = curNode == parent->left ? parent->right : parent->left;
			auto SL = silbing->left, SR = silbing->right;
			// 2

			auto _Process = [&]() {
				// 2.1
				if ((SL == nullptr || SL->color == Black) && (SR == nullptr || SR->color == Black)) {
					// 2.1.1
					if (parent->color == Red) {
						parent->color = Black;
						silbing->color = Red;
						return;
					}
					// 2.1.2
					else /* parent->color == Black */ {
						silbing->color = Red;
						flag = true;
						return;
					}
				}
				// 2.2
				else {
					// 2.2.1
					if ((silbing == parent->left && SL != nullptr && SL->color == Red) ||
						(silbing == parent->right && SR != nullptr && SR->color == Red)) {
						// (1)
						if (silbing == parent->left) {
							parent = singleRotateWithLeft(parent);
							curNode = parent->right;
							swap(parent->color, curNode->color);
							SL->color = Black;
						}
						//(2)
						else /* silbing == parent->right */ {
							parent = singleRotateWithRight(parent);
							curNode = parent->left;
							swap(parent->color, curNode->color);
							SR->color = Black;
						}
					}
					// 2.2.2
					else if ((silbing == parent->left && (SL == nullptr || SL->color == Black)) ||
						(silbing == parent->right && (SR == nullptr || SR->color == Black))) {
						// (1)
						if (silbing == parent->left) {
							silbing = singleRotateWithRight(silbing);
							parent = singleRotateWithLeft(parent);
						}
						// (2)
						else /* silbing == parent->right */ {
							silbing = singleRotateWithLeft(silbing);
							parent = singleRotateWithRight(parent);
						}
					}
				}
			};

			if (silbing->color == Black) {
				_Process();
			}
			// 3 
			else /* silbing->color == Red */ {
				// (1)
				if (silbing == parent->left) {
					singleRotateWithLeft(parent);
					silbing->color = Black;
					silbing->right->color = Red;
					auto tmp = silbing;
					silbing = parent->left;
					SL = silbing->left, SR = silbing->right;
					_Process();
					parent = tmp;
				}
				// (2)
				else /* silbing == parent->right */ {
					singleRotateWithRight(parent);
					silbing->color = Black;
					silbing->left->color = Red;
					auto tmp = silbing;
					silbing = parent->right;
					SL = silbing->left, SR = silbing->right;
					_Process();
					parent = tmp;
				}
			}
		};

		if (curNode == nullptr)
			return nullptr;
		else if (val < curNode->val) {
			curNode->left = erase(curNode->left, val, curNode, parent, needProcess);
			if (needProcess == true)
				Process();
		}
		else if (val > curNode->val) {
			curNode->right = erase(curNode->right, val, curNode, parent, needProcess);
			if (needProcess == true)
				Process();
		}
		else {
			// case 1
			if (curNode->left == nullptr && curNode->right == nullptr) {
				// case1.1: Red
				if (curNode->color == Red) {
					delete curNode;
					return nullptr;
				}
				// case1.2: Black
				else {
					auto tmp = curNode;
					Process();
					if (tmp == curNode) {
						delete curNode;
						return nullptr;
					}
					else if (curNode->left == tmp)
						curNode->left = nullptr;
					else if (curNode->right == tmp)
						curNode->right = nullptr;
					delete tmp;
					return curNode;
				}
			}
			// case 2
			else if (curNode->left == nullptr || curNode->right == nullptr) {
				if (curNode->left != nullptr) {
					auto ret = curNode->left;
					delete curNode;
					ret->color = Black;
					return ret;
				}
				else {
					auto ret = curNode->right;
					delete curNode;
					ret->color = Black;
					return ret;
				}
			}
			// case 3
			else/* curNode->left != nullptr && curNode->right != nullptr */ {
				auto nextNode = curNode->right;
				while (nextNode->left)
					nextNode = nextNode->left;
				swap(curNode->val, nextNode->val);
				curNode->right = erase(curNode->right, val, curNode, parent, needProcess);
				if (needProcess == true)
					Process();
			}
		}
		return curNode;
	}
};