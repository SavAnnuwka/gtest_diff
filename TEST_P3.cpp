//
// Created by jetbrains on 23/05/2018.
//

#include <iostream>
#include "gtest/gtest.h"

class FooTest : public ::testing::TestWithParam<const char*> {};

std::string printToStringParamNameCharPtr(const ::testing::TestParamInfo<const char *>info)
{
    return info.param;
}

TEST_P(FooTest, Bar) {

    ASSERT_EQ("Hello111", GetParam());
}

INSTANTIATE_TEST_CASE_P(HardCodedStrings, FooTest, ::testing::Values("Hello", "World") , printToStringParamNameCharPtr );

