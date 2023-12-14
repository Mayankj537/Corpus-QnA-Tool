#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;
class para {
    public:
    int book_code;
     int page;
     int paragraph;
     Dict dict;
     double Score=0;
};

class MaxHeap {
private:
    std::vector<std::pair<double, Node * > > heap;

    // Helper function to heapify the vector
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].first > heap[parent].first) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } 
            else {
                break;
            }
        }
    }

public:
    // Function to push an element into the max heap
    void push(const std::pair<double, Node *>& element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    // Function to pop the maximum element from the max heap
    std::pair<double, Node *> pop() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        std::pair<double, Node *> result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        // Heapify down
        int index = 0;
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < heap.size() && heap[leftChild].first > heap[largest].first) {
                largest = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild].first > heap[largest].first) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }

        return result;
    }

    // Function to check if the max heap is empty
    bool empty() const {
        if(heap.size()==0){
            return true;
        }
        else{
            return false;
        }
    }
};






class QNA_tool {

private:
    
    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user
    
    
    // You can add attributes/helper functions here
    
public:

    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
    vector <para *> collection;
    Dict Corpora;
    int lastpage=-1;
    int lastparagraph=-1;
    int lastbook=-1;
    double score(string word);//from private to public;
    void scorer(vector<para* > &k,string question);
    
    
    
    
};