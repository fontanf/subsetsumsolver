#include "subsetsumsolver/generator.hpp"

#include "subsetsumsolver/instance_builder.hpp"

#include <cmath>

using namespace subsetsumsolver;

namespace
{

template <typename T>
T gcd(T a, T b)
{
   if (b == 0)
       return a;
   return gcd(b, a % b);
}

}

Instance subsetsumsolver::generate_pthree(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e3);
    instance_builder.set_capacity(number_of_items * 1e3 / 4);
    for (ItemId pos = 0; pos < number_of_items; ++pos)
        instance_builder.add_item(distribution(generator));
    return instance_builder.build();
}

Instance subsetsumsolver::generate_psix(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e6);
    instance_builder.set_capacity(number_of_items * 1e6 / 4);
    for (ItemId pos = 0; pos < number_of_items; ++pos)
        instance_builder.add_item(distribution(generator));
    return instance_builder.build();
}

Instance subsetsumsolver::generate_evenodd(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e3 / 2);
    instance_builder.set_capacity(2 * (number_of_items * 1e3 / 8) + 1);
    for (ItemId pos = 0; pos < number_of_items; ++pos)
        instance_builder.add_item(2 * distribution(generator));
    return instance_builder.build();
}

Instance subsetsumsolver::generate_avis(
        ItemId number_of_items)
{
    ItemId n = number_of_items;
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e3);
    instance_builder.set_capacity(n * (n + 1) * ((n - 1) / 2) + n * (n - 1) / 2);
    for (ItemId pos = 0; pos < number_of_items; ++pos)
        instance_builder.add_item(n * (n + 1) + pos);
    return instance_builder.build();
}

Instance subsetsumsolver::generate_todd(
        ItemId number_of_items)
{
    ItemId n = number_of_items;
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e3);
    Weight weight_sum = 0;
    for (ItemId pos = 0; pos < number_of_items; ++pos) {
        int i1 = (int)std::floor(std::log(n)) + n + 1;
        int i2 = (int)std::floor(std::log(n)) + pos;
        Weight item_weight = (1 << i1) + (1 << i2) + 1;
        instance_builder.add_item(item_weight);
        weight_sum += item_weight;
    }
    instance_builder.set_capacity(weight_sum / 2);
    return instance_builder.build();
}

Instance subsetsumsolver::generate_somatoth(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    std::uniform_int_distribution<Weight> distribution(1, number_of_items);
    Weight w1;
    Weight w2;
    Weight capacity;
    for (;;) {
        w1 = distribution(generator);
        w2 = distribution(generator);
        std::cout << "w1 " << w1 << " w2 " << w2 << " gcd " << gcd(w1, w2) << std::endl;
        if (gcd(w1, w2) != 1)
            continue;

        capacity = (w1 - 1) * (w2 - 1) - 1;
        std::cout << capacity / w1 << " " << capacity / w2 << " " << number_of_items / 2 << std::endl;
        if (capacity / w1 >= number_of_items / 2)
            continue;
        if (capacity / w2 >= number_of_items / 2)
            continue;
    }

    instance_builder.set_capacity(capacity);
    for (ItemId pos = 0; pos < number_of_items; ++pos) {
        if (pos % 2 == 0) {
            instance_builder.add_item(std::ceil((double)pos / 2) * w1);
        } else {
            instance_builder.add_item(std::ceil((double)pos / 2) * w2);
        }
    }

    return instance_builder.build();
}

Instance subsetsumsolver::generate_evenodd6(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e6 / 2);
    instance_builder.set_capacity((number_of_items * 1e6 / 60) + 1);
    for (ItemId pos = 0; pos < number_of_items; ++pos)
        instance_builder.add_item(2 * distribution(generator));
    return instance_builder.build();
}

Instance subsetsumsolver::generate_evenodd8(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e8 / 2);
    Weight weight_sum = 0;
    for (ItemId pos = 0; pos < number_of_items; ++pos) {
        Weight item_weight = 2 * distribution(generator);
        instance_builder.add_item(item_weight);
        weight_sum += item_weight;
    }
    instance_builder.set_capacity(weight_sum / 2 + 1);
    return instance_builder.build();
}

Instance subsetsumsolver::generate_tenfive6(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e5);
    Weight weight_sum = 0;
    for (ItemId pos = 0; pos < number_of_items; ++pos) {
        Weight item_weight = 10 * distribution(generator);
        instance_builder.add_item(item_weight);
        weight_sum += item_weight;
    }
    instance_builder.set_capacity((weight_sum / 600) * 10 + 5);
    return instance_builder.build();
}

Instance subsetsumsolver::generate_tenfive8(
        ItemId number_of_items,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;
    std::uniform_int_distribution<Weight> distribution(1, 1e7);
    Weight weight_sum = 0;
    for (ItemId pos = 0; pos < number_of_items; ++pos) {
        Weight item_weight = 10 * distribution(generator);
        instance_builder.add_item(item_weight);
        weight_sum += item_weight;
    }
    instance_builder.set_capacity((weight_sum / 20) * 10 + 5);
    return instance_builder.build();
}
