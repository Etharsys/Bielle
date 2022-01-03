#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>
#include <math.h>
#include <set>


using namespace std;

/*
int solution(vector<int> &D, int X) {
    // write your code in C++14 (g++ 6.2.0)
    // D could be void, so we take 0 days
    if (D.size() == 0) {
        return 0;
    }

    u_int nb_days = 1;
    int small_mis = D.at(0);
    int max_mis   = D.at(0);
    int cur_mis   = D.at(0);
    for (u_int i = 1; i <= D.size(); ++i) {
        if (i != D.size()) {
            cur_mis = D.at(i);
        }
        cout << "mM:" << small_mis << "," << max_mis << endl;
        
        small_mis = small_mis < cur_mis ? small_mis : cur_mis; // reaffect smallest mission
        max_mis   =   max_mis > cur_mis ?   max_mis : cur_mis; // reaffect maximum mission

        cout << small_mis << "," << max_mis << " - "<< max_mis - small_mis << endl;

        if (max_mis - small_mis > X) {
            cout << "+1" << endl;
            small_mis = cur_mis; // reset smallest mission
            max_mis   = cur_mis;       // reset maximum mission 
            nb_days++;
        }
    }

    return nb_days;
}*/

int solution(vector<int> &D, vector<int> &C, int P) {
    // write your code in C++14 (g++ 6.2.0)
    u_int ans = 0;

    while (D.size() != 0) {
        auto min = D.at(0);
        auto minc = C.at(0);
        int j;
        for (u_int i = 0; i < D.size(); ++i) {
            if (D.at(i) < min || (D.at(i) == min && C.at(i) < minc)) {
                min = D.at(i);
                minc = D.at(i);
                j = i;
            }
        }
        //int i = distance(D.begin(), min_element(D.begin(), D.end()));
        //cout << i << endl;
        //auto val = C.at(i);
        //cout << val << endl;

        if (P - minc < 0) {
            break;
        }
        D.at(j) = 1000000;
        P = P - minc;
        ans++;
    }

    return ans;
}

int main() 
{
    vector<int> v { 5, 5, 5, 5 };
    vector<int> v2 { 8, 3, 3, 4 };
    cout << solution(v, v2, 6) << endl;
    return 0;
}








/*

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution1(std::vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    std::vector<int> positif = A;
    std::sort(positif.begin(), positif.end());
    int cpt = 1;

    for (auto e : positif) {
        std::cout << cpt << "," << e << std::endl;
        if (cpt > e) {
            continue;
        }
        if (cpt == e) {
            cpt ++;
            continue;
        }
        break;
    }
    return cpt;
}

int solution2(string &direction, int radius, vector<int> &X, vector<int> &Y) {
    // write your code in C++14 (g++ 6.2.0)
    std::vector<int> ans (X.size(),1); // nb enemies with value 1

    // delete too far enemies
    for (u_int e = 1; e <= ans.size(); e++){
        int sqr_dist = X.at(e) * X.at(e) + Y.at(e) * Y.at(e);
        if (sqr_dist > radius * radius) {
            ans.at(e) == 0;
        }
    }

    // delete angle enemies
    for (u_int e = 1; e <= ans.size(); e++) {
        if (direction == "U") {
            vector<int> vec1 { 0, 1 };
            vector<int> vec2 { X.at(e), Y.at(e) };
            // calculation of the angle between the 2 previous vectors :
            // (arccos(innerproduct(vec1,vec2)) + convertion to degree)
            double inner = acos(inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0)) * 180/M_PI;
            if (!(inner > -45 && inner < 45)) {
                ans.at(e) == 0;
            }
        }
    }

    // remove unvalid enemies (0)
    remove_if(ans.begin(), ans.end(), [](int x){ return x == 1;});
    return ans.size();
}


void t(const vector<int>& v){
    return;
}

int main() {
    //vector<int> vec1 { 0, 1 };
    //vector<int> vec2 { -1, 0 };
    //double inner = acos(inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0)) * 180/M_PI;
    //cout << inner << endl;
    //std::vector<int> test { 1, -2, 3, 5, 1, 3 };
    //std::cout << solution(test) << std::endl;
    int a = 2;
    cout << &a << endl;
    return 0;
}*/