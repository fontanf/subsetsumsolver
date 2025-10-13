# SubsetSumSolver

A solver for the subset sum problem

## Implemented algorithms

* Dynamic programming
  * Bellman
    * Array `-a dynamic-programming-bellman-array`
    * List (only optimal value) `-a dynamic-programming-bellman-list`
    * Word RAM (only optimal value) `-a dynamic-programming-bellman-word-ram`
    * Word RAM with recursive scheme `-a dynamic-programming-bellman-word-ram-rec`
  * Balancing
    * Array (only optimal value) `-a dynamic-programming-balancing-array`

## Usage

### Command line

Compile:
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
cmake --install build --config Release --prefix install
```

Download data:
```shell
python3 scripts/download_data.py
```

Solve:
```shell
./install/bin/subsetsumsolver  --verbosity-level 1  --input data/pthree/pthree_1000_1  --algorithm dynamic-programming-bellman-word-ram-rec
```
```
====================================
           KnapsackSolver           
====================================

Problem
-------
Subset sum problem

Instance
--------
Number of items:  1000
Capacity:         250000

Algorithm
---------
Dynamic programming - Bellman - word RAM - recursive scheme

Parameters
----------
Time limit:            inf
Messages
    Verbosity level:   1
    Standard output:   1
    File path:         
    # streams:         0
Logger
    Has logger:        0
    Standard error:    0
    File path:         

    Time (s)  Sol.       Value       Bound         Gap     Gap (%)                         Comment
    --------  ----       -----       -----         ---     -------                         -------
       0.000     1           0      250000      250000      100.00                                
       0.033     1      250000      250000           0        0.00        algorithm end (solution)

Final statistics
----------------
Value:                        250000
Has solution:                 1
Bound:                        250000
Absolute optimality gap:      0
Relative optimality gap (%):  0
Time (s):                     0.0330949

Solution
--------
Number of items:  484 / 1000 (48.4%)
Weight:           250000 / 250000 (100%)
Feasible:         1
```

Run tests:
```
export SUBSET_SUM_DATA=$(pwd)/data
cd build/test
ctest --parallel
```
