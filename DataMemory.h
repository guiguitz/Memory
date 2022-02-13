#include <string>
#include <vector>

using Word_M = struct Word_M
{
    std::string m_word;
    const int m_idxInsideMemory;
    explicit Word_M(const int idxInsideMemory);
};

using Main_memory = struct Main_memory
{
    std::vector<Word_M> m_words;
    explicit Main_memory();
};