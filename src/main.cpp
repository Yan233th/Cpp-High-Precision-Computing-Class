#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <chrono>
using TimePoint = chrono::high_resolution_clock::time_point;
using D = chrono::duration<double>;

#ifdef CMAKE
#include "BigInt.hpp"
#else
#include "../includes/BigInt.hpp"
#endif

int main()
{
   
    BigInt A;
    BigInt B;
    // cout <<"输入A的值：" << endl;
    // cin >> A;
    // cout <<"输入B的值：" << endl;
    // cin >> B;
    cin >> A >> B;
    // A = (A - B); // 未完成, 相当于 A = B
    // BigInt C = {'-', vector<int> {114514}};
    // C.output ();
    // cout << "A + B = " << A + B << endl;
    cout << "A - B = " << A-B << endl;

    // cout << (A > B) << endl;
    // cout << (A >= B) << endl;
    // cout << (A < B) << endl;
    // cout << (A <= B) << endl;
    // cout << (A == B) << endl;
    // cout << "A * B = " << A * B << endl;
    // cout << A << ' ' << B << ' ' << C << endl;
    return 0;
}