/*****************************************
** File:    booktree.cpp
** Project: CMSC 341 Project 2, Fall 2025
** Author:  Akanksha Madhu Kiran
** Date:    10/21/2025
** E-mail:  amadhuk1@umbc.edu
** This file contains the booktree class.
*****************************************/
#include "booktree.h"
BookTree::BookTree(){//constructor
    m_root = nullptr;
}

BookTree::~BookTree(){//destructor to clear tree memory
    if(m_root != nullptr){
        clear(m_root);
        m_root = nullptr;
    }
}


void BookTree::loadData(Book data[], int arrayLength){//loads book data into tree
	for (int i = 0; i < arrayLength; i++){//loops and inserts into tree
        insert(data[i].m_title, data[i].m_author, data[i].m_text);
    }
}




int BookTree::findFrequency(string title, string word){
    if (m_root == nullptr){//check if empty tree
        return 0;
    }

    //convert letters of word to lowercase
    for (char &c : word){
        if (c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }
    }

    BNode* cur = m_root;
    BNode* parent = nullptr;

    while (cur != nullptr){//loop to search book title
        parent = cur;
        if (title == cur->m_title) { //move found node to root using splay
            m_root = splay(m_root, title);
            Node* n = m_root->m_tree.find(word);//search word
            return (n != nullptr) ? n->m_count : 0;

        } else if (lessTitle(title, cur->m_title)) {
            cur = cur->m_left;
        } else {
            cur = cur->m_right;
        }
    }
    if (parent != nullptr) {
        m_root = splay(m_root, parent->m_title);//still splay if not found
    }

    return 0;//to return if not found
}




int BookTree::searchCount(string title, string word) {
    if (!m_root){//check if empty
        return 0;
    }

    int nodesVisited = 0;
    BNode* cur = m_root;
    BNode* last = nullptr;

    //convert search title to lowercase
    for (char &c : title)
        if (c >= 'A' && c <= 'Z') c += ('a' - 'A');

    while (cur != nullptr){//traverse until tree is found
        nodesVisited++;
        last = cur;

        if (title == cur->m_title) {
            //Found splay the found node
            m_root = splay(m_root, cur->m_title);
            return nodesVisited;
        }
        else if (title < cur->m_title) {
            cur = cur->m_left;
        }
        else {
            cur = cur->m_right;
        }
    }

    //Not found splay the last checked node
    if (last)
        m_root = splay(m_root, last->m_title);

    return nodesVisited;
}



int BookTree::getTextTreeHeight(string title){
    if (m_root == nullptr){
        return -1;//check if empty
    }
    
    //search for book
    BNode *cur = m_root;
    while (cur != nullptr){
        if (title == cur->m_title){
            m_root = splay(m_root, title);//splay when found
            if (m_root != nullptr && m_root->m_title == title) {
                 return m_root->getTextTreeHeight();//get height of the key
            }
            return -1;
        } else if (lessTitle(title, cur->m_title)){
            cur = cur->m_left;
        } else {
            cur = cur->m_right;
        }
    }
    return -1;//if not found
}


string BookTree::getRootKey(){
	// implementation is provided
	// do not modify this function
	return m_root->m_title;
}


bool BookTree::insert(string title, string author, string text){//inserts new book based on title
    if (m_root == nullptr){ //cretes new node/tree if empty tree
        m_root = new BNode(title, author, text);
        return true;
    }

    
    m_root = splay(m_root, title);//to bring node with closest node to root using splay

    if (m_root->m_title == title){
        return false;
    }


    BNode *n = new BNode(title, author, text);//Create new node
    if (lessTitle(title, m_root->m_title)){//attach left and right childs
        n->m_right = m_root;
        n->m_left = m_root->m_left;
        m_root->m_left = nullptr;
    } else {
        n->m_left = m_root;
        n->m_right = m_root->m_right;
        m_root->m_right = nullptr;
    }
    m_root = n;//update root
    return true;

}
bool BookTree::removeWord(string title, string word){
    for (char &c : word) {//covert to lower case
        if (c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }
    }

    BNode *cur = m_root;//find book node
    while (cur != nullptr){
        if (title == cur->m_title){
            return cur->m_tree.remove(word);//to remove word
        } else if (lessTitle(title, cur->m_title)){
            cur = cur->m_left;
        } else {
            cur = cur->m_right;
        }
    }
    return false;//if not found
}


void BookTree::dump(bool verbose) const{//displays booktree
	dumpHelper(m_root, verbose);
    cout << endl;
}



/////////////////////////Wordtree//////////////////////////////////////////

WordTree::~WordTree(){//destructor clears AVL tree
    clear(m_root);
    m_root = nullptr;
}

Node* WordTree::find(const string& word){//searches word node
    Node *cur = m_root;
    while (cur != nullptr){
        if (word == cur->m_word){
            return cur;
        }
        if (word < cur->m_word){
            cur = cur->m_left;//move to left child 
        } else {
            cur = cur->m_right;//move to right side
        }
    }
    return nullptr;//if not found
}

bool WordTree::remove(const string& word){//removes word node
    bool removed = false;
    m_root = removeRec(m_root, word, removed);
    return removed;
}

Node* WordTree::removeRec(Node* cur, const string& word, bool& removed) {
    if (cur == nullptr){
        return nullptr;
    }

    if (word < cur->m_word) {
        cur->m_left = removeRec(cur->m_left, word, removed);
    } else if (word > cur->m_word) {
        cur->m_right = removeRec(cur->m_right, word, removed);
    } else {
        removed = true;
        if (cur->m_count > 1) {//if duplication just decrement
            cur->m_count--;
            return cur;
        }

        //node with one child or no child
        if (cur->m_left == nullptr || cur->m_right == nullptr) {
            Node* child = (cur->m_left != nullptr) ? cur->m_left : cur->m_right;
            delete cur;
            return child;
        }

        //node with two children
        Node* pred = cur->m_left;
        while (pred->m_right != nullptr){
            pred = pred->m_right;
        }


        cur->m_word = pred->m_word;
        cur->m_count = pred->m_count;
        bool check_removed = false;
        cur->m_left = removeRec(cur->m_left, pred->m_word, check_removed);//delete
    }
    
    if (cur == nullptr){
        return nullptr;
    }
    return rebalance(cur);//rebalance
}



void WordTree::insert(const string& word){
    if(word.empty()){
        return;
    }
    string lowerWord = word;//make a copy
    for (char &c : lowerWord) {
        if (c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }
    }

    m_root = insertRec(m_root, lowerWord);//insert into tree
}

Node* WordTree::insertRec(Node* cur, const string& word) {
    if (!cur) {//if empty
        Node* n = new Node(word);
        n->m_count = 1;
        n->m_height = 0;
        return n;
    }
    if (word == cur->m_word) {
        cur->m_count++;//increment frequency
        return cur;
    }
    if (word < cur->m_word){
        cur->m_left = insertRec(cur->m_left, word);
    } else {
        cur->m_right = insertRec(cur->m_right, word);
    }
    return rebalance(cur);//to balance
}



int WordTree::searchCount(string word){
    //convert to lowercase
    for (char &c : word) {
        if (c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }
    }
    Node* cur = m_root;
    int count = 0;//visits nodes
    
    while (cur != nullptr) {
        if (word == cur->m_word) {
            return count;//return steps when found
        }
        count++;
        if (word < cur->m_word) {
            cur = cur->m_left;
        } else {
            cur = cur->m_right;
        }
    }
    return count;//return number of steps even if not found
}



int WordTree::getTreeHeight(){
    // implementation is provided
	// do not modify this function
    return m_root->m_height;
}

void WordTree::dump(std::ostream& ostr){
    dump(m_root, ostr);//get tree structure
}

void WordTree::dump(Node* aNode, std::ostream& ostr){//inorder dump
    if (aNode != nullptr){
        ostr << "[";
        dump(aNode->m_left, ostr);
        ostr << aNode->m_word << ":" << aNode->m_count << ":" << aNode->m_height;
        dump(aNode->m_right, ostr);
        ostr << "]";
    }
}

////////////////////////BNode////////////////////////////////////


BNode::BNode(){
    m_left = nullptr;
    m_right = nullptr;
}


BNode::BNode(string title, string author, string text){
    m_title = title;
    m_author = author;
    m_left = nullptr;
    m_right = nullptr;

    char (*localToLower)(char) = [](char c) -> char {//convert character
        if (c >= 'A' && c <= 'Z'){
            return c + ('a' - 'A');
        }
        return c;
    };

    string word;
    for (char c : text) {
        if (c == DELIMITER[0]) {//split text 
            if (!word.empty()) {
                m_tree.insert(word);//insert
                word.clear();
            }
        } else {
            word += localToLower(c);//add letters
        }
    }
    if (!word.empty()){
        m_tree.insert(word);//insert last word
    }
}

BNode::~BNode(){}//default constructor

int BNode::findFrequency(string word){
    for (char &c : word){
        if (c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }
    }
        
    Node* n = m_tree.find(word);//search wordtree
    return n ? n->getFrequency() : 0;
}


int BNode::searchCount(string word){//returns node visited
    return m_tree.searchCount(word);
}


int BNode::getTextTreeHeight(){//returns height
    return m_tree.getTreeHeight();
}

//helper functions
///////////////////////////////////////////////////////////////////////////////

void BookTree::dumpHelper(BNode* root, bool verbose) const{//helper for dump
    if(root != nullptr){
        cout << "(";//start of subtree
        dumpHelper(root->m_left, verbose);
        if(verbose){
            cout << root->m_title << ":" << root->m_author;//show details
            root->m_tree.dump();
        } else {
            cout << root->m_title;//only show title
        }
        dumpHelper(root->m_right, verbose);
        cout << ")";//end of subtree
   }
}

void BookTree::clear(BNode *&cur){//deletes all nodes
    if (cur != nullptr){
        clear(cur->m_left);
        clear(cur->m_right);
        delete cur;
        cur = nullptr;
    }
}



BNode* BookTree::rotateRight(BNode *x){ //Right rotation
    BNode *y = x->m_left;
    x->m_left = y->m_right;
    y->m_right = x;
    return y;
}


BNode* BookTree::rotateLeft(BNode *x){ //Left rotation
    BNode *y = x->m_right;
    x->m_right = y->m_left;
    y->m_left = x;
    return y;
}


BNode* BookTree::splay(BNode *root, const std::string &key){ //get node with key up to root
    if (root == nullptr){
        return root;
    }

    //Root matches
    if (root->m_title == key){
        return root;
    }

    //Key in left subtree
    if (lessTitle(key, root->m_title)){
        if (root->m_left == nullptr){
            return root;
        }

        if (lessTitle(key, root->m_left->m_title)){
                root->m_left->m_left = splay(root->m_left->m_left, key);
                root = rotateRight(root);//first rotation
        } 
        else if (lessTitle(root->m_left->m_title, key)){
                root->m_left->m_right = splay(root->m_left->m_right, key);
                if (root->m_left->m_right != nullptr){
                    root->m_left = rotateLeft(root->m_left);
                }
        }
        return (root->m_left == nullptr) ? root : rotateRight(root);
    } else {
        if (root->m_right == nullptr){//Key in right subtree
            return root;
        }

        if (lessTitle(root->m_right->m_title, key)){
            root->m_right->m_right = splay(root->m_right->m_right, key);
            root = rotateLeft(root);
        } 
        else if (lessTitle(key, root->m_right->m_title)){
            root->m_right->m_left = splay(root->m_right->m_left, key);
            if (root->m_right->m_left != nullptr){
                root->m_right = rotateRight(root->m_right);
            }
        }
        return (root->m_right == nullptr) ? root : rotateLeft(root);
    }
}

bool BookTree::lessTitle(const std::string& a, const std::string& b){
    
    int i = 0;
    while (i < (int)a.length() && i < (int)b.length()) {
        char ca = a[i];
        char cb = b[i];
        if (ca >= 'A' && ca <= 'Z'){
            ca += ('a' - 'A');
        }
        if (cb >= 'A' && cb <= 'Z'){
            cb += ('a' - 'A');
        }
        if (ca != cb){
            return ca < cb;
        }
        i++;
    }
    return a.length() < b.length();
}



void WordTree::clear(Node *&cur){//clears WordTree
    if (cur != nullptr){
        clear(cur->m_left);
        clear(cur->m_right);
        delete cur;
        cur = nullptr;
    }
}

bool WordTree::checkEmpty(){//if empty returns true
    if(m_root == nullptr){
        return true;
    } else {
        return false;
    }
}

int WordTree::nodeHeight(Node* n) {//returns height
    return n ? n->m_height : -1;
}

void WordTree::updateHeight(Node* n) {//updates height
    if(n){
        int lh = nodeHeight(n->m_left);
        int rh = nodeHeight(n->m_right);
        n->m_height = 1 + (lh > rh ? lh : rh);
    }
}


int WordTree::balanceFactor(Node* n) {//calculate balance factor
    return n ? nodeHeight(n->m_left) - nodeHeight(n->m_right) : 0;
}

Node* WordTree::rotateRight(Node* y) {
    Node* x = y->m_left;
    Node* T2 = x->m_right;
    x->m_right = y;
    y->m_left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* WordTree::rotateLeft(Node* x) {
    Node* y = x->m_right;
    Node* T2 = y->m_left;
    y->m_left = x;
    x->m_right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* WordTree::rebalance(Node* n) {
    updateHeight(n);
    int bf = balanceFactor(n);
    if (bf > 1) {
        if (balanceFactor(n->m_left) < 0){
            n->m_left = rotateLeft(n->m_left);
        }
        return rotateRight(n); 
    }
    if (bf < -1) {
        if (balanceFactor(n->m_right) > 0){
            n->m_right = rotateRight(n->m_right);
        }
        return rotateLeft(n); 
    }
    return n;
}



