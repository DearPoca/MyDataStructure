class UnionFind
{
private:
    int *forest;
    int *rank;
    int count;

public:
    UnionFind(int n)
    {
        count = n;

        forest = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i)
        {
            forest[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind()
    {
        delete[] forest;
        delete[] rank;
    }

    int find(int index)
    {
        while (index != forest[index])
        {
            forest[index] = forest[forest[index]];
            index = forest[index];
        }

        return index;
    }

    bool isConnected(int primary, int secondray)
    {
        int primaryRoot = find(primary);
        int secondaryRoot = find(secondray);

        return primaryRoot == secondaryRoot;
    }

    void unionElements(int primary, int secondray)
    {
        int primaryRoot = find(primary);
        int secondaryRoot = find(secondray);

        if (primaryRoot == secondaryRoot)
            return;

        if (rank[primaryRoot] < rank[secondaryRoot])
        {
            forest[primaryRoot] = secondaryRoot;
        }
        else if (rank[primaryRoot] > rank[secondaryRoot])
        {
            forest[secondaryRoot] = primaryRoot;
        }
        else
        {
            forest[secondaryRoot] = primaryRoot;
            rank[primaryRoot] += 1;
        }
    }
};