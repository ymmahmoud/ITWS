#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
	ifstream istr(argv[1]);
	map<int, int> nums;
	int n;
	while( istr >> n ){
		map<int, int>::iterator itr2 = nums.find(n);
		if( itr2 == nums.end() ){
			nums.insert( make_pair(n, 1) );
		} else{
			(itr2->second)++;
		}

	}
	vector<int> modes;
	int max_occurs = 0;
	map<int, int>::const_iterator itr;
	for(itr = nums.begin(); itr != nums.end(); ++itr){
		if( itr->second > max_occurs ){
			max_occurs = itr->second;
			modes.clear();
			modes.push_back(itr->first);
		} else if( itr->second == max_occurs ){
			modes.push_back(itr->first);
		}
	}

	cout << "Modes: ";
	for (int i = 0; i < modes.size(); ++i){
		cout << modes[i] << ", ";
	}
	cout << endl;

	return 0;
}