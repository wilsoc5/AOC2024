#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <numeric>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v){
  for (auto&& vi : v){
      os <<vi <<" ";
  }
  return os;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t safe_count = 0;
    
    while(getline(in,line)){
        if (line.empty()){
            continue;
        }
        stringstream ss(line);
        vector<int> report;
        int val;
        while(ss) {
            ss >>val;
            if (ss)
                report.push_back(val);
        }
        vector<int> diff;
        std::adjacent_difference(report.begin(), report.end(), std::back_inserter(diff));
        cout <<"========\n" <<line <<endl;
        cout <<"========\n" <<report<<endl;
        cout <<"========\n" <<diff <<endl;

        bool safe = true;
        bool isneg = diff[1] < 0;
        for(int i = 1; i < diff.size(); ++i){
           if (diff[i] < 0 != isneg){
                safe = false;
                break;
            }
            if (abs(diff[i]) == 0){
                safe = false;
                break;
            }
            if (abs(diff[i]) > 3){
                safe = false;
                break;
            }
        }
        if (safe){
            safe_count += 1;
        }
        cout <<((safe) ? "Safe" : "Unsafe") <<endl;
    }
    cout <<safe_count <<" Reports are safe."<<endl;
    return 0;
}
