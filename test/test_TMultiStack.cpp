#include "MultiStack.h"

#include "../gtest/gtest.h"

TEST(TMultiStack, can_create_MultiStack_with_positive_length)
{
	ASSERT_NO_THROW(TMultiStack<int> A(5, 4));
}

TEST(TMultiStack, throws_when_create_MultiStack_with_null)
{
	ASSERT_ANY_THROW(TMultiStack<int> A(0));
}

TEST(TMultiStack, throws_when_create_MultiStack_with_negative_length)
{
	ASSERT_ANY_THROW(TMultiStack<int> A(3,-1));
}

TEST(TMultiStack, check_empty_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_EQ(true, A.IsEmpty(1));
}

TEST(TMultiStack, check_for_non_existent_empty_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_ANY_THROW(A.IsEmpty(5));
}

TEST(TMultiStack, check_negative_empty_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_ANY_THROW(A.IsEmpty(-5));
}

TEST(TMultiStack, check_IsFull_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_EQ(false, A.IsFull(1));
}

TEST(TMultiStack, check_for_non_existent_IsFull_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_ANY_THROW(A.IsFull(5));
}

TEST(TMultiStack, check_negative_IsFull_MultiStack)
{
	TMultiStack<int> A(5, 4);

	ASSERT_ANY_THROW(A.IsFull(-5));
}

TEST(TMultiStack, can_push_with_mem)
{
	TMultiStack<int> A(5, 4);

	ASSERT_NO_THROW(A.Push(10, 1));
}

TEST(TMultiStack, throws_when_push_with_no_mem)
{
	TMultiStack<int> A(5, 4);

	ASSERT_ANY_THROW(A.Push(10, 5));
}

TEST(TMultiStack, can_copy_stack)
{
	TMultiStack<int> A(5, 4);
	A.Push(10, 1);

	ASSERT_NO_THROW(TMultiStack<int> B(A));
}

TEST(TMultiStack, can_assing_stack)
{
	TMultiStack<int> A(5, 4);
	A.Push(10, 1);
	TMultiStack<int> B(5, 4);
	B = A;

	ASSERT_EQ(10, B.Get(1));
}

TEST(TMultiStack, can_get)
{
	TMultiStack<int> A(5, 4);
	A.Push(10, 1);

	ASSERT_NO_THROW(A.Get(1));
}

TEST(TMultiStack, throws_when_get_nonexistent)
{
	TMultiStack<int> A(5, 4);
	A.Push(10, 1);

	ASSERT_ANY_THROW(A.Get(-4));
}

TEST(TMultiStack, throws_when_get_negative)
{
	TMultiStack<int> A(5, 4);
	A.Push(10, 1);

	ASSERT_ANY_THROW(A.Get(5));
}

TEST(TMultiStack, can_get_size)
{
	TMultiStack<int> A(5, 4);

	ASSERT_NO_THROW(A.Length());
}

TEST(TMultiStack, can_Resize)
{
	TMultiStack<int> A(1, 1);
	A.Push(10, 0);

	ASSERT_NO_THROW(A.Resize(5, 0));
}

TEST(TMultiStack, throws_when_Resize_negative)
{
	TMultiStack<int> A(1, 1);
	A.Push(10, 0);

	ASSERT_ANY_THROW(A.Resize(-1, 0));
}

TEST(TMultiStack, can_StackRelocation)
{
	TMultiStack<int> A(9, 3);
	A.Push(11, 0);
	A.Push(12, 1);
	A.Push(12, 1);
	A.Push(12, 1);

	ASSERT_NO_THROW(A.Push(15, 1));
}
