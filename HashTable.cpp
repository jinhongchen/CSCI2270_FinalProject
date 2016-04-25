#include "HashTable.h"

using namespace std;

HashTable::HashTable() {
    keys = new string[MAXTABSZ];
    hashTable = new int[MAXTABSZ*4];
    for (int i=0; i<MAXTABSZ; i++) {
        hashTable[i]=0;
    }
}

HashTable::~HashTable() {
}

void HashTable::readKeys(ifstream & file) {
    for (int i=0; i<MAXTABSZ; i++ ) {
        getline(file, keys[i]);
    }
}

void HashTable::testHashSumPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashSum);
}

void HashTable::testHashSumCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashSum);
}

void HashTable::testHashBernsteinPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashBernstein);
}

void HashTable::testHashBernsteinCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashBernstein);
}

void HashTable::testHashFletcherPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashFletcher);
}

void HashTable::testHashFletcherCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashFletcher);
}

void HashTable::testHashAdlerPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashAdler);
}

void HashTable::testHashAdlerCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashAdler);
}

void HashTable::testHashBobJenkinsPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashBobJenkins);
}

void HashTable::testHashBobJenkinsCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashBobJenkins);
}

void HashTable::testHashPaulHsiehPerf(int tableSize) {
    testPerf(tableSize, &HashTable::hashSum);
}

void HashTable::testHashPaulHsiehCollision(int numKeys, int tableSize) {
    testCollision(numKeys, tableSize, &HashTable::hashSum);
}

void HashTable::testPerf(int tableSize, int (HashTable::*hash)(std::string,int)) {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i=0; i<MAXTABSZ; i++) {
        (this->*hash)(keys[i], tableSize);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
    cout << "HashSum took " << fp_ms.count() << " ms for " << MAXTABSZ << " keys" << endl;
}

void HashTable::testCollision(int numKeys, int tableSize, int (HashTable::*hash)(std::string,int)) {
    for (int i=0; i<MAXTABSZ*4; i++) {
        hashTable[i]=0;
    }
    cout<<"Number of keys: " << numKeys << " tableSize: " << tableSize;
    int colsn=0;
    int idx;
    for (int i=0; i<numKeys; i++) {
        idx = (this->*hash)(keys[i], tableSize);
        if ( hashTable[idx] == 0 ) {
            // first one
            hashTable[idx] = -1;
        } else if ( hashTable[idx] == -1 ) {
            colsn++; 
        }
    }
    // get space usage
    int wasted=0;
    for (int i=0; i<tableSize; i++) {
        if ( hashTable[i] == 0 ) {
            wasted++;
        }
    }
    //wasted space
    double w = (double)100*wasted/tableSize;
    cout << " total collisions: " << colsn << " wasted space: " << w <<"%" << endl;
}

int HashTable::hashSum(std::string x, int s) {
    int sum=0;
    for (int i=0; i<x.length(); i++) {
        sum=sum + x.at(i);
    }
    return sum%s;
}

// Bernstein's hash
int HashTable::hashBernstein(std::string x, int s) {
    unsigned int hash = 5381;
    for(int i = 0; i < x.length(); ++i)
            hash = 33 * hash + x.at(i);
    hash = hash ^ (hash >> 16);
    return hash%s;
}

int HashTable::hashFletcher(std::string x, int s) {
    unsigned int hash;
    int len = x.length();
    len /= 2;
    int i=0;
    unsigned int sum1 = 0xFFFF, sum2 = 0xFFFF;
    while (len) {
            int tlen = len > 360 ? 360 : len;
            len -= tlen;
            do {
                    sum1 += x.at(i);
                    i++;
                    sum2 += sum1;
            } while (--tlen);
            sum1 = (sum1 & 0xffff) + (sum1 >> 16);
            sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    }
    /* Second reduction step to reduce sums to 16 bits */
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    hash = sum2 << 16 | sum1;
    return hash%s;
}

int HashTable::hashAdler(std::string x, int s) {
	int len = x.length();
	unsigned int hash;
	unsigned int a = 1, b = 0;
	int i = 0;
	while (len > 0){
		int tlen = len > 5550 ? 5550 : len;
		len -= tlen;
		do {
			a += x.at(i);
			b += a;
			i++;
		} while (--tlen);
		a %= 65521;
		b %= 65521;
		
	}
	hash = (b << 16) | a;
	return hash % s; 
}

int HashTable::hashBobJenkins(std::string x, int s) {
	unsigned int hash, i;
	for(hash=0, i=0; i<x.length(); ++i) {
    	hash += x.at(i);
    	hash += (hash << 10);
    	hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash % s;
}

int HashTable::hashPaulHsieh(std::string x, int s) {
	int len = x.length();
	unsigned int hash = (unsigned int)len, tmp = 0;
	if(len == 0) return 0;
	
    int rem = len & 3;
	len >>= 2;
	int i = 0;
	/* Main loop */
	for(;len > 0; len--) {
		hash  += x.at(i);
		tmp = (x.at(i+2) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		i   += 2;
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch(rem) {
		case 3:
			hash += x.at(i);
			hash ^= hash << 16;
			hash ^= x.at(i) << 18;
			hash += hash >> 11;
			break;
		case 2:
			hash += x.at(i);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1:
			hash += x.at(i);
			hash ^= hash << 10;
			hash += hash >> 1;
	}

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	return hash;
}
