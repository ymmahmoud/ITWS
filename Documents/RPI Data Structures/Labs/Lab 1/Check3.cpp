#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>
#include <vector>

using std::vector;

// How many numbers to enter

int main()
{
   int numToEnter = 10;
   std::cout << "Enter number of terms to check"<< std::endl;
   std::cin >> numToEnter;
   vector <float> sum;
   float average = 0;
   float input;

   // Get 10 numbers from the user
   for (int i = 0; i != numToEnter; i++)
   {
       std::cout << "Enter a number: ";
       std::cin >> input;

       sum.push_back(input);
   }

   // Get average and print it
   for (int i = 0; i <= sum.size(); i++){
	   average += sum[i];
   }
   average /= sum.size();
   std::cout << "The average is: " << average << std::endl;
   for (int i = 0; i < sum.size(); i++){
	   if (sum[i] < average){
		   std::cout << sum[i] << std::endl;
	   }
   }
   return 0;
}