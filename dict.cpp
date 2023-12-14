// Do NOT add any other includes
#include "dict.h"
#include <fstream>

Dict::Dict()
{
    ht = new Hashtable();
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

Dict::~Dict()
{
     delete ht;
}

string stringconverter(string s)
{
    string s_new = "";
    for (int i = 0; i < s.size(); i++)
    {
        if ((int(s[i]) >= 'A' && int(s[i]) <= 'Z'))
        {
            s_new += std::tolower(s[i]);
        }
        else{
            s_new+=s[i];
        }
    }
    return s_new;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    string s = "";
    for (int i = 0; i <= sentence.size(); i++)
    {
        
        string sep=".,-:!\"\'()?[];@  ";
        
        int hashvalue=0;
        if ((i == sentence.size() && s!="" )|| (sep.find(sentence[i])!=string::npos) )
        {
            s = stringconverter(s);
            if (true){
            hashvalue=ht->hash(s);
            // cout<<hashvalue<<endl;
            if (ht->htable[hashvalue]->search(s) == -2)
            {
                ht->htable[hashvalue]->insert(s);
            }
            else
            {
                SymNode *p = ht->htable[hashvalue]->get_root();
                while (p != NULL)
                {
                    if (p->key == s)
                    {
                        p->wordcount++;
                        break; // to be written
                    }
                    else if (s < p->key)
                    {
                        p = p->left;
                    }
                    else
                    {
                        p = p->right;
                    }
                }
            }
            }
            s = "";
        }

        else
        {
            s += sentence[i];
        }
    }
    return;

}

long long Dict::get_word_count(string word)
{
    // Implement your function here
    word = stringconverter(word);
    int hashvalue=ht->hash(word);
    SymNode *p = ht->htable[hashvalue]->get_root();
    while (p != NULL)
    {
        if (p->key == word)
        {
            return p->wordcount; // to be written
        }
        else if (word < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return 0;
}

void Inorder(SymNode *root, vector<string> &vs)
{
    string s = "";
    if (root == NULL)
        return;
    Inorder(root->left, vs);
    s += root->key + ", " + std::to_string(root->wordcount);
    vs.push_back(s);
    Inorder(root->right, vs);
}

void Dict::dump_dictionary(string filename)
{
    ofstream ip(filename.c_str());
    fstream file;
    vector<string> commands;
    for(int i=0;i<101;i++){
    Inorder(ht->htable[i]->get_root(), commands);
    }
    // sort(commands.begin(),commands.end());
    file.open(filename, ios::out | ios::app);
    for (int i = 1; i < commands.size(); i++)
    {
        file << commands[i] << endl;
    }
    file.close();
}

// int main()
// {
//     Dict *d = new Dict();
//     std::string sentence1 = "The brown.fox jump.s dog.A   &Ankit";
//     std::string sentence2 = "She sells seashells by t he seashore.";
//     std::string sentence3 = "Programming is both an art and a science.";
//     std::string sentence4 = "Life is like a bicycle, to keep your balance, you must keep moving.";
//     std::string sentence5 = "In three words I can sum up everything I've learned about life, it goes on.";
//     d->insert_sentence(0, 0, 0, 0, sentence1);
//     d->insert_sentence(0, 0, 0, 0, sentence2);
//     d->insert_sentence(0,0,0,0,sentence3);
//     d->insert_sentence(0,0,0,0,sentence4);
//     d->insert_sentence(0,0,0,0,sentence5);
//     d->dump_dictionary("output3.txt");
// }
 
