#ifdef _CPPUNIT

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#pragma comment(lib, "../cppunit/lib/cppunitd.lib")

class TestUnit : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestUnit);
    CPPUNIT_TEST(TestUnitTest);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp()
    {
        
    }
    void tearDown()
    {

    }
public:

    void TestUnitTest()
    {
        CPPUNIT_ASSERT(1 == 1);
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestUnit);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestUnit, "TestUnit");

#endif 