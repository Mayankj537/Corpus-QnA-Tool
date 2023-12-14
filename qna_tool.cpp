#include "qna_tool.h"
#include <assert.h>
#include <sstream>

using namespace std;

string stringconverterto(string s) {
  string s_new = "";
  for (int i = 0; i < s.size(); i++) {
    if ((int(s[i]) >= 'A' && int(s[i]) <= 'Z')) {
      s_new += std::tolower(s[i]);
    } else {
      s_new += s[i];
    }
  }
  return s_new;
}

QNA_tool::QNA_tool() {
  // Implement your function here


}

QNA_tool::~QNA_tool() {
  // Implement your function here
    for(auto c:collection){
      delete c;
    }
  

  
}

double QNA_tool::score(string word) {
  
  long long k;
  ifstream file("unigram_freq.csv");
  if (!file.is_open()) {
    std::cerr << "ERROR" << std::endl;
  }
  string line;
  int i = 0;
  while (std::getline(file, line)) {
    i++;
    if (i == 1)
      continue;
    std::istringstream iss(line);
    std::string val1, val2;

    if (std::getline(iss, val1, ',') && std::getline(iss, val2, ',')) {
      if (val1 == word) {
       
        k = stoll(val2);
        break;
      }
    }
  }
  file.close();
  
 
  double score = static_cast<double>(Corpora.get_word_count(word) + 1) /(k + 1);
  
  return score;
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph,
                               int sentence_no, string sentence) {
  // Implement your function here
  // string s = "";
  // for (int i = 0; i <= sentence.size(); i++) {

  //   string sep = ".,-:!\"\'()?[];@  ";
  //   int hashvalue = 0;
  //   if ((i == sentence.size() && s != "") ||
  //       (sep.find(sentence[i]) != string::npos)) {
  //     s = stringconverterto(s);
  //     if (true) {
  //       hashvalue = ht->hash(s);
  //       // cout<<hashvalue<<endl;
  //       if (ht->htable[hashvalue]->search(s) == -2) {
  //         ht->htable[hashvalue]->insert(s);
  //         SymNode *p = ht->htable[hashvalue]->get_root();
  //         while (p != NULL) {
  //           if (p->key == s) {
  //             p->linkedlistword.addwordcount(book_code, page, paragraph);
  //             break; // to be written
  //           } else if (s < p->key) {
  //             p = p->left;
  //           } else {
  //             p = p->right;
  //           }
  //         }
  //       } else {
  //         SymNode *p = ht->htable[hashvalue]->get_root();
  //         while (p != NULL) {
  //           if (p->key == s) {
  //             p->wordcount++;
  //             break; // to be written
  //           } else if (s < p->key) {
  //             p = p->left;
  //           } else {
  //             p = p->right;
  //           }
  //         }
  //       }
  //     }
  //     s = "";
  //   }

  //   else {
  //     s += sentence[i];
  //   }
  // }

  // return;
  // cout<<sentence<<endl;
  // cout<<book_code<<" "<<page<<" "<<paragraph<<endl;
  Corpora.insert_sentence(book_code,page,paragraph,sentence_no,sentence);
  // cout<<Corpora.get_word_count("november")<<endl;
  if((book_code!=lastbook)||(paragraph!=lastparagraph)||(lastpage!=page)){
    // cout<<"HI"<<endl;
    para* p= new para;
    p->book_code=book_code;
    p->paragraph=paragraph;
    p->page=page;
    
    p->dict.insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    lastbook= book_code;
    lastparagraph =paragraph;
    lastpage=page;
    
    collection.push_back(p);
  //   cout<<"HI"<<endl;
  //   cout<<lastbook<<" "<<lastparagraph<<" "<<lastpage<<endl;
  //   cout<<collection[0]->dict.get_word_count("november")<<endl;
  }
  else if((book_code==lastbook)&&(paragraph==lastparagraph)&&(lastpage==page)){
    // cout<<"else"<<endl;
    collection[collection.size()-1]->dict.insert_sentence(book_code,page,paragraph,sentence_no,sentence);

  }
  
}
void tolower(string &word)
{
  for(char &c:word)
  {
    if(c> 'A' && c<'Z') c = c - 'A' + 'a';
  }
}
void QNA_tool::scorer(vector<para* > &k,string question){
 
  // vector<string> words;
  // string s = "";
  // for (int i = 0; i < question.size(); i++) {
  //   string sep = ".,-:!\"\'()?[];@  ";
  //   if ((i == (question.size() - 1) && s != "") ||
  //       (sep.find(question[i]) != string::npos)) {
  //     s = stringconverterto(s);
  //     words.push_back(s);
  //   } else {
  //     s += question[i];
  //   }
  // }
  std::vector<std::string> words;
    std::string word="";
    string seprators =".,-:!\"\'( )?[ ]; @";
    for (char ch : question) {
        if (seprators.find(ch)!=string::npos){
            if (!word.empty()) {
              
                tolower(word);
              
                words.push_back(word);
                word.clear();

            }
        } else {
            word += ch;
        }
    }

    // Push the last word if any
    if (!word.empty()) {
        words.push_back(word);
    }

   
  vector<pair<string,double> > scores;
  
  for(int i=0;i<words.size();i++){

    double sc= score(words[i]);
    pair <string,double> p;
    p.first =words[i];
    p.second= sc;
    scores.push_back(p);\


  }
  for(para* c:k){
    for(int i=0;i<words.size();i++){
    c->Score+=(double)(scores[i].second)*(double)(c->dict.get_word_count(words[i]));
    

  }
    

  }
  
}

Node *QNA_tool::get_top_k_para(string question, int k) {
  // cout<<1<<endl;
  scorer(collection,question);
  // vector<string> words;
  // string s = "";
  // for (int i = 0; i < question.size(); i++) {
  //   string sep = ".,-:!\"\'()?[];@  ";
  //   if ((i == (question.size() - 1) && s != "") ||
  //       (sep.find(question[i]) != string::npos)) {
  //     s = stringconverterto(s);
  //     words.push_back(s);
  //   } else {
  //     s += question[i];
  //   }
  // }
  
  MaxHeap maxheap;
  // for (int i = 0; i < 100; i++) {
  //   if (getwordcountbook1(words,i)==0)
  //       continue;
  //   for (int j = 0; j < 600; j++) {
  //       if (getwordcountpage1(words,i,j)==0)
  //           continue;
  //     for (int k = 0; k < 20; k++) {
  //       scorepara = 0;
  //       for (string ch : words) {
  //         ch = stringconverterto(ch);
  //         hashvalue = ht->hash(ch);
  //         SymNode *p = ht->htable[hashvalue]->get_root();
  //         while (p != NULL) {
  //           if (p->key == ch) {
  //             freq = p->linkedlistword.getwordcountpara(i, j, k);
  //             break; // to be written
  //           } else if (ch < p->key) {
  //             p = p->left;
  //           } else {
  //             p = p->right;
  //           }
  //         }

  //         scorepara += (score(ch) * freq);
  //       }
  //       if (scorepara != 0) {
  //         Node *n = new Node(i, j, k);
  //         maxheap.push(make_pair(scorepara, n));
  //       }
  //     }
  //   }
  // }
  for(para* c:collection){
    if(c->Score!=0){
    Node* n=new Node(c->book_code,c->page,c->paragraph,0,0);
    
  
    maxheap.push(make_pair(c->Score,n));
    }
    
  }


  Node* p1;
  //Node *p2;
  auto topElement = maxheap.pop();
  
  Node* head = new Node(topElement.second->book_code, topElement.second->page,
                  topElement.second->paragraph,0,0);
  p1 = head;
  k--;

  while (k >0 && !maxheap.empty()) {
    k--;
    auto topElement = maxheap.pop();
    
    Node* p2 = new Node(topElement.second->book_code, topElement.second->page,
                  topElement.second->paragraph,0,0);
    p1->right = p2;
    p2->left = p1;
    p1 = p2;
  }

  return head;
  // Implement your function here

}

void QNA_tool::query(string question, string filename) {
  // Implement your function here
  std::cout << "Q: " << question << std::endl;
  std::cout << "A: "
            << "Studying COL106 :)" << std::endl;
  return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}


void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY,
                         string question) {

  // first write the k paragraphs into different files

  Node *traverse = root;
  int num_paragraph = 0;

  while (num_paragraph < k) {
    assert(traverse != nullptr);
    string p_file = "paragraph_";
    p_file += to_string(num_paragraph);
    p_file += ".txt";
    // delete the file if it exists
    remove(p_file.c_str());
    ofstream outfile(p_file);
    string paragraph =
        get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
    assert(paragraph != "$I$N$V$A$L$I$D$");
    outfile << paragraph;
    outfile.close();
    traverse = traverse->right;
    num_paragraph++;
  }

  // write the query to query.txt
  ofstream outfile("query.txt");
  outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the "
             "basis of this, ";
  outfile << question;
  // You can add anything here - show all your creativity and skills of using
  // ChatGPT
  outfile.close();

  // you do not need to necessarily provide k paragraphs - can configure
  // yourself

  // python3 <filename> API_KEY num_paragraphs query.txt
  string command = "python3 ";
  command += filename;
  command += " ";
  command += API_KEY;
  command += " ";
  command += to_string(k);
  command += " ";
  command += "query.txt";

  system(command.c_str());
  return;
}
