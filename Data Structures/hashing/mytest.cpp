/*****************************************                                                                          
** File:    mytest.cpp                                                                                            
** Project: CMSC 341 Project 4, Fall 2025                                                                           
** Author:  Akanksha Madhu Kiran                                                                           
** Date:    12/02/2025                                                                                  
** E-mail:  amadhuk1@umbc.edu                                                                                       
** This file contains the test cases                                                                        
*****************************************/
#include "cache.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;
unsigned int hashCode(string key);
const int MINSEARCH = 0;
const int MAXSEARCH = 7;
// the following array defines sample search strings for testing
string searchStr[MAXSEARCH+1]={"c++","python","java","scheme","prolog","c#","c","js"};
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
    
    int getMin(){return m_min;}
    int getMax(){return m_max;}
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

class Tester{
    public:
        Tester();
        bool testInsertNonColliding();
        bool testInsertColliding();
        bool testFindErrorCase();
        bool testFindNonColliding();
        bool testFindColliding();
        bool testRemoveNonColliding();
        bool testRemoveColliding();
        bool testRemoveCascade();
        bool testRehashAfterInsert();
        bool testRehashCompletionInsert();
        bool testRehashAfterRemove();
        bool testRehashCompletionRemove();
        bool testInsertLarge();
        bool testRandomizedOperations();
        bool testGetPersonDeleted();
        bool testGetPersonDNE();
        bool testChangePolicyDuringRehash();
        bool testLazyDeletionBehavior();
        bool testUpdateIDDuplicate();
        bool testSearchDuringRehash();
        bool testRemoveNonexistent();
        bool testEdgeLoadFactor();
        bool testEdgeDeletedRatio();
        bool testQuadraticHashing();
        bool testRehash25PercentIncrement();


        void TestResult();

    private:
        int m_passed;
        int m_failed;
        vector<Person> generatePeople(int n, bool colliding = false);
};

Tester::Tester() {
    m_passed = 0;
    m_failed = 0;
}

vector<Person> Tester::generatePeople(int n, bool colliding) {
    //generates n person objects.
    vector<Person> vec;
    for (int i = 0; i < n; i = i + 1) {
        string key;
        if (colliding) {
            int group = (n/4);
            if (group < 1){
                group = 1;
            }
            key = "key" + to_string(i % group);
        } else {
            key = "key" + to_string(i);
        }
        int id = MINID + i;
        vec.push_back(Person(key, id));
    }
    return vec;
}


bool Tester::testInsertNonColliding() {
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(60, false);
    //inserts 60 unique keys no collisions expected

    bool ok = true;
    for (int i = 0; i < (int)people.size(); ++i) {
        if (!C.insert(people[i])){
            ok = false;
        }
    }

    for (int i = 0; i < (int)people.size(); ++i) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty() || !(r == people[i])){
            ok = false;
        }
    }

    ok ? m_passed++ : m_failed++;
    return ok;
}


bool Tester::testInsertColliding() {
    Cache C(50, hashCode, LINEAR);
    vector<Person> people = generatePeople(60, true);
    //repeated keys to force collisions

    bool ok = true;
    for (int i = 0; i < (int)people.size(); ++i) {
        if (!C.insert(people[i])){
            ok = false;
        }
    }

    for (int i = 0; i < (int)people.size(); ++i) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty() || !(r == people[i])){
            ok = false;
        }
    }

    ok ? m_passed++ : m_failed++;
    return ok;
}

bool Tester::testFindErrorCase() {
    //tests non-existent ID
    Cache C(101, hashCode, LINEAR);
    Person p("existent", 1);
    C.insert(p);

    bool ok = true;
    if (!C.getPerson("wrongkey", 1).getKey().empty()){
        ok = false;
    }
    if (!C.getPerson("existent", 999).getKey().empty()){
        ok = false;
    }

    ok ? m_passed++ : m_failed++;
    return ok;
}

bool Tester::testFindNonColliding() {
    //Find existing not colliding
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(50, false);

    for (int i = 0; i < (int)people.size(); i++){
        C.insert(people[i]);
    }
    bool ok = true;
    for (int i = 0; i < (int)people.size(); i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty()){
            ok = false;
        }
        if (!(r == people[i])){
            ok = false;
        }
    }
    ok ? m_passed++ : m_failed++;
    return ok;
}

bool Tester::testFindColliding() {
    //test find colliding IDs
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(500, true);

    for (int i = 0; i < (int)people.size(); i++){
        C.insert(people[i]);
    }
    bool ok = true;
    for (int i = 0; i < (int)people.size(); i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty()){
            ok = false;
        }
        if (!(r == people[i])){
            ok = false;
        }
    }

    ok ? m_passed++ : m_failed++;
    return ok;
}


bool Tester::testRemoveNonColliding() {
    //remove 10 elements from table with no collisions
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(50, false);

    for (int i = 0; i < (int)people.size(); ++i){
        C.insert(people[i]);
    }

    bool ok = true;
    for (int i = 0; i < 10; i++){
        if (!C.remove(people[i])){
            ok = false;
        }
    }

    for (int i = 0; i < 10; i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (!r.getKey().empty()) ok = false;
    }

    for (int i = 10; i < (int)people.size(); i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty() || !(r == people[i])){
            ok = false;
        }
    }
    ok ? m_passed++ : m_failed++;
    return ok;
}


bool Tester::testRemoveColliding() {
    //remove with collisions
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(50, true);

    for (int i = 0; i < (int)people.size(); ++i){
        C.insert(people[i]);
    }

    bool ok = true;
    for (int i = 0; i < 20; i++){
        if (!C.remove(people[i])){
            ok = false;
        }
    }

    for (int i = 0; i < 20; i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (!r.getKey().empty()){
            ok = false;
        }
    }

    for (int i = 20; i < (int)people.size(); i++) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty() || !(r == people[i])){
            ok = false;
        }
    }
    ok ? m_passed++ : m_failed++;
    return ok;
}


bool Tester::testRemoveCascade() {
    //multiple deletions
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(40, false);

    for (int i = 0; i < (int)people.size(); ++i){
        C.insert(people[i]);
    }

    bool ok = true;
    for (int i = 0; i < 12; ++i) {
        if (!C.remove(people[i])){
            ok = false;
        }
    }

    for (int i = 0; i < 12; ++i) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (!r.getKey().empty()){
            ok = false;
        }
    }
    for (int i = 12; i < (int)people.size(); ++i) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (r.getKey().empty()){
            ok = false;
        }
    }
    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testRehashAfterInsert(){
    //test rehash after insert
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(500, false);

    for (int i = 0; i < (int)people.size(); i++){
        C.insert(people[i]);
    }

    bool ok = (C.lambda() < 0.5f);

    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testRehashCompletionInsert(){
    //tests rehash completion
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(500, false);

    for (int i = 0; i < (int)people.size(); i = i + 1){
        C.insert(people[i]);
    }

    bool ok = (C.deletedRatio() < 1.0f);

    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testRehashAfterRemove(){
    //test rehash after remove
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(50, false);

    for (int i = 0; i < (int)people.size(); i++){
        C.insert(people[i]);
    }

    for (int i = 0; i < 40; i++){
        C.remove(people[i]);
    }
    float before = C.deletedRatio();
    Person dummy("dummy", 9999);
    C.insert(dummy);
    C.remove(dummy);

    float after = C.deletedRatio();

    bool ok = (after <= before);

    ok ? m_passed++ : m_failed++;
    return ok;
}



bool Tester::testRehashCompletionRemove() {
    Cache C(101, hashCode, LINEAR);
    vector<Person> people = generatePeople(50, false);

    for (int i = 0; i < (int)people.size(); i = i + 1){
        C.insert(people[i]);
    }
    for (int i = 0; i < 40; i = i + 1){
        C.remove(people[i]);
    }

    for (int i = 0; i < 20; i = i + 1){
        C.insert(Person("extra"+to_string(i), 5000+i));
    }

    bool ok = (C.deletedRatio() < 1.0f);

    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testInsertLarge() {
    Cache C(101, hashCode, DOUBLEHASH);
    int N = 5000;
    vector<Person> people = generatePeople(N, true);

    bool ok = true;
    for (int i = 0; i < (int)people.size(); ++i) {
        if (!C.insert(people[i])) {

        }
    }
    int found = 0;
    for (int i = 0; i < (int)people.size(); ++i) {
        Person r = C.getPerson(people[i].getKey(), people[i].getID());
        if (!(r.getKey().empty())){
            found++;
        }
    }
    ok = (found >= (int)(0.9 * N));
    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testRandomizedOperations() {
    Cache C(101, hashCode, QUADRATIC);
    Random rndID(MINID, MINID + 100000);
    Random rndStr(MINSEARCH, MAXSEARCH);
    rndID.setSeed(123);
    rndStr.setSeed(456);

    vector<Person> pool;
    int ops = 2000;
    bool ok = true;

    for (int i = 0; i < ops; ++i) {
        int choice = i % 3;
        if (choice == 0) {
            string s = searchStr[rndStr.getRandNum()];
            Person p(s, rndID.getRandNum());
            if (C.insert(p)){
                pool.push_back(p);
            }
        } else if (choice == 1) {
            if (!pool.empty()) {
                int idx = (i * 7) % pool.size();
                C.remove(pool[idx]);
            }
        } else {
            if (!pool.empty()) {
                int idx = (i * 11) % pool.size();
                Person r = C.getPerson(pool[idx].getKey(), pool[idx].getID());
                if (r.getKey().empty()) {

                } else {
                    if (!(r == pool[idx])){
                        ok = false;
                    }
                }
            }
        }
    }

    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testGetPersonDeleted() {
    Cache C(101, hashCode, LINEAR);
    Person p("todelete", MINID + 1);
    C.insert(p);
    C.remove(p);
    Person r = C.getPerson(p.getKey(), p.getID());
    bool ok = r.getKey().empty();
    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testGetPersonDNE() {
    Cache C(101, hashCode, LINEAR);
    Person r = C.getPerson("doesnotexist", MINID + 2);
    bool ok = r.getKey().empty();
    if (ok) m_passed = m_passed + 1; else m_failed = m_failed + 1;
    return ok;
}


bool Tester::testChangePolicyDuringRehash() {
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(600, false);

    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        C.insert(*it);
    }

    C.changeProbPolicy(DOUBLEHASH);

    Person extra("extra", MINID + 999);
    C.insert(extra);

    Person r = C.getPerson(extra.getKey(), extra.getID());

    bool ok = !r.getKey().empty() && (r == extra);
    if (ok) m_passed++; else m_failed++;
    return ok;
}

bool Tester::testLazyDeletionBehavior() {
    Cache C(500, hashCode, LINEAR);
    Person p("lazy", MINID+1);
    C.insert(p);
    C.remove(p);

    Person newP("lazy", MINID+2);
    bool inserted = C.insert(newP);

    Person oldSearch = C.getPerson(p.getKey(), p.getID());
    Person newSearch = C.getPerson(newP.getKey(), newP.getID());

    bool ok = inserted && oldSearch.getKey().empty() && !(newSearch.getKey().empty()) && newSearch == newP;
    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testUpdateIDDuplicate() {
    Cache C(500, hashCode, LINEAR);
    Person p1("key1", MINID+1);
    Person p2("key2", MINID+2);
    C.insert(p1);
    C.insert(p2);

    bool updated = C.updateID(p2.getKey(), p1.getID());

    bool ok = !updated;
    if (ok) m_passed++; else m_failed++;
    return ok;
}

// --- Test searching during incremental rehash ---
bool Tester::testSearchDuringRehash() {
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(600, false);

    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        C.insert(*it);
    }

    bool ok = true;
    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        Person r = C.getPerson(it->getKey(), it->getID());
        if (r.getKey().empty() || !(r == *it)) ok = false;
    }

    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testRemoveNonexistent() {
    Cache C(500, hashCode, LINEAR);
    Person p("existent", MINID+1);
    C.insert(p);

    Person dummy("doesnotexist", MINID+999);
    bool removed = C.remove(dummy);

    bool ok = !removed;
    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testEdgeLoadFactor() {
    int tableSize = 200; 
    Cache C(tableSize, hashCode, LINEAR);
    vector<Person> people = generatePeople(100, false);

    for (int i = 0; i < 100; i++){
        C.insert(people[i]);
    }

    float expected = 100.0f / C.m_currentCap;
    bool ok = (C.lambda() - expected) < 1e-6;
    if (ok) m_passed++; else m_failed++;
    return ok;
}



bool Tester::testEdgeDeletedRatio() {
    int tableSize = 10;
    Cache C(tableSize, hashCode, LINEAR);
    vector<Person> people = generatePeople(10, false);

    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        C.insert(*it);
    }

    for (int i = 0; i < 8; ++i){
        C.remove(people[i]);
    }

    bool ok = fabs(C.deletedRatio() - 0.8) < 1e-6;
    if (ok) m_passed++; else m_failed++;
    return ok;
}


bool Tester::testQuadraticHashing() {
    Cache C(500, hashCode, QUADRATIC);
    vector<Person> people = generatePeople(200, true);

    bool ok = true;
    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        if (!C.insert(*it)) ok = false;
    }

    for (vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        Person r = C.getPerson(it->getKey(), it->getID());
        if (r.getKey().empty() || !(r == *it)){
            ok = false;
        }
    }

    if (ok) m_passed++; else m_failed++;
    return ok;
}

bool Tester::testRehash25PercentIncrement() {
    Cache C(500, hashCode, LINEAR);
    vector<Person> people = generatePeople(500, false);

    for (unsigned int i = 0; i < people.size(); i++) {
        C.insert(people[i]);
    }

    Person dummy("dummy", MINID + 9999);
    C.insert(dummy);

    bool allFound = true;
    for (unsigned int i = 0; i < people.size(); i++) {
        Person result = C.getPerson(people[i].getKey(), people[i].getID());
        if (result.getKey().empty() || !(result == people[i])) {
            allFound = false;
        }
    }

    Person result = C.getPerson(dummy.getKey(), dummy.getID());
    if (result.getKey().empty() || !(result == dummy)){
        allFound = false;
    }

    if (allFound) m_passed++; else m_failed++;
    return allFound;
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

unsigned int hashCode(const string str);

int main(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode, DOUBLEHASH);
    
    Tester tester;
    cout << "testInsertNonColliding: " << (tester.testInsertNonColliding() ? "PASS" : "FAIL") << endl;
    cout << "testInsertColliding: " << (tester.testInsertColliding() ? "PASS" : "FAIL") << endl;
    cout << "testInsertLarge: " << (tester.testInsertLarge() ? "PASS" : "FAIL") << endl;
    cout << "testFindErrorCase: " << (tester.testFindErrorCase() ? "PASS" : "FAIL") << endl;
    cout << "testFindNonColliding: " << (tester.testFindNonColliding() ? "PASS" : "FAIL") << endl;
    cout << "testFindColliding: " << (tester.testFindColliding() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveNonColliding: " << (tester.testRemoveNonColliding() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveColliding: " << (tester.testRemoveColliding() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveCascade: " << (tester.testRemoveCascade() ? "PASS" : "FAIL") << endl;
    cout << "testRehashAfterInsert: " << (tester.testRehashAfterInsert() ? "PASS" : "FAIL") << endl;
    cout << "testRehashCompletionInsert: " << (tester.testRehashCompletionInsert() ? "PASS" : "FAIL") << endl;
    cout << "testRehashAfterRemove: " << (tester.testRehashAfterRemove() ? "PASS" : "FAIL") << endl;
    cout << "testRehashCompletionRemove: " << (tester.testRehashCompletionRemove() ? "PASS" : "FAIL") << endl;
    cout << "testRandomizedOperations: " << (tester.testRandomizedOperations() ? "PASS" : "FAIL") << endl;
    cout << "testGetPersonDeleted: " << (tester.testGetPersonDeleted() ? "PASS" : "FAIL") << endl;
    cout << "testGetPersonDNE: " << (tester.testGetPersonDNE() ? "PASS" : "FAIL") << endl;
    cout << "testChangePolicyDuringRehash: " << (tester.testChangePolicyDuringRehash() ? "PASS" : "FAIL") << endl;
    cout << "testLazyDeletionBehavior: " << (tester.testLazyDeletionBehavior() ? "PASS" : "FAIL") << endl;
    cout << "testUpdateIDDuplicate: " << (tester.testUpdateIDDuplicate() ? "PASS" : "FAIL") << endl;
    cout << "testSearchDuringRehash: " << (tester.testSearchDuringRehash() ? "PASS" : "FAIL") << endl;
    cout << "testRemoveNonexistent: " << (tester.testRemoveNonexistent() ? "PASS" : "FAIL") << endl;
    cout << "testEdgeLoadFactor: " << (tester.testEdgeLoadFactor() ? "PASS" : "FAIL") << endl;
    cout << "testEdgeDeletedRatio: " << (tester.testEdgeDeletedRatio() ? "PASS" : "FAIL") << endl;
    cout << "testQuadraticHashing: " << (tester.testQuadraticHashing() ? "PASS" : "FAIL") << endl;
    cout << "testRehash25PercentIncrement: " << (tester.testRehash25PercentIncrement() ? "PASS" : "FAIL") << endl;

    tester.TestResult();
    return 0;
}

unsigned int hashCode(const string str) {
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;
    for ( int i = 0 ; i < (int)(str.length()); i++)
       val = val * thirtyThree + str[i] ;
    return val ;
 }