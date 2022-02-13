#include "Cache.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define DEBUG(code)           \
    if (0)                    \
    {                         \
        cout << code << '\n'; \
    }

#define DEBUG_IN_TMP_FILE(code)               \
    if (1)                                  \
    {                                       \
        tmp_file << code << '\n';           \
    }                                       \

// String delimiter.
static vector<string> split(const string& s, const string& delimiter)
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
    vector<instruction> runInstruction;
    int address;
    bool operation;
    string data;
    for (auto& line : inputLines)
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
        runInstruction.emplace_back(address, operation, data);
    }

    cache my_cache;

    DEBUG("Instructions:")
    for (auto& instruction : runInstruction)
    {
        DEBUG("   {" << instruction.m_address << ", " << instruction.m_operation << ", " << instruction.m_data << "}")
        my_cache.runInstructionInCache(instruction);
    }

    // Writing results in results.txt
    my_cache.generateFinalResults();


    ofstream tmp_file("tmp.txt");
    DEBUG_IN_TMP_FILE("\n\nBLOCKS IN CACHE:\n\n")
    for (auto& block : my_cache.m_blocks)
    {
        DEBUG_IN_TMP_FILE("########################")
        DEBUG_IN_TMP_FILE("   {" << block.m_dirty << ", " << block.m_idx_inside_cache << "}")
        for (auto& word : block.m_block)
        {
            DEBUG_IN_TMP_FILE("     -> {" << word.m_word << ", " << word.m_valid << ", " << word.m_idx_inside_block
                                        << "}")
        }
    }

    DEBUG_IN_TMP_FILE("\n\nDATA MEMORY:\n\n")
    for (auto& word : my_cache.m_data_memory.m_words)
    {
        DEBUG_IN_TMP_FILE("------------------------------")
        DEBUG_IN_TMP_FILE("     -> {" << word.m_word << ", " << word.m_idx_inside_memory << "}")
    }

    tmp_file.close();
    return 0;
}
