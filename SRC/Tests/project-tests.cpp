#include <boost/test/included/unit_test.hpp>
#include "LinkedList.h"

BOOST_AUTO_TEST_SUITE( Total_time )

BOOST_AUTO_TEST_CASE( Create_List_Test )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    BOOST_CHECK_EQUAL(testList.getHead().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Add_Item )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.getHead().x,Test2.x);
}

BOOST_AUTO_TEST_CASE( Add_4_Items )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    coords Test3 = {35,12};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.getHead().x,Test3.x);
}

BOOST_AUTO_TEST_CASE( Add_100_Items )
{
    coords limit = {99,99};
    coords testCoords = {10,40};
    List testList(testCoords);
    for (int i = 0; i<100; i++) {
        testList.addNode({i,i});
    }
    BOOST_CHECK_EQUAL(testList.getHead().x,limit.x);
}

BOOST_AUTO_TEST_CASE( Remove_Item ) {
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    testList.popHead();
    BOOST_CHECK_EQUAL(testList.getHead().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Get_First_Item )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.getTail().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Check_New_Head )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    testList.popTail();
    BOOST_CHECK_EQUAL(testList.getTail().x,Test2.x);
}

BOOST_AUTO_TEST_CASE( Check_Size )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.size(), 2);
}

BOOST_AUTO_TEST_CASE( Search_Test )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.searchList({20,20}), 1);
}

BOOST_AUTO_TEST_CASE( Search_Test_Missing_Item )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.addNode(Test2);
    BOOST_CHECK_EQUAL(testList.searchList({12,13}), 0);
}

BOOST_AUTO_TEST_SUITE_END()
