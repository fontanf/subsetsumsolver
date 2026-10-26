#pragma once

#include "subsetsumsolver/solution.hpp"

namespace subsetsumsolver
{

struct DynamicProgrammingBellmanArrayOutput: public Output
{
    /** Constructor. */
    DynamicProgrammingBellmanArrayOutput(const Instance& instance):
        Output(instance)
    { }

    /**
     * Greatest common divisor of the weights of the items: the table is
     * indexed by the weights divided by it.
     */
    Weight gcd = 1;

    std::vector<ItemId> values;

    bool is_reachable(Weight weight) const
    {
        if (weight % gcd != 0)
            return false;
        return values[weight / gcd] != -1;
    }
};

DynamicProgrammingBellmanArrayOutput dynamic_programming_bellman_array(
        const Instance& instance,
        const Parameters& parameters = {});

Output dynamic_programming_bellman_list(
        const Instance& instance,
        const Parameters& parameters = {});

struct DynamicProgrammingBellmanWordRamOutput: public Output
{
    /** Constructor. */
    DynamicProgrammingBellmanWordRamOutput(const Instance& instance):
        Output(instance)
    { }

    /**
     * Greatest common divisor of the weights of the items: the table is
     * indexed by the weights divided by it.
     */
    Weight gcd = 1;

    std::vector<uint64_t> values;

    bool is_reachable(Weight weight) const
    {
        if (weight % gcd != 0)
            return false;
        Weight word = (weight / gcd) / 64;
        int bit = (weight / gcd) % 64;
        return ((values[word] >> bit) & 1) == 1;
    }
};

DynamicProgrammingBellmanWordRamOutput dynamic_programming_bellman_word_ram(
        const Instance& instance,
        const Parameters& parameters = {});

Output dynamic_programming_bellman_word_ram_rec(
        const Instance& instance,
        const Parameters& parameters = {});

}
