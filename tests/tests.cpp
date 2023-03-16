#include <gtest/gtest.h>
#include

void f() {
    class Test {
    public:
        Test(int _a, std::string): a(_a) {
            a = _a;
        }


        int getA() {
            return a;
        }

        ~Test() {
        }
    public:
        int *ptr;
        int a;
    };

        // Компайл тайм тестики
        static_assert(std::is_same_v<vector<int>::const_pointer, const int*>);
        static_assert(std::is_same_v<vector<int>::const_iterator::meta_pointer, const int*>);
        static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>);

        //    vector<double> d(5);

        //    d.Fill(4);

        //    vector<double> l(d);

        //    d = l;

        //    vector<double> f(200, 5);

        //    l = vector<double>(10) = f;

        //    std::vector<int> k;

        //    auto c = k.begin();
        //    c = std::move(k.end());

        //    auto n = l.begin();
        //    auto m = l.end();
        //    n = m;

        //    vector<int> i(10, 4);

        //    i.data()[10] = 9;

    //    vector<int> a(10);
    //    a = vector<int>(23);

    //    vector<int> l(20);

    //    a = l;
    //    a = vector<int>(5, 3);
    //    a.fill(10);

    //    std::for_each(a.begin(), a.end(), [](int a) { std::cout << a; });


    //    vector<Test> a(10);

    //    a.emplace_back(3, "hello");
    //    a.emplace_back(10, "lol");

    //    std::for_each(a.begin(), a.end(), [](auto& a) { std::cout << a.a << ' '; });

}
