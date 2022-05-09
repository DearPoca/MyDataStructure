class UnionFind {
private:
    int* forest;  // 存储节点的指向
    int* rank;    // 每棵树的层数
    int count;    // 节点的个数

public:
    UnionFind(int n) {
        count = n;

        // 初始化，默认每一个节点都指向自身，每个节点的节点个数都是1
        forest = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            forest[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind() {
        delete[] forest;
        delete[] rank;
    }

    // 查找过程, 查找节点index所指向的节点
    int find(int index) {
        while (index != forest[index]) {
            // 路径压缩
            forest[index] = forest[forest[index]];
            index = forest[index];
        }

        return index;
    }

    // 查看节点primary和节点secondray是否同指一个根节点
    // O(h)复杂度, h为树的高度
    bool isConnected(int primary, int secondray) {
        int primaryRoot = find(primary);
        int secondaryRoot = find(secondray);

        return primaryRoot == secondaryRoot;
    }

    // 合并节点primary和节点secondray所属的树
    // O(h)复杂度, h为树的高度
    void unionElements(int primary, int secondray) {
        int primaryRoot = find(primary);
        int secondaryRoot = find(secondray);

        if (primaryRoot == secondaryRoot) return;

        // 当树的层数相同时，进行一下 层数的维护
        // 节点层数小的树 指向节点层数多的树，
        // 也就是尽量的减少层数，这样O(h)中的h就越小，
        // 那么性能就得到了提升。

        if (rank[primaryRoot] < rank[secondaryRoot]) {
            // primary 这个节点 指向 secondary 这个节点
            forest[primaryRoot] = secondaryRoot;
        } else if (rank[primaryRoot] > rank[secondaryRoot]) {
            // secondary 这个节点 指向 primary这个节点
            forest[secondaryRoot] = primaryRoot;
        } else {  // 树的层数相等 谁指向谁都一样
            // secondary 这个节点 指向 primary这个节点
            forest[secondaryRoot] = primaryRoot;
            rank[primaryRoot] += 1;
        }
    }
};