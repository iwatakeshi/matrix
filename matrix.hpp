#ifndef MATRIX_H
#define MATRIX_H
#include <array.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
  matrix(): matrix(0, 0) {}

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
    
    for(auto row = list.begin(), i = 0; row != list.end(); row++, i++) {
      matrix_[i] = array<T>((*row).size());
      for (auto column = (*row).begin(), j = 0; column != (*row).end(); column++, j++) {
        matrix_[i][j] = *column;
      }
    }
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
  friend ostream& operator << (ostream& os, const matrix<T>& matrix) {
    auto n = matrix.rows();
    for (auto i = 0; i < n; i++) {
      os << matrix[i] << std::endl;
    }
    return os;
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

    if (column < 0 || column >= matrix_[row].length()) {
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

    if (column < 0 || column >= matrix_[row].length()) {
      throw std::out_of_range("Index is out of bounds");
    }

    return matrix_[row][column];
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
  void reserve(int64_t rows, int64_t columns) {
    reserve(rows, columns, false);
  }
  
  /**
   * Allocates space on the heap.
   */
  void reserve(int64_t rows, int64_t columns, bool copy) {
    // Do nothing if the size has not changed
    if (rows == rows_) {
      return;
    }

    // Update the rows and columns
    rows_ = rows;
    columns_ = columns;

    // Resize the rows
    matrix_.reserve(rows, copy);

    // Resize the columns
    for(auto i = 0; i < rows; i++) {
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
  typename array<array<T>>::iterator begin() {
    return matrix_.begin();
  }

  /**
   * Returns an iterator referring to the past-the-end row in the matrix.
   */
  typename array<array<T>>::iterator end() {
    return matrix_.end();
  }

};

#endif