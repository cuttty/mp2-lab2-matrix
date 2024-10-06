#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(m);
    ASSERT_EQ(m,m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(m);
    ASSERT_NE(m.get_pMem(), m1.get_pMem());
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m.get_size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m[1][3] = 6);
    ASSERT_NO_THROW(m[1][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[-1][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[10][3] = 7);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m=m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(5);
    ASSERT_NO_THROW(m=m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    size_t tmp = m.get_size();
    m=m1;
    ASSERT_NE(tmp, m.get_size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    ASSERT_NO_THROW(m=m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(5);
    ASSERT_TRUE(m==m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(5);
    ASSERT_TRUE(m==m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    ASSERT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(5);
    ASSERT_NO_THROW(m+m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    ASSERT_ANY_THROW(m+m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(5);
    ASSERT_NO_THROW(m-m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    ASSERT_ANY_THROW(m-m1);
}

TEST(TDynamicMatrix, can_multiply_const_to_matrix) {
    TDynamicMatrix<int> m(4);
    ASSERT_NO_THROW(m*6);
}

TEST(TDynamicMatrix, can_multiply_vector_to_matrix) {
    TDynamicMatrix<int> m(4);
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(m*v);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_matrix_equal_size) {
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(4);
    ASSERT_NO_THROW(m*m1);
}

TEST(TDynamicMatrix, cant_multiply_matrix_to_matrix_different_size) {
    TDynamicMatrix<int> m(4);
    TDynamicMatrix<int> m1(5);
    ASSERT_ANY_THROW(m*m1);
}
