#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t value(0);
    uint64_t line_count = 0;
    std::vector<int32_t> left, right;
    while(getline(in,line)){
        stringstream ins(line);
        int lv, rv;
        ins >>lv >>rv;
        left.push_back(lv);
        right.push_back(rv);
        cout <<"==============\n"<<line <<endl;
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int sum = 0;
    std::vector<uint32_t> distv;
    for (int i = 0; i < left.size(); ++i){
        int dist = abs(left[i] - right[i]);
        distv.push_back(dist);
        sum += dist;
        cout <<left[i] <<"\t" <<right[i]<<"\t" <<dist <<"\t" <<sum<<endl;
    }
    cout <<"Sum of cal values is: " <<sum<<endl;

    uint64_t sim_score_sum = 0;
    for (int i = 0; i < left.size(); ++i){
        int count = std::count(right.begin(), right.end(), left[i]);
        int sim_score = left[i] * count;
        sim_score_sum += sim_score;
    }
    cout <<"Sum of similarity score is: " <<sim_score_sum<<endl;


    return 0;
}
