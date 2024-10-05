#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <list>
#include <algorithm>
using namespace std;

struct LineInfo {
    string content;
    size_t length, uppercaseCount, specialCharCount;

    LineInfo(const string& line) : content(line) {
        length = line.length();
        uppercaseCount = count_if(line.begin(), line.end(), [](unsigned char c) { return isupper(c); });
        specialCharCount = count_if(line.begin(), line.end(), [](unsigned char c) {
            return !isalnum(c);
            });
    }
};

bool compareByContent(const LineInfo& a, const LineInfo& b) {
    return a.content < b.content; 
}

int main() {
    ifstream inputFile("python.txt");
    list<LineInfo> lines; 
    string line;

   
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            lines.emplace_back(line); 
        }
    }

    lines.sort(compareByContent); 

    for (const auto& info : lines) {
        cout << info.length << ","
            << info.uppercaseCount << ","
            << info.specialCharCount << " "
            << info.content << endl;
    }

    return 0;
}
