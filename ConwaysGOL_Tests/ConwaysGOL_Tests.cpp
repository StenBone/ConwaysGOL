#define BOOST_TEST_MODULE ConwaysGOL_Tests
#include <boost/test/included/unit_test.hpp> //single-header
#include "../ConwaysGOL/ConwaysGOL.cpp"
#include <string>
#include "../ConwaysGOL/Board.h"

BOOST_AUTO_TEST_CASE(glider_test)
{
    /**
    * desired source
    Creates a new board with cell layout below
    Board test_board{
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };
    test_board = board.next_generation();

    expected_board{
        {0, 0, 0, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 1},
        {0, 0, 1, 0}
    };

    BOOST_CHECK(test_board == expected_value);
    */

    Board test_board{
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };




    std::string expected_value = "Bill";

    std::map<std::pair<int, int>, Cell> board{};

    BOOST_CHECK(expected_value == "");
}