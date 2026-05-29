/*****************************************                                                                          
** File:    cache.cpp                                                                                            
** Project: CMSC 341 Project 4, Fall 2025                                                                           
** Author:  Akanksha Madhu Kiran                                                                                    
** Date:    12/02/2025                                                                                              
** E-mail:  amadhuk1@umbc.edu                                                                                       
** This file contains the cache.cpp implementation                                                                           
*****************************************/
#include "cache.h"

Cache::Cache(int size, hash_fn hash, prob_t probing = DEFPOLCY) {
    //ensure valid size
    if (size < MINPRIME){
        size = MINPRIME;
    }
    if (size > MAXPRIME){
        size = MAXPRIME;
    }
    if (!isPrime(size)){//check if prime
        size = findNextPrime(size);//if not prime make size the next prime no.
    }
    m_currentCap = size;
    m_hash = hash;
    m_currentTable = new Person*[m_currentCap]();//create hash table
    m_currentSize  = 0;
    m_currNumDeleted = 0;
    m_currProbing = probing;
    m_oldTable = nullptr;
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;
    m_oldProbing = DEFPOLCY;
    m_newPolicy = probing;
    m_transferIndex = 0;
}

Cache::~Cache() {
    if(m_currentTable != nullptr){//free all nodes in current table
        for (int i = 0; i < m_currentCap; i = i + 1) {
           delete m_currentTable[i];
        }
        delete[] m_currentTable;
        m_currentTable = nullptr;
    }
    if(m_oldTable != nullptr){//free all nodes in old table
        for (int i = 0; i < m_oldCap; i = i + 1) {
            delete m_oldTable[i];
        }
        delete[] m_oldTable;
        m_oldTable = nullptr;
    }
}


void Cache::changeProbPolicy(prob_t policy) {
    if(m_newPolicy != policy){//update policy if different
        m_newPolicy = policy; 
    } else {
        return;
    }
}

bool Cache::insert(Person person) {
    if(person.getKey().empty()){//if empty key
        return false;
    }
    if(person.getID() < MINID || person.getID() > MAXID){//if out of bounds
        return false;
    }
    bool oldFlag = false;
    if(queryPerson(person, oldFlag) != nullptr){//if already exists don't insert
        return false;
    }

    startRehashIfNeeded();//rehash

    int idx = queryIndex(person, false, false);//find index where needs to be inserted
    if(idx == -1){
        return false;//no position
    }
    if(m_currentTable[idx] != nullptr){//check if bucket has deleted person
        delete m_currentTable[idx];//remove old deleted node
        m_currentTable[idx] = nullptr;
        m_currNumDeleted = max(0, m_currNumDeleted - 1);
    } else {
        m_currentSize = m_currentSize + 1;//insert into empty location
    }
    m_currentTable[idx] = new Person(person);//new person object
    m_currentTable[idx]->setUsed(true);//mark as used
    transfer();//move elements
    return true;
}

bool Cache::remove(Person person) {
    transfer();//rehash
    int idx = queryIndex(person, false, false);
    if(idx != -1 && m_currentTable[idx] != nullptr && m_currentTable[idx]->getUsed()){ //check if location valid
        m_currentTable[idx]->setUsed(false);//mark deleted in current table
        m_currNumDeleted++;
        return true;
    }

    if(m_oldTable != nullptr){//check old table
        idx = queryIndex(person, true, false);
        if (idx != -1 && m_oldTable[idx] != nullptr && m_oldTable[idx]->getUsed()) {
            m_oldTable[idx]->setUsed(false);//mark deleted in old table
            m_oldNumDeleted++;
            return true;
        }
    }
    return false;//if not found in both table
}

const Person Cache::getPerson(string key, int id) const {
    Person temp(key, id);//create new object to help hashing

    int idx = queryIndex(temp, false, false);//search current table for index
    if(idx != -1 && m_currentTable[idx] != nullptr && m_currentTable[idx]->getUsed()){
        return *(m_currentTable[idx]);//return found person
    }

    if(m_oldTable != nullptr){//if rehashing search old table
        idx = queryIndex(temp, true, false);
        if (idx != -1 && m_oldTable[idx] != nullptr && m_oldTable[idx]->getUsed()) {
            return *(m_oldTable[idx]);
        }
    }
    return Person();//if not found
}


bool Cache::updateID(Person person, int ID) {
    if(ID < MINID || ID > MAXID || getPerson(person.m_key, ID).getUsed()){//check if valid id
        return false;
    }
    bool oldFlag = false;
    Person* temp = queryPerson(person,oldFlag);//search for person
    if(!temp){
        return false;//does not exist
    }
    temp->setID(ID);//update id
    return true;
}


float Cache::lambda() const {
    if(m_currentCap == 0){//check valid
        return 0.0;
    }
    return (float)m_currentSize/m_currentCap;
}

float Cache::deletedRatio() const {
    if (m_currentSize == 0){//check valid
        return 0.0;
    }
    return (float)m_currNumDeleted / m_currentSize;
}

void Cache::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr) {
        for (int i = 0; i < m_currentCap; i = i + 1) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr) {
        for (int i = 0; i < m_oldCap; i = i + 1) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
    }
}


bool Cache::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int Cache::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}


int Cache::queryIndex(const Person& person, bool old, bool collideDel) const {
    Person** table;
    int capacity;
    if(old){//pick table and capacity according to old
        table = m_oldTable;
        capacity = m_oldCap;
    } else {
        table = m_currentTable;
        capacity = m_currentCap;
    }
    if(table == nullptr || capacity <= 0){//check if valid table and capacity
        return -1;
    }
    int hv = m_hash(person.getKey());//compute hash value
    if(hv < 0){
        hv = -hv;//make hash positive(absolute value)
    }
    hv %= capacity;
    int hashVal = hv;//slot index
    int firstDeleted = -1;
    int i = 0;

    prob_t policy;
    if (old) {
        policy = m_oldProbing;
    } else {
        policy = m_currProbing;
    }

    while (i < capacity){//loop until we check every index
        int index;
        if(policy == LINEAR) {
            index = (hashVal + i) % capacity;//linear probing
        } else if(policy == QUADRATIC) {
            index = (hashVal + (i * i) % capacity) % capacity;//quadratic probing
        } else {
            int h2_raw = m_hash(person.getKey());//double hashing
            if(h2_raw < 0){
                h2_raw = -h2_raw;
            }
            int h2 = 11 - (h2_raw % 11);
            if(h2 <= 0){
                h2 = 1;
            }
            int step = (i * h2);
            index = (hashVal + step) % capacity;//compute index
            if(index < 0){
                index += capacity;//if negative index
            }
        }
        Person* slot = table[index];
        if(slot == nullptr){
            if(firstDeleted != -1){
                return firstDeleted;//prefer first deleted
            }
            return index;//if empty slot found
        }
        if(!slot->getUsed()){//slot is deleted record for reuse
            if (firstDeleted == -1 && !collideDel) {
                firstDeleted = index;
            }
        }
        else if(*slot == person){
            return index;
        }
        i++;
    }
    if(firstDeleted != -1){
        return firstDeleted;
    }
    return -1;//if not found no reusable slot
}



Person* Cache::queryPerson(const Person& person) const {
    bool old = false;
    return queryPerson(person, old);//sets old boolean value
}

Person* Cache::queryPerson(const Person& person, bool& old) const {
    old = false;
    if(m_currentTable){
        int idx = queryIndex(person, false, true);//search current table allowing collision
        Person* p = m_currentTable[idx];
        if(p && p->getUsed() && *p == person){
            old = false;
            return p;//return pointer ti person in current table
        }
    }

    if(m_oldTable){//if rehashing check old table as well
        int idx = queryIndex(person, true, true);
        Person* p = m_oldTable[idx];
        if(p && p->getUsed() && *p == person){
            old = true;//if found in old table
            return p;
        }
    }
    return nullptr;//if not found
}


int Cache::getProbeIndex(const Person& person, int i, bool old) const {
    int cap;
    if(old){ //pick capacity
        cap = m_oldCap;
    }else{
        cap = m_currentCap;
    }
    if(cap <= 0){//check if valid
        return 0;
    }

    int hv = m_hash(person.getKey());//calculate hash
    if(hv < 0){
        hv = -hv;//absolute value
    }

    int h1 = hv % cap;//primary hash reduced
    if(h1 < 0){
        h1 += cap;
    }

    prob_t policy;
    if(old){
        policy = m_oldProbing;
    } else {
        policy = m_currProbing;
    }
    if(policy == LINEAR){
        int res = (h1 + i) % cap;//linear probing
        if(res < 0){
            res += cap;
        }
        return res;
    } else if (policy == QUADRATIC){
        int offset = (i * i) % cap;//quadratic probing
        int res = (h1 + offset) % cap;
        if (res < 0){
            res += cap;
        }
        return res;
    } else {
        int hv2 = m_hash(person.getKey());//double hashing
        if (hv2 < 0){
            hv2 = -hv2;
        }
        int h2 = 11 - (hv2 % 11);//step size second
        if (h2 <= 0){
            h2 = 1;
        }
        int step = (i * h2);//compute
        int res = (h1 + step) % cap;
        if (res < 0){
            res += cap;
        }
        return res;
    }
}

void Cache::startRehashIfNeeded() {
    if (m_oldTable != nullptr){
        return;//chacke if rehash
    }

    int used = m_currentSize - m_currNumDeleted;//no. of used entries
    if (used < 0){
        used = 0;
    }

    bool needByLoad = false;
    if (m_currentCap > 0) {
        needByLoad = ((float)used/(float)m_currentCap) > 0.5f;//rehash if load factor
    }

    bool needByDeleted = false;
    if (m_currentSize > 0) {
        needByDeleted = ((float)m_currNumDeleted/(float)m_currentSize) > 0.8f;//rehash if many deleted
    }

    if (!(needByLoad || needByDeleted)){
        return;//no rehash
    }
    //move current table to old table
    m_oldTable = m_currentTable;
    m_oldCap = m_currentCap;
    m_oldSize = m_currentSize;
    m_oldNumDeleted = m_currNumDeleted;
    m_oldProbing = m_currProbing;

    int target = used * 4;//choose new target
    if (target < MINPRIME){
        target = MINPRIME;//check if atleast MINPRIME
    }
    int newCap = findNextPrime(target);//find next prime
    if (newCap > MAXPRIME){
        newCap = MAXPRIME;//go till MAXPRIME
    }

    m_currentCap = newCap;//set new capacity
    m_currentTable = new Person*[m_currentCap]();//allocate new table

    m_currentSize = 0;//reset values
    m_currNumDeleted = 0;

    m_currProbing = m_newPolicy;
    m_transferIndex = 0;
}


bool Cache::continueRehashOneBatch() {
    if(m_oldTable == nullptr){//check if table
        return false;
    }
    while(m_transferIndex < m_oldCap){//loop through until transfer slot is found
        Person* node = m_oldTable[m_transferIndex];
        m_oldTable[m_transferIndex] = nullptr;//clear old table slot
        if(node == nullptr) {
            m_transferIndex++;//if just empty move on
            return true;
        }
        if(!node->getUsed()) {
            delete node;//delete the marked deleted node
            m_transferIndex++;
            return true;
        }
        Person temp(node->getKey(), node->getID(), true);//temp for hashing
        int hv = m_hash(temp.getKey());//compute hash
        if(hv < 0){
            hv = -hv;
        }
        int cap = m_currentCap;//new capacity
        int h1 = hv % cap;
        if(h1 < 0){
            h1 += cap;
        }
        int index = h1;
        int i = 0;

        while(i < cap && m_currentTable[index] != nullptr && m_currentTable[index]->getUsed()){//probe until available slot
            i = i + 1;
            if(m_currProbing == LINEAR){//linear probing
                index = (h1 + i) % cap;
                if(index < 0){
                    index += cap;
                }
            } else if (m_currProbing == QUADRATIC){//quadratic probing
                int offset = (i * i) % cap;
                index = (h1 + offset) % cap;
                if(index < 0){
                    index += cap;
                }
            } else {//double hashing
                int hv2 = m_hash(temp.getKey());
                if(hv2 < 0){
                    hv2 = -hv2;
                }
                int h2 = 11 - (hv2 % 11);//step size
                if(h2 <= 0){
                    h2 = 1;
                }
                int step = (i * h2);
                index = (h1 + step) % cap;
                if(index < 0){
                    index += cap;
                }
            }
        }

        if(m_currentTable[index] != nullptr && !m_currentTable[index]->getUsed()){
            delete m_currentTable[index];//reuse deleted old object
            m_currNumDeleted--;
        } else if (m_currentTable[index] == nullptr) {
            m_currentSize++;
        }
        m_currentTable[index] = node;//move node pointer
        m_transferIndex++;
        return true;
    }

    if(m_transferIndex >= m_oldCap){
        for(int j = 0; j < m_oldCap; j = j + 1){
            delete m_oldTable[j];//clean any pointers
        }
        delete[] m_oldTable;//free old table
        m_oldTable = nullptr;
        m_oldCap = 0;
        m_oldSize = 0;
        m_oldNumDeleted = 0;
        m_transferIndex = 0;
        return false;//rehash done
    }

    return false;//no action
}

void Cache::transfer() {
    startRehashIfNeeded();//ensure rehashed

    if(m_oldTable == nullptr){
        return;//do nothing
    }
    int amount = m_oldCap/4;//move
    if(amount < 1){
        amount = 1;//ensure 1 slot atleast
    }
    int moved = 0;

    while(moved < amount && m_oldTable != nullptr){
        continueRehashOneBatch();//move 1 at a time
        moved++;
    }
}