#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
string longestSequenceV(string sequence) {
    string V;
    for (int i = 0; i < sequence.size(); i++) {
        int startIndex = i, endIndex = i;
        if (startIndex > 0)
            for (int j = i-1; j >= 0; j--) {
                if (sequence[j] > sequence[j+1])
                    startIndex -= 1;
                else 
                    break;
            }
        if (endIndex < sequence.size()-1)
            for (int j = i+1; j < sequence.size(); j++) {
                if (sequence[j] > sequence[j-1])
                    endIndex += 1;
                else
                    break;
            }
        string tempV = sequence.substr(startIndex, endIndex-startIndex+1);
        if (tempV.size() > V.size()) {
            V = tempV;
        }
    }
    return V;
}

int main(int argc, char const *argv[]){
    ifstream file;
    file.open(argv[1]);
    string temp;
    std::getline(file, temp);
    cout << longestSequenceV(temp) << endl;
}