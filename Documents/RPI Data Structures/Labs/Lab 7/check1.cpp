#include <iostream>
#include<bits/stdc++.h>
using namespace std;

// Recursive function to count number of paths
int countPaths(int n, int m)
{
    // If we reach bottom or top left, we
    // have only one way to reach (0, 0)
    if (n==0 || m==0)
        return 1;
    
    // Else count sum of both ways
    return (countPaths(n-1, m) + countPaths(n, m-1));
}

// Driver Code
int main()
{
    int n = 1, m = 0;
    cout << "Number of Paths " << countPaths(n, m) << endl;
    return 0;
}
