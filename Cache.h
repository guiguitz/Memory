#include <string>
#include <vector>
#include "DataMemory.h"
#include <fstream>

typedef struct intruction
{
    int address;
    bool operation; /* 0 -> reading or 1 -> writing */
    std::string data;
};

using Word = struct Word
{
    std::string m_word;
    bool m_valid;
    const int m_idxInsideBlock;
    int m_tag = 5000;
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
    Main_memory m_data_memory;
    int m_read_counter = 0;
    int m_write_counter = 0;
    int m_hit_counter = 0;
    int m_miss_counter = 0;
    std::fstream m_result_file{};
    explicit Cache();
    ~Cache();
    void doInstruction_in_Cache(const ::intruction &instru);
    void final_Results();
    void updateMemoryWithBlockData (const int address, const int word_idx, const int block_num);
};
