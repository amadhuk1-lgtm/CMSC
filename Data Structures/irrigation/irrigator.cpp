/*****************************************                                                                          
** File:    irrigator.cpp                                                                                            
** Project: CMSC 341 Project 3, Fall 2025                                                                           
** Author:  Akanksha Madhu Kiran                                                                                    
** Date:    11/11/2025                                                                                              
** E-mail:  amadhuk1@umbc.edu                                                                                       
** This file contains the region and irrigator class.                                                                           
*****************************************/

#include "irrigator.h"

using namespace std;

//default constructor
Region::Region(){

    m_heap = nullptr;//initialize to nullptr and 0 for all member variables
    m_size = 0;
    m_priorFunc = nullptr;
    m_heapType = NOTYPE;
    m_structure = NOSTRUCT;
    m_regPrior = 0;
}

//constructor
Region::Region(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure, int regPrior){

    m_heap = nullptr;
    m_size = 0;
    m_priorFunc = priFn;
    m_heapType = heapType;
    m_structure = structure;
    m_regPrior = regPrior;
}

//destructor
Region::~Region() {
    clear(); //clear all and free memory
    m_priorFunc = nullptr;
    m_heapType = NOTYPE;
    m_structure = NOSTRUCT;
    m_regPrior = 0;
}


void Region::clear() {
    deleteTree(m_heap); //delete heap
    m_heap = nullptr; //initialize member variables to null and 0
    m_size = 0;
    m_regPrior = 0;
}



Region::Region(const Region& rhs){
    m_heap = nullptr; //empty heap
    m_size = rhs.m_size;
    m_priorFunc = rhs.m_priorFunc;
    m_heapType = rhs.m_heapType;
    m_structure = rhs.m_structure;
    m_regPrior = rhs.m_regPrior;
    m_heap = copyTree(rhs.m_heap); //deep copy heaps
}


Region& Region::operator=(const Region& rhs) {
    if (this != &rhs) { //check self assignment
        clear(); //delete heaps
        m_size = rhs.m_size;
        m_priorFunc = rhs.m_priorFunc;
        m_heapType = rhs.m_heapType;
        m_structure = rhs.m_structure;
        m_regPrior = rhs.m_regPrior;
        m_heap = copyTree(rhs.m_heap); //deep copy heaps
    }
    return *this; //returns reference to current object
}

void Region::mergeWithQueue(Region& rhs) {
    if (this == &rhs) { //check if self merging
        throw domain_error("Cannot merge region with itself."); //invalid
    }
    
    if (m_priorFunc != rhs.m_priorFunc || m_structure != rhs.m_structure || m_heapType != rhs.m_heapType) { //check region
        throw domain_error("Cannot merge with different priority functions, structures, or heap types.");
    }

    m_heap = merge(m_heap, rhs.m_heap); //to merge
    m_size += rhs.m_size; //increment size

    rhs.m_heap = nullptr; //clear after merge
    rhs.m_size = 0;
    rhs.m_regPrior = 0;

    m_regPrior = peekPriority(); //update priority
}


bool Region::insertCrop(const Crop& input) {
    if (m_priorFunc == nullptr){ //no insert if no priority
        return false;
    }
    int pr = m_priorFunc(input); //check priority
    if (pr == 0){
        return false;
    }

    Crop* node = new Crop(input); //create new object crop
    node->m_left = nullptr;
    node->m_right = nullptr;
    node->m_npl = 0;

    m_heap = merge(m_heap, node); //merge new node to heap
    m_size++; //update size of heap
    m_regPrior = peekPriority(); //update priority
    return true;
}

int Region::numCrops() const {
    return m_size; //return number of crops
}

prifn_t Region::getPriorityFn() const {
    return m_priorFunc; //return pointer to region's priority function
}


Crop Region::getNextCrop() {
    if (m_heap == nullptr) { //heap empty
        throw out_of_range("Region empty.");
    }
    Crop result = *m_heap; //copy highest priority crop
    Crop* left = m_heap->m_left;
    Crop* right = m_heap->m_right;
    delete m_heap;
    m_heap = merge(left, right); //merge subtrees
    if (m_size > 0){ //decrement if not 0
        m_size--;
    }
    m_regPrior = peekPriority(); //update priority
    return result;
}




void Region::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
    if (priFn == nullptr) { //return if priority function is null
        return;
    }

    Crop* head = nullptr;
    Crop* tail = nullptr;
    detachAllNodes(m_heap, head, tail); //detach nodes to linkedlist

    m_heap = nullptr; //reset heap and size of heap
    m_size = 0;

    m_priorFunc = priFn;
    m_heapType = heapType;

    Crop* cur = head; //start from head
    while (cur != nullptr) { //insert using new priority
        Crop* next = cur->m_right;
        cur->m_right = nullptr;
        cur->m_left = nullptr;
        cur->m_npl = 0; //reset npl

        int p = 0;
        if (m_priorFunc != nullptr) { //ensure valid priority
            p = m_priorFunc(*cur);
            if (p != 0) {
                m_heap = merge(m_heap, cur); //merge if some priority
                m_size++; //increment size
            } else {
                delete cur; //delete if invalid priority
            }
        } else {
            delete cur;
        }
        cur = next; //move to next crop
    }
    m_regPrior = peekPriority(); //update priority

    if (m_structure == LEFTIST) {
        recomputeNPL(m_heap); //npl recompute
    }
}


void Region::setStructure(STRUCTURE structure) {
    if (structure != SKEW && structure != LEFTIST) { //check if valid
        return;
    }

    Crop* head = nullptr;
    Crop* tail = nullptr;
    detachAllNodes(m_heap, head, tail); //detach nodes to linkedlist

    m_heap = nullptr;
    m_size = 0;
    m_structure = structure; //set new structure

    Crop* cur = head;
    while (cur != nullptr){
        Crop* next = cur->m_right; //store next node
        cur->m_right = nullptr;
        cur->m_left = nullptr;
        cur->m_npl = 0;
        m_heap = merge(m_heap, cur); //merge crop to heap
        m_size++;
        cur = next; //move to next node
    }

    m_regPrior = peekPriority(); //update priority
    if (m_structure == LEFTIST) {
        recomputeNPL(m_heap); //npl recompute
    }

}

STRUCTURE Region::getStructure() const {
    return m_structure; //return heap structure
}

HEAPTYPE Region::getHeapType() const {
    return m_heapType; //return heap type
}

void Region::printCropsQueue() const {
    preorderTraversal(m_heap); //print crops
}

void Region::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    cout << "Region " << m_regPrior << ": => ";
    dump(m_heap);
  }
  cout << endl;
}

void Region::dump(Crop *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
        cout << m_priorFunc(*pos) << ":" << pos->m_cropID;
    else
        cout << m_priorFunc(*pos) << ":" << pos->m_cropID << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Crop& crop) {
  sout << "Crop ID: " << crop.getCropID() 
        << ", current temperature: " << crop.getTemperature()
        << ", current soil moisture: " << crop.getMoisture() << "%"
        << ", current time: " << crop.getTimeString()
        << ", plant type: " << crop.getTypeString();
  return sout;
}

//////////////////////////////////////////////////////////////
//constructor
Irrigator::Irrigator(int size){
    m_capacity = size + ROOTINDEX;
    m_size = 0;
    if (size < 0) { //check invalid size
        m_capacity = ROOTINDEX;
    }
    m_heap = new Region[m_capacity]; //allocate region objects
}

//destructor
Irrigator::~Irrigator() {
    delete[] m_heap; //delete heap
    m_heap = nullptr;
    m_capacity = 0;
    m_size = 0;
}

bool Irrigator::addRegion(Region & aRegion) {
    if (m_size + ROOTINDEX >= m_capacity) { //check capacity
        return false;
    }
    aRegion.m_regPrior = aRegion.getPriorityFn() ? aRegion.peekPriority() : 0; //get priority

    m_size++; //increase size
    m_heap[m_size] = aRegion; //insert region at end
    percolateUp(m_size); //recheck to satisfy heap property
    return true;
}


bool Irrigator::getRegion(Region & aRegion) {
    if (m_size < ROOTINDEX){ //check if heap empty
        return false;
    }
    aRegion = m_heap[ROOTINDEX];
    m_heap[ROOTINDEX] = m_heap[m_size]; //move region to root
    m_size--; //decrease heap size
    percolateDown(ROOTINDEX); //recheck to satisfy heap property
    return true;
}

bool Irrigator::getNthRegion(Region & aRegion, int n) {
    if (n < 1 || n > m_size){ //check size
        return false;
    }
    Region* temp = nullptr;
    int tempCount = 0;
    if (n - 1 > 0){ //assign space
        temp = new Region[n - 1];
    }

    Region cur;
    int i = 0;
    bool ok = true;
    while (i < n && ok) { //get n regions
        if (!getRegion(cur)){ //check if next region is valid or not
            ok = false;
        } else {
            if (i < n - 1) { //store n-1 regions
                temp[tempCount] = cur;
                tempCount++;
            } else { //get region
                aRegion = cur;
            }
        }
        i++;
    }

    if (!ok) { //if did not get clear
        if (temp != nullptr){
            delete[] temp;
        }
        return false;
    }

    for (int j = 0; j < tempCount; j++) { //insert removed regions back into heap
        if (m_size + ROOTINDEX >= m_capacity) {
            if (temp != nullptr){
                delete[] temp;
            }
            return false;
        }
        m_size++;
        m_heap[m_size] = temp[j];
        percolateUp(m_size);
    }

    if (temp != nullptr) { //clear
        delete[] temp;
        temp = nullptr;
    }
    return true;
}

void Irrigator::dump() {
    dump(ROOTINDEX);
    cout << endl;
}

void Irrigator::dump(int index) {
    if (index <= m_size && index >= ROOTINDEX) {
        cout << "(";
        dump(index * 2);
        cout << m_heap[index].m_regPrior;
        dump(index * 2 + 1);
        cout << ")";
    }
}

bool Irrigator::setPriorityFn(prifn_t priFn, HEAPTYPE heapType, int n) {
    if (n < 1 || n > m_size){ //check if valid size
        return false;
    }
    if (priFn == nullptr){
        return false;
    }

    Region* temp = nullptr;
    int tempCount = 0;
    if (n - 1 > 0){ //store regions temporarily
        temp = new Region[n - 1];
    }
    Region cur;
    Region target; //to change
    int i = 0;
    bool ok = true;
    while (i < n && ok) { //get n regions and storing n-1 in temp
        if (!getRegion(cur)){
            ok = false;
        } else {
            if (i < n - 1) {
                temp[tempCount] = cur;
                tempCount++;
            } else {
                target = cur; //save found region
            }
        }
        i++;
    }
    if (!ok) { //cear if not found
        if (temp != nullptr){
            delete[] temp;
        }
        return false;
    }
    target.setPriorityFn(priFn, heapType);
    target.m_regPrior = target.peekPriority(); //update priority

    if (m_size + ROOTINDEX >= m_capacity) { //insert regions
        if (temp != nullptr){
            delete[] temp;
        }
        return false;
    }
    m_size++;
    m_heap[m_size] = target;
    percolateUp(m_size);


    for (int j = 0; j < tempCount; j++) {
        if (m_size + ROOTINDEX >= m_capacity) {
            if (temp != nullptr){
                delete[] temp;
            }
            return false;
        }
        m_size++;
        m_heap[m_size] = temp[j];
        percolateUp(m_size);
    }


    if (temp != nullptr) {
        delete[] temp;
        temp = nullptr;
    }
    return true;
}


bool Irrigator::setStructure(STRUCTURE structure, int n) {
    if (n < 1 || n > m_size){ //check size validity
        return false;
    }
    if (structure != SKEW && structure != LEFTIST){ //check structure type
        return false;
    }

    Region* temp = nullptr;
    int tempCount = 0;
    if (n - 1 > 0){
        temp = new Region[n - 1];
    }

    Region cur;
    Region target;
    int i = 0;
    bool ok = true;
    while (i < n && ok) { //get nth region
        if (!getRegion(cur)){
            ok = false;
        } else {
            if (i < n - 1) {
                temp[tempCount] = cur;
                tempCount++;
            } else {
                target = cur;
            }
        }
        i++;
    }

    if (!ok) { //if not found
        if (temp != nullptr){
            delete[] temp;
        }
        return false;
    }

    target.setStructure(structure);
    target.m_regPrior = target.peekPriority(); //updates priority

    if (m_size + ROOTINDEX >= m_capacity) {
        if (temp != nullptr){
            delete[] temp;
        }
        return false;
    }
    m_size++;
    m_heap[m_size] = target; //insert changed region
    percolateUp(m_size);

    for (int j = 0; j < tempCount; j++) {
        if (m_size + ROOTINDEX >= m_capacity) {
            if (temp != nullptr){
                delete[] temp;
            }
            return false;
        }
        m_size++;
        m_heap[m_size] = temp[j];
        percolateUp(m_size);
    }

    if (temp != nullptr) {
        delete[] temp;
        temp = nullptr;
    }
    return true;
}

bool Irrigator::getCrop(Crop & aCrop) {
    if (m_size < ROOTINDEX) { //check if empty
        throw out_of_range("Irrigator is empty");
    }

    Region candidate;
    Region foundRegion;
    bool found = false;
    bool canGet = true;


    while (m_size >= ROOTINDEX && canGet && !found) {
        canGet = getRegion(candidate); //get region
        if (canGet) {
            if (candidate.numCrops() == 0) { //if empty move on
            } else {
                foundRegion = candidate;
                found = true;
            }
        }
    }

    if (!found) { //if not found
        throw out_of_range("No crops available");
    }

    bool success = true;
    try {
        aCrop = foundRegion.getNextCrop(); //get next crop
    } catch (const out_of_range& e) {
        success = false;
    }

    if (!success){
        return false;
    }

    foundRegion.m_regPrior = foundRegion.peekPriority();
    if (foundRegion.numCrops() > 0) {
        if (m_size + ROOTINDEX >= m_capacity) {
            return true;
        }
        m_size++;
        m_heap[m_size] = foundRegion;
        percolateUp(m_size);
    }

    return true;
}

/////////////////////////////////////////////////////////////
//HELPERS REGION

void Region::deleteTree(Crop* root) {
    //deletes all crops
    if (root == nullptr){
        return;
    }
    deleteTree(root->m_left);
    deleteTree(root->m_right);
    delete root;
}

Crop* Region::copyTree(const Crop* root) const {
    //deep copy of crop
    if (root == nullptr){
        return nullptr;
    }
    Crop* node = new Crop(root->m_cropID, root->m_temperature, root->m_moisture, root->m_time, root->m_type);
    node->m_npl = root->m_npl;
    node->m_left = copyTree(root->m_left);
    node->m_right = copyTree(root->m_right);
    return node;
}

Crop* Region::merge(Crop* h1, Crop* h2) { //merge two heaps
    if (h1 == nullptr){
        return h2;
    }
    if (h2 == nullptr){
        return h1;
    }
    int p1 = m_priorFunc(*h1);
    int p2 = m_priorFunc(*h2);
    bool chooseH1 = false;
    if (m_heapType == MINHEAP){
        chooseH1 = (p1 <= p2);
    } else {
        chooseH1 = (p1 >= p2);
    }
    if (!chooseH1){
        swap(h1, h2);
    }
    h1->m_right = merge(h1->m_right, h2); //merge right subtree

    int leftNPL = 0;
    if (h1->m_left != nullptr){
        leftNPL = h1->m_left->m_npl;
    }
    int rightNPL = 0;
    if (h1->m_right != nullptr){
        rightNPL = h1->m_right->m_npl;
    }
    if (leftNPL < rightNPL){ //to maintain leftist property
        swap(h1->m_left, h1->m_right);
    }
    h1->m_npl = (h1->m_right ? h1->m_right->m_npl : 0) + 1;
    if (!h1->m_left && !h1->m_right)
        h1->m_npl = 0;

    return h1;
}



void swapRegions(Region& r1, Region& r2) {
    //to swap two region objects
    if (&r1 == &r2){
        return;
    }
    Region temp = r1;
    r1 = r2;
    r2 = temp;
}

void swapCropPointers(Crop*& a, Crop*& b) {
    //swap two crop pointers
    if (a == b){
        return;
    }
    Crop* tmp = a;
    a = b;
    b = tmp;
}

int Region::recomputeNPL(Crop* root) {
    //recomputes npl
    if (root == nullptr){
        return -1;
    }

    int leftNPL = recomputeNPL(root->m_left);
    int rightNPL = recomputeNPL(root->m_right);

    if (m_structure == LEFTIST) {
        if (leftNPL < rightNPL) { 
            swapCropPointers(root->m_left, root->m_right);
            swap(leftNPL, rightNPL); 
        }
        root->m_npl = rightNPL + 1;
        if (root->m_left == nullptr && root->m_right == nullptr) {
            root->m_npl = 0;
        }
    } else {
        root->m_npl = 0;
    }
    return root->m_npl;
}

void Region::detachAllNodes(Crop* root, Crop*& head, Crop*& tail) {
    //detach nodes to linkedlist
    if (root == nullptr){
        return;
    }

    Crop* left = root->m_left;
    Crop* right = root->m_right;

    root->m_left = nullptr;
    root->m_right = nullptr;
    root->m_npl = 0;

    if (head == nullptr) {
        head = tail = root;
    } else {
        tail->m_right = root;
        tail = root;
    }

    detachAllNodes(left, head, tail);
    detachAllNodes(right, head, tail);
}

void Region::preorderTraversal(Crop* root) const {
    if (root == nullptr){
        return;
    }
    cout << *root << endl;
    preorderTraversal(root->m_left);
    preorderTraversal(root->m_right);
}

int Region::peekPriority() const {
    //returns priority of crop
    if (m_heap == nullptr){
        return 0;
    }
    if (m_priorFunc == nullptr){
        return 0;
    }
    return m_priorFunc(*m_heap);
}

///////////////////////////////////////////////////////////////////
//HELPERS IRRIGATOR

void Irrigator::percolateUp(int index) {
    if (index <= ROOTINDEX || index > m_size){
        return;
    }
    int parent = index / 2;

    if (parent >= ROOTINDEX) {
        if (m_heap[index].m_regPrior < m_heap[parent].m_regPrior) {
            swapRegions(m_heap[index], m_heap[parent]);
            percolateUp(parent); //to hold heap property
        }
    }
}

void Irrigator::percolateDown(int index) {
    //moves down the heap until heap property maintained
    if (index < ROOTINDEX || index > m_size){
        return;
    }
    int child = index * 2;
    int smallest = index;

    if (child <= m_size) {
        if (m_heap[child].m_regPrior < m_heap[smallest].m_regPrior) {
            smallest = child;
        }
    }
    if (child + 1 <= m_size) {
        if (m_heap[child + 1].m_regPrior < m_heap[smallest].m_regPrior) {
            smallest = child + 1;
        }
    }
    if (smallest != index) {
        swapRegions(m_heap[index], m_heap[smallest]);
        percolateDown(smallest);
    }
}

