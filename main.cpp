#include "Cache.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
#define DEBUG(code)           \
    if (0)                    \
    {                         \
        cout << code << '\n'; \
    }

fstream tmp_file{"tmp.txt"};
#define DEBUG_IN_A_FILE(code)                                                  \
  tmp_file.open("tmp.txt", fstream::app);                                      \
  if (1) {                                                                     \
    tmp_file << code << '\n';                                                  \
  }                                                                            \
  tmp_file.close();

// String delimiter
static vector<string> split(const string &s, const string &delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

int main()
{
    // Parsing input file.
    ifstream inputFile{"input.txt"};
    vector<string> inputLines;
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            inputLines.push_back(line);
        }
        inputFile.close();
    }

    const string delimiter = " ";
    vector<string> splitted_line;
    vector<intruction> instru;
    int address;
    bool operation;
    string data;
    for (auto &line : inputLines)
    {
        splitted_line = split(line, delimiter);
        address = stoi(splitted_line[0]);
        if (splitted_line.size() == 2)
        {
            operation = false;
            data = string{};
        }
        else
        {
            operation = true;
            data = splitted_line[2];
        }
        instru.push_back({address, operation, data});
    }

    Cache myCache;
    DEBUG("Instructions:")
    for (auto &instruction : instru)
    {
        DEBUG("   {" << instruction.address << ", " << instruction.operation << ", " << instruction.data << "}")
        myCache.doInstruction_in_Cache(instruction);
    }
    myCache.final_Results();

    DEBUG_IN_A_FILE("\n\nBlocks in cache \n\n")
    for (auto& block : myCache.m_blocks)
    {
        DEBUG_IN_A_FILE("########################")
        DEBUG_IN_A_FILE("   {" << block.m_dirty << ", " << block.m_idxInsideCache << "}")
        for (auto& word : block.m_block) {
            DEBUG_IN_A_FILE("     -> {" << word.m_word << ", " << word.m_valid << ", " << word.m_idxInsideBlock << "}")
        }
    }

    DEBUG_IN_A_FILE("\n\nData Memory \n\n")
    for (auto& word : myCache.m_data_memory.m_words)
    {
        DEBUG_IN_A_FILE("------------------------------")
        DEBUG_IN_A_FILE("     -> {" << word.m_word << ", " << word.m_idxInsideMemory << "}")
    }

    return 0;
}
