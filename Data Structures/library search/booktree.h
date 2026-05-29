/*****************************************
** File:    booktree.h
** Project: CMSC 341 Project 2, Fall 2025
** Author:  Akanksha Madhu Kiran
** Date:    10/21/2025
** E-mail:  amadhuk1@umbc.edu
** This file contains the booktree header file.
*****************************************/
#ifndef BOOKTREE_H
#define BOOKTREE_H
#include <string>
#include <iostream>
using namespace std;
#define DELIMITER " "
class Grader;//for grading purposes
class Tester;//for your test cases
class BookTree;
class BNode;
class Wordtree;
class Book{
    public:
        Book(string author, string title, string text){
            m_author=author;
            m_title=title;
            m_text=text;
        }
        string m_author;
        string m_title;
        string m_text;
};

class Node {
    public:
        friend class Grader;
        friend class Tester;
        friend class WordTree;
        friend class BookTree;
        Node(const string& v){ 
            m_word=v; 
            m_left=nullptr;
            m_right=nullptr;
            m_height=0;
            m_count=0;
        }
        void printWord(){
            cout << m_word << endl;
        }
        int getFrequency(){
            return m_count;
        }
        int getHeight(){
            return m_height;
        }
        string getValue(){
            return m_word;
        }
    private:
        string  m_word;
        Node*   m_left;
        Node*   m_right;
        int     m_height;
        int     m_count;
};

class WordTree{
    public:
        friend class Grader;
        friend class Tester;
        friend class BookTree;
        WordTree(){
            m_root=nullptr;
        }
        ~WordTree();
        void insert(const string& word);
        Node* find(const string& word);
        bool remove(const string& word);
        void dump(std::ostream& ostr = std::cout);
        int searchCount(string word);
        int getTreeHeight();
        
    private:
        Node* m_root;
        // ***************************************************
        // Any private helper functions must be delared here!
        // ***************************************************
        void clear(Node* &cur);
        Node* rebalance(Node* node);
        Node* rotateLeft(Node* x);
        Node* rotateRight(Node* x);
        int nodeHeight(Node* n);
        void updateHeight(Node* n);
        int balanceFactor(Node* n);
        Node* removeRec(Node* cur, const std::string& word, bool& removed);
        Node* insertRec(Node* cur, const string& word);
        void dump(Node* aNode, std::ostream& ostr);
        bool checkEmpty();
};

class BNode{
    public:
        friend class Grader;
        friend class Tester;
        friend class BookTree;
        BNode();
        BNode(string title, string author, string text);
        ~BNode();
        int findFrequency(string word);
        int searchCount(string word);
        int getTextTreeHeight();

    private:
        string m_title;
        string m_author;
        WordTree m_tree;
        BNode* m_left;
        BNode* m_right;

};

class BookTree{
    public:
        friend class Grader;
        friend class Tester;
        BookTree();
        ~BookTree();
        void dump(bool verbose=false) const;
        void loadData(Book data[], int arrayLength);
        bool insert(string title, string author, string text);
        int findFrequency(string title, string word);
        bool removeWord(string title, string word);
        int searchCount(string title, string word);
        int getTextTreeHeight(string title);
        string getRootKey();//returns the book title at root

    private:
        BNode* m_root;

        // ***************************************************
        // Any private helper functions must be delared here!
        // ***************************************************
        void clear(BNode* &cur);
        BNode* splay(BNode *root, const std::string &key);
        BNode* rotateLeft(BNode* x);
        BNode* rotateRight(BNode* x);
        static bool lessTitle(const std::string& a, const std::string& b);
        Node* removeRec(Node* cur, const string& word, bool& removed);
        void dumpHelper(BNode* root, bool verbose=false) const;
        
        
};
#endif
