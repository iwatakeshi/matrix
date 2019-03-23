#include "matrix.hpp"
#include <iostream>
using namespace std;
using namespace stdlib;

int main() {
  matrix<int> m = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
  };

  matrix<int> n = {
    { 2, 4, 6 },
    { 8, 10, 12 },
    { 14, 16, 18 }
  };
  
  cout << m << endl;
  cout << n << endl;
  cout << m + n << endl;
  cout << n - m << endl;

  m += m;
  cout << m << endl;
}