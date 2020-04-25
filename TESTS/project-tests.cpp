#define BOOST_TEST_MODULE MyModule
#include <boost/test/included/unit_test.hpp>
#include "../SRC/LinkedList.h"
#include "../SRC/BinarySearch.cpp"
#include "../SRC/QuickSort.cpp"

BOOST_AUTO_TEST_SUITE( Total_time )
//UNIT TESTS FOR LINKED LIST
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
    testList.push_back(Test2);
    BOOST_CHECK_EQUAL(testList.getHead().x,Test2.x);
}

BOOST_AUTO_TEST_CASE( Add_4_Items )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    coords Test3 = {35,12};
    testList.push_back(Test3);
    BOOST_CHECK_EQUAL(testList.getHead().x,Test3.x);
}

BOOST_AUTO_TEST_CASE( Add_100_Items )
{
    coords limit = {99,99};
    coords testCoords = {10,40};
    List testList(testCoords);
    for (int i = 0; i<100; i++) {
        testList.push_back({i,i});
    }
    BOOST_CHECK_EQUAL(testList.getHead().x,limit.x);
}

BOOST_AUTO_TEST_CASE( Remove_Item ) {
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    testList.popHead();
    BOOST_CHECK_EQUAL(testList.getHead().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Get_First_Item )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    BOOST_CHECK_EQUAL(testList.getTail().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Check_New_Head )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    testList.popTail();
    BOOST_CHECK_EQUAL(testList.getTail().x,testCoords.x);
}

BOOST_AUTO_TEST_CASE( Check_Size )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    BOOST_CHECK_EQUAL(testList.size(), 2);
}

BOOST_AUTO_TEST_CASE( Search_Test )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    BOOST_CHECK_EQUAL(testList.searchList({20,20}), 1);
}

BOOST_AUTO_TEST_CASE( Search_Test_Missing_Item )
{
    coords testCoords = {10,40};
    List testList(testCoords);
    coords Test2 = {20,20};
    testList.push_back(Test2);
    BOOST_CHECK_EQUAL(testList.searchList({12,13}), 0);
}

//File unit testing using boost filesystem library


//BOOST_AUTO_TEST_CASE( Check_File_Exists ) //Should return true if file is in directory
//{
//    try
//    {

//        QString filePath = QDir::homePath() + "/" + "Test" + ".annotations";
//        filesystem::path testPath(filePath)
//        if (filesystem::exists(testPath) && filesystem::is_regular_file(testPath))
//                return true;
//    }
//    catch(filesystem::filesystem_error & exc){
//            qDebug() << "File system error occured..." << exc;
//    }
//    return false;

//}

//BOOST_AUTO_TEST_CASE( Check_File_Directory_Exists ) //Should return true if directory exists
//{
//    try
//    {
//        namespace filesystem = boost::filesystem;
//        QString filePath = QDir::homePath();
//        filesystem::path testPath(filePath)
//        if (filesystem::exists(testPath) && filesystem::is_directory(testPath))
//                return true;
//    }
//    catch(filesystem::filesystem_error & exc)
//            qDebug() << "File system error occured..." << exc;

//}
//QUICK SORT TEST

BOOST_AUTO_TEST_CASE( Quick_Sort )
{
    std::string j[6] = { "2","3","8","13","15","48" };
    std::string testItems[6] = { "2","3","15","8","48","13" };
    int testItemCount = 6;
    std::string items[testItemCount];
    for (int i = 0; i < testItemCount ; i++) {
        std::string temp = testItems[i];
        items[i] = temp;
    }
    std::string * sortedItems = quickSort(items,testItemCount,0);
    BOOST_CHECK_EQUAL(sortedItems,j);
}
////SEARCH ALGORITHM TESTS
BOOST_AUTO_TEST_CASE( Binary_Search_Found )
{
    std::string testList[] = { "Cat","Cow","Dog","Lion","Zebra"};
    std::string searchValue = "Dog";
    int pos = binarySearch(testList,searchValue);
    BOOST_CHECK_EQUAL(pos,2);

}

BOOST_AUTO_TEST_CASE( Binary_Search_Not_Found)
{
    std::string testList[] = { "16","40","45","108","155" };
    std::string searchValue = "2478";
    int pos = binarySearch(testList,searchValue);
    BOOST_CHECK_EQUAL(pos,-1);
}

BOOST_AUTO_TEST_SUITE_END()

