#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H

#include <cmath>
#include <stdexcept>

#define EPS 1e-7

class S21Matrix {
 public:
  // constructors
  S21Matrix();
  ~S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // methods
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) const noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  double& operator()(int row, int col) const;
  S21Matrix& operator*=(const double other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) noexcept;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  friend S21Matrix operator*(const double num, const S21Matrix& other);

  // accesors
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  // mutators
  void SetRows(int value);
  void SetCols(int value);

 private:
  int rows_, cols_;
  double** matrix_;

  void Allocate();
  S21Matrix GetMinor(int i, int j) const;
  void checkSquare() const;
  void checkSize(const S21Matrix& other) const;
};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H
