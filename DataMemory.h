#include <string>
#include <vector>

using wordInMemory = struct wordInMemory
{
    explicit wordInMemory(const int idx_inside_memory);

    std::string m_word;
    const int m_idx_inside_memory;
};

using dataMemory = struct dataMemory
{
    explicit dataMemory();

    std::vector<wordInMemory> m_words;
};
