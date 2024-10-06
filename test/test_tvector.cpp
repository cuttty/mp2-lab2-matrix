#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(v);
    ASSERT_EQ(v,v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(v);
    ASSERT_NE(v.get_pMem(), v1.get_pMem());
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[-3] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[5] = 4); //ожидаем, что ошибка будет
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v=v); // ожидаем, что ошибки не будет
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_NO_THROW(v=v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    size_t size = v.size();
    v = v1;
    ASSERT_NE(v.size(), size);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_NO_THROW(v=v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_TRUE(v==v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(4);
    ASSERT_TRUE(v==v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_FALSE(v==v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v+6);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v-6);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v*6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_NO_THROW(v+v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_ANY_THROW(v+v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_NO_THROW(v-v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_ANY_THROW(v-v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_NO_THROW(v*v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_ANY_THROW(v*v1);
}

TEST(TDynamicVector, can_get_pMem)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v.get_pMem());
}

TEST(TDynamicVector, cant_create_vector_bigger_MAX_SIZE)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, compare_non_equal_vectors_return_true)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_TRUE(v!=v1);
}

TEST(TDynamicVector, compare_non_equal_vector_to_itself_return_false)
{
    TDynamicVector<int> v(4);
    ASSERT_FALSE(v!=v);
}

TEST(TDynamicVector, assert_ne_equal_vectors_return_false)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(4);
    ASSERT_FALSE(v!=v1);
}

TEST(TDynamicVector, do_move_semantic_correctly)
{
    TDynamicVector<int> v(5);
    int* tmp = v.get_pMem();
    TDynamicVector<int> v1(std::move(v));


    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.get_pMem(), nullptr);

    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.get_pMem(), tmp);
}

TEST(TDynamicVector, do_move_semantic_operator) {
    TDynamicVector<int> v(5);
    int* tmp = v.get_pMem();
    TDynamicVector<int> v1 = std::move(v);

    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.get_pMem(), nullptr);

    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.get_pMem(), tmp);

}
