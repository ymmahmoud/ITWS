#include <iostream>
#include <vector>
#include <algorithm>
#include "time.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout << "Please enter the time (hour minute second)" << endl;
    int hour, minute, second;
    cin >> hour >> minute >> second;
    Time now(hour, minute, second);
    
    now.PrintAmPM();
    
    vector<Time> times_manual;
    Time t1 (12,0,0);
    Time t2 (0,0,0);
    Time t3 (9,7,0);
    Time t4 (15,8,59);
    Time t5 (23,59,59);

    times_manual.push_back(t1);
    times_manual.push_back(t2);
    times_manual.push_back(t3);
    times_manual.push_back(t4);
    times_manual.push_back(t5);


    sort (times_manual.begin(), times_manual.end(), IsEarlierThan);
    for (int i = 0; i < times_manual.size(); i++)
    {
        times_manual[i].PrintAmPM();
    }
    
    return 0;
}