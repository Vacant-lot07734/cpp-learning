#include <iostream>
#include <ostream>
#include <stdio.h>
using namespace std;
using int32 = uint32_t;

int32 GetGlobalDepthMask() {
    int32 global_depth_ = 255;
    return (1 << global_depth_) - 1;
}

int32 GetSplitImageIndex(int32 bucket_idx) {
    // 分裂后的两个，从一个可以获取另一个
    int32 global_depth_ = 255;
    int32 tmp = bucket_idx + (1 << (global_depth_ - 1));
    auto mask = GetGlobalDepthMask();
    return tmp & mask;
}
int main() {
    string s = "Hello World!";
    cout << s.substr(5) << endl;
}


