// Copyright 2018 Bogatova Margarita

#include <gtest/gtest.h>

#include "include/priority_queue.h"

TEST(PriorityQueueTest, can_create_empty_priority_queue) {
    // AAA
    ASSERT_NO_THROW(PriorityQueue<int> p);
}

TEST(PriorityQueueTest, can_create_priority_queue) {
    // AAA
    ASSERT_NO_THROW(PriorityQueue<int> pq(5, 5));
}


TEST(PriorityQueueTest, cant_create_priority_queue_with_negative_priority) {
    // AAA
    ASSERT_ANY_THROW(PriorityQueue<int> pq(5, -5));
}

TEST(PriorityQueueTest, can_copy_priority_queue) {
    // Arrange
    PriorityQueue<int> pq(5, 5);

    // Act & Assert
    ASSERT_NO_THROW(PriorityQueue<int> pq1(pq));
}

TEST(PriorityQueueTest, text_and_its_copy_have_different_memory) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);
    PriorityQueue<int> pq2(pq1);

    // Act
    pq2.push(3, 3);
    pq2.push(1, 0);

    // Assert
    EXPECT_FALSE(pq1 == pq2);
}

TEST(PriorityQueueTest, can_equate_priority_queue_to_itself) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);

    // Act & Assert
    ASSERT_NO_THROW(pq1 = pq1);
}

TEST(PriorityQueueTest, can_equate_priority_queue) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);
    PriorityQueue<int> pq2(2, 2);

    // Act
    pq1.push(4, 4);
    pq2.push(3, 3);

    // Assert
    pq1 = pq2;
    EXPECT_EQ(pq1.extract_max(), 3);
}

TEST(PriorityQueueTest, can_extract_max_from_queue) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);

    // Act
    pq1.push(4, 4);
    pq1.push(6, 6);

    // Assert
    pq1.extract_max();
    EXPECT_EQ(pq1.extract_max(), 6);
}

TEST(PriorityQueueTest, cant_extract_max_from_empty_queue) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act & Assert
    ASSERT_ANY_THROW(pq1.extract_max());
}

TEST(PriorityQueueTest, can_delete_max_from_queue) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);

    // Act
    pq1.push(4, 4);
    pq1.push(6, 6);

    // Assert
    ASSERT_NO_THROW(pq1.delete_max());
    EXPECT_EQ(pq1.extract_max(), 5);
}

TEST(PriorityQueueTest, cant_delete_max_from_empty_queue) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act & Assert
    ASSERT_ANY_THROW(pq1.delete_max());
}

TEST(PriorityQueueTest, can_push_element_in_empty_queue) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act & Assert
    pq1.push(4, 4);
    EXPECT_EQ(pq1.extract_max(), 4);
}

TEST(PriorityQueueTest, cant_push_element_with_negative_priority_in_queue) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);

    // Act & Assert
    ASSERT_ANY_THROW(pq1.push(5, -3));
}

TEST(PriorityQueueTest, can_push_element_in_queue) {
    // Arrange
    PriorityQueue<int> pq1(5, 6);

    // Act & Assert
    pq1.push(4, 4);
    EXPECT_EQ(pq1.extract_max(), 5);
}

TEST(PriorityQueueTest, item_with_highest_priority_has_correct_position) {
    // Arrange
    PriorityQueue<int> pq1(1, 3);

    // Act
    pq1.push(5, 2);
    pq1.push(3, 2);
    pq1.push(4, 4);

    // Assert
    EXPECT_EQ(pq1.extract_max(), 4);
}

TEST(PriorityQueueTest, item_with_highest_priority_is_not_only_one_in_queue) {
    // Arrange
    PriorityQueue<int> pq1(1, 3);
    int maxVal1, maxVal2;
    // Act
    pq1.push(3, 2);
    pq1.push(4, 4);
    pq1.push(2, 4);

    maxVal1 = pq1.extract_max();
    pq1.delete_max();
    maxVal2 = pq1.extract_max();

    // Assert
    EXPECT_TRUE(maxVal1 == 4 && maxVal2 == 2);
}

TEST(PriorityQueueTest, can_push_item_with_lowest_priority) {
    // Arrange
    PriorityQueue<int> pq1(5, 5);

    // Act
    pq1.push(0, 0);

    // Assert
    EXPECT_EQ(pq1.extract_max(), 5);
}

TEST(PriorityQueueTest, item_with_lowest_priority_has_correct_position) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    for (int i = 0; i < 5; i++) {
        pq1.push(i, i);
    }

    for (int i = 0; i < 4; i++) {
        pq1.delete_max();
    }

    // Assert
    EXPECT_EQ(pq1.extract_max(), 0);
}


TEST(PriorityQueueTest, queued_elements_with_the_same_priority) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    for (int i = 0; i < 5; i++) {
        pq1.push(i, 5);
    }

    // Assert
    EXPECT_EQ(pq1.extract_max(), 0);
}

TEST(PriorityQueueTest, function_empty_returns_true_if_queue_is_empty) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    pq1.push(5, 5);
    pq1.delete_max();

    // Assert
    EXPECT_TRUE(pq1.empty());
}

TEST(PriorityQueueTest, function_empty_returns_false_if_queue_is_not_empty) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    pq1.push(5, 5);

    // Assert
    EXPECT_FALSE(pq1.empty());
}

TEST(PriorityQueueTest, when_push_size_is_changed) {
    // Arrange
    PriorityQueue<int> pq1;
    std::size_t tmp;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    tmp = pq1.size();
    pq1.push(9, 3);

    // Assert
    EXPECT_EQ(tmp+1, pq1.size());
}

TEST(PriorityQueueTest, when_delete_size_is_changed) {
    // Arrange
    PriorityQueue<int> pq1;
    std::size_t tmp;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    tmp = pq1.size();
    pq1.delete_max();

    // Assert
    EXPECT_EQ(tmp - 1, pq1.size());
}

TEST(PriorityQueueTest, can_get_max_priority) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq1.push(3, 3);
    pq1.push(2, 6);

    // Assert
    EXPECT_EQ(pq1.get_max_priority(), 6);
}
TEST(PriorityQueueTest, can_set_min_priority) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq1.push(3, 3);
    pq1.push(2, 6);

    // Assert
    EXPECT_EQ(pq1.get_min_priority(), 3);
}

TEST(PriorityQueueTest, same_queue_is_equal_to) {
    // Arrange
    PriorityQueue<int> pq1, pq2;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq2.push(5, 5);
    pq2.push(9, 6);

    // Assert
    EXPECT_TRUE(pq1 == pq2);
}

TEST(PriorityQueueTest, queue_is_equal_to_itself) {
    // Arrange
    PriorityQueue<int> pq1;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq1.push(3, 3);
    pq1.push(2, 6);

    // Assert
    EXPECT_TRUE(pq1 == pq1);
}

TEST(PriorityQueueTest, not_the_same_queues_are_unequal) {
    // Arrange
    PriorityQueue<int> pq1, pq2;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq2.push(4, 3);
    pq2.push(2, 6);

    // Assert
    EXPECT_TRUE(pq1 != pq2 && !(pq1 == pq2));
}

TEST(PriorityQueueTest,
    queues_with_the_same_values_but_with_different_priorities_are_not_equal) {
    // Arrange
    PriorityQueue<int> pq1, pq2;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq2.push(5, 7);
    pq2.push(9, 4);

    // Assert
    EXPECT_TRUE(pq1 != pq2 && !(pq1 == pq2));
}

TEST(PriorityQueueTest,
    queues_with_the_same_priorities_but_with_different_values_are_not_equal) {
    // Arrange
    PriorityQueue<int> pq1, pq2;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq2.push(2, 5);
    pq2.push(4, 6);

    // Assert
    EXPECT_TRUE(pq1 != pq2 && !(pq1 == pq2));
}

TEST(PriorityQueueTest, can_swap_two_queue) {
    // Arrange
    PriorityQueue<int> pq1, pq2;

    // Act
    pq1.push(5, 5);
    pq1.push(9, 6);
    pq2.push(2, 8);
    pq2.push(4, 9);

    pq1.swap(pq2);

    // Assert
    EXPECT_TRUE(pq1.get_max_priority() == 9 && pq2.get_max_priority() == 6);
}
