// /*****************************************
// ** File:    mytest.cpp
// ** Project: CMSC 341 Project 2, Fall 2025
// ** Author:  Akanksha Madhu Kiran
// ** Date:    10/21/2025
// ** E-mail:  amadhuk1@umbc.edu
// ** This file contains all the test cases.
// *****************************************/

#include "booktree.h"
using namespace std;

//database format: "Author's name", "Book title", "Text from book"
Book database[9] = {
    Book("Charles Dickens","Great Expectations","I give Pirrip as my fathers family name ..."),
    Book("Charles Dickens","A TALE OF TWO CITIES","Two other passengers besides the one were plodding ..."),
    Book("MARK TWAIN","THE ADVENTURES OF TOM SAWYER","Hang the boy cant I never learn anything ..."),
    Book("MARK TWAIN","ADVENTURES OF HUCKLEBERRY FINN","We played robber now and then about a month ..."),
    Book("Jane Austen","Pride and Prejudice","An invitation to dinner was soon afterwards dispatched ..."),
    Book("Herman Melville","Moby Dick","It was a queer sort of place a gable ended old house ..."),
    Book("Frank Baum","The Wonderful Wizard of Oz","This at first seemed a great misfortune ..."),
    Book("Fyodor Dostoyevsky","The Brothers Karamazov","Those innocent eyes slit my soul up like a razor ..."),
    Book("Edgar Allan Poe","The Masque of the Red Death","It was a voluptuous scene that masquerade ...")
};


class Tester {
public:
    Tester();

    bool testAVLBalanceInsert();
    bool testBSTPropertyInsert();
    bool testSplayInsertRoot();
    bool testAVLBalanceRemove();
    bool testBSTAfterRemove();
    bool testWordRemoveMultiple();
    bool testFindMultiple();
    bool testSearchCountBookTree();
    bool testFindFrequencyBookTree();
    bool testDuplicateInsertFrequency();
    bool testRemoveSingleOccurrence();
    bool testRemoveDecrementFrequency();
    bool testDeepAVLRotations();
    bool testSearchCountMissingWord();
    bool testFindFrequencyNonexistentBook();
    bool testEmptyTreeRemove();
    bool testSplayRootUpdate();
    bool testInsertAlphabeticalOrder();
    bool testCaseInsensitiveSearchCount();
    bool testMassInsertionBalance();
    bool testBookTreeWordFrequencyEdge();

    void TestResult();

private:
    int m_passed;
    int m_failed;
    //Helpers
    bool isBST(Node* node, string lessV = "", string moreV = ""){//to check if BST
        if (!node){//if empty node
            return true;
        }
        if ((lessV != "" && node->m_word <= lessV) || (moreV != "" && node->m_word >= moreV)){
            return false;
        }
        bool check1 = isBST(node->m_left, lessV, node->m_word);
        bool check2 = isBST(node->m_right, node->m_word, moreV);
        
        return check1 && check2;
    }

    bool isBalanced(Node* node) {//check AVL balance and height
        if (!node){
            return true;
        }
        int lh = node->m_left ? node->m_left->m_height : -1;
        int rh = node->m_right ? node->m_right->m_height : -1;

        if (abs(lh - rh) > 1){//to check if balance valid
            return false;
        }

        int expected = 1 + (lh > rh ? lh : rh);
        if (node->m_height != expected){//to make sure height matches
            return false;
        }
        return isBalanced(node->m_left) && isBalanced(node->m_right);
    }

    //check BookTree BST
    bool checkBookBST(BNode* node, string lessV = "", string moreV = "") {
        if (!node){
            return true;
        }
        if ((lessV != "" && node->m_title <= lessV) || (moreV != "" && node->m_title >= moreV)){
            return false;
        }

        bool check1 = checkBookBST(node->m_left, lessV, node->m_title);
        bool check2 = checkBookBST(node->m_right, node->m_title, moreV);
        
        return check1 && check2;
    }

    //check all WordTrees in BookTree for balance
    bool checkAllBalanced(BNode* bnode) {
        if (!bnode){
            return true;
        }
        if (!isBalanced(bnode->m_tree.m_root)){
            return false;
        }
        return checkAllBalanced(bnode->m_left) && checkAllBalanced(bnode->m_right);
    }

    //check all WordTrees in BookTree for BST property
    bool checkAllBST(BNode* bnode) {
        if (!bnode){
            return true;
        }
        if (!isBST(bnode->m_tree.m_root)){
            return false;
        }
        return checkAllBST(bnode->m_left) && checkAllBST(bnode->m_right);
    }
};



Tester::Tester(){//Constructor
    m_passed = 0;
    m_failed = 0;
}


bool Tester::testAVLBalanceInsert(){//check AVL balance after inserting
    BookTree bt;
    bt.insert("Book1","Author1","Harry Potter");
    bt.insert("Book2","Author2","Percy Jackson");
    bool pass = checkAllBalanced(bt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testBSTPropertyInsert(){//check BST after inserting
    BookTree bt;
    bt.insert("BookA","A","Students love Pizza");
    bt.insert("BookB","B","Student hate vegetables");
    bool pass = checkAllBST(bt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testSplayInsertRoot(){//check if splay tree root updates
    BookTree bt;
    const char* titles[] = {"Spone", "Sptwo", "Spthree", "Spfour"};
    bool pass = true;

    for (int i = 0; i < 4 && pass; i++) {
        bt.insert(titles[i], "A", "a b c");
        if (bt.m_root == nullptr || bt.m_root->m_title != titles[i]) {
            pass = false;
        }
        else if (!checkBookBST(bt.m_root, "", "")) {
            pass = false;
        }
    }

    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}



bool Tester::testAVLBalanceRemove(){//check balance after removing
    WordTree wt;
    string words[] = {"apple","orange","banana","cherry"};
    for(int i=0;i<4;i++){
        wt.insert(words[i]);
    }
    wt.remove("banana");
    bool pass = isBalanced(wt.m_root) && isBST(wt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testBSTAfterRemove(){//BST still valid after removing
    WordTree wt;
    string words[] = {"a","b","c","d","e"};
    for(int i=0;i<5;i++){
        wt.insert(words[i]);
    }
    wt.remove("c");
    bool pass = isBST(wt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testWordRemoveMultiple(){//check if removed same rbook title
    WordTree wt;
    wt.insert("apple"); 
    wt.insert("apple"); 
    wt.insert("apple");
    wt.remove("apple"); 
    wt.remove("apple"); 
    wt.remove("apple");
    bool pass = (wt.m_root == nullptr);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testFindMultiple(){//checks if correct return node frequency
    WordTree wt;
    wt.insert("apple"); 
    wt.insert("apple");
    Node* n = wt.find("apple");
    bool pass = (n!=nullptr && n->getFrequency()==2);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testSearchCountBookTree(){//check if search count works
    BookTree bt;
    bt.insert("Wizard of Oz", "Matilda", "Tinman Tinman Tinman");
    int count = bt.searchCount("Wizard of Oz", "Tinman");
    bool pass = (count == 1);
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testFindFrequencyBookTree(){//check frequency in booktree
    BookTree bt;
    bt.loadData(database,9);
    int freq = bt.findFrequency("The Wonderful Wizard of Oz","This");
    bool pass = (freq == 1);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testDuplicateInsertFrequency(){//check if duplicate titles increment frequency 
    WordTree wt;
    wt.insert("apple"); 
    wt.insert("apple");
    Node* n = wt.find("apple");
    bool pass = (n->getFrequency()==2);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testRemoveSingleOccurrence(){//to remove only one title if duplicated title
    WordTree wt;
    wt.insert("apple"); 
    wt.insert("apple");
    wt.remove("apple");
    Node* n = wt.find("apple");
    bool pass = (n != nullptr && n->getFrequency() == 1);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testRemoveDecrementFrequency(){//check frequency decreasing works
    WordTree wt;
    wt.insert("apple"); 
    wt.insert("apple");
    wt.remove("apple");
    Node* n = wt.find("apple");
    bool pass = (n && n->getFrequency()==1);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testDeepAVLRotations(){//rotation check
    WordTree wt;
    string words[] = {"m","b","q","a","c","z"};
    for(int i=0;i<6;i++){
        wt.insert(words[i]);
    }
    bool pass = isBalanced(wt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testSearchCountMissingWord(){//checking missing word
    BookTree bt;
    bt.loadData(database,9);
    int visited = bt.searchCount("The Wonderful Wizard of Oz","missing");
    int freq = bt.findFrequency("The Wonderful Wizard of Oz","missing");
    bool pass = (freq == 0 && visited > 0);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testFindFrequencyNonexistentBook(){//checking frequency of book that does not exist
    BookTree bt;
    bt.loadData(database,9);
    int freq = bt.findFrequency("Nonexistent Book","word");
    bool pass = (freq==0);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testEmptyTreeRemove(){//to check if remove from empty tree works
    WordTree wt;
    wt.remove("apple");
    bool pass = (wt.m_root==nullptr);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testSplayRootUpdate(){//to check if splay updates root correctly
    BookTree bt;
    bt.insert("BookX","AuthorX","text");
    bt.insert("BookY","AuthorY","text");
    bool pass = (bt.m_root && (bt.m_root->m_title=="BookY" || bt.m_root->m_title=="BookX"));
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testInsertAlphabeticalOrder(){//to check if inserting alphabetically produces valid BST
    WordTree wt;
    string words[] = {"a","b","c","d","e"};
    for(int i=0;i<5;i++){
        wt.insert(words[i]);
    }
    bool pass = isBST(wt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testCaseInsensitiveSearchCount(){ //to make it case sensitive
    BookTree bt;
    bt.insert("Wizard", "Matilda", "Tin Tin TIN");
    int count = bt.searchCount("Wizard", "tin");
    bool pass = (count == 1);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testMassInsertionBalance(){//big insertion still stays balanced
    WordTree wt;
    string words[] = {"m","b","q","a","c","z","k","l","n","o"};
    for(int i = 0; i < 10 ; i++){
        wt.insert(words[i]);
    }
    bool pass = isBalanced(wt.m_root);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::testBookTreeWordFrequencyEdge(){//edge frequency check
    BookTree bt;
    bt.loadData(database,9);
    int freq = bt.findFrequency("Pride and Prejudice","invitation");
    bool pass = (freq==1);
    if (pass){
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}


int main(){
    cout << "Creating sample trees and running all tests..." << endl << endl;

    WordTree wt;
    string words[] = {"apple","orange","cherry","plum","tomato","banana","apple"};
    for (int i = 0; i < 7; i++){
        wt.insert(words[i]);
    }
    cout << "AVL Tree Dump:" << endl;
    wt.dump();
    cout << "\nFrequency of 'apple': " << wt.find("apple")->getFrequency() << "\n\n";

    BookTree bt;
    bt.loadData(database,9);
    cout << "BookTree Dump:" << endl;
    bt.dump();
    cout << "\nFrequency of 'tinman' in The Wonderful Wizard of Oz: " << bt.findFrequency("The Wonderful Wizard of Oz","tinman") << "\n\n";

    Tester tester;
    cout << "Running all 21 tests:\n\n";

    cout << "testAVLBalanceInsert: " << (tester.testAVLBalanceInsert() ? "PASS" : "FAIL") << endl;
    cout << "testBSTPropertyInsert: " << (tester.testBSTPropertyInsert() ? "PASS" : "FAIL") << endl;
    cout << "testSplayInsertRoot: " << (tester.testSplayInsertRoot() ? "PASS" : "FAIL") << endl;
    cout << "testAVLBalanceRemove: " << (tester.testAVLBalanceRemove() ? "PASS" : "FAIL") << endl;
    cout << "testBSTAfterRemove: " << (tester.testBSTAfterRemove() ? "PASS" : "FAIL") << endl;
    cout << "testWordRemoveMultiple: " << (tester.testWordRemoveMultiple() ? "PASS" : "FAIL") << endl;
    cout << "testFindMultiple: " << (tester.testFindMultiple() ? "PASS" : "FAIL") << endl;
    cout << "testSearchCountBookTree: " << (tester.testSearchCountBookTree() ? "PASS" : "FAIL") << endl;
    cout << "testFindFrequencyBookTree: " << (tester.testFindFrequencyBookTree() ? "PASS" : "FAIL") << endl;
    cout << "testDuplicateInsertFrequency: " << (tester.testDuplicateInsertFrequency() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveSingleOccurrence: " << (tester.testRemoveSingleOccurrence() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveDecrementFrequency: " << (tester.testRemoveDecrementFrequency() ? "PASS" : "FAIL") << endl;
    cout << "testDeepAVLRotations: " << (tester.testDeepAVLRotations() ? "PASS" : "FAIL") << endl;
    cout << "testSearchCountMissingWord: " << (tester.testSearchCountMissingWord() ? "PASS" : "FAIL") << endl;
    cout << "testFindFrequencyNonexistentBook: " << (tester.testFindFrequencyNonexistentBook() ? "PASS" : "FAIL") << endl;
    cout << "testEmptyTreeRemove: " << (tester.testEmptyTreeRemove() ? "PASS" : "FAIL") << endl;
    cout << "testSplayRootUpdate: " << (tester.testSplayRootUpdate() ? "PASS" : "FAIL") << endl;
    cout << "testInsertAlphabeticalOrder: " << (tester.testInsertAlphabeticalOrder() ? "PASS" : "FAIL") << endl;
    cout << "testCaseInsensitiveSearchCount: " << (tester.testCaseInsensitiveSearchCount() ? "PASS" : "FAIL") << endl;
    cout << "testMassInsertionBalance: " << (tester.testMassInsertionBalance() ? "PASS" : "FAIL") << endl;
    cout << "testBookTreeWordFrequencyEdge: " << (tester.testBookTreeWordFrequencyEdge() ? "PASS" : "FAIL") << endl;

    tester.TestResult();
    return 0;
}

void Tester::TestResult() {//to print results
    cout << "\nSummary:\n";
    cout << "Tests Passed: " << m_passed << "\n";
    cout << "Tests Failed: " << m_failed << "\n";
    cout << "Percentage pass: " << (100.0 * m_passed / (m_passed + m_failed)) << "%\n";
}