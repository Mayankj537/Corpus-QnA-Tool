// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class SymNode
{

public:
    string key;
    int height;
    int address = -1;
    SymNode *par;
    SymNode *left;
    SymNode *right;
    long long wordcount;

    SymNode()
    {
        key = "";
        height = 0;
        par = NULL;
        left = NULL;
        right = NULL;
        wordcount = 0;
    }

    SymNode(string k)
    {
        key = k;
        height = 0;
        par = NULL;
        left = NULL;
        right = NULL;
        wordcount = 1;
    }

    SymNode *LeftLeftRotation()
    {
        SymNode *a = this->right;
        SymNode *b = a->left;
        a->left = this;
        this->right = b;
        this->height = std::max(findht(this->left), findht(this->right)) + 1;
        a->height = std::max(findht(a->left), findht(a->right)) + 1;
        return a;
    }

    SymNode *RightRightRotation()
    {
        SymNode *a = this->left;
        SymNode *b = a->right;
        a->right = this;
        this->left = b;
        this->height = std::max(findht(this->left), findht(this->right)) + 1;
        a->height = std::max(findht(a->left), findht(a->right)) + 1;
        return a;
    }

    SymNode *LeftRightRotation()
    {
        this->left = this->left->LeftLeftRotation();
        return this->RightRightRotation();
    }

    SymNode *RightLeftRotation()
    {
        this->right = this->right->RightRightRotation();
        return this->LeftLeftRotation();
    }

    int findht(SymNode *node)
    {
        if (node == NULL)
        {
            return -1;
        }
        else if (node->left == NULL && node->right == NULL)
        {
            return 0;
        }
        else if (node->left == NULL && node->right != NULL)
        {
            return (1 + node->right->height);
        }
        else if (node->left != NULL && node->right == NULL)
        {
            return (1 + node->left->height);
        }
        else
        {
            return (1 + max(node->left->height, node->right->height));
        }
    }

    ~SymNode()
    {
    }
};

class SymbolTable
{
private:
    int size = 0;
    SymNode *root = NULL;

public:
    SymbolTable()
    {
        size = 0;
        root = NULL;
    }
    int findheight(SymNode *node)
    {
        if (node == NULL)
        {
            return -1;
        }
        else if (node->left == NULL && node->right == NULL)
        {
            return 0;
        }
        else if (node->left == NULL && node->right != NULL)
        {
            return (1 + node->right->height);
        }
        else if (node->left != NULL && node->right == NULL)
        {
            return (1 + node->left->height);
        }
        else
        {
            return (1 + max(node->left->height, node->right->height));
        }
    }
    int bf(SymNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int lh, rh;
        if (node->left != NULL)
        {
            lh = node->left->height;
        }
        if (node->left == NULL)
        {
            lh = -1;
        }
        if (node->right == NULL)
        {
            rh = -1;
        }
        if (node->right != NULL)
        {
            rh = node->right->height;
        }
        return lh - rh;
    }
    SymNode *Ins(SymNode *root, string data)
    {
        if (root == NULL)
        {
            root = new SymNode(data);
            return root;
        }
        if (root->key == data)
        {
            return root;
        }
        else if (data < root->key)
        {
            root->left = Ins(root->left, data);
        }
        else
        {
            root->right = Ins(root->right, data);
        }
        root->height = 1 + max(findheight(root->left), findheight(root->right));
        int a = bf(root);
        if (a > 1 && findheight(root->left->left) >= findheight(root->left->right))
        {
            return root->RightRightRotation();
        }
        if (a < -1 and findheight(root->right->left) <= findheight(root->right->right))
        {
            return root->LeftLeftRotation();
        }
        if (a > 1 && findheight(root->left->left) < findheight(root->left->right))
        {
            return root->LeftRightRotation();
        }
        if (a < -1 && findheight(root->right->left) > findheight(root->right->right))
        {
            return root->RightLeftRotation();
        }
        return root;
    }

    void insert(string k)
    {
        int x = search(k);
        if (x == -2)
        {
            size++;
        }
        root = Ins(root, k);
    }
    SymNode *minNode(SymNode *node)
    {
        SymNode *current = node;
        while (current->left != NULL)
        {
            current = current->left;
        }

        return current;
    }
    SymNode *deleteNode(SymNode *root, string key)
    {
        if (root == NULL)
        {
            return root;
        }
        if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }
            else if (root->left != NULL && root->right == NULL)
            {
                SymNode *t = root->left;
                delete root;
                return t;
            }
            else if (root->left == NULL && root->right != NULL)
            {
                SymNode *t = root->right;
                delete root;
                return t;
            }
            else
            {
                SymNode *temp = minNode(root->right);
                root->key = temp->key;
                root->address = temp->address;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        root->height = 1 + max(findheight(root->left), findheight(root->right));
        int balance = bf(root);
        if (balance > 1 && bf(root->left) >= 0)
        {
            root = root->RightRightRotation();
        }
        if (balance > 1 && bf(root->left) < 0)
        {
            root = root->LeftRightRotation();
        }
        if (balance < -1 && bf(root->right) <= 0)
        {
            root = root->LeftLeftRotation();
        }
        if (balance < -1 && bf(root->right) > 0)
        {
            root = root->RightLeftRotation();
        }

        return root;
    }
    void remove(string k)
    {
        int s = search(k);
        if (s == -2)
        {
            return;
        }
        size--;
        root = deleteNode(root, k);
    }
    int finder(SymNode *root, string k)
    {
        if (root == NULL)
            return -2;
        else if (root->key == k)
            return root->address;
        else if (root->key > k)
        {
            int val = finder(root->left, k);
            return val;
        }
        else
        {
            int val = finder(root->right, k);
            return val;
        }
    }
    int search(string k)
    {
        return finder(root, k);
    }

    void assign_address(string k, int idx)
    {
        SymNode *temp = root;
        while (temp != NULL)
        {
            if (k < temp->key)
            {
                temp = temp->left;
            }
            else if (k > temp->key)
            {
                temp = temp->right;
            }
            else
            {
                temp->address = idx;
                return;
            }
        }
        if (temp == NULL)
        {
            insert(k);
            assign_address(k, idx);
        }
    }

    int get_size()
    {
        return size;
    }

    SymNode *get_root()
    {
        return root;
    }
    void destruct(SymNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        destruct(root->left);
        destruct(root->right);
        delete root;
    }
    ~SymbolTable()
    {
        destruct(root);
    }
};

class Hashtable
{
public:
    vector<SymbolTable *> htable; // to be changed

    Hashtable()
    {

        htable = std::vector<SymbolTable *>(101);
        for(int i=0;i<101;i++){
            htable[i]= new SymbolTable();
        }
    }

    int hash(std::string id) // to be changed;
    {
         int hashvalue = 1;
        int k = 7;
        for (int i = 0; i < id.size(); i++)
        {
            if (i < k)
                hashvalue = hashvalue * int(id[i]);
            else
            {
                hashvalue += int(id[i]);
            }
        }

        hashvalue = hashvalue % 101;
        return abs(hashvalue);
    }

    vector<SymbolTable *> gethashtable()
    {
        return htable;
    }
    ~Hashtable()
    {
        for (int i = 0; i < 101; i++)
        {
            htable[i]->destruct(htable[i]->get_root());
        }
    }
};

class Dict
{
private:
    Hashtable * ht;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
