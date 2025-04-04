#include <iostream>
#include <string>
#include <vector>
#include "../c_defination/def.h"
#include <string>
using namespace std;

class buf {
public:
    char buffer[255];
    int size = 0;
    int idx = 0;

    buf() = default;

    explicit buf(int size) : size(size) {
    }

    ~buf() = default;

    void append(char c) {
        if (idx == size) {
            std::cerr << "buffer overflow" << std::endl;
        } else {
            buffer[idx] = c;
            std::cout << buffer[idx++] << std::endl;
        }
    }
    void append(char c, size_t count) {
        if (idx + count > size) {
            std::cerr << "buffer overflow" << std::endl;
        }
        else {
            memset(buffer + idx, c, count);
            for (int i = 0; i < count; i++) {
                std::cout << buffer[idx];
            }
            idx += count;
        }
    }
    template<typename Iter, typename = std::enable_if_t<
        !std::is_integral<Iter>::value> >
    void append(Iter bp, Iter ep) {
        size_t count = std::distance(bp, ep);
        // size_t count = ep - bp;
        if (idx + count > size) {
            std::cerr << "buffer overflow" << std::endl;
        }
        else {
            auto it = bp;
            while (it != ep) {
                buffer[idx++] = *it;
                std::cout << *it;
                it++;
            }
        }
    }
};

int MainThread() {
    buf buf(10);
    int n = 0;
    while (cin >> n) {
        if (n > 0) {
            buf.append('a', n);
        }
        else if (n == -1) {
            buf.append('b');
        }
        else if (n < -1) {
            buf.append(97, abs(n));
        }
        else if (n == 0) {
            string str("12345");
            buf.append(str.begin(), str.end());
            std::iterator_traits<decltype(str.begin())> x;

        }
    }
    string s = "sfs";
    s.data();
    cout << "begin\n" << buf.buffer << endl << "end\n";

}
