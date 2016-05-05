/*
Final Project
Richard Li
4/22/16
Hash algorithm
*/

#include <iostream>
#include <fstream>
#include <cerrno>
#include <string>
#include <sstream>
#include <algorithm>
#include "HashTable.h"

using namespace std;

bool isNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool checkInput(string input) {
	if (input.length() > 7 || input.length() == 0){
		cout<<"Incorrect range"<<endl;
		return false;
	}
	//cout<<"input at 0: "<<input.at(0)<<endl;
	if (input.at(0) == '-' || input.at(0) == '+'){
		cout<<"Enter only an integer without +/- signs"<<endl;
		return false;
	}
	int tablesz;
	if ( isNumber(input) ) {
	    tablesz = stoi(input);
            if ( tablesz <=0 || tablesz > MAXTABSZ ) {
                cout << "Table size is too large, max allowed is " << MAXTABSZ << " (one million) " << endl;
                return false;

            } else {
				return true;
			}
        } else {
            cout << input << " is not a number" << endl;
            return false;
        }
}

int main (int argc, char *argv[]) {

        if ( argc != 2 ) {
                cout<<"Usage: " << argv[0] <<" uuid.txt" <<endl;
                exit(1);
        }

        ifstream file;
        file.open(argv[1]);
        if(file.good() != true ){
                cout<<"File " << argv[1] << " could not be opened, error: "<<errno<<endl;
                exit(1);
        }

	bool flag = true;
	int ans;
	string input;
	HashTable h;

	h.readKeys(file);

	int tabsize;
	cout << "Enter hash table size (<=" << MAXTABSZ << ")" << endl;
	getline(cin, input);

    if (checkInput(input)!= true){
		exit(1);
	} else {
		tabsize = stoi(input);
	}

	while (flag) {
		cout<<"======Main Menu======"<<endl;
		cout << "1. Test CSCI-2270's hash function" << endl;
		cout << "2. Test Bernstein's hash function" << endl;
		cout << "3. Test Fletcher's hash function" << endl;
		cout << "4. Test Adler's hash function" << endl;
		cout << "5. Test Bob Jenkins' hash function" << endl;
		cout << "6. Test Paul Hsieh's hash function" << endl;
		cout << "7. Change hash table size" << endl;
		cout << "8. Quit" << endl;

		cin >> ans;
		switch (ans){
			//testing 2270's hash performance
			case 1:
				h.testHashSumPerf(tabsize);
				h.testHashSumCollision(tabsize, tabsize);
				h.testHashSumCollision(tabsize, tabsize*1.1);
				h.testHashSumCollision(tabsize, tabsize*1.2);
				h.testHashSumCollision(tabsize, tabsize*1.3);
				break;
			//bernstein's hash
			case 2:
				h.testHashBernsteinPerf(tabsize);
				h.testHashBernsteinCollision(tabsize, tabsize);
				h.testHashBernsteinCollision(tabsize, tabsize*1.1);
				h.testHashBernsteinCollision(tabsize, tabsize*1.2);
				h.testHashBernsteinCollision(tabsize, tabsize*1.3);
				break;
			//fletcher's hash
			case 3:
				h.testHashFletcherPerf(tabsize);
				h.testHashFletcherCollision(tabsize, tabsize);
				h.testHashFletcherCollision(tabsize, tabsize*1.1);
				h.testHashFletcherCollision(tabsize, tabsize*1.2);
				h.testHashFletcherCollision(tabsize, tabsize*1.3);
				break;
			//adler's hash
			case 4:
				h.testHashAdlerPerf(tabsize);
				h.testHashAdlerCollision(tabsize, tabsize);
				h.testHashAdlerCollision(tabsize, tabsize*1.1);
				h.testHashAdlerCollision(tabsize, tabsize*1.2);
				h.testHashAdlerCollision(tabsize, tabsize*1.3);
				break;
			//b jenkin's hash
			case 5:
				h.testHashBobJenkinsPerf(tabsize);
				h.testHashBobJenkinsCollision(tabsize, tabsize);
				h.testHashBobJenkinsCollision(tabsize, tabsize*1.1);
				h.testHashBobJenkinsCollision(tabsize, tabsize*1.2);
				h.testHashBobJenkinsCollision(tabsize, tabsize*1.3);
				break;
			//p hsieh's hash
			case 6:
				h.testHashPaulHsiehPerf(tabsize);
				h.testHashPaulHsiehCollision(tabsize, tabsize);
				h.testHashPaulHsiehCollision(tabsize, tabsize*1.1);
				h.testHashPaulHsiehCollision(tabsize, tabsize*1.2);
				h.testHashPaulHsiehCollision(tabsize, tabsize*1.3);
				break;
			//new table size
			case 7:
				cout << "Enter hash table size (<=" << MAXTABSZ << ")" << endl;
				getline(cin, input);
				if (checkInput(input)!= true){
					break;
				} else {
					tabsize = stoi(input);
				}
				break;
			case 8:
				cout<<"Goodbye!"<<endl;
				flag = false;
				break;
			default:
				cout<<"Incorrect input"<<endl;
				cin.clear();
 +			    cin.ignore(1000,'\n');
		}
	}
	return 0;
}
