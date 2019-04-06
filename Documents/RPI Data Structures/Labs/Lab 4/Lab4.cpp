#include <iostream>

using namespace std;

int bar(int x, int y){
	int answer = y;
	for (int a = 1; a<x; a++){
		cout << x << "  "<< a<< "  "<<y<<endl;
		answer += bar(x-a,y+x);
	}
	return answer;
}

int main(){
	int val = bar(4,0);
	cout<<val;
}