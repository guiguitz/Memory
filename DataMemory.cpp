#include "DataMemory.h"

using namespace std;

Word_M::Word_M(const int idxInsideMemory)
    : m_word{string{}}, m_idxInsideMemory{idxInsideMemory} {}

Main_memory::Main_memory()
{
    for (int i = 0; i < 1024; i++)
    {
        m_words.emplace_back(i);
    }
}