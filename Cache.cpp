#include "Cache.h"

using namespace std;

Word::Word(const int idxInsideBlock)
    : m_word{string{}}, m_valid{false}, m_idxInsideBlock{idxInsideBlock} {}

Block::Block(const int idxInsideCache)
    : m_dirty{false}, m_idxInsideCache{idxInsideCache}
{
    for (int i = 0; i < 3; i++)
    {
        m_block.emplace_back(i);
    }
}

Cache::Cache()
{
    for (int i = 0; i < 63; i++)
    {
        m_blocks.emplace_back(i);
    }
}
