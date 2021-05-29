#define _CRT_SECURE_NO_WARNINGS
#include"redBlackTree.h"
using namespace std;

int main() {
	vector<int> nums = { 1,5,6,7,8,9,10,11,12,13,14,15,18,24,2,155,1642,4242,23,3 };
	redBlackTree<int> redBlackTreeRoot;
	for (int i = 0; i < nums.size(); ++i) {
		redBlackTreeRoot.insert(nums[i]);
	}
	cout << "=============================================================================" << endl;
	cout << "插入后中序遍历: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "插入后前序遍历:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;

	redBlackTreeRoot.erase(14);
	cout << "删除14后中序遍历: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "删除14后前序遍历:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	redBlackTreeRoot.erase(9);
	cout << "删除9后中序遍历: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "删除9后前序遍历:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	redBlackTreeRoot.erase(5);
	cout << "删除5后中序遍历: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "删除5后前序遍历:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	return 0;
}


