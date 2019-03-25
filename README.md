# `matrix<T>`

A simple matrix class in C++.

## Usage

To use this library, install [buckaroo](https://github.com/LoopPerfect/buckaroo/wiki/Installation#buckaroo) and [buck](https://github.com/LoopPerfect/buckaroo/wiki/Installation#buck). Once installed, [initialize](https://github.com/LoopPerfect/buckaroo/wiki/Commands#init) buckaroo in your project folder and run the following command:

```bash
# Add the latest version
buckaroo add github.com/iwatakeshi/matrix/
# Install the depenencies
buckaroo install
```

You can also add a [version constraint](https://github.com/LoopPerfect/buckaroo/wiki/Version-Constraints-DSL) if you need to.

## API

| Constructor           | Performance | Description                                                       |
| --------------------- | ----------- | ----------------------------------------------------------------- |
| `matrix()`            | _O(1)_      | Initializes a new empty matrix.                                   |
| `matrix(n, m)`        | _O(n^2)_    | Initializes a new matrix of size `n` by `m`.                      |
| `matrix(n, m, value)` | _O(n^2)_    | Initializes a new matrix of size `n` by `m` with the given value. |
| `matrix(list)`        | _O(n^2)_    | Initializes a new matrix with list initialization.                |

| Method                   | Performance | Description                                                                        |
| -------------------------| ----------- | ---------------------------------------------------------------------------------- |
| `at(row): array<T>`      | _O(1)_      | Returns the column at the given row and column with bound checking.                |
| `at(row, columm): T`     | _O(1)_      | Returns the value at the given row and column with bound checking.                 |
| `at(row, columm, value)` | _O(1)_      | Sets the value at the given row and column with bound checking.                    |
| `begin(): iterator`      | _O(1)_      | Returns an iterator pointing to the first element in the matrix.                   |
| `end(): iterator`        | _O(1)_      | Returns an iterator referring to the past-the-end element in the matrix container. |

| Operator       | Performance | Description                                                    |
| -------------- | ----------- | -------------------------------------------------------------- |
| `a[index]`     | _O(1)_      | Overloads **[]** to select the row from this matrix.           |
| `a + b`        | _O(n^2)_    | Adds two matrixs.                                              |
| `a += b`       | _O(n^2)_    | Adds two matrixs and assigns it to `a`.                        |
| `a - b`        | _O(n^2)_    | Subtracts two matrixs.                                         |
| `a -= b`       | _O(n^2)_    | Subtracts two matrixs and assigns it to `a`.                   |
| `a * b`        | _O(n^3)_    | Multiplies two matrixs.                                        |
| `a *= b`       | _O(n^3)_    | Multiplies two matrixs and assigns it to `a`.                  |
| `ostream << a` | _O(n^2)_    | Outputs the contents of the matrix to the given output stream. |

## Example

```cpp
#include <iostream>
#include <matrix.hpp>
using namespace stdlib;
using std::cout;
using std::endl;

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
  return 0;
}
```
