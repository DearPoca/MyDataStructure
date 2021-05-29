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
	cout << "������������: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "�����ǰ�����:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;

	redBlackTreeRoot.erase(14);
	cout << "ɾ��14���������: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "ɾ��14��ǰ�����:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	redBlackTreeRoot.erase(9);
	cout << "ɾ��9���������: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "ɾ��9��ǰ�����:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	redBlackTreeRoot.erase(5);
	cout << "ɾ��5���������: " << endl;
	redBlackTreeRoot.inorderTraversal();
	cout << "=============================================================================" << endl;
	cout << "ɾ��5��ǰ�����:" << endl;
	redBlackTreeRoot.preorderTraversal();
	cout << "=============================================================================" << endl;
	return 0;
}


