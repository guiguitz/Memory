#include "DataMemory.h"

#include <fstream>
#include <string>
#include <vector>

using instruction = struct instruction
{
    explicit instruction(const int& address, const bool& operation, std::string data);

    int m_address;
    bool m_operation; /* 0 -> reading or 1 -> writing */
    std::string m_data;
};

using word = struct word
{
    explicit word(const int idx_inside_block);

    std::string m_word;
    bool m_valid;
    const int m_idx_inside_block;
    int m_tag = 5000;
};

using block = struct block
{
    explicit block(const int idx_inside_cache);

    std::vector<word> m_block;
    bool m_dirty;
    const int m_idx_inside_cache;
};

using cache = struct cache
{
    explicit cache();
    ~cache();

    std::vector<block> m_blocks;
    dataMemory m_data_memory;
    int m_read_counter = 0;
    int m_write_counter = 0;
    int m_hit_counter = 0;
    int m_miss_counter = 0;
    std::ofstream m_result_file;

    void runInstructionInCache(const instruction& runInstruction);
    void generateFinalResults();
    void updateMemoryWithBlockData(const int address, const int word_idx, const int block_num);
};
