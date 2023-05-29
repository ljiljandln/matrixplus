#include "s21_matrix_oop.h"

// constructors
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) throw std::out_of_range("Error: out of range");
  rows_ = rows;
  cols_ = cols;
  Allocate();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  Allocate();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

// public methods
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          return false;
        }
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  checkSize(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  checkSize(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) const noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("Error: Wrong matrix size");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result = S21Matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  checkSquare();
  double res = 0;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix temp(rows_ - 1, cols_ - 1);
    for (int i = 0; i < cols_; i++) {
      for (int j = 0; j < temp.rows_; j++) {
        for (int k = 0; k < i; k++) {
          temp.matrix_[j][k] = matrix_[j + 1][k];
        }
        for (int k = i; k < temp.cols_; k++) {
          temp.matrix_[j][k] = matrix_[j + 1][k + 1];
        }
      }
      res += matrix_[0][i] * pow(-1, i) * temp.Determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  checkSquare();
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double det = GetMinor(i, j).Determinant();
      result.matrix_[i][j] = det * pow(-1, i + j);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0 || rows_ != cols_) {
    throw std::out_of_range("Error: determinant = 0");
  }
  S21Matrix res = S21Matrix(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    res = CalcComplements().Transpose();
    res.MulNumber(1 / det);
  }
  return res;
}

// operators
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (!EqMatrix(other)) {
    this->~S21Matrix();
    new (this) S21Matrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (!EqMatrix(other)) {
    this->~S21Matrix();
    new (this) S21Matrix(std::move(other));
  }
  return *this;
}

double& S21Matrix::operator()(int row, int col) const {
  if (cols_ <= col || rows_ <= row || row < 0 || col < 0) {
    throw std::out_of_range("Error: out of range");
  }
  return matrix_[row][col];
}

S21Matrix& S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = *this;
  return result += other;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = *this;
  return result -= other;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix result = other;
  return result *= num;
}

// accessors
int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

// mutators
void S21Matrix::SetCols(const int value) {
  if (value < 0) throw std::out_of_range("Error: invalid size of matrix");
  if (value != cols_) {
    S21Matrix newMatrix(rows_, value);
    int newCols = (value > cols_) ? cols_ : value;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < newCols; j++) {
        newMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = newMatrix;
  }
}

void S21Matrix::SetRows(const int value) {
  if (value < 0) throw std::out_of_range("Error: invalid size of matrix");
  if (value != rows_) {
    S21Matrix newMatrix(value, cols_);
    int newRows = (value > rows_) ? rows_ : value;
    for (int i = 0; i < newRows; i++) {
      for (int j = 0; j < cols_; j++) {
        newMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = newMatrix;
  }
}

// private methods
void S21Matrix::Allocate() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix S21Matrix::GetMinor(int row, int col) const {
  int row_skip = 0;
  S21Matrix minor(cols_ - 1, rows_ - 1);
  for (int i = 0; i < rows_ - 1; i++) {
    int column_skip = 0;
    if (i == row) row_skip = 1;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) column_skip = 1;
      minor.matrix_[i][j] = matrix_[i + row_skip][j + column_skip];
    }
  }
  return minor;
}

void S21Matrix::checkSquare() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: The matrix must be square");
  }
}

void S21Matrix::checkSize(const S21Matrix& other) const {
  if (other.GetCols() != cols_ || other.GetRows() != rows_) {
    throw std::out_of_range("Error: Wrong matrix size");
  }
}
