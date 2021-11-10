#define BOOST_TEST_MODULE ConwaysGOL_Tests
#include <boost/test/included/unit_test.hpp> //single-header
#include "../ConwaysGOL/ConwaysGOL.cpp"
#include <string>

BOOST_AUTO_TEST_CASE(my_boost_test)
{
    std::string expected_value = "Bill";

    std::map<std::pair<int, int>, Cell> board{};

    BOOST_CHECK(expected_value == "");
}