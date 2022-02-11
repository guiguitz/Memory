#include "Cache.h"
#include "DataMemory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG(code) if (0) { cout << code << '\n';}

int main()
{
    ifstream inputFile{"input.txt"};
    vector<string> inputLines;
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            DEBUG(line)
            inputLines.push_back(line);
        }
        inputFile.close();
    }

    ofstream resultFile;
    resultFile.open("result.txt");
    resultFile.close();
    return 1;
}
