#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

using board_t = vector<string>;

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

int main(int argc, char* argv[]){
    if (argc < 2){
        cout <<"Usage " <<argv[0] <<" <input file>" <<endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    string line;
    uint64_t line_count = 0;
    board_t board;
    while(getline(in,line)){
        if (line.empty()){
            continue;
        }
        board.push_back(line);
    }
    cout <<board<<endl;

    int occurrences = 0;
    int p2 = 0;
    for (int32_t ri = 0; ri < board.size(); ri++){
        const string r = board[ri];
        cout <<"Running row " <<ri << ": " <<r <<endl;
        std::string::size_type pos = 0;
        //forward;
        std::string target = "XMAS";
        /*
        while ((pos = r.find(target, pos )) != std::string::npos) {
            cout <<"\t[ " <<ri <<"," <<pos <<"] Forward\n";
            ++ occurrences;
            pos += target.length();
        }
        //backward;
        pos = 0;
        std::string target2 = "SAMX";
        while ((pos = r.find(target2, pos )) != std::string::npos) {
            cout <<"\t[ " <<ri <<"," <<pos <<"] Backward\n";
            ++ occurrences;
            pos += target.length();
        }
        */

        for (int32_t ci = 0; ci < r.length(); ci++){
            if (r[ci] == 'X'){
                //forward
                if ((ci + 3 < r.length()) &&
                    (r[ci + 1] == 'M') &&
                    (r[ci + 2] == 'A') &&
                    (r[ci + 3] == 'S')) {
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Horizontal Forward\n";
                      ++occurrences;
                }
                //backward
                if ((ci > 2 ) &&
                    (r[ci - 1] == 'M') &&
                    (r[ci - 2] == 'A') &&
                    (r[ci - 3] == 'S')) {
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Horizontal Backward\n";
                      ++occurrences;
                }
                //vertical down
                if (ri + 3 < board.size()){
                    if ((board[ri + 1][ci] == 'M') && 
                        (board[ri + 2][ci] == 'A') && 
                        (board[ri + 3][ci] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Vertical Down\n";
                      ++occurrences;
                    }
                    //diagonal down left;
                    if ((ci > 2) && 
                        (board[ri + 1][ci - 1] == 'M') && 
                        (board[ri + 2][ci - 2] == 'A') && 
                        (board[ri + 3][ci - 3] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Diag Down Left \n";
                      ++occurrences;
                    }
                    //diagonal down right;
                    if ((ci + 3 < r.length()) && 
                        (board[ri + 1][ci + 1] == 'M') && 
                        (board[ri + 2][ci + 2] == 'A') && 
                        (board[ri + 3][ci + 3] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Diag Down Right \n";
                      ++occurrences;
                    }
                }
                //vertical up
                if (ri > 2 ){
                    if ((board[ri - 1][ci] == 'M') && 
                        (board[ri - 2][ci] == 'A') && 
                        (board[ri - 3][ci] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Vertical Up \n";
                      ++occurrences;
                    }
                    //diagonal up left;
                    if ((ci > 2) && 
                        (board[ri - 1][ci - 1] == 'M') && 
                        (board[ri - 2][ci - 2] == 'A') && 
                        (board[ri - 3][ci - 3] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Diag Up Left \n";
                      ++occurrences;
                    }
                    //diagonal up right;
                    if ((ci + 3 < r.length()) && 
                        (board[ri - 1][ci + 1] == 'M') && 
                        (board[ri - 2][ci + 2] == 'A') && 
                        (board[ri - 3][ci + 3] == 'S')  
                    ){
                      cout <<"\t[ " <<ri <<"," <<ci <<"] Diag Up Right \n";
                      ++occurrences;
                    }
                }
            }
            if (r[ci] == 'A'){
                //vertical down
                if ((ri + 1 < board.size()) && (ri > 0)){
                    if ((ci > 0) && (ci + 1 < r.length())){
                        //diagonal X Left;
                        if ((((board[ri + 1][ci - 1] == 'M') && (board[ri - 1][ci + 1] == 'S') ) || 
                             ((board[ri + 1][ci - 1] == 'S') && (board[ri - 1][ci + 1] == 'M') ) ) && 
                            (((board[ri + 1][ci + 1] == 'M') && (board[ri - 1][ci - 1] == 'S') ) || 
                            ((board[ri + 1][ci + 1] == 'S') && (board[ri - 1][ci - 1] == 'M') ) )){
                          cout <<"\t[ " <<ri <<"," <<ci <<"] Diag Down Left \n";
                          ++p2;
                        }
                    }
                }
            }
        }
    }

    cout <<"Number: " <<occurrences<<endl;
    cout <<"P2 Number: " <<p2<<endl;

    return 0;
}
