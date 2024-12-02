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

bool computeSafe(std::vector<int> diff){
    bool safe = true;
    bool isneg = diff[1] < 0;
    bool damper_active = true;
    bool p2safe = true;
    
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
    return safe;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t safe_count = 0;
    uint64_t p2safe_count = 0;
    
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

        bool safe = computeSafe(diff);
        if (safe){
            safe_count += 1;
            p2safe_count += 1;
        } else {
            bool p2safe = false;
            for (int i = 0; i < report.size(); ++i){
                auto report2 = report;
                report2.erase(report2.begin() + i);
                vector<int> diffp2;
                std::adjacent_difference(report2.begin(), report2.end(), std::back_inserter(diffp2));
                p2safe = computeSafe(diffp2);
                if (p2safe){
                    break;
                }
            }
            p2safe_count += ((p2safe) ? 1 : 0);
        }

        cout <<((safe) ? "Safe" : "Unsafe") <<endl;
    }
    cout <<safe_count <<" Reports are safe."<<endl;
    cout <<p2safe_count <<" Reports are safe with damper."<<endl;
    return 0;
}
