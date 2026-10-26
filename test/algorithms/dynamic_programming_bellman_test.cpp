#include "subsetsumsolver/tests.hpp"

#include "subsetsumsolver/algorithms/dynamic_programming_bellman.hpp"
#include "subsetsumsolver/instance_builder.hpp"

#include <boost/filesystem.hpp>

using namespace subsetsumsolver;
namespace fs = boost::filesystem;

TEST_P(ExactAlgorithmTest, ExactAlgorithm)
{
    TestParams test_params = GetParam();
    const Instance instance = get_instance(test_params.files);
    const Solution solution = get_solution(instance, test_params.files);
    auto output = test_params.algorithm(instance);
    EXPECT_EQ(output.value, solution.weight());
    EXPECT_EQ(output.value, output.solution.weight());
    EXPECT_EQ(output.bound, solution.weight());
}

TEST_P(ExactNoSolutionAlgorithmTest, ExactNoSolutionAlgorithm)
{
    TestParams test_params = GetParam();
    const Instance instance = get_instance(test_params.files);
    const Solution solution = get_solution(instance, test_params.files);
    auto output = test_params.algorithm(instance);
    EXPECT_EQ(output.value, solution.weight());
    EXPECT_EQ(output.bound, solution.weight());
}

INSTANTIATE_TEST_SUITE_P(
        SubsetSumDynamicProgrammingBellmanArray,
        ExactAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_array(instance);
                    },
                },
                {
                    get_pthree_instance_paths(10),
                    get_pthree_instance_paths(30),
                    get_pthree_instance_paths(100),
                    get_pthree_instance_paths(300),
                    get_pthree_instance_paths(1000),
                    get_psix_instance_paths(10),
                })));

INSTANTIATE_TEST_SUITE_P(
        SubsetSumDynamicProgrammingBellmanList,
        ExactNoSolutionAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_list(instance);
                    },
                },
                {
                    get_pthree_instance_paths(10),
                    get_pthree_instance_paths(30),
                    get_pthree_instance_paths(100),
                    get_pthree_instance_paths(300),
                    get_pthree_instance_paths(1000),
                    get_psix_instance_paths(10),
                })));

INSTANTIATE_TEST_SUITE_P(
        SubsetSumDynamicProgrammingBellmanWordRam,
        ExactNoSolutionAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_word_ram(instance);
                    },
                },
                {
                    get_pthree_instance_paths(10),
                    get_pthree_instance_paths(30),
                    get_pthree_instance_paths(100),
                    get_pthree_instance_paths(300),
                    get_pthree_instance_paths(1000),
                    get_psix_instance_paths(10),
                })));

INSTANTIATE_TEST_SUITE_P(
        SubsetSumDynamicProgrammingBellmanWordRamRec,
        ExactAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_word_ram_rec(instance);
                    },
                },
                {
                    get_pthree_instance_paths(10),
                    get_pthree_instance_paths(30),
                    get_pthree_instance_paths(100),
                    get_pthree_instance_paths(300),
                    get_pthree_instance_paths(1000),
                    get_psix_instance_paths(10),
                })));

TEST(SubsetSumDynamicProgrammingBellmanWordRam, NothingButZeroReachable)
{
    // Only weight '0' is reachable: the final scan for the optimal value
    // must stop at word '0' instead of reading out of bounds.
    for (Weight item_weight: {-1, 200}) {
        InstanceBuilder instance_builder;
        instance_builder.set_capacity(100);
        if (item_weight >= 0)
            instance_builder.add_item(item_weight);
        const Instance instance = instance_builder.build();
        auto output = dynamic_programming_bellman_word_ram(instance);
        EXPECT_EQ(output.value, 0);
        EXPECT_EQ(output.bound, 0);
    }
}

struct SubsetSumDynamicProgrammingBellmanWordRamRecTestParams
{
    fs::path instance_path;

    fs::path certificate_path;
};

inline std::ostream& operator<<(
        std::ostream& os,
        const SubsetSumDynamicProgrammingBellmanWordRamRecTestParams& test_params)
{
    os << test_params.instance_path;
    return os;
}

class SubsetSumDynamicProgrammingBellmanWordRamRecTest: public testing::TestWithParam<SubsetSumDynamicProgrammingBellmanWordRamRecTestParams> { };

TEST_P(SubsetSumDynamicProgrammingBellmanWordRamRecTest, SubsetSumDynamicProgrammingBellmanWordRamRec)
{
    SubsetSumDynamicProgrammingBellmanWordRamRecTestParams test_params = GetParam();
    InstanceBuilder instance_builder;
    instance_builder.read(test_params.instance_path.string(), "standard");
    const Instance instance = instance_builder.build();
    const Solution solution(instance, test_params.certificate_path.string());

    auto output = dynamic_programming_bellman_word_ram_rec(instance);
    EXPECT_EQ(output.value, solution.weight());
    EXPECT_EQ(output.value, output.solution.weight());
    EXPECT_EQ(output.bound, solution.weight());
}

INSTANTIATE_TEST_SUITE_P(
        SubsetSum,
        SubsetSumDynamicProgrammingBellmanWordRamRecTest,
        testing::ValuesIn(std::vector<SubsetSumDynamicProgrammingBellmanWordRamRecTestParams>{
            {
                fs::path("data") / "tests" / "no_item" / "instance.txt",
                fs::path("data") / "tests" / "no_item" / "solution.txt",
            }, {
                fs::path("data") / "tests" / "single_item" / "instance.txt",
                fs::path("data") / "tests" / "single_item" / "solution.txt",
            }, {
                fs::path("data") / "tests" / "single_item_too_heavy" / "instance.txt",
                fs::path("data") / "tests" / "single_item_too_heavy" / "solution.txt",
            }}));
