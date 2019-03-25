#ifndef MATRIX_H
#define MATRIX_H
#include <array.hpp>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <to_string.hpp>

namespace stdlib {
template <class T>
class matrix {
  private:
  array<array<T>> matrix_;
  int64_t rows_ = 0;
  int64_t columns_ = 0;

  public:
  /**
   * Initializes a new empty matrix.
   */
  matrix() :
      matrix(0, 0) {}

  /**
   * Initializes a new n x m matrix with the given value.
   */
  matrix(int64_t rows, int64_t columns, const T& value = T()) :
      rows_(rows), columns_(columns), matrix_(rows, array<T>(columns, value)) {}

  /**
   * Initializes a new n x m matrix with nested list initialization.
   */
  matrix(std::initializer_list<std::initializer_list<T>> const& list) {
    matrix_.reserve(list.size());
    rows_ = list.size();
    columns_ = (*(list.begin())).size();
    int i = 0;
    for (auto row = list.begin(); row != list.end(); row++) {
      if ((*row).size() != columns_) {
        throw std::logic_error("The columns are not equal");
      }
      matrix_[i] = array<T>((*row).size());

      int j = 0;
      for (auto column = (*row).begin(); column != (*row).end(); column++) {
        matrix_[i][j] = *column;
        j += 1;
      }
      i += 1;
    }
  }

  /**
   * Performs a deep copy of the matrix
   */
  matrix(const matrix<T>& right) {
    reserve(right.rows_, right.columns_);
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < columns_; j++) {
        matrix_[i][j] = right[i][j];
      }
    }
  }

  typedef typename array<array<T>>::iterator iterator;
  typedef typename array<array<T>>::const_iterator const_iterator;

  /**
   * Overloads the assignment operator.
   */
  matrix<T>& operator=(const matrix<T>& right) {
    reserve(right.rows_, right.columns_);
    for (auto i = 0; i < right.rows_; i++) {
      for (auto j = 0; j < right.columns_; j++) {
        matrix_[i][j] = right[i][j];
      }
    }
    return *this;
  }

  /**
   * Overloads [] to select the rows from this matrix.
   */
  array<T>& operator[](int64_t index) {
    return matrix_[index];
  }

  /**
   * Overloads [] to select the rows from this matrix.
   */
  const array<T>& operator[](int64_t index) const {
    return matrix_[index];
  }

  /**
   * Outputs the contents of the matrix to the given output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const matrix<T>& matrix) {
    auto n = matrix.rows();
    auto m = matrix.columns();
    for (auto i = 0; i < n; i++) {
      os << "[ ";
      for (auto j = 0; j < m; j++) {
        os << std::setw(2) << stdlib::to_string(matrix[i][j]);
        if (j != m - 1) {
          os << " ";
        }
      }
      os << " ]" << std::endl;
    }
    return os;
  }

  /**
   * Adds two matrices together
   */
  matrix<T> operator+(const matrix<T>& right) {
    if (this->rows_ != right.rows_) {
      throw std::logic_error("The rows of the matrices are not equal");
    }

    if (this->columns_ != right.columns_) {
      throw std::logic_error("The columns of the matrices are not equal");
    }

    matrix<T> temp(this->rows_, this->columns_);

    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->columns_; j++) {
        temp[i][j] = operator[](i)[j] + right[i][j];
      }
    }

    return temp;
  }

  /**
   * Adds two matrices together
   */
  matrix<T>& operator+=(const matrix<T>& right) {
    if (this->rows_ != right.rows_) {
      throw std::logic_error("The rows of the matrices are not equal");
    }

    if (this->columns_ != right.columns_) {
      throw std::logic_error("The columns of the matrices are not equal");
    }

    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->columns_; j++) {
        operator[](i)[j] = operator[](i)[j] + right[i][j];
      }
    }

    return *this;
  }

  /**
   * Subtracts two matrices together.
   */
  matrix<T> operator-(const matrix<T>& right) {
    if (this->rows_ != right.rows_) {
      throw std::logic_error("The rows of the matrices are not equal");
    }

    if (this->columns_ != right.columns_) {
      throw std::logic_error("The columns of the matrices are not equal");
    }

    matrix<T> temp(this->rows_, this->columns_);

    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->columns_; j++) {
        temp[i][j] = operator[](i)[j] - right[i][j];
      }
    }

    return temp;
  }

  /**
   * Subtracts two matrices together.
   */
  matrix<T>& operator-=(const matrix<T>& right) {
    if (this->rows_ != right.rows_) {
      throw std::logic_error("The rows of the matrices are not equal");
    }

    if (this->columns_ != right.columns_) {
      throw std::logic_error("The columns of the matrices are not equal");
    }

    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < this->columns_; j++) {
        operator[](i)[j] = operator[](i)[j] - right[i][j];
      }
    }

    return *this;
  }

  /**
   * Multiplies two matrices together.
   */
  matrix<T> operator*(const matrix<T>& right) {
    if (columns_ != right.rows_) {
      throw std::runtime_error("The number of columns in the rhs must be equal to the number of rows in the lhs");
    }

    matrix<T> temp(this->rows_, right.columns_);

    for (auto i = 0; i < this->rows_; i++) {
      for (auto j = 0; j < right.columns_; j++) {
        for (auto k = 0; k < this->columns_; k++) {
          temp.matrix_[i][j] += matrix_[i][k] * right.matrix_[k][j];
        }
      }
    }

    return temp;
  }

  /**
   * Multiplies two matrices together and assigns it to the lhs.
   */
  matrix<T>& operator*=(const matrix<T>& right) {
    *this = *this * right;
    return *this;
  }

  /**
   * Returns the column at the given index with bound checking.
   */
  array<T>& at(int64_t row) {
    if (row < 0 || row >= rows_) {
      throw std::out_of_range("Index is out of bounds");
    }

    return matrix_[row];
  }

  /**
   * Returns the column at the given index with bound checking.
   */
  const array<T>& at(int64_t row) const {
    if (row < 0 || row >= rows_) {
      throw std::out_of_range("Index is out of bounds");
    }

    return matrix_[row];
  }

  /**
   * Returns the element at the given indices with bound checking.
   */
  array<T>& at(int64_t row, int64_t column) {
    if (row < 0 || row >= rows_) {
      throw std::out_of_range("Index is out of bounds");
    }

    if (column < 0 || column >= columns_) {
      throw std::out_of_range("Index is out of bounds");
    }

    return matrix_[row][column];
  }

  /**
   * Returns the element at the given indices with bound checking.
   */
  const array<T>& at(int64_t row, int64_t column) const {
    if (row < 0 || row >= rows_) {
      throw std::out_of_range("Index is out of bounds");
    }

    if (column < 0 || column >= columns_) {
      throw std::out_of_range("Index is out of bounds");
    }

    return matrix_[row][column];
  }

  /**
   * Sets the value at the given indices with bound checking.
   */
  void at(int64_t row, int64_t column, const T& value) {
    if (row < 0 || row >= rows_) {
      throw std::out_of_range("Index is out of bounds");
    }

    if (column < 0 || column >= columns_) {
      throw std::out_of_range("Index is out of bounds");
    }

    matrix_[row][column] = value;
  }

  /**
   * Returns the number of rows in this matrix.
   */
  int64_t rows() const {
    return rows_;
  }

  /**
   * Returns the number of columns* in this array.
   */
  int64_t columns() const {
    return columns_;
  }

  /**
   * Allocates space on the heap.
   */
  void reserve(int64_t rows, int64_t columns, bool copy = false) {
    // Do nothing if the size has not changed
    if (rows == this->rows_ && columns == this->columns_) {
      return;
    }

    // Update the rows and columns
    rows_ = rows;
    columns_ = columns;

    // Resize the rows
    matrix_.reserve(rows, copy);

    // Resize the columns
    for (auto i = 0; i < rows; i++) {
      if (copy) {
        matrix_[i].reserve(columns, copy);
      } else {
        matrix_[i] = array<T>(columns);
      }
    }
  }

  /**
   * Returns an iterator pointing to the first row in the matrix.
   */
  iterator begin() {
    return matrix_.begin();
  }

  /**
   * Returns an iterator referring to the past-the-end row in the matrix.
   */
  iterator end() {
    return matrix_.end();
  }

  /**
   * Returns a const_iterator pointing to the first row in the matrix.
   */
  const_iterator begin() const {
    return matrix_.begin();
  }

  /**
   * Returns a const_iterator referring to the past-the-end row in the matrix.
   */
  const_iterator end() const {
    return matrix_.end();
  }
};
}

#endif