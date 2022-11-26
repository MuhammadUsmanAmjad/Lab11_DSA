#include <bits/stdc++.h>
using namespace std;
vector<pair<int, char>> frequency_Counter(string s)
{
    map<char, int> mp;
    for (int i = 0; i < s.size(); i++)
        mp[s[i]]++;
    vector<pair<int, char>> v;
    for (int i = 0; i < s.size(); i++)
    {
        if (mp[s[i]] != 0)
        {
            v.push_back(make_pair(mp[s[i]], s[i]));
            mp[s[i]] = 0;
        }
    }
    // for (int i = 0; i < v.size(); i++)
    //     cout << v[i].first << " " << v[i].second << endl;
    return v;
}
struct MinHeapHash
{
    char ch;
    int frequency;
    MinHeapHash *left, *right;
    MinHeapHash(char ch, int f)
    {
        this->ch = ch;
        this->frequency = f;
        this->left = this->right = nullptr;
    }
};
void insert(queue<MinHeapHash *> &q, MinHeapHash *n)
{
    if (q.empty() || q.front()->frequency >= n->frequency)
    {
        q.push(n);
        return;
    }
    MinHeapHash *t = q.front();
    q.pop();
    insert(q, n);
    q.push(t);
}
void print(MinHeapHash *root, string str)
{
    if (!root)
        return;

    if (root->ch != '$')
        cout << root->ch << ": " << str << "\n";

    print(root->left, str + "0");
    print(root->right, str + "1");
}
void make_Huffman_tree(vector<pair<int, char>> v, int size)
{
    queue<MinHeapHash *> q;
    for (int i = 0; i < size; i++)
    {
        MinHeapHash *m = new MinHeapHash(v[i].second, v[i].first);
        q.push(m);
    }
    MinHeapHash *left, *right, *temp;
    while (q.size() != 1)
    {
        left = q.front();
        q.pop();
        right = q.front();
        q.pop();
        temp = new MinHeapHash('$', left->frequency + right->frequency);
        temp->left = left;
        temp->right = right;
        insert(q, temp);
    }
    print(q.front(), "");
}
int main()
{
    string str;
    ifstream fin;
    fin.open("Hash.txt");
    if (!fin)
        exit;
    else
    {
        char ch = fin.eof();
        getline(fin, str, ch);
    }
    vector<pair<int, char>> v = frequency_Counter(str);
    sort(v.begin(), v.end());
    cout << "__________________\n";
    make_Huffman_tree(v, v.size());
    return 0;
}