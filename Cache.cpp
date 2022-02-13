#include "Cache.h"
#include <string>
#include <iostream>

using namespace std;

#define DEBUG(code)           \
    if (0)                    \
    {                         \
        cout << code << '\n'; \
    }

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
    m_result_file.open("result.txt");
}

Cache::~Cache()
{
    m_result_file.close();
}

void Cache::updateMemoryWithBlockData (const int address, const int word_idx, const int block_num)
{
    Block& actual_cache_block = m_blocks[block_num];
    Word& actual_cache_word = actual_cache_block.m_block[word_idx];

    DEBUG("\ninput block:")
    DEBUG("actual_cache_block.m_block[0].m_word: " << actual_cache_block.m_block[0].m_word)
    DEBUG("actual_cache_block.m_block[1].m_word: " << actual_cache_block.m_block[1].m_word)
    DEBUG("actual_cache_block.m_block[2].m_word: " << actual_cache_block.m_block[2].m_word)
    DEBUG("actual_cache_block.m_block[3].m_word: " << actual_cache_block.m_block[0].m_word)

    if (word_idx == 0)
    {
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address+1].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address+2].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address+3].m_word = actual_cache_block.m_block[3].m_word;
        DEBUG("\ninput block:")
        DEBUG("address: " << address << " - address+1: " << address+1 << " - address+2: " << address+2 << " - address+3: " << address+3)
        DEBUG("m_data_memory.m_words[ <<address].m_word: " << m_data_memory.m_words[address].m_word)
        DEBUG("m_data_memory.m_words[ <<address+1].m_word: " << m_data_memory.m_words[address+1].m_word)
        DEBUG("m_data_memory.m_words[ <<address+2].m_word: " << m_data_memory.m_words[address+2].m_word )
        DEBUG("m_data_memory.m_words[ <<address+3].m_word: " << m_data_memory.m_words[address+3].m_word)
    }
    else if (word_idx == 1)
    {
        m_data_memory.m_words[address-1].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address+1].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address+2].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-1: " << address-1 << " - address: " << address << " - address+1: " << address+1 << " - address+2: " << address+2)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address-1].m_word)
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word)
        DEBUG("m_data_memory.m_words[address+1].m_word: " << m_data_memory.m_words[address+1].m_word )
        DEBUG("m_data_memory.m_words[address+2].m_word: " << m_data_memory.m_words[address+2].m_word)
    }
    else if (word_idx == 2)
    {
        m_data_memory.m_words[address-2].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address-1].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address+1].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-2: " << address-2 << " - address-1: " << address-1 << " - address: " << address << " - address+1: " << address+1)
        DEBUG("m_data_memory.m_words[address-2].m_word: " << m_data_memory.m_words[address-2].m_word)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address-1].m_word)
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word )
        DEBUG("m_data_memory.m_words[address+1].m_word: " << m_data_memory.m_words[address+1].m_word)
    }
    else if (word_idx == 3)
    {
        m_data_memory.m_words[address-3].m_word = actual_cache_block.m_block[0].m_word;
        m_data_memory.m_words[address-2].m_word = actual_cache_block.m_block[1].m_word;
        m_data_memory.m_words[address-1].m_word = actual_cache_block.m_block[2].m_word;
        m_data_memory.m_words[address].m_word = actual_cache_block.m_block[3].m_word;

        DEBUG("address-3: " << address-3 << " - address-2: " << address-2 << " - address-1: " << address-1 << " - address: " << address)
        DEBUG("m_data_memory.m_words[address-3].m_word: " << m_data_memory.m_words[address-3].m_word)
        DEBUG("m_data_memory.m_words[address-2].m_word: " << m_data_memory.m_words[address-2].m_word)
        DEBUG("m_data_memory.m_words[address-1].m_word: " << m_data_memory.m_words[address-1].m_word )
        DEBUG("m_data_memory.m_words[address].m_word: " << m_data_memory.m_words[address].m_word)
    }
}

void Cache::doInstruction_in_Cache(const intruction &instru)
{
    const int address = instru.address;
    const bool op = instru.operation;
    const string data = instru.data;
    const int block_num = address / 16;
    const int word_idx = address % 4;
    // DEBUG("block_num: " << block_num)
    // DEBUG("word_idx: " << word_idx)
    Block& actual_cache_block = m_blocks[block_num];
    Word& actual_cache_word = actual_cache_block.m_block[word_idx];
    // DEBUG("actual_cache_block.m_dirty: " << actual_cache_block.m_dirty)
    // DEBUG("actual_cache_block.m_idxInsideCache: " << actual_cache_block.m_idxInsideCache)
    actual_cache_word.m_valid = true;
    bool is_dirty = actual_cache_block.m_dirty;

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
        // DEBUG("actual_cache_word.m_tag: " << actual_cache_word.m_tag)
        m_result_file << address << " " << op << " " << data << " W\n";
    }
    else
    {
        m_read_counter++;
        bool is_valid = actual_cache_word.m_valid;
        bool is_same_tag = actual_cache_word.m_tag == address;
        // DEBUG("actual_cache_word.m_tag: " << actual_cache_word.m_tag)
        // DEBUG("address: " << address)
        // DEBUG("is_valid: " << is_valid << " - is_same_tag: " << is_same_tag)
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

void Cache::final_Results() {
  m_result_file << "\n"
                << "READS: " << m_read_counter;
  m_result_file << "\n"
                << "WRITES: " << m_write_counter;
  m_result_file << "\n"
                << "HITS: " << m_hit_counter;
  m_result_file << "\n"
                << "MISSES: " << m_miss_counter;
  m_result_file << "\n"
                << "HIT RATE: "
                << ((float)m_hit_counter / (float)m_read_counter);
  m_result_file << "\n"
                << "MISS RATE: "
                << (1 - ((float)m_hit_counter / (float)m_read_counter));
  m_result_file << "\n";
}
