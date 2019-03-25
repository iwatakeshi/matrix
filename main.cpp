#include "matrix.hpp"
#include <iostream>
using namespace std;
using namespace stdlib;

int main() {
  matrix<int> m = {
    { 1, 2 },
    { 4, 5 },
    { 7, 8 }
  };

  matrix<int> n = {
    { 2, 4, 6 },
    { 8, 10, 12 },
  };
  
  // cout << m * n << endl;

  m *= n;

  cout << m << endl;

  return 0;
}