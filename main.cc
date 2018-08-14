

#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

 using testing::internal::linked_ptr;

 using namespace testing;
//
class testStruct {
    int field1_;
    float field2_;
};

class MyMock {


    MyMock() = default;

    virtual ~MyMock();

    MOCK_METHOD1(VoidReturning, void(int n));

    MOCK_METHOD2( method1,  void(testStruct, int )); //error

};

MyMock::~MyMock() {

}


class SimpleClass {
    int i;
};

class A {



    //CPP-12736 Parser prediction is broken during parsing of macro call arguments
    MOCK_METHOD1(method1, void(SimpleClass    ));

    MOCK_METHOD1(method2, void(linked_ptr<SimpleClass>*));


  //CPP-9293 __LINE__ can change value while expanding macro
    MOCK_METHOD2(BAR, void(unsigned, unsigned)){};
    MOCK_METHOD3(method3, void(unsigned, unsigned, int)){};

    MOCK_METHOD10(Decimal, int(bool, char, short, int,
                               long, float, double, unsigned, char*, const std::string& str));

};
//CPP-9293 __LINE__ can change value while expanding macro
TEST(AssertTest, FailsFatallyOnFalse) {
    EXPECT_DEATH_IF_SUPPORTED({
                                  testing::internal::Assert(false, __FILE__, __LINE__, "This should fail.");
                              }, "");

    EXPECT_DEATH_IF_SUPPORTED({
                                  testing::internal::Assert(false, __FILE__, __LINE__);
                              }, "");
}

template<typename T>
inline testing::internal::ReferenceWrapper<T> ByRef(T &l_value) {
    return testing::internal::ReferenceWrapper<T>(l_value);
}

//////////



using namespace ::testing;

class DemoTest : public ::testing::StrictMock<Test> {
protected:
    MOCK_METHOD1(foo, void(int));
};

//CPP-11431 False positive inspection error on gmock AllOf matcher
TEST_F(DemoTest, Example) {
    EXPECT_CALL(*this, foo(AllOf(Gt(3), Ne(5)))); // inspection error here
    foo(4);
}


class BipartiteTest : public ::testing::TestWithParam<int> { };
class BipartiteRandomTest
        : public ::testing::TestWithParam<std::pair<int, int> > {
};

//CPP-12564 Incorrect parser error when using Value-Parameterized GTest
TEST_P(BipartiteRandomTest, Exhaustive) {
}


//CPP-12748
ACTION_P(Actionp, a) { return 1; } //no error
ACTION_P3(Actionp3, a, b, c) { return 2; } // //Error after macro substitution

ACTION_P2(Actionp2, a, b) { return 3; } //Error after macro substitution

ACTION(Action) { return 4; } // //Error after macro substitution

ACTION_TEMPLATE(CreateNew,
                HAS_1_TEMPLATE_PARAMS(typename, T),
                AND_0_VALUE_PARAMS()) {
    return new T;
}

int main() {

}


////
//// Created by gabe on 5/18/15.
////
class Foo {
public:
    virtual std::string getName() = 0;

    virtual std::string getName1(std::shared_ptr<Foo> tmp) = 0;
};

class MockClion : public Foo {
    MOCK_METHOD0(getName, std::string());

    MOCK_METHOD1(getName1, std::string(std::shared_ptr<Foo>));
};

class NamingServiceBinderHelperMock {
public:
    MOCK_METHOD0(unbind, void());
  ///  CPP-9293 __LINE__ can change value while expanding macro
    MOCK_METHOD4(rebind, bool(int, const std::string &, const std::string &, const std::string &));
};


////

typedef ::std::vector<::std::string> Strings;
namespace testing {
    namespace internal {
        GTEST_API_ std::string JoinAsTuple(const Strings &fields) {
            switch (fields.size()) {
                case 0:
                    return "";
                case 1:
                    return fields[0];
                default:
                    std::string result = "(" + fields[0];
                    for (size_t i = 1; i < fields.size(); i++) {
                        result += ", ";
                        result += fields[i];
                    }
                    result += ")";
                    return result;
            }
        }
    }
}
namespace testing {
    namespace internal {
        TEST(JoinAsTupleTest, JoinsOneTuple) {

            const char* fields[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
            EXPECT_EQ("(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)",
                      JoinAsTuple(Strings(fields, fields + 10)));
        }

    } // namespace internal
}


class MockFoo  {
public:
    MockFoo() {}

    // Makes sure that a mock function parameter can be named.
    MOCK_METHOD1(VoidReturning, void(int n));  // NOLINT

    MOCK_METHOD0(Nullary, int());  // NOLINT

    // Makes sure that a mock function parameter can be unnamed.
    MOCK_METHOD1(Unary, bool(int));  // NOLINT
    MOCK_METHOD2(Binary, long(short, int));  // NOLINT
    MOCK_METHOD10(mm, int(bool, char, short, int, long, float,  double, unsigned, char*,   std::string& str));
    MOCK_METHOD10(jj, int(bool, char, char, char, char, char,  char, char, char, char));

    MOCK_METHOD1(TakesNonConstReference, bool(int&));  // NOLINT
    MOCK_METHOD1(TakesConstReference, std::string(const int&));

#ifdef GMOCK_ALLOWS_CONST_PARAM_FUNCTIONS
    MOCK_METHOD1(TakesConst, bool(const int));  // NOLINT
#endif

    // Tests that the function return type can contain unprotected comma.
    MOCK_METHOD0(ReturnTypeWithComma, std::map<int, std::string>());
    MOCK_CONST_METHOD1(ReturnTypeWithComma, std::map<int, std::string>(int));  // NOLINT

    MOCK_METHOD0(OverloadedOnArgumentNumber, int());  // NOLINT
    MOCK_METHOD1(OverloadedOnArgumentNumber, int(int));  // NOLINT

    MOCK_METHOD1(OverloadedOnArgumentType, int(int));  // NOLINT
    MOCK_METHOD1(OverloadedOnArgumentType, char(char));  // NOLINT

    MOCK_METHOD0(OverloadedOnConstness, int());  // NOLINT
    MOCK_CONST_METHOD0(OverloadedOnConstness, char());  // NOLINT

    MOCK_METHOD1(TypeWithHole, int(int (*)()));  // NOLINT
    MOCK_METHOD1(TypeWithComma, int(const std::map<int, std::string>&));  // NOLINT

#if GTEST_OS_WINDOWS
    MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, CTNullary, int());
  MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CTUnary, bool(int));
  MOCK_METHOD10_WITH_CALLTYPE(STDMETHODCALLTYPE, CTDecimal,
                              int(bool b, char c, short d, int e, long f,
                                  float g, double h, unsigned i, char* j,
                                  const std::string& k));
  MOCK_CONST_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CTConst, char(int));

  // Tests that the function return type can contain unprotected comma.
  MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, CTReturnTypeWithComma,
                             std::map<int, std::string>());
#endif  // GTEST_OS_WINDOWS

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockFoo);
};


