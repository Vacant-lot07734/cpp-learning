// //
// // Created by Vacant lot on 2025/4/1.
// //
//
// #ifndef TEST_H
// #define TEST_H
//
// #endif //TEST_H
// #include "blockingqueue.h"
// #include <iostream>
// #include <chrono>
// #include <thread>
// using namespace std;
// // 测试
// void produce(BlockQueue<int> &q){
//     const int num = 9;
//     for(int i = 0; i < num; ++i){
//         //q.offer(i);  // 只打印  0   1
//         q.put(i);
//     }
// }
//
// void consume(BlockQueue<int> &q){
//     while(false == q.empty()){
//         int tmp = q.take();
//         cout << tmp << endl;
//         std::this_thread::sleep_for(chrono::seconds(1));
//     }
// }
//
// void testBlockQueue(){
//     BlockQueue<int> iqueue(2);
//     std::thread t1(produce, std::ref(iqueue));
//     std::thread t2(consume, std::ref(iqueue));
//     std::thread t3(consume, std::ref(iqueue));
//     t1.join();
//     t2.join();
//     t3.join();
// }
