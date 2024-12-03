#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t line_count = 0;
    int64_t sum = 0;
    while(getline(in,line)){
        if (line.empty()){
            continue;
        }
        
        string delimiter = "mul(";

        while (! line.empty()){
        auto pos = line.find(delimiter);
        string token = line.substr(0, pos);
        stringstream num (token);
        int n1 = -1;
        int n2 = -1;
        char comma, paren;
        num >> n1 >> comma >>n2 >>paren;
        // Add the token to the array
        cout <<token  << " | " <<n1 <<" | "<<comma <<" | " <<n2; 
        if (num && (comma == ',') && (paren == ')')){
            cout << "\t= " <<n1 * n2;
            sum += n1 * n2;
        }
        cout <<endl;
        //if (pos != string::npos) 
        line.erase(0,pos + delimiter.length());
        }
    }
    cout  <<"Sum = " <<sum <<endl;

    return 0;
}
