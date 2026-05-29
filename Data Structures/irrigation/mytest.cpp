/*****************************************                                                                         
** File:    mytest.cpp                                                                                            
** Project: CMSC 341 Project 3, Fall 2025                                                                          
** Author:  Akanksha Madhu Kiran                                                                                   
** Date:    11/11/2025                                                                                            
** E-mail:  amadhuk1@umbc.edu                                                                                     
** This file contains all test cases.                                                                           
*****************************************/
#include "irrigator.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
    Random(){}
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_unidist = uniform_int_distribution<>(min,max);
        }
        else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_uniReal = uniform_real_distribution<double>((double)min,(double)max);
        }
        else { //the case of SHUFFLE to generate every number only once
            m_generator = mt19937(m_device());
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = mt19937(seedNum);
    }
    void init(int min, int max){
        m_min = min;
        m_max = max;
        m_type = UNIFORMINT;
        m_generator = mt19937(10);// 10 is the fixed seed value
        m_unidist = uniform_int_distribution<>(min,max);
    }
    void getShuffle(vector<int> & array){
        // this function provides a list of all values between min and max
        // in a random order, this function guarantees the uniqueness
        // of every value in the list
        // the user program creates the vector param and passes here
        // here we populate the vector using m_min and m_max
        for (int i = m_min; i<=m_max; i++){
            array.push_back(i);
        }
        shuffle(array.begin(),array.end(),m_generator);
    }

    void getShuffle(int array[]){
        // this function provides a list of all values between min and max
        // in a random order, this function guarantees the uniqueness
        // of every value in the list
        // the param array must be of the size (m_max-m_min+1)
        // the user program creates the array and pass it here
        vector<int> temp;
        for (int i = m_min; i<=m_max; i++){
            temp.push_back(i);
        }
        shuffle(temp.begin(), temp.end(), m_generator);
        vector<int>::iterator it;
        int i = 0;
        for (it=temp.begin(); it != temp.end(); it++){
            array[i] = *it;
            i++;
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = floor(result*100.0)/100.0;
        return result;
    }

    string getRandString(int size){
        // the parameter size specifies the length of string we ask for
        // to use ASCII char the number range in constructor must be set to 97 - 122
        // and the Random type must be UNIFORMINT (it is default in constructor)
        string output = "";
        for (int i=0;i<size;i++){
            output = output + (char)getRandNum();
        }
        return output;
    }
    
    int getMin(){
        return m_min;
    }
    int getMax(){
        return m_max;
    }
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    random_device m_device;
    mt19937 m_generator;
    normal_distribution<> m_normdist;//normal distribution
    uniform_int_distribution<> m_unidist;//integer uniform distribution
    uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

// the followings are sample priority functions to be used by Region class
// Priority functions compute an integer priority for a crop.
int priorityFn1(const Crop &crop);// works with a MAXHEAP
int priorityFn2(const Crop &crop);// works with a MINHEAP

class Tester {
public:
    Tester();

    bool testInsertMinHeap();
    bool testInsertMaxHeap();
    bool testRemoveMinHeap();
    bool testRemoveMaxHeap();
    bool testLeftistNPLValues();
    bool testLeftistNPLProperty();
    bool testRebuildWithNewPriority();
    bool testMergeEmptyWithNormal();
    bool testCopyCtorNormal();
    bool testCopyCtorEdge();
    bool testAssignNormal();
    bool testAssignEdge();
    bool testDequeueEmptyThrows();
    bool testMergeDifferentPriorityThrows();
    bool testIrrigatorFullSuite();
    bool testAddRegionNormal();
    bool testGetRegionNormal();
    bool testGetNthRegionNormal();
    bool testSetPriorityFnNormal();
    bool testSetStructureNormal();
    bool testGetRegionEmpty();
    bool testGetNthRegionInvalid();
    bool testSetPriorityFnInvalid();
    bool testSetStructureInvalid();
    bool testLargeInsertion();

    void TestResult();

private:
    int m_passed;
    int m_failed;

    //helpers
    bool checkHeapOrder(Crop* node, prifn_t priFn, HEAPTYPE heapType) const;
    bool checkHeapOrderRec(Crop* node, prifn_t priFn, HEAPTYPE heapType) const;
    bool checkLeftistNPLValues(Crop* node) const;
    bool checkLeftistProperty(Crop* node) const;
    int computeNPL(Crop* node) const;
};


Tester::Tester() {
    m_passed = 0;
    m_failed = 0;
}


bool Tester::checkHeapOrderRec(Crop* node, prifn_t priFn, HEAPTYPE heapType) const {
    if(node == nullptr){
        return true;
    }

    int pNode = 0;
    if(priFn != nullptr){
        pNode = priFn(*node);
    }

    if(node->m_left != nullptr) {
        int pLeft = 0;
        if(priFn != nullptr){
            pLeft = priFn(*node->m_left);
        }
        if(heapType == MINHEAP) {
            if(pNode > pLeft){
                return false;
            }
        } else {
            if(pNode < pLeft){
                return false;
            }
        }
    }

    if(node->m_right != nullptr) {
        int pRight = 0;
        if(priFn != nullptr){
            pRight = priFn(*node->m_right);
        }
        if(heapType == MINHEAP) {
            if(pNode > pRight){
                return false;
            }
        } else {
            if(pNode < pRight){
                return false;
            }
        }
    }

    bool leftOk = checkHeapOrderRec(node->m_left, priFn, heapType);
    if(!leftOk){
        return false;
    }
    bool rightOk = checkHeapOrderRec(node->m_right, priFn, heapType);
    return rightOk;
}

bool Tester::checkHeapOrder(Crop* node, prifn_t priFn, HEAPTYPE heapType) const {
    return checkHeapOrderRec(node, priFn, heapType);
}


int Tester::computeNPL(Crop* node) const {
    if(node == nullptr){
        return 0;
    }
    int leftNPL = computeNPL(node->m_left);
    int rightNPL = computeNPL(node->m_right);
    int val = 1 + (leftNPL < rightNPL ? leftNPL : rightNPL);
    return val;
}


bool Tester::checkLeftistNPLValues(Crop* node) const {
    if(node == nullptr){
        return true;
    }
    // In this course convention lowest level nodes store zero - so adjust:
    // The stored node->m_npl should be (min(npl(left), npl(right)) + 1) OR 0 for leaves?
    // We compute according to standard definition and compare.
    int computedLeft = node->m_left ? node->m_left->m_npl : 0;
    int computedRight = node->m_right ? node->m_right->m_npl : 0;
    int expected = (computedLeft < computedRight ? computedLeft : computedRight) + 1;
    if(node->m_left == nullptr && node->m_right == nullptr) {
        if (node->m_npl != 0){
            return false;
        }
    } else {
        if (node->m_npl != expected){
            return false;
        }
    }
    bool leftOk = checkLeftistNPLValues(node->m_left);
    if(!leftOk){
        return false;
    }
    bool rightOk = checkLeftistNPLValues(node->m_right);
    return rightOk;
}


bool Tester::checkLeftistProperty(Crop* node) const {
    //Check leftist property. Left subtree must have >= NPL than right subtree.
    if(node == nullptr){
        return true;
    }
    int leftN = node->m_left ? node->m_left->m_npl : 0;
    int rightN = node->m_right ? node->m_right->m_npl : 0;
    if(leftN < rightN){
        return false;
    }
    bool leftOk = checkLeftistProperty(node->m_left); //recursively check
    if(!leftOk){
        return false;
    }
    bool rightOk = checkLeftistProperty(node->m_right);
    return rightOk;
}


bool Tester::testInsertMinHeap() {
    //test insertion into Min heap
    Region r(priorityFn2, MINHEAP, SKEW, 0); //create region
    Random idGen(MINCROPID, MAXCROPID); //random crop ID generate
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    bool pass = checkHeapOrder(r.m_heap, r.m_priorFunc, r.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }

    return pass;
}


bool Tester::testInsertMaxHeap() {
    //test insertion into max heap
    Region r(priorityFn1, MAXHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    bool pass = checkHeapOrder(r.m_heap, r.m_priorFunc, r.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testRemoveMinHeap() {
    //test remove min heap
    Region r(priorityFn2, MINHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    int prev = -1;
    bool ok = true;
    for(int i = 0; i < n && ok; i++) {
        Crop c = r.getNextCrop();
        int p = priorityFn2(c);
        if(i == 0){
            prev = p;
        } else {
            if(p < prev){
                ok = false;
            }
            prev = p;
        }
    }

    if(ok){
        m_passed++;
    } else {
        m_failed++;
    }
    return ok;
}


bool Tester::testRemoveMaxHeap() {
    //test remove max heap
    Region r(priorityFn1, MAXHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    int prev = -1;
    bool ok = true;
    for(int i = 0; i < n && ok; i++) {
        Crop c = r.getNextCrop();
        int p = priorityFn1(c);
        if(i == 0) {
            prev = p;
        } else {
            if (p > prev) ok = false;
            prev = p;
        }
    }

    if(ok){
        m_passed++;
    } else {
        m_failed++;
    }
    return ok;
}


bool Tester::testLeftistNPLValues() {
    Region r(priorityFn2, MINHEAP, LEFTIST, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for (int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    bool pass = checkLeftistNPLValues(r.m_heap);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testLeftistNPLProperty() {
    Region r(priorityFn2, MINHEAP, LEFTIST, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    bool pass = checkLeftistProperty(r.m_heap);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testRebuildWithNewPriority() {
    Region r(priorityFn2, MINHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    int oldSize = r.numCrops();

    r.setPriorityFn(priorityFn1, MAXHEAP);

    int newSize = r.numCrops();
    bool pass = (oldSize == newSize) && checkHeapOrder(r.m_heap, r.m_priorFunc, r.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testMergeEmptyWithNormal() {
    //test merge empty with normal
    Region lhs(priorityFn2, MINHEAP, LEFTIST, 0);
    Region rhs(priorityFn2, MINHEAP, LEFTIST, 0);

    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        lhs.insertCrop(c);
    }

    int lhsSizeBefore = lhs.numCrops();


    lhs.mergeWithQueue(rhs);

    int lhsSizeAfter = lhs.numCrops();
    int rhsSizeAfter = rhs.numCrops();

    bool pass = (lhsSizeBefore == lhsSizeAfter) && (rhsSizeAfter == 0) && checkHeapOrder(lhs.m_heap, lhs.m_priorFunc, lhs.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testCopyCtorNormal() {
    //test copy constructor normal
    Region r(priorityFn2, MINHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    Region copyR(r);
    bool pass = (copyR.numCrops() == r.numCrops()) && checkHeapOrder(copyR.m_heap, copyR.m_priorFunc, copyR.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testCopyCtorEdge() {
    //test copy constructor edge
    Region r;
    Region copyR(r);
    bool pass = (copyR.numCrops() == 0) && (copyR.m_heap == nullptr);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testAssignNormal() {
    Region r(priorityFn2, MINHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 300;
    for(int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        r.insertCrop(c);
    }

    Region assignTo;
    assignTo = r;
    bool pass = (assignTo.numCrops() == r.numCrops()) && checkHeapOrder(assignTo.m_heap, assignTo.m_priorFunc, assignTo.m_heapType);
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testAssignEdge() {
    Region r;
    Region nonEmpty(priorityFn2, MINHEAP, SKEW, 0);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    for(int i = 0; i < 300; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(), moistGen.getRandNum(), timeGen.getRandNum(), typeGen.getRandNum());
        nonEmpty.insertCrop(c);
    }

    nonEmpty = r;
    bool pass1 = (nonEmpty.numCrops() == 0);

    Region target;
    target = r;
    target = nonEmpty;
    bool pass2 = (target.numCrops() == 0);

    bool pass = pass1 && pass2;
    if(pass){
        m_passed++; 
    } else {
        m_failed++;
    }
    return pass;
}


bool Tester::testDequeueEmptyThrows() {
    Region r;
    bool threw = false;
    try {
        r.getNextCrop();
    } catch (const out_of_range& e) {
        threw = true;
    } catch (...) {
        threw = false;
    }
    if(threw){
        m_passed++; 
    } else {
        m_failed++;
    }
    return threw;
}


bool Tester::testMergeDifferentPriorityThrows() {
    Region r1(priorityFn1, MAXHEAP, LEFTIST, 0);
    Region r2(priorityFn2, MINHEAP, LEFTIST, 0);
    bool threw = false;
    try {
        r1.mergeWithQueue(r2);
    } catch (const domain_error& e) {
        threw = true;
    } catch (...) {
        threw = false;
    }
    if(threw){
        m_passed++; 
    } else {
        m_failed++;
    }
    return threw;
}


bool Tester::testAddRegionNormal() {
    Random rgnGen(1, 100);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    Irrigator testIrrigator(5);
    bool addOK = true;

    for (int i = 0; i < 5; i++) {
        Region region(priorityFn2, MINHEAP, LEFTIST, rgnGen.getRandNum());
        for (int j = 0; j < 3; j++) {
            Crop c(idGen.getRandNum(), tempGen.getRandNum(),
                   moistGen.getRandNum(), timeGen.getRandNum(),
                   typeGen.getRandNum());
            if (!region.insertCrop(c)){
                addOK = false;
            }
        }
        if (!testIrrigator.addRegion(region)){
            addOK = false;
        }
    }
    if(addOK){
        m_passed++; 
    } else {
        m_failed++;
    }

    return addOK;
}

bool Tester::testGetRegionNormal() {
    Irrigator testIrrigator(3);
    Region region(priorityFn1, MAXHEAP, LEFTIST, 10);
    testIrrigator.addRegion(region);

    Region r;
    bool result = testIrrigator.getRegion(r);
    if(result){
        m_passed++; 
    } else {
        m_failed++;
    }
    return result;
}


bool Tester::testGetNthRegionNormal() {
    //test nth region got correctly
    Irrigator testIrrigator(3);
    Region r1(priorityFn1, MAXHEAP, LEFTIST, 10);
    Region r2(priorityFn2, MINHEAP, LEFTIST, 20);
    testIrrigator.addRegion(r1);
    testIrrigator.addRegion(r2);

    Region r;
    bool result = testIrrigator.getNthRegion(r, 2);
    if(result){
        m_passed++; 
    } else {
        m_failed++;
    }
    return result;
}


bool Tester::testSetPriorityFnNormal() {
    Irrigator testIrrigator(3);
    Region region(priorityFn2, MINHEAP, LEFTIST, 5);
    testIrrigator.addRegion(region);

    bool result = testIrrigator.setPriorityFn(priorityFn1, MAXHEAP, 1);
    if(result){
        m_passed++; 
    } else {
        m_failed++;
    }
    return result;
}


bool Tester::testSetStructureNormal() {
    //test if structure set accurately
    Random rgnGen(1, 100);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);
    Irrigator testIrrigator(3);
    Region region(priorityFn2, MINHEAP, LEFTIST, 5);
    for (int i = 0; i < 3; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(),
               moistGen.getRandNum(), timeGen.getRandNum(),
               typeGen.getRandNum());
        region.insertCrop(c);
    }
    testIrrigator.addRegion(region);

    bool result = testIrrigator.setStructure(SKEW, 1);
    if(result){
        m_passed++; 
    } else {
        m_failed++;
    }

    return result;
}


bool Tester::testGetRegionEmpty() {
    //test get region
    Irrigator irrigator(3);
    Region dummy;
    bool handled = !irrigator.getRegion(dummy);
    if(handled){
        m_passed++; 
    } else {
        m_failed++;
    }
    return handled;
}


bool Tester::testGetNthRegionInvalid() {
    Irrigator testIrrigator(2);
    Region r1(priorityFn1, MAXHEAP, LEFTIST, 10);
    Region r2(priorityFn2, MINHEAP, LEFTIST, 20);
    testIrrigator.addRegion(r1);
    testIrrigator.addRegion(r2);

    bool handled = !testIrrigator.getNthRegion(r1, 5);
    if(handled){
        m_passed++; 
    } else {
        m_failed++;
    }
    return handled;
}


bool Tester::testSetPriorityFnInvalid() {
    Irrigator testIrrigator(2);
    Region r1(priorityFn1, MAXHEAP, LEFTIST, 10);
    testIrrigator.addRegion(r1);

    bool handled = !testIrrigator.setPriorityFn(priorityFn1, MAXHEAP, 5);
    if(handled){
        m_passed++; 
    } else {
        m_failed++;
    }
    return handled;
}


bool Tester::testSetStructureInvalid() {
    Irrigator testIrrigator(2);
    Region r1(priorityFn1, MAXHEAP, LEFTIST, 10);
    testIrrigator.addRegion(r1);

    bool handled = !testIrrigator.setStructure(SKEW, 5);
    if(handled){
        m_passed++; 
    } else {
        m_failed++;
    }
    return handled;
}

bool Tester::testLargeInsertion() {
    //test large insertion
    Region r(priorityFn1, MAXHEAP, LEFTIST, 1);
    Random idGen(MINCROPID, MAXCROPID);
    Random tempGen(MINTEMP, MAXTEMP);
    Random moistGen(MINMOISTURE, MAXMOISTURE);
    Random timeGen(MINTIME, MAXTIME);
    Random typeGen(MINTYPE, MAXTYPE);

    int n = 500; // inserting more than 300 nodes
    for (int i = 0; i < n; i++) {
        Crop c(idGen.getRandNum(), tempGen.getRandNum(),
               moistGen.getRandNum(), timeGen.getRandNum(),
               typeGen.getRandNum());
        r.insertCrop(c);
    }

    bool sizeCheck = (r.numCrops() == n);
    bool heapCheck = checkHeapOrder(r.m_heap, r.m_priorFunc, r.m_heapType);

    bool pass = sizeCheck && heapCheck;
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }

    return pass;
}



void Tester::TestResult() {
    cout << "\nSummary:\n";
    cout << "Tests Passed: " << m_passed << "\n";
    cout << "Tests Failed: " << m_failed << "\n";
    int total = m_passed + m_failed;
    if (total == 0) {
        cout << "No tests executed.\n";
    } else {
        double pct = (100.0 * m_passed) / total;
        cout << "Percentage pass: " << pct << "%\n";
    }
}


int main(){
    Random regionGen(10,30);
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    Irrigator regionsQueue(20);
    cout << "Creating 10 regions and adding them to the system:" << endl;
    for (int j=0;j<10;j++){
        int rndRegion = regionGen.getRandNum();
        Region aRegion(priorityFn2, MINHEAP, LEFTIST, rndRegion);
        for (int i=0;i<5;i++){
            Crop aCrop(idGen.getRandNum(),
                        temperature,// it is the same in the region
                        moistureGen.getRandNum(),
                        time,       // it is the same in the region
                        typeGen.getRandNum());
            aRegion.insertCrop(aCrop);
        }
        // cout << "Region Priority: " << rndRegion << endl;
        aRegion.dump();
        regionsQueue.addRegion(aRegion);
    }

    cout << endl;
    cout << "Checking the tree of regions:" << endl;
    regionsQueue.dump();

    Region highPrioRegion;

    cout << endl << "Get the highest priority region:" << endl;
    regionsQueue.getRegion(highPrioRegion);
    cout << endl; highPrioRegion.dump();

    cout << endl << "Get the 3rd highest priority region:" << endl;
    regionsQueue.getNthRegion(highPrioRegion, 3); // get third highest priority
    cout << endl; highPrioRegion.dump();

    cout << endl << "Checking the tree of regions:" << endl;
    cout << endl; regionsQueue.dump();

    cout << "Changing the priority function in the highest priority region:" << endl;
    regionsQueue.setPriorityFn(priorityFn1, MAXHEAP, 1); // change the root's priority function

    cout << endl << "Get the highest priority region, it must be a max heap now:" << endl;
    regionsQueue.getRegion(highPrioRegion);
    cout << endl; highPrioRegion.dump();

    cout << endl << "Get the highest priority region, this one be a min heap:" << endl;
    regionsQueue.getRegion(highPrioRegion); 
    cout << endl; highPrioRegion.dump();

    cout << endl;

    Tester tester;
    cout << "testLargeInsertion: " << (tester.testLargeInsertion() ? "PASS" : "FAIL") << endl;
    cout << "testInserMinHeap: " << (tester.testInsertMinHeap() ? "PASS" : "FAIL") << endl;
    cout << "testInsertMaxHeap: " << (tester.testInsertMaxHeap() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveMinHeap: " << (tester.testRemoveMinHeap() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveMaxHeap: " << (tester.testRemoveMaxHeap() ? "PASS" : "FAIL") << endl;
    cout << "testLeftistNPLValues: " << (tester.testLeftistNPLValues() ? "PASS" : "FAIL") << endl;
    cout << "testLeftistNPLProperty: " << (tester.testLeftistNPLProperty() ? "PASS" : "FAIL") << endl;
    cout << "testRebuildWithNewPriority: " << (tester.testRebuildWithNewPriority() ? "PASS" : "FAIL") << endl;
    cout << "testMergeEmptyWithNormal: " << (tester.testMergeEmptyWithNormal() ? "PASS" : "FAIL") << endl;
    cout << "testCopyCtorNormal: " << (tester.testCopyCtorNormal() ? "PASS" : "FAIL") << endl;
    cout << "testCopyCtorEdge: " << (tester.testCopyCtorEdge() ? "PASS" : "FAIL") << endl;
    cout << "testAssignNormal: " << (tester.testAssignNormal() ? "PASS" : "FAIL") << endl;
    cout << "testAssignEdge: " << (tester.testAssignEdge() ? "PASS" : "FAIL") << endl;
    cout << "testDequeueEmptyThrows: " << (tester.testDequeueEmptyThrows() ? "PASS" : "FAIL") << endl;
    cout << "testMergeDifferentPriorityThrows: " << (tester.testMergeDifferentPriorityThrows() ? "PASS" : "FAIL") << endl;
    cout << "testAddRegionNormal: " << (tester.testAddRegionNormal()? "PASS" : "FAIL") << endl;
    cout << "testGetRegionNormal: " << (tester.testGetRegionNormal()? "PASS" : "FAIL") << endl;
    cout << "testGetNthRegionNormal: " << (tester.testGetNthRegionNormal()? "PASS" : "FAIL") << endl;
    cout << "testSetPriorityFnNormal: " << (tester.testSetPriorityFnNormal()? "PASS" : "FAIL") << endl;
    cout << "testSetStructureNormal: " << (tester.testSetStructureNormal()? "PASS" : "FAIL") << endl;    
    cout << "testGetRegionEmpty: " << (tester.testGetRegionEmpty()? "PASS" : "FAIL") << endl;
    cout << "testGetNthRegionInvalid: " << (tester.testGetNthRegionInvalid()? "PASS" : "FAIL") << endl;
    cout << "testSetPriorityFnInvalid: " << (tester.testSetPriorityFnInvalid()? "PASS" : "FAIL") << endl;
    cout << "testSetStructureInvalid: " << (tester.testSetStructureInvalid()? "PASS" : "FAIL") << endl;
    tester.TestResult();
    return 0;
}

int priorityFn1(const Crop &crop) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [30-116]
    //the highest priority would be 110+6 = 116
    //the lowest priority would be 30+0 = 30
    //the larger value means the higher priority
    int minValue = 30;
    int maxValue = 116;
    int priority = crop.getTemperature() + crop.getType();
    if (priority >= minValue && priority <= maxValue)
        return priority;
    else
        return 0; // this is an invalid order object
}

int priorityFn2(const Crop &crop) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [1-103]
    //the highest priority would be 1+0 = 1
    //the lowest priority would be 100+3 = 103
    //the smaller value means the higher priority
    int minValue = 1;
    int maxValue = 103;
    int priority = crop.getMoisture() + crop.getTime();
    if (priority >= minValue && priority <= maxValue)
        return priority;
    else
        return 0; // this is an invalid order object
}
