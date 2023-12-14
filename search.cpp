// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine()
{
    // Implement your function here
    vector<container> a;
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}

string stringconverter1(string s)
{
    string s_new = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (int(s[i]) >= 65 && int(s[i]) <= 122)
        {
            s_new += std::tolower(s[i]);
        }
        else
        {
            s_new += s[i];
        }
    }
    return s_new;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    sentence = stringconverter1(sentence);
    container temp = container(book_code, page, paragraph, sentence_no, sentence);
    a.push_back(temp);
}

vector<int> search1(string word, string sentence)
{
    vector<int> a;
    int n = sentence.size();
    int m = word.size();
    int hash_0 = 0;
    for (int i = 0; i < m; i++)
    {
        hash_0 = (hash_0 + int(sentence[i]));
    }
    int hash_w = 0;
    for (int i = 0; i < m; i++)
    {
        hash_w = ((hash_w + int(word[i])));
    }

    for (int i = 0; i < n - m + 1; i++)
    {
        if (hash_0 == hash_w)
        {

            if (word == sentence.substr(i, m))
            {
                a.push_back(i);
            }
        }
        else
        {

            hash_0 = hash_0 - int(sentence[i]) + int(sentence[m + i]);
        }
    }
    return a;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    Node *head = NULL;
    for (int i = 0; i < a.size(); i++)
    {
        vector<int> v;
        v = search1(pattern, a[i].sentence);
        if (v.size() != 0)
        {
            for (int j = 0; j < v.size(); j++)
            {
                Node *p = head;
                if (p == NULL)
                {
                    p = new Node(a[i].book_code, a[i].page, a[i].paragraph, a[i].sentence_no, v[j]);
                    head = p;
                }
                else
                {
                    while (p->right != NULL)
                    {
                        p = p->right;
                    }
                    p->right = new Node(a[i].book_code, a[i].page, a[i].paragraph, a[i].sentence_no, v[j]);
                    p->right->left = p;
                }
            }
        }
    }
    Node *p = head;
    while (p->right != NULL)
    {
        n_matches++;
        p = p->right;
    }
    n_matches++;
    return head;
}

// int main()
// {
//     int n;
//     SearchEngine *se = new SearchEngine();
//     se->insert_sentence(1, 1, 1, 1, "I am Handsome");
//     se->insert_sentence(1, 1, 1, 1, "I am Genius");
//     se->insert_sentence(1, 1, 1, 1, "I am a Myran eni some");
//     Node * n1=se->search("some", n);
//     cout<<n;
// }