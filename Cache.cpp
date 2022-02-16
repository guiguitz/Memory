#include "Cache.h"

#include <iostream>
#include <string>
#include <utility>

using std::string;

using namespace std;

#define DEBUG(code)           \
    if (0)                    \
    {                         \
        cout << code << '\n'; \
    }

instruction::instruction(const int& address, const bool& operation, string data)
    : m_address{address}, m_operation{operation}, m_data{std::move(data)}
{

}

word::word(const int idx_inside_block) : m_word{string{}}, m_valid{false}, m_idx_inside_block{idx_inside_block} {}

block::block(const int idx_inside_cache) : m_dirty{false}, m_idx_inside_cache{idx_inside_cache}
{
    for (int i = 0; i < 4; i++)
    {
        m_block.emplace_back(i);
    }
}

cache::cache() : m_result_file{"result.txt"}
{
    for (int i = 0; i < 64; i++)
    {
        m_blocks.emplace_back(i);
    }
}

cache::~cache()
{
    m_result_file.close();
}

void cache::updateMemoryWithBlockData(const int address, const int word_idx, const int block_num)
{
    block& actual_cache_block = m_blocks[block_num];

    DEBUG("\nInput block:")
    DEBUG("actual_cache_block.m_block[0].m_word: " << actual_cache_block.m_block[0].m_word)
    DEBUG("actual_cache_block.m_block[1].m_word: " << actual_cache_block.m_block[1].m_word)
    DEBUG("actual_cache_block.m_block[2].m_word: " << actual_cache_block.m_block[2].m_word)
    DEBUG("actual_cache_block.m_block[3].m_word: " << actual_cache_block.m_block[0].m_word)

    if (word_idx == 0)
    {
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address + 1].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address + 2].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address + 3].m_word = actual_cache_block.m_block[3].m_word;
        DEBUG("\ninput block:")
        DEBUG("address: " << address << " - address+1: " << address + 1 << " - address+2: " << address + 2
                          << " - address+3: " << address + 3)
        DEBUG("m_data_memory.m_words[ <<address].m_word: " << m_data_memory.m_words[address].m_word)
        DEBUG("m_data_memory.m_words[ <<address+1].m_word: " << m_data_memory.m_words[address + 1].m_word)
        DEBUG("m_data_memory.m_words[ <<address+2].m_word: " << m_data_memory.m_words[address + 2].m_word)
        DEBUG("m_data_memory.m_words[ <<address+3].m_word: " << m_data_memory.m_words[address + 3].m_word)
    }
    else if (word_idx == 1)
    {
        m_data_memory.m_words[address - 1].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address + 1].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address + 2].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-1: " << address - 1 << " - address: " << address << " - address+1: " << address + 1
                            << " - address+2: " << address + 2)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address - 1].m_word)
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word)
        DEBUG("m_data_memory.m_words[address+1].m_word: " << m_data_memory.m_words[address + 1].m_word)
        DEBUG("m_data_memory.m_words[address+2].m_word: " << m_data_memory.m_words[address + 2].m_word)
    }
    else if (word_idx == 2)
    {
        m_data_memory.m_words[address - 2].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address - 1].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address + 1].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-2: " << address - 2 << " - address-1: " << address - 1 << " - address: " << address
                            << " - address+1: " << address + 1)
        DEBUG("m_data_memory.m_words[address-2].m_word: " << m_data_memory.m_words[address - 2].m_word)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address - 1].m_word)
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word)
        DEBUG("m_data_memory.m_words[address+1].m_word: " << m_data_memory.m_words[address + 1].m_word)
    }
    else if (word_idx == 3)
    {
        m_data_memory.m_words[address - 3].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address - 2].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address - 1].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-3: " << address - 3 << " - address-2: " << address - 2 << " - address-1: " << address - 1
                            << " - address: " << address)
        DEBUG("m_data_memory.m_words[address-3].m_word: " << m_data_memory.m_words[address - 3].m_word)
        DEBUG("m_data_memory.m_words[address-2].m_word: " << m_data_memory.m_words[address - 2].m_word)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address - 1].m_word)
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word)
    }
}

void cache::runInstructionInCache(const instruction& runInstruction)
{
    const int address = runInstruction.m_address;
    const bool op = runInstruction.m_operation;
    const string data = runInstruction.m_data;
    const int block_num = address / 16;
    const int word_idx = address % 4;

    block& actual_cache_block = m_blocks[block_num];
    word& actual_cache_word = actual_cache_block.m_block[word_idx];
    actual_cache_word.m_valid = true;

    const bool is_dirty = actual_cache_block.m_dirty;

    if (is_dirty)
    {
        updateMemoryWithBlockData(address, word_idx, block_num);
    }

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
        m_result_file << address << " " << op << " " << data << " W\n";
    }
    else
    {
        m_read_counter++;
        bool is_valid = actual_cache_word.m_valid;
        bool is_same_tag = actual_cache_word.m_tag == address;
        if (is_valid && is_same_tag)
        {
            m_hit_counter++;
            m_result_file << address << " " << op << " H\n";
        }
        else
        {
            m_miss_counter++;
            actual_cache_word.m_word = m_data_memory.m_words[address].m_word;
            actual_cache_word.m_tag = address;
            m_result_file << address << " " << op << " M\n";
        }
    }
}

void cache::generateFinalResults()
{
    m_result_file << "\n"
                  << "READS: " << m_read_counter;
    m_result_file << "\n"
                  << "WRITES: " << m_write_counter;
    m_result_file << "\n"
                  << "HITS: " << m_hit_counter;
    m_result_file << "\n"
                  << "MISSES: " << m_miss_counter;
    m_result_file << "\n"
                  << "HIT RATE: " << ((float) m_hit_counter / (float) m_read_counter);
    m_result_file << "\n"
                  << "MISS RATE: " << (1 - ((float) m_hit_counter / (float) m_read_counter));
    m_result_file << "\n";
}
