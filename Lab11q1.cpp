#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
template <typename T>
struct HashItem
{
    int key;
    T value;
    HashItem *next;
    HashItem(T Value, int key = 0)
    {
        this->key = key;
        this->value = Value;
        this->next = nullptr;
    }
};
template <typename U>
class HashMap
{
    vector<U> Hash_Vector;
    int current_Elements;

public:
    HashMap()
    {
        Hash_Vector.reserve(10);
        this->current_Elements = 10;
    }
    HashMap(int const Capacity)
    {
        if (Capacity > 1)
        {
            this->Hash_Vector.reserve(Capacity);
            this->current_Elements = Capacity;
        }
        else
            throw("Error");
    }
    // Seperate Chaining...
    void insert_Chaining(char ch, int key)
    {
        int i = key % current_Elements;
        if (Hash_Vector[i].key == 0)
        {
            Hash_Vector[i].value = ch;
            Hash_Vector[i].key = key;
            return;
        }
        if (Hash_Vector[i].value == ch)
        {
            Hash_Vector[i].key += key;
            return;
        }
        U *n = &Hash_Vector[i];
        while (n->next != nullptr)
        {
            n = n->next;
        }
        n->next = new U(ch, key);
        return;
    }
    int get_hash(int key)
    {
        return key % this->current_Elements;
    }
    void print()
    {
        for (int i = 0; i < current_Elements; i++)
        {
            U *t = &Hash_Vector[i];
            while (t != nullptr)
            {
                cout << t->key << "  " << t->value << endl;
                t = t->next;
            }
        }
    }
    // Linear Probing
    void insert_linear(char ch, int key)
    {
        int i = key % current_Elements;
        if (Hash_Vector[i].key == 0)
        {
            Hash_Vector[i].key = key;
            Hash_Vector[i].value = ch;
            return;
        }
        for (int k = i + 1; k <= current_Elements && k >= i - 1; k++)
        {
            if (k >= current_Elements)
                k = 0;
            if (Hash_Vector[k].key == 0)
            {
                Hash_Vector[k].key = key;
                Hash_Vector[k].value = ch;
                return;
            }
        }
    }
    // Quadratic Probing...
    void Insert_Quadratic(char ch, int key)
    {
        int i = key % current_Elements;
        if (Hash_Vector[i].key == 0)
        {
            Hash_Vector[i].key = key;
            Hash_Vector[i].value = ch;
            return;
        }
        if (Hash_Vector[i].key != key)
        {
            for (int k = i + 1; k <= current_Elements && k >= i - 1; k *= 2)
            {
                if (k == 0)
                    k += 1;
                if (k >= current_Elements)
                    k = 0;
                if (Hash_Vector[k].key == 0)
                {
                    Hash_Vector[k].key = key;
                    Hash_Vector[k].value = ch;
                    return;
                }
            }
        }
    }
    // Double-hashing...
    void Insert_Double_Hashing(char ch, int key)
    {
        int i = key % current_Elements;
        if (Hash_Vector[i].key == 0)
        {
            Hash_Vector[i].key = key;
            Hash_Vector[i].value = ch;
            return;
        }
        while (true)
        {
            i = (i * key + 1) % current_Elements;
            if (Hash_Vector[i].key == 0)
            {
                Hash_Vector[i].key = key;
                Hash_Vector[i].value = ch;
                return;
            }
        }
    }

    bool delete_key(int key)
    {
        int i = key % current_Elements;
        if (this->Hash_Vector[i].key == 0)
            return false;
        U *n = &Hash_Vector[i];
        n->key = 0;
        n->value = ' ';
        n = n->next;
        while (n)
        {
            U *p = n;
            n = n->next;
            delete p;
        }
        Hash_Vector[i].next = nullptr;
        return true;
    }
    ~HashMap()
    {
        Hash_Vector.clear();
        this->current_Elements = 0;
        cout << "~HashMap() Called\n";
    }
};
int main()
{
    HashMap<HashItem<char>> h;
    h.insert_Chaining('a', 12);
    h.insert_Chaining('b', 19);
    h.insert_Chaining('c', 234);
    h.insert_Chaining('f', 121);
    h.insert_Chaining('t', 110);
    h.insert_Chaining('g', 135);
    h.print();
    return 0;
}