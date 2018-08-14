#include "gtest/gtest.h"
#include "gmock/gmock.h"




//////////////
/////////////
//TEST
TEST(test_case_name, test_nameGOOD)
{
    ASSERT_EQ(1, 1);
}

TEST(test_case_name, test_nameFail)
{
    ASSERT_EQ(1, 0) << "1 is not equal 0";
}


//////////////
/////////////
///TEST_F
class Foo
{
public:
    Foo()
            : i(0)
    {
        std::cout << "CONSTRUCTED" << std::endl;
    }
    ~Foo()
    {
        std::cout << "DESTRUCTED" << std::endl;
    }
    int i;
};

class TestFoo : public ::testing::Test
{
protected:
    void SetUp()
    {
        foo = new Foo;
        foo->i = 5;
    }
    void TearDown()
    {
        delete foo;
    }
    Foo *foo;
};

TEST_F(TestFoo, test1_good)
{
    ASSERT_EQ(foo->i, 5);
    foo->i = 10;
}

TEST_F(TestFoo, test2_fail)
{
    ASSERT_EQ(foo->i, 51);
}




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
