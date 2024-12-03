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
    int64_t p2sum = 0;
    const string delimiter = "mul(";
    const string delimiter1 = "do()";
    const string delimiter2 = "don't()";

    bool p2enabled = true;
    while(getline(in,line)){
        if (line.empty()){
            continue;
        }
        
        while (! line.empty()){
            auto posmul = line.find(delimiter);
            auto posdo = line.find(delimiter1);
            auto posdont = line.find(delimiter2);

            cout <<"LINE: " <<line <<"\t posmul: " <<posmul <<"\t posdo: " <<posdo <<"\tposdont: " << posdont <<endl;
            if ((posmul < posdo) && (posmul < posdont)){
                auto pos = posmul;
                string token = line.substr(pos + delimiter.length(), -1);
                stringstream num (token);
                int n1 = -1;
                int n2 = -1;
                char comma, paren;
                num >> n1 >> comma >>n2 >>paren;
                cout <<"TOKEN: " <<token  << " | " <<n1 <<" | "<<comma <<" | " <<n2; 
                if (num && (comma == ',') && (paren == ')')){
                    cout << "\t= " <<n1 * n2;
                    sum += n1 * n2;
                    if ((posmul < posdont) && (posmul < posdo)){
                        if (p2enabled){
                            p2sum += n1*n2;
                            cout <<"\t P2sum enabled";
                        } 
                    }
                    else if (posmul < posdo){
                        if (p2enabled){
                            p2sum += n1*n2;
                            cout <<"\t P2sum enabled";
                        }
                    }
                    else if ((posdont < posmul) && (posdont < posdo)){
                        p2enabled = false;
                        cout <<"\t P2sum disabled";

                    }
                    else if (!p2enabled && (posdo < posmul)){
                        p2enabled = true;
                        p2sum += n1 * n2;
                        cout <<"\t P2sum ensabled";
                    }
                }
                cout <<endl;
                line.erase(0,pos + delimiter.length());
            }
            else if ((posdo < posmul) && (posdo < posdont)){
                auto pos = posdo;
                line.erase(0,pos + delimiter1.length());
                p2enabled = true;
            }
            else if ((posdont < posmul) && (posdont < posdo)){
                auto pos = posdont;
                line.erase(0,pos + delimiter2.length());
                p2enabled = false;
            }
            else {
                line.erase(0,posmul + delimiter.length());
            }
        }
    }
    cout  <<"Sum = " <<sum <<endl;
    cout  <<"Sum P2 = " <<p2sum <<endl;

    return 0;
}
