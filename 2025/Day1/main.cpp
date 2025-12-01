#include <iostream>
#include <vector>

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

int main(void) {

    vector<vector<char>>temp_ = readCharFile("main.cpp");
    
    cout << "File content read into 2D char vector:" << endl;
    
    for (const auto& line : temp_) {
        for (const auto& ch : line) {
            cout << ch;
        }
        cout << endl;
    }
    

    return 0;
}
