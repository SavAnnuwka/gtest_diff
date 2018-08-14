//
// Created by jetbrains on 22/05/2018.
//

#include "typed_test.h"


#include "gtest/gtest.h"
#include "prime_table.h"

#if GTEST_HAS_TYPED_TEST

    using testing::Types;


    typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> Implementations;

    TYPED_TEST_CASE(PrimeTableTest, Implementations);

    TYPED_TEST(PrimeTableTest, ReturnsFalseForNonPrimes) {

        EXPECT_FALSE(this->table_->IsPrime(-5));
        EXPECT_FALSE(this->table_->IsPrime(0));
        EXPECT_FALSE(this->table_->IsPrime(1));
        EXPECT_FALSE(this->table_->IsPrime(4));
        EXPECT_FALSE(this->table_->IsPrime(6));
        EXPECT_FALSE(this->table_->IsPrime(100));
    }

    TYPED_TEST(PrimeTableTest, ReturnsTrueForPrimes) {
        EXPECT_TRUE(this->table_->IsPrime(2));
        EXPECT_TRUE(this->table_->IsPrime(3));
        EXPECT_TRUE(this->table_->IsPrime(5));
        EXPECT_TRUE(this->table_->IsPrime(7));
        EXPECT_TRUE(this->table_->IsPrime(11));
        EXPECT_TRUE(this->table_->IsPrime(131));
    }

    TYPED_TEST(PrimeTableTest, CanGetNextPrime) {
        EXPECT_EQ(2, this->table_->GetNextPrime(10));
        EXPECT_EQ(3, this->table_->GetNextPrime(2));
        EXPECT_EQ(5, this->table_->GetNextPrime(3));
        EXPECT_EQ(7, this->table_->GetNextPrime(5));
        EXPECT_EQ(11, this->table_->GetNextPrime(7));
        EXPECT_EQ(131, this->table_->GetNextPrime(128));
    }


#endif  // GTEST_HAS_TYPED_TEST

#if GTEST_HAS_TYPED_TEST_P

    using testing::Types;


    template <class T>
    class PrimeTableTest2 : public PrimeTableTest<T> {
    };

    TYPED_TEST_CASE_P(PrimeTableTest2);
    TYPED_TEST_P(PrimeTableTest2, ReturnsFalseForNonPrimes) {
        EXPECT_FALSE(this->table_->IsPrime(-15));
        EXPECT_FALSE(this->table_->IsPrime(10));
        EXPECT_FALSE(this->table_->IsPrime(11));
        EXPECT_FALSE(this->table_->IsPrime(14));
        EXPECT_FALSE(this->table_->IsPrime(16));
        EXPECT_FALSE(this->table_->IsPrime(1100));
    }

    TYPED_TEST_P(PrimeTableTest2, ReturnsTrueForPrimes) {
        EXPECT_TRUE(this->table_->IsPrime(2));
        EXPECT_TRUE(this->table_->IsPrime(3));
        EXPECT_TRUE(this->table_->IsPrime(5));
        EXPECT_TRUE(this->table_->IsPrime(7));
        EXPECT_TRUE(this->table_->IsPrime(11));
        EXPECT_TRUE(this->table_->IsPrime(131));
    }

    TYPED_TEST_P(PrimeTableTest2, CanGetNextPrime) {
        EXPECT_EQ(2, this->table_->GetNextPrime(0));
        EXPECT_EQ(3, this->table_->GetNextPrime(2));
        EXPECT_EQ(5, this->table_->GetNextPrime(3));
        EXPECT_EQ(7, this->table_->GetNextPrime(5));
        EXPECT_EQ(11, this->table_->GetNextPrime(7));
        EXPECT_EQ(131, this->table_->GetNextPrime(128));
    }
    REGISTER_TYPED_TEST_CASE_P(
            PrimeTableTest2,
            ReturnsFalseForNonPrimes, ReturnsTrueForPrimes, CanGetNextPrime);

    typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable>
            PrimeTableImplementations;
    INSTANTIATE_TYPED_TEST_CASE_P(OnTheFlyAndPreCalculated,    // Instance name
                                  PrimeTableTest2,             // Test case name
                                  PrimeTableImplementations);  // Type list

#endif  // GTEST_HAS_TYPED_TEST_P
