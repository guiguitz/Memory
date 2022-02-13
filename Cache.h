#include <string>
#include <vector>

using Word = struct Word
{
    std::string m_word;
    bool m_valid;
    const int m_idxInsideBlock;
    explicit Word(const int idxInsideBlock);
};

using Block = struct Block
{
    std::vector<Word> m_block;
    bool m_dirty;
    const int m_idxInsideCache;
    explicit Block(const int idxInsideCache);
};

using Cache = struct Cache
{
    std::vector<Block> m_blocks;
    explicit Cache();
};
