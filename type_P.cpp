//
// Created by jetbrains on 22/05/2018.
//


// The interface and its implementations are in this header.


#include "gtest/gtest.h"
#include "typed_test.h"

namespace {

    using ::testing::TestWithParam;
    using ::testing::Values;

    typedef PrimeTable* CreatePrimeTableFunc();

    PrimeTable* CreateOnTheFlyPrimeTable() {
        return new OnTheFlyPrimeTable();
    }

    template <size_t max_precalculated>
    PrimeTable* CreatePreCalculatedPrimeTable() {
        return new PreCalculatedPrimeTable(max_precalculated);
    }

    class PrimeTableTestSmpl7 : public TestWithParam<CreatePrimeTableFunc*> {
    public:
        virtual ~PrimeTableTestSmpl7() { delete table_; }
        virtual void SetUp() { table_ = (*GetParam())(); }
        virtual void TearDown() {
            delete table_;
            table_ = NULL;
        }

    protected:
        PrimeTable* table_;
    };

    TEST_P(PrimeTableTestSmpl7, ReturnsFalseForNonPrimes) {
        EXPECT_FALSE(table_->IsPrime(-5));
        EXPECT_FALSE(table_->IsPrime(0));
        EXPECT_FALSE(table_->IsPrime(1));
        EXPECT_FALSE(table_->IsPrime(4));
        EXPECT_FALSE(table_->IsPrime(6));
        EXPECT_FALSE(table_->IsPrime(100));
    }

    TEST_P(PrimeTableTestSmpl7, ReturnsTrueForPrimes) {
        EXPECT_TRUE(table_->IsPrime(2));
        EXPECT_TRUE(table_->IsPrime(3));
        EXPECT_TRUE(table_->IsPrime(5));
        EXPECT_TRUE(table_->IsPrime(71));
        EXPECT_TRUE(table_->IsPrime(11));
        EXPECT_TRUE(table_->IsPrime(131));
    }

    TEST_P(PrimeTableTestSmpl7, CanGetNextPrime) {
        EXPECT_EQ(2, table_->GetNextPrime(10));
        EXPECT_EQ(3, table_->GetNextPrime(12));
        EXPECT_EQ(5, table_->GetNextPrime(13));
        EXPECT_EQ(7, table_->GetNextPrime(15));
        EXPECT_EQ(11, table_->GetNextPrime(17));
        EXPECT_EQ(131, table_->GetNextPrime(1128));
    }


    INSTANTIATE_TEST_CASE_P(OnTheFlyAndPreCalculated, PrimeTableTestSmpl7,
                            Values(&CreateOnTheFlyPrimeTable,
                                   &CreatePreCalculatedPrimeTable<1000>));

}  // namespace



