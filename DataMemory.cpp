#include "DataMemory.h"

using namespace std;

wordInMemory::wordInMemory(const int idx_inside_memory) : m_word{string{}}, m_idx_inside_memory{idx_inside_memory} {}

dataMemory::dataMemory()
{
    for (int i = 0; i < 1024; i++)
    {
        m_words.emplace_back(i);
    }
}
