namespace {

    template<class T>
    PrimeTable *CreatePrimeTable();

    template<>
    PrimeTable *CreatePrimeTable<OnTheFlyPrimeTable>() {
        return new OnTheFlyPrimeTable;
    }

    template<>
    PrimeTable *CreatePrimeTable<PreCalculatedPrimeTable>() {
        return new PreCalculatedPrimeTable(10000);
    }


    template<class T>
    class PrimeTableTest : public testing::Test {
    protected:

        PrimeTableTest() : table_(CreatePrimeTable<T>()) {}

        virtual ~PrimeTableTest() { delete table_; }


        PrimeTable *const table_;
    };
}