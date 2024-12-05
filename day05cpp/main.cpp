#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <optional>

using namespace std;

typedef std::pair<uint16_t, uint16_t> mapping_t;

ostream& operator<<(ostream& os, const mapping_t& m){
    os <<"{ (" <<m.first<<", " <<m.second <<") " <<"}";
    return os;
}

typedef vector<mapping_t> map_t;

typedef vector<uint16_t> update_t;
typedef vector<update_t> set_t;


typedef std::set<uint16_t> set16_t;

typedef std::map<uint16_t, set16_t > rules_t;

template<typename T>
ostream& operator<<(ostream& os, const set<T>& v){
    bool first = true;
    os <<"{ ";
    for (const auto& vi : v){
        if (!first) os <<", ";
        os <<vi ; 
        first = false;
    }
    os <<" } ";
    return os;
}
ostream& operator<<(ostream& os, const rules_t& m){
    bool first = true;
    os <<"{ ";
    for (const auto& vi : m){
        if (!first) os <<", ";
        os <<" { " <<vi.first <<": " <<vi.second <<" }"; 
        first = false;
    }
    os <<"}";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v){
    bool first = true;
    os <<"{ ";
    for (const auto& vi : v){
        if (!first) os <<", ";
        os <<vi ; 
        first = false;
    }
    os <<" } ";
    return os;
}

std::optional<mapping_t> parse_mapping(istream& in){
    mapping_t m;
    char pipe;
    in >> m.first >> pipe >> m.second;
    cout <<"\t\t\t\tMapping_t: " <<m;
    if (!in){
        return {};
    }
    return m;
}

rules_t parse_rules(istream& in){
    rules_t m;
    string line;
    getline(in,line);
    while (!line.empty()){
        stringstream ss(line);
        auto ming = parse_mapping(ss);
        if (ming){
            m[ming->first].insert(ming->second);
            cout <<"\n\t\tMing: " <<*ming <<endl;
        }
        getline(in,line);
    }
    return m;
}

set_t parse_seeds(istream& in){
    string line;
    string val;
    set_t set;
    getline(in,line);
    while(!line.empty()){
        update_t seeds;
        cout <<"Parse Seeds: ";
        cout <<line<<endl;
        stringstream ss(line);
        while (ss){
            getline(ss, val, ',');
            if (ss){
                seeds.push_back(stoull(val));
            }
        }
        set.push_back(seeds);
        getline(in,line);
    }
    return set;
}

std::pair<rules_t, set_t> parse_file(istream& in){
    auto m = parse_rules(in);
    auto set = parse_seeds(in);
    return std::make_pair(std::move(m),std::move(set));
}

uint64_t check_rules(std::pair<rules_t, set_t>& msp){
    const rules_t& m = msp.first;
    const set_t& s = msp.second;
    uint64_t res = 0;

    for (uint32_t i = 0; i < s.size(); ++i){
        bool valid = true;
        cout <<"Set " <<i << " : " << s[i] << endl;
        const auto& si = s[i];
        for (uint32_t j = 1; j < si.size() && valid; ++j){
            auto val = si[j];
            cout <<"\tVal: " <<val ;
            if (m.contains(val)){
                auto r = m.at(val);
                cout <<"\t" <<r ;
                for (auto&& k : r){
                    cout <<"\t" <<k;
                    auto resit = std::find(si.begin(), si.end(), k);
                    if (resit == si.end())
                        continue;
                    auto idx = resit - si.begin();
                    if (idx < j) {
                        valid = false;
                        cout <<"\t Invalid: " <<k <<" @ "<<idx <<" > " <<j;
                        break;
                    }
                }
            }
            cout <<endl;
        }
        if (valid){
            //grab the middle page number:
            auto mid = si[si.size() / 2];
            cout <<" Middle value: " <<mid <<endl;
            res += mid;
        }
    }
    cout <<"Res: " <<res <<endl;
    return res;
}

int main(int argc, char* argv[]){
    using std::begin, std::end;
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t sum = 0;
    uint64_t power_sum = 0;

    auto a = parse_file(in);
    cout <<"a " <<a.first <<endl;
    cout <<"b " <<a.second <<endl;

    auto res = check_rules(a);

    return 0;
}
