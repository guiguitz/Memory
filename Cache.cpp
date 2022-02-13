#include "Cache.h"
#include <string>

using namespace std;

Word::Word(const int idxInsideBlock)
    : m_word{string{}}, m_valid{false}, m_idxInsideBlock{idxInsideBlock} {}

Block::Block(const int idxInsideCache)
    : m_dirty{false}, m_idxInsideCache{idxInsideCache}
{
    for (int i = 0; i < 4; i++)
    {
        m_block.emplace_back(i);
    }
}

Cache::Cache()
{
    for (int i = 0; i < 64; i++)
    {
        m_blocks.emplace_back(i);
    }
}

void Cache::doInstruction_in_Cache(const intruction &instru)
{
    m_result_file.open("result.txt");
    int address = instru.address;
    bool op = instru.operation;
    string data = instru.data;
    const int block_num = address / 64;
    const int word_idx = address % 4;
    Block actual_cache_block = m_blocks[block_num];
    Word actual_cache_word = actual_cache_block.m_block[word_idx];
    actual_cache_word.m_valid = true;
    if (op)
    {
        m_write_counter++;
        bool is_dirty = actual_cache_block.m_dirty;
        if (is_dirty)
        {
            m_data_memory.m_words[address].m_word = actual_cache_word.m_word;
        }
        actual_cache_word.m_word = data;
        actual_cache_word.m_tag = address;
        actual_cache_block.m_dirty = true;
        m_result_file << address << " " << op << " " << data << " W";
    }
    else
    {
        m_read_counter++;
        bool is_valid = actual_cache_word.m_valid;
        bool is_same_tag = actual_cache_word.m_tag == address;
        // DEPOIS OLHAR SE O BLOCO ESTA SUJO
        if (is_valid && is_same_tag)
        {
            m_hit_counter++;
            m_result_file << address << " " << op << " H";
        }
        else
        {
            m_miss_counter++;
            actual_cache_word.m_word = m_data_memory.m_words[address].m_word;
            actual_cache_word.m_tag = address;
            m_result_file << address << " " << op << " M";
        }
    }
    m_result_file.close();
}

void Cache::final_Results()
{
    m_result_file.open("result.txt");
    m_result_file << "\n"
                  << "READS: " << m_read_counter;
    m_result_file << "\n"
                  << "WRITES: " << m_write_counter;
    m_result_file << "\n"
                  << "HITS: " << m_hit_counter;
    m_result_file << "\n"
                  << "MISSES: " << m_miss_counter;
    m_result_file << "\n"
                  << "HIT RATE: " << m_hit_counter / m_read_counter;
    m_result_file << "\n"
                  << "MISS RATE: " << 1 - m_hit_counter;
    m_result_file.close();
}
