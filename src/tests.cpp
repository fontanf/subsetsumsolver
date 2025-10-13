#include "subsetsumsolver/tests.hpp"

#include "subsetsumsolver/instance_builder.hpp"

#include <boost/filesystem.hpp>

using namespace subsetsumsolver;

namespace fs = boost::filesystem;

std::string subsetsumsolver::get_path(
        const std::vector<std::string>& path)
{
    if (path.empty())
        return "";
    fs::path p(path[0]);
    for (size_t i = 1; i < path.size(); ++i)
        p /= path[i];
    return p.string();
}

std::vector<TestInstancePath> subsetsumsolver::get_pthree_instance_paths(
        ItemId number_of_items)
{
    std::vector<TestInstancePath> instance_paths;
    for (int i = 0; i < 100; ++i) {
        instance_paths.push_back({
                get_path({"pthree", "pthree_" + std::to_string(number_of_items) + "_" + std::to_string(i)}), "standard",
                get_path({"pthree", "pthree_" + std::to_string(number_of_items) + "_" + std::to_string(i) + "_solution.txt"}), "standard"});
    }
    return instance_paths;
}

std::vector<TestInstancePath> subsetsumsolver::get_psix_instance_paths(
        ItemId number_of_items)
{
    std::vector<TestInstancePath> instance_paths;
    for (int i = 0; i < 100; ++i) {
        instance_paths.push_back({
                get_path({"psix", "psix_" + std::to_string(number_of_items) + "_" + std::to_string(i)}), "standard",
                get_path({"psix", "psix_" + std::to_string(number_of_items) + "_" + std::to_string(i) + "_solution.txt"}), "standard"});
    }
    return instance_paths;
}

std::vector<TestParams> subsetsumsolver::get_test_params(
        const std::vector<Algorithm>& algorithms,
        const std::vector<std::vector<TestInstancePath>>& instance_paths)
{
    std::vector<TestParams> res;
    for (const Algorithm& algorithm: algorithms) {
        for (const auto& v: instance_paths) {
            for (const TestInstancePath& files: v) {
                TestParams test_params;
                test_params.algorithm = algorithm;
                test_params.files = files;
                res.push_back(test_params);
            }
        }
    }
    return res;
}

const Instance subsetsumsolver::get_instance(
            const TestInstancePath& files)
{
    InstanceBuilder instance_builder;
    std::string instance_path = get_path({
            std::getenv("SUBSET_SUM_DATA"),
            files.instance_path});
    std::cout << "Instance path:  " << instance_path << std::endl;
    instance_builder.read(
            instance_path,
            files.instance_format);
    return instance_builder.build();
}

const Solution subsetsumsolver::get_solution(
        const Instance& instance,
        const TestInstancePath& files)
{
    std::string certificate_path = get_path({
            std::getenv("SUBSET_SUM_DATA"),
            files.certificate_path});
    return Solution(
            instance,
            certificate_path);
}
