#include <bits/stdc++.h>
using namespace std;
//Implement a Hashmap
//Separate Chaining Technique

template <typename T>
class Node
{
public:
    string key;
    T value;
    Node<T> *next;

    Node(string key, T val)
    {
        this->key = key;
        value = val;
        next = NULL;
    }
    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
};

template <typename T>
class HashTable
{
    Node<T> **table; //pointer to an array of pointers
    int current_size;
    int table_size;

    int hashfn(string key)
    {
        int idx = 0;
        int p = 1;
        for (int j = 0; j < key.length(); j++)
        {
            idx = idx + (key[j] * p) % table_size;
            idx = idx % table_size;
            p = (p * 27) % table_size;
        }
        return idx;
    }

    void rehash()
    {
        Node<T> **oldtable = table;
        int oldtablesize = table_size;
        table_size = 2 * table_size;
        table = new Node<T> *[table_size];
        // Setting NULL to all values of the new table
        for (int i = 0; i < table_size; i++)
        {
            table[i] = NULL;
        }
        current_size = 0;

        //transferring from old table to new table
        for (int i = 0; i < oldtablesize; i++)
        {
            Node<T> *temp = oldtable[i];
            while (temp != NULL)
            {
                insert(temp->key, temp->value);
                temp = temp->next;
            }
            if (oldtable[i] != NULL)
            {
                delete oldtable[i];
            }
        }
        delete[] oldtable;
    }

public:
    HashTable(int ts = 7)
    {
        table_size = ts;
        table = new Node<T> *[table_size];
        current_size = 0;
        for (int i = 0; i < table_size; i++)
        {
            table[i] = NULL;
        }
    }

    void insert(string key, T val)
    {
        int index = hashfn(key);
        Node<T> *n = new Node<T>(key, val);
        n->next = table[index];
        table[index] = n;
        current_size++;

        //rehashing
        float load_factor = current_size / (1.0 * table_size);
        if (load_factor > 0.7)
        {
            rehash();
        }
    }
    void print()
    {
        for (int i = 0; i < table_size; i++)
        {
            cout << "Bucket " << i << " ->";
            Node<T> *temp = table[i];
            ;
            while (temp != NULL)
            {
                cout << temp->key << " ->";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    //Logic behind T* is that if we do not find that key then we return NULL
    T *search(string key)
    {
        int idx = hashfn(key);
        Node<T> *temp = table[idx];
        while (temp != NULL)
        {
            if (temp->key == key)
            {
                return &temp->value;
            }
            temp = temp->next;
        }
        return NULL;
    }
    // The return type of this is set to T& because when we update the value we
    //want it to reflect in the original as well
    T &operator[](string key)
    {
        T *f = search(key);
        if (f == NULL)
        {
            T garbage;
            insert(key, garbage);
            f = search(key);
        }
        return *f;
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    HashTable<int> price_menu;
    price_menu.insert("Burger", 120);
    price_menu.insert("Pepsi", 20);
    price_menu.insert("Noodles", 60);
    price_menu.insert("French Fries", 25);
    price_menu.insert("Biryani", 95);

    price_menu["Dosa"] = 60;
    price_menu["Dosa"] += 10;
    cout << "Price of dosa :" << price_menu["Dosa"] << endl;

    price_menu.print();

    int *price = price_menu.search("Pepsi");
    if (price == NULL)
    {
        cout << "Item not found " << endl;
    }
    else
    {
        cout << "Price is: " << *price << endl;
    }
    return 0;
}