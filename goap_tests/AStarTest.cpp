#include "gtest/gtest.h"

// https://stackoverflow.com/questions/14186245/unit-testing-c-how-to-test-private-members
#define TEST_FRIENDS \
    friend class AStarTest_pop_and_close_for_empty_open_throws_Test; \
    friend class AStarTest_add_to_open_list_preserves_sorting_Test; \
    friend class AStarTest_pop_and_close_for_empty_open_does_nothing_Test; \
    friend class AStarTest_pop_and_close_moves_first_element_from_open_to_closed_Test; \
    friend class AStarTest_pop_and_close_appends_element_to_closed_Test;

#include "AStar.h"

// The fixture for testing class SimVar.
class AStarTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    AStar a;

    // You can remove any or all of the following functions if its body is empty.

    AStarTest() {
        // You can do set-up work for each test here.
    }

    virtual ~AStarTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(AStarTest, add_to_open_list_preserves_sorting) {
    Node n1, n2, n3, n4, n5;
    n1.f_ = 10;
    n2.f_ = 5;
    n3.f_ = 15;
    n4.f_ = 0;
    n5.f_ = 6;

    a.addToOpenList(std::move(n1));
    a.addToOpenList(std::move(n2));
    a.addToOpenList(std::move(n3));
    a.addToOpenList(std::move(n4));
    a.addToOpenList(std::move(n5));

    ASSERT_EQ(0, a.open_[0].f_);
    ASSERT_EQ(5, a.open_[1].f_);
    ASSERT_EQ(6, a.open_[2].f_);
    ASSERT_EQ(10, a.open_[3].f_);
    ASSERT_EQ(15, a.open_[4].f_);
}

TEST_F(AStarTest, pop_and_close_for_empty_open_throws) {
    ASSERT_EQ(0, a.open_.size());
    ASSERT_ANY_THROW(a.popAndClose());
}

TEST_F(AStarTest, pop_and_close_moves_first_element_from_open_to_closed) {
    Node n1, n2, n3, n4, n5;
    n1.f_ = 10;
    n2.f_ = 5;
    n3.f_ = 4;
    n4.f_ = 15;
    n5.f_ = 7;

    a.addToOpenList(std::move(n1));
    a.addToOpenList(std::move(n2));
    a.addToOpenList(std::move(n3));
    a.addToOpenList(std::move(n4));
    a.addToOpenList(std::move(n5));

    ASSERT_EQ(4, a.open_[0].f_);
    ASSERT_EQ(5, a.open_[1].f_);
    ASSERT_EQ(7, a.open_[2].f_);
    ASSERT_EQ(10, a.open_[3].f_);
    ASSERT_EQ(15, a.open_[4].f_);

    ASSERT_EQ(5, a.open_.size());
    ASSERT_EQ(0, a.closed_.size());

    a.popAndClose();
    ASSERT_EQ(4, a.open_.size());
    ASSERT_EQ(1, a.closed_.size());
    ASSERT_EQ(5, a.open_[0].f_);
    ASSERT_EQ(7, a.open_[1].f_);
    ASSERT_EQ(10, a.open_[2].f_);
    ASSERT_EQ(15, a.open_[3].f_);

    a.popAndClose();
    ASSERT_EQ(3, a.open_.size());
    ASSERT_EQ(2, a.closed_.size());
    ASSERT_EQ(7, a.open_[0].f_);
    ASSERT_EQ(10, a.open_[1].f_);
    ASSERT_EQ(15, a.open_[2].f_);

    a.popAndClose();
    ASSERT_EQ(2, a.open_.size());
    ASSERT_EQ(3, a.closed_.size());
    ASSERT_EQ(10, a.open_[0].f_);
    ASSERT_EQ(15, a.open_[1].f_);

    std::cout << "open:\n";
    a.printOpenList();
    std::cout << "closed:\n";
    a.printClosedList();
}

