#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(create_matrix_with_size, True) {
  S21Matrix m(3, 3);
  ASSERT_TRUE(3 == m.GetRows());
  ASSERT_TRUE(3 == m.GetCols());
}

TEST(getCols, True) {
  S21Matrix TestMatrix1(4, 4);
  EXPECT_EQ(TestMatrix1.GetCols(), 4);
}

TEST(getRows, True) {
  S21Matrix TestMatrix1(4, 4);
  EXPECT_EQ(TestMatrix1.GetRows(), 4);
}

TEST(setCols, True) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1(1, 1) = 4;
  TestMatrix1.SetCols(4);
  EXPECT_EQ(TestMatrix1.GetCols(), 4);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
  TestMatrix1.SetCols(2);
  EXPECT_EQ(TestMatrix1.GetCols(), 2);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
}

TEST(setRows, True) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1(1, 1) = 4;
  TestMatrix1.SetRows(4);
  EXPECT_EQ(TestMatrix1.GetRows(), 4);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
  TestMatrix1.SetRows(2);
  EXPECT_EQ(TestMatrix1.GetRows(), 2);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
}

TEST(set_cols_incorrect, False) {
  S21Matrix TestMatrix1(3, 3);
  EXPECT_THROW(TestMatrix1.SetRows(-4), std::out_of_range);
}

TEST(set_rows_incorrect, False) {
  S21Matrix TestMatrix1(3, 3);
  EXPECT_THROW(TestMatrix1.SetCols(-4), std::out_of_range);
}

TEST(incorrectInit0, False) {
  EXPECT_THROW(S21Matrix TestMatrix(3, -1), std::out_of_range);
}

TEST(incorrectInit1, False) {
  EXPECT_THROW(S21Matrix TestMatrix(-3, 1), std::out_of_range);
}

TEST(incorrectInit2, False) {
  EXPECT_THROW(S21Matrix TestMatrix(-1, 1), std::out_of_range);
}

TEST(create_matrix_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix m(rows, cols);
  ASSERT_TRUE(rows == m.GetRows());
  ASSERT_TRUE(cols == m.GetCols());
}

TEST(create_matrix_copy, True) {
  S21Matrix m(4, 3);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      m(i, j) = i + j;
    }
  }
  S21Matrix m2(m);
  ASSERT_TRUE(m == m2);
}

TEST(create_matrix_move, True) {
  S21Matrix m(4, 3);
  S21Matrix m2 = std::move(m);
  ASSERT_TRUE(4 == m2.GetRows());
  ASSERT_TRUE(3 == m2.GetCols());
}

TEST(create_matrix, True) { S21Matrix m; }

TEST(eq_not_equal_size, False) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 2);
  ASSERT_FALSE(a == b);
}

TEST(eq_not_equal_size2, False) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 2);
  ASSERT_FALSE(a == b);
}

TEST(eq_not_equal_value, False) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = i + 1;
      b(i, j) = i;
    }
  }
  ASSERT_FALSE(a == b);
}

TEST(eq_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = rand();
      a(i, j) = rand_val;
      b(i, j) = rand_val;
    }
  }
  ASSERT_TRUE(a == b);
}

TEST(sum_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  EXPECT_THROW(a.SumMatrix(b), std::out_of_range);
}

TEST(sum_wrong_size2, True) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_THROW(a.SumMatrix(b), std::out_of_range);
}

TEST(sum_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  S21Matrix sum(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a(i, j) = rand() % 100 + 1;
      b(i, j) = rand() % 100 + 1;
      sum(i, j) = a(i, j) + b(i, j);
    }
  }
  a.SumMatrix(b);
  ASSERT_TRUE(a == sum);
}

TEST(sub_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  S21Matrix sub(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a(i, j) = rand() % 100 + 1;
      b(i, j) = rand() % 100 + 1;
      sub(i, j) = a(i, j) - b(i, j);
    }
  }
  a.SubMatrix(b);
  ASSERT_TRUE(a == sub);
}

TEST(sub_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  EXPECT_THROW(a.SubMatrix(b), std::out_of_range);
}

TEST(mult_number_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix check(rows, cols);
  double mult_number = 2;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a(i, j) = rand() % 100 + 1;
      check(i, j) = a(i, j) * mult_number;
    }
  }
  a.MulNumber(mult_number);
  ASSERT_TRUE(a == check);
}

TEST(mult_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(cols, rows);
  S21Matrix check(rows, rows);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) a(i, j) = rand() % 100 + 1;
  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) b(i, j) = rand() % 100 + 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      check(i, j) = 0;
      for (int k = 0; k < a.GetCols(); k++)
        check(i, j) = check(i, j) + a(i, k) * b(k, j);
    }
  }
  a.MulMatrix(b);
  ASSERT_TRUE(a == check);
}

TEST(mult, True) {
  const int rows = 2;
  const int cols = 3;
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  S21Matrix check(2, 2);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) a(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) b(i, j) = c++;

  check(0, 0) = 58;
  check(0, 1) = 64;
  check(1, 0) = 139;
  check(1, 1) = 154;

  a.MulMatrix(b);
  ASSERT_TRUE(a == check);
}

TEST(mult_matrix_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  EXPECT_THROW(a.MulMatrix(b), std::out_of_range);
}

TEST(transpose_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix m(rows, cols);
  S21Matrix check(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = rand() % 100 + 1;
      m(i, j) = rand_val;
      check(j, i) = rand_val;
    }
  }
  S21Matrix res = m.Transpose();
  ASSERT_TRUE(res == check);
}

TEST(complements_1, True) {
  S21Matrix m(3, 3);
  S21Matrix r(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;

  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 2;

  m(2, 0) = 5;
  m(2, 1) = 2;
  m(2, 2) = 1;

  r(0, 0) = 0;
  r(0, 1) = 10;
  r(0, 2) = -20;

  r(1, 0) = 4;
  r(1, 1) = -14;
  r(1, 2) = 8;

  r(2, 0) = -8;
  r(2, 1) = -2;
  r(2, 2) = 4;

  S21Matrix res(m.CalcComplements());
  ASSERT_TRUE(res == r);
}

TEST(complements_wrong_size, True) {
  S21Matrix a(3, 2);
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
}

TEST(Inverse, False) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::invalid_argument);
}
TEST(Inverse, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));

  S21Matrix matrix_c(1, 1);
  S21Matrix matrix_c_res(1, 1);
  matrix_c_res(0, 0) = 1;
  matrix_c(0, 0) = 1;
  ASSERT_TRUE(matrix_c.InverseMatrix().EqMatrix(matrix_c_res));

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  EXPECT_THROW(matrix_b.InverseMatrix(), std::out_of_range);
}

TEST(op_plus, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 1;
      b(i, j) = 1;
      c(i, j) = 2;
    }
  }
  S21Matrix m(a + b);
  ASSERT_TRUE(c == m);
}

TEST(op_minus, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 1;
      b(i, j) = 1;
    }
  }
  S21Matrix m(a - b);
  ASSERT_TRUE(c == m);
}

TEST(op_mult_matrix, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      b(i, j) = 1;
      c(i, j) = 4;
    }
  }
  S21Matrix m(a * b);
  ASSERT_TRUE(c == m);
}

TEST(op_mult_number, True) {
  S21Matrix a(2, 2);
  S21Matrix c(2, 2);
  int n = 2;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      c(i, j) = 4;
    }
  }
  S21Matrix m(a * n);
  ASSERT_TRUE(c == m);
}

TEST(op_is_equal, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      b(i, j) = 2;
    }
  }
  ASSERT_TRUE(a == b);
}

TEST(op_is_equal_2, False) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      b(i, j) = 3;
    }
  }
  ASSERT_FALSE(a == b);
}

TEST(op_is_equal_3, False) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  ASSERT_FALSE(a == b);
}

TEST(op_equals, True) {
  S21Matrix a(2, 2);
  S21Matrix c(3, 3);
  a = c;
  ASSERT_TRUE(a == c);
}

TEST(op_plus_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 1;
      b(i, j) = 1;
      c(i, j) = 2;
    }
  }
  a += b;
  ASSERT_TRUE(a == c);
}

TEST(op_minus_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 1;
      b(i, j) = 1;
      c(i, j) = 0;
    }
  }
  a -= b;
  ASSERT_TRUE(a == c);
}

TEST(op_mult_matrix_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      b(i, j) = 1;
      c(i, j) = 4;
    }
  }
  a *= b;
  ASSERT_TRUE(a == c);
}

TEST(op_mult_number_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix c(2, 2);
  int n = 2;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 2;
      c(i, j) = 4;
    }
  }
  a *= n;
  ASSERT_TRUE(a == c);
}

TEST(MatrixTests, MulNumMatrix1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = -78.14;
  TestMatrix1(0, 1) = 0;
  TestMatrix1(1, 0) = -0.3;
  TestMatrix1(1, 1) = 2;
  ResultMatrix(0, 0) = -781.4;
  ResultMatrix(0, 1) = 0;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = 20;
  EXPECT_TRUE((10. * TestMatrix1) == ResultMatrix);
}

TEST(op_braces, True) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  double n = a(0, 0);
  ASSERT_TRUE(1 == n);
  n = a(0, 1);
  ASSERT_TRUE(n == 2);
}

TEST(braces_out_of_range, True) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m(5, 5), std::out_of_range);
}