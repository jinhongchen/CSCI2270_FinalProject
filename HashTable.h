#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#define MAXTABSZ 1000000

struct HashElem{
	std::string title;
	int year;

	HashElem(){};
	HashElem(std::string in_title, int in_year)
	{
		title = in_title;
		year = in_year;
	}
};

class HashTable
{
	public:
		HashTable();
		~HashTable();
		void readKeys(std::ifstream & file);
		void testHashSumPerf(int tableSize);
		void testHashSumCollision(int numKeys, int tableSize);
                void testHashBernsteinPerf(int tableSize);
		void testHashBernsteinCollision(int numKeys, int tableSize);
		void testHashFletcherPerf(int tableSize);
		void testHashFletcherCollision(int numKeys, int tableSize);
		void testHashAdlerPerf(int tableSize);
		void testHashAdlerCollision(int numKeys, int tableSize);
		void testHashBobJenkinsPerf(int tableSize);
		void testHashBobJenkinsCollision(int numKeys, int tableSize);
		void testHashPaulHsiehPerf(int tableSize);
		void testHashPaulHsiehCollision(int numKeys, int tableSize);
	private:
		// csci-2270's hash
		int hashSum(std::string x, int s);
		// Bernstein's hash
		// https://en.wikipedia.org/wiki/List_of_hash_functions
		int hashBernstein(std::string x, int s);
		// http://en.wikipedia.org/wiki/Fletcher's_checksum
		int hashFletcher(std::string x, int s);
		// http://en.wikipedia.org/wiki/Adler-32
		int hashAdler(std::string x, int s);
		// Bob Jenkins, http://www.burtleburtle.net/bob/hash/doobs.html
		int hashBobJenkins(std::string x, int s);
		// Paul Hsieh, http://www.azillionmonkeys.com/qed/hash.html
		int hashPaulHsieh(std::string x, int s);
		void testPerf(int tableSize, int (HashTable::*f)(std::string,int));
		void testCollision(int numKeys, int tableSize, int (HashTable::*f)(std::string,int));
		std::string *keys;
		int *hashTable;
};

#endif // HASHTABLE_H
