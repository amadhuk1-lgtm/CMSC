/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 1, Fall 2025
** Author:  Akanksha Madhu Kiran
** Date:    09/29/2025
** E-mail:  amadhuk1@umbc.edu
** This file contains tests for the Railroad class.
*****************************************/
#include "railroad.h"

class Tester{
public:
    Tester();

    bool defaultConstructor();
    bool extendAtHead_normal();
    bool extendAtHead_error();
    bool extendAtTail_normal();
    bool extendAtTail_error();
    bool removeStation_normal();
    bool removeStation_error();
    bool removeStation_links_cleared();
    bool removeStation_withLinks();
    bool assignment_normal();
    bool assignment_edge_1();
    bool assignment_edge_2();
    bool copy_normal();
    bool copy_edge_1();
    bool copy_edge_2();
    bool makeRoute_start_missing();
    bool makeRoute_overwrite_link();
    bool makeRoute_valid();
    bool travel_valid();
    bool travel_invalid();
    bool setNumPassengers_basic();
    bool clearAllRoutes_basic();
    bool clearNetwork_basic();
    void TestResult();

private:
    int m_passed; //number of tests passed or failed
    int m_failed;
};

int main() {
    Railroad aNetwork;
    for (int i = 1; i < 10; i++){ //adding stations(nodes)
        aNetwork.extendAtTail(i, i * 2);
    } 
    cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    list<pair<int, DIRECTION>> aRoute; //holding routes
    aRoute.push_back(pair<int, DIRECTION>(2, NORTH));
    aRoute.push_back(pair<int, DIRECTION>(5, SOUTH));
    aRoute.push_back(pair<int, DIRECTION>(8, NONE));//adding stops
    aNetwork.makeRoute(aRoute);
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();
    cout << "\n\nRemove node 5.\n\n";
    aNetwork.removeStation(5);
    cout << "Removing node 5 invalidates the route passing through 5.\n\n";
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();
    Tester tester;
    cout << "defaultConstructor: " << (tester.defaultConstructor() ? "PASS" : "FAIL") << endl;
    cout << "extendAtHead_normal: " << (tester.extendAtHead_normal() ? "PASS" : "FAIL") << endl;
    cout << "extendAtHead_error: " << (tester.extendAtHead_error() ? "PASS" : "FAIL") << endl;
    cout << "extendAtTail_normal: " << (tester.extendAtTail_normal() ? "PASS" : "FAIL") << endl;
    cout << "extendAtTail_error: " << (tester.extendAtTail_error() ? "PASS" : "FAIL") << endl;
    cout << "removeStation_normal: " << (tester.removeStation_normal() ? "PASS" : "FAIL") << endl;
    cout << "removeStation_error: " << (tester.removeStation_error() ? "PASS" : "FAIL") << endl;
    cout << "removeStation_links_cleared: " << (tester.removeStation_links_cleared() ? "PASS" : "FAIL") << endl;
    cout << "removeStation_withLinks: " << (tester.removeStation_withLinks() ? "PASS" : "FAIL") << endl;
    cout << "assignment_normal: " << (tester.assignment_normal() ? "PASS" : "FAIL") << endl;
    cout << "assignment_edge_1: " << (tester.assignment_edge_1() ? "PASS" : "FAIL") << endl;
    cout << "assignment_edge_2: " << (tester.assignment_edge_2() ? "PASS" : "FAIL") << endl;
    cout << "copy_normal: " << (tester.copy_normal() ? "PASS" : "FAIL") << endl;
    cout << "copy_edge_1: " << (tester.copy_edge_1() ? "PASS" : "FAIL") << endl;
    cout << "copy_edge_2: " << (tester.copy_edge_2() ? "PASS" : "FAIL") << endl;
    cout << "makeRoute_start_missing: " << (tester.makeRoute_start_missing() ? "PASS" : "FAIL") << endl;
    cout << "makeRoute_overwrite_link: " << (tester.makeRoute_overwrite_link() ? "PASS" : "FAIL") << endl;
    cout << "makeRoute_valid: " << (tester.makeRoute_valid() ? "PASS" : "FAIL") << endl;
    cout << "travel_valid: " << (tester.travel_valid() ? "PASS" : "FAIL") << endl;
    cout << "travel_invalid: " << (tester.travel_invalid() ? "PASS" : "FAIL") << endl;
    cout << "setNumPassengers_basic: " << (tester.setNumPassengers_basic() ? "PASS" : "FAIL") << endl;
    cout << "clearAllRoutes_basic: " << (tester.clearAllRoutes_basic() ? "PASS" : "FAIL") << endl;
    cout << "clearNetwork_basic: " << (tester.clearNetwork_basic() ? "PASS" : "FAIL") << endl;
    tester.TestResult(); //show end result of passes and fails
    return 0;
}

Tester::Tester(){
    m_passed=0;
    m_failed=0;
}

bool Tester::defaultConstructor() {
    Railroad rr; //create object
    bool pass = rr.m_head == nullptr && rr.m_tail == nullptr && rr.m_numStations == 0; //check all conditions
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::extendAtHead_normal() {
    Railroad rr;
    for (int i = 1; i <= 100; ++i) { //adding 100 stations at head
        if (!rr.extendAtHead(i, i*10)){ //to check if added or not
            return false;
        }
    }
    int count = 0;
    Station* cur = rr.m_head;
    while (cur) { //goes through linked list
        count++;
        cur = cur->m_next;
    }
    bool pass = count == 100 && rr.m_head && rr.m_tail; //to check if stations added
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::extendAtHead_error() {
    Railroad rr;
    bool neg = rr.extendAtHead(-10, 1);
    bool zero = rr.extendAtHead(0, 1);
    bool dups = false;
    if (rr.extendAtHead(10, 1) && !rr.extendAtHead(10, 2)) {
        dups = true; //to check if already exists
    }
    bool pass = false;
    if (!neg && !zero && dups) { //if all conditions pass
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::extendAtTail_normal() {
    bool pass = true;
    Railroad rr;
    for (int i = 1; i <= 100; i++) {
        if (!rr.extendAtTail(i, i * 2)) { //to check if adding stations worked
            pass = false;
        }
    }
    int count = 0;
    Station* cur = rr.m_head;
    while (cur != nullptr) { //goes through the linked list
        count++;
        cur = cur->m_next;
    }
    if (!(pass && count == 100)) { //to check if conditions satisfied
        pass = false;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::extendAtTail_error() {
    bool pass = false;
    Railroad rr;
    bool neg = rr.extendAtTail(-1, 1);
    bool zero = rr.extendAtTail(0, 1);
    bool dups = false;
    if (rr.extendAtTail(5, 1) && !rr.extendAtTail(5, 9)) {
        dups = true;
    }
    if (!neg && !zero && dups) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::removeStation_normal() {
    bool pass = true;
    Railroad rr;
    bool insertFailed = false;
    for (int i = 1; i <= 10 && !insertFailed; i++) { //to add 10 stations
        if (!rr.extendAtTail(i, i)) {
            pass = false; //check if addition fails
            insertFailed = true;
        }
    }
    bool removeFailed = false;
    for (int i = 1; i <= 10 && !removeFailed; i++) { //loop through to remove stations
        if (!rr.removeStation(i)) {
            pass = false;
            removeFailed = true;
        }
    }
    if (!(rr.m_head == nullptr && rr.m_tail == nullptr)) { //cross check if list empty
        pass = false;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::removeStation_error() {
    bool pass = false;
    Railroad rr;
    for (int i = 1; i <= 10; i++) { //adding 10 stations
        rr.extendAtTail(i, i);
    }
    if (!rr.removeStation(1000)) { //to check what happens when removing stations that don't exist
        pass = true;//if it works then pass true
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::removeStation_links_cleared() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(1, 10); //add stations
    rr.extendAtTail(2, 20);
    rr.m_head->m_north = rr.m_tail; //links stations both ways
    rr.m_tail->m_south = rr.m_head;
    bool check = false;
    if (rr.m_head->m_north == rr.m_tail) {
        check = true;
    }
    bool removed = rr.removeStation(2); //to remove station
    bool left = false;
    if (rr.m_head->m_north == nullptr) {
        left = true; //to check if removed station was successful
    }
    if (check && removed && left) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::removeStation_withLinks(){
    Railroad rr;
    rr.extendAtHead(1, 10);
    rr.extendAtTail(2, 20);
    rr.extendAtTail(3, 30);

    list<pair<int,DIRECTION>> route = {{1, EAST}, {2, EAST}, {3, EAST}};
    rr.makeRoute(route);

    bool removed = rr.removeStation(2);

    if (removed) { //check that removal was successful
        if (rr.findStation(1)->m_east == nullptr) {
            m_passed++;
            return true; //both conditions satisfied
        } else {
            m_failed++;
            return false;
        }
    } else {
        m_failed++;
        return false;
    }
}

bool Tester::assignment_normal() {
    bool pass = true;
    Railroad rr1, rr2;
    bool extendFailed = false;
    for (int i = 1; i <= 20 && !extendFailed; i++) { //loop through to add more stations
        if (!rr1.extendAtHead(i, i * 3)) {
            pass = false; //check if addition successful or not
            extendFailed = true;
        }
    }
    rr2 = rr1;
    bool diffPointers = false;
    if (rr1.m_head != rr2.m_head) { //to check if heads are not same
        diffPointers = true;
    }
    Station* a = rr1.m_head;
    Station* b = rr2.m_head;
    bool misMatch = false;
    while (a && b && !misMatch) { //to compare stations
        if (!(a->m_code == b->m_code && a->m_passengers == b->m_passengers)) {
            pass = false;
            misMatch = true;
        }
        a = a->m_next; //moving forward
        b = b->m_next;
    }
    if (!(diffPointers && pass)) {
        pass = false;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::assignment_edge_1() {
    bool pass = false;
    Railroad rr1;
    Railroad rr2;
    rr1.extendAtHead(5, 10); //adding a station
    rr2 = rr1;
    bool diffPointers = false;
    if (rr1.m_head != rr2.m_head) { //to check if deep copy created
        diffPointers = true;
    }
    if (diffPointers && rr2.m_head && rr2.m_head->m_code == 5) { //cross check
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::assignment_edge_2() {
    bool pass = false;
    Railroad rr1;
    Railroad rr2;
    rr1.extendAtHead(5, 10); //add stations
    rr1.extendAtTail(6, 20);
    rr2 = rr1;
    bool diffPointers = false;
    if (rr1.m_head != rr2.m_head) { //check if different heads
        diffPointers = true;
    }
    if (diffPointers && rr2.m_head && rr2.m_head->m_code == 5) { //check if station copied
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::copy_normal() {
    bool pass = true;
    Railroad rr1;
    Railroad rr2;
    for (int i = 1; i <= 30; i++) { //loop through to add 30 stations
        if (!rr1.extendAtTail(i, i)) { 
            pass = false;
        }
    }
    rr2 = Railroad(rr1);
    bool diffPtrs = false;
    if (rr1.m_head != rr2.m_head) { //to check if heads are not same
        diffPtrs = true; 
    }
    Station* a = rr1.m_head;
    Station* b = rr2.m_head;
    bool misMatch = false;
    while (a && b && !misMatch) { //loop through linked list to check if station code and passengers
        if (!(a->m_code == b->m_code && a->m_passengers == b->m_passengers)) {
            pass = false;
            misMatch= true;
        }
        a = a->m_next;
        b = b->m_next; //move forward
    }
    if (!(diffPtrs && pass)) {
        pass = false;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::copy_edge_1() {
    bool pass = false;
    Railroad rr1;
    Railroad rr2;
    rr1.extendAtTail(11, 4);
    rr2 = Railroad(rr1); //copy constructor
    bool diffPtrs = false;
    if (rr1.m_head != rr2.m_head) { //check if copies are not same
        diffPtrs = true;
    }
    if (diffPtrs && rr2.m_head->m_code == 11) { //check stuff in station
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::copy_edge_2() {
    bool pass = true;
    Railroad rr1;
    Railroad rr2;
    rr1.extendAtTail(14, 21);
    rr1.extendAtTail(42, 42); //add stations
    rr2 = Railroad(rr1);
    bool diffPtrs = false;
    if (rr1.m_head != rr2.m_head) { //check if different pointers
        diffPtrs = true;
    }
    Station* a = rr1.m_head;
    Station* b = rr2.m_head;
    bool misMatch = false;
    while (a && b && !misMatch) {
        if (a->m_code != b->m_code) { //compare nodes/stations
            pass = false;
            misMatch = true;
        }
        a = a->m_next;
        b = b->m_next;
    }
    if (!(diffPtrs && pass)) {
        pass = false;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::makeRoute_start_missing() {
    bool pass = false;
    Railroad rr;
    list<pair<int, DIRECTION> > route;
    route.push_back(pair<int, DIRECTION>(99, NORTH));
    route.push_back(pair<int, DIRECTION>(100, NORTH));
    if (!rr.makeRoute(route)) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::makeRoute_overwrite_link() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(1, 1);
    rr.extendAtTail(2, 2);
    list<pair<int, DIRECTION> > rt1 = { {1, NORTH}, {2, SOUTH} };
    bool mk1 = rr.makeRoute(rt1);
    list<pair<int, DIRECTION> > rt2 = { {1, NORTH}, {3, SOUTH} };
    bool mk2 = !rr.makeRoute(rt2);
    if (mk1 && mk2) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::makeRoute_valid() {
    bool pass = false;
    Railroad rr;
    rr.extendAtHead(1, 10);
    rr.extendAtTail(2, 20);
    rr.extendAtTail(3, 30);
    list<pair<int, DIRECTION> > route = { {1, EAST}, {2, SOUTH}, {3, NONE} };
    bool mk = rr.makeRoute(route);
    bool dirOK = false;
    if (rr.m_head->m_east && rr.m_head->m_east->m_code == 2) {
        dirOK = true;
    }
    if (mk && dirOK) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::travel_valid() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(2, 10);
    rr.extendAtTail(5, 15);
    rr.extendAtTail(8, 20);
    list<pair<int, DIRECTION> > route = { {2, NORTH}, {5, SOUTH}, {8, NONE} };
    rr.makeRoute(route);
    int total = rr.travel(route);
    if (total == 45) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::travel_invalid() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(3, 11);
    list<pair<int, DIRECTION> > route = { {3, SOUTH}, {4, NORTH} };
    int result = rr.travel(route);
    if (result == -1) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::setNumPassengers_basic() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(7, 5);
    bool beforeOK = false;
    if (rr.m_head->m_passengers == 5) {
        beforeOK = true;
    }
    bool setOK = rr.setNumPassengers(7, 99);
    bool afterOK = false;
    if (rr.m_head->m_passengers == 99) {
        afterOK = true;
    }
    if (beforeOK && setOK && afterOK) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::clearAllRoutes_basic() {
    bool pass = false;
    Railroad rr;
    rr.extendAtTail(1, 10);
    rr.extendAtTail(2, 20);
    rr.m_head->m_north = rr.m_tail;
    rr.clearAllRoutes();
    if (rr.m_head->m_north == nullptr && rr.m_tail->m_south == nullptr) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

bool Tester::clearNetwork_basic() {
    bool pass = false;
    Railroad rr;
    for (int i = 1; i <= 20; i++) {
        rr.extendAtTail(i, i);
    }
    rr.clearNetwork();
    if (rr.m_head == nullptr && rr.m_tail == nullptr && rr.m_numStations == 0) {
        pass = true;
    }
    if (pass) {
        m_passed++;
    } else {
        m_failed++;
    }
    return pass;
}

void Tester::TestResult() {
    cout << "\nSummary: " << endl;
    cout << "Tests Passed: " << m_passed << "\n";
    cout << "Tests Failed: " << m_failed << "\n";
    cout << "Percentage pass: " 
         << (100.0 * m_passed / (m_passed + m_failed)) << "%\n";
}
