add_library(SubsetSumSolver)
target_sources(SubsetSumSolver PRIVATE
    instance.cpp
    instance_builder.cpp
    solution.cpp
    algorithm_formatter.cpp)
target_include_directories(SubsetSumSolver PUBLIC
    ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(SubsetSumSolver PUBLIC
    OptimizationTools::utils)
add_library(SubsetSumSolver ALIAS SubsetSumSolver)

add_subdirectory(algorithms)

if(SUBSETSUMSOLVER_BUILD_MAIN)
    add_executable(SubsetSumSolver_main)
    target_sources(SubsetSumSolver_main PRIVATE
        main.cpp)
    target_link_libraries(SubsetSumSolver_main PUBLIC
        SubsetSumSolver_dynamic_programming_bellman
        SubsetSumSolver_dynamic_programming_balancing
        SubsetSumSolver_dynamic_programming_primal_dual
        Boost::program_options)
    set_target_properties(SubsetSumSolver_main PROPERTIES OUTPUT_NAME "subsetsumsolver")
    install(TARGETS SubsetSumSolver_main)
endif()

add_library(SubsetSumSolver_generator)
target_sources(SubsetSumSolver_generator PRIVATE
    generator.cpp)
target_link_libraries(SubsetSumSolver_generator PUBLIC
    SubsetSumSolver)
add_library(SubsetSumSolver::generator ALIAS SubsetSumSolver_generator)

if(SUBSETSUMSOLVER_BUILD_TEST)
    add_library(SubsetSumSolver_tests)
    target_sources(SubsetSumSolver_tests PRIVATE
        tests.cpp)
    target_link_libraries(SubsetSumSolver_tests PUBLIC
        SubsetSumSolver
        Boost::filesystem
        GTest::gtest_main)
    add_library(SubsetSumSolver::tests ALIAS SubsetSumSolver_tests)
endif()
