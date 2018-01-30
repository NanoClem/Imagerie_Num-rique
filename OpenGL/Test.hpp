
class Test {

  private:
    int a,b,c;

  public:
    inline Test(int _a = 2, int _b = 0, int _c = 6)
            :a(_a), b(_b), c(_c)
            {}
    inline ~Test() {}
};
