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
    // cout << "A - B = " ;

    // TimePoint start, end;
    // const int times = 11451419;
    // srand (114514);
    // start = chrono::high_resolution_clock::now ();
    // for (int i = 1; i <= times; i++) A == B;
    // end = chrono::high_resolution_clock::now ();
    // D duration1 = end - start;
    // srand (114514);
    // start = chrono::high_resolution_clock::now ();
    // for (int i = 1; i <= times; i++) A > B;
    // end = chrono::high_resolution_clock::now ();
    // D duration2 = end - start;
    // srand (114514);
    // start = chrono::high_resolution_clock::now ();
    // for (int i = 1; i <= times; i++) A < B;
    // end = chrono::high_resolution_clock::now ();
    // D duration3 = end - start;
    // cout << "1 Costs " << duration1.count () << "s" << endl;
    // cout << "2 Costs " << duration2.count () << "s" << endl;
    // cout << "3 Costs " << duration3.count () << "s" << endl;

    // cout << (A > B) << endl;
    // cout << (A >= B) << endl;
    // cout << (A < B) << endl;
    // cout << (A <= B) << endl;
    // cout << (A == B) << endl;
    // cout << "A * B = " << A * B << endl;
    // cout << A << ' ' << B << ' ' << C << endl;
    return 0;
}