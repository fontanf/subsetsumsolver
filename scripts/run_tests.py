import argparse
import sys
import os

parser = argparse.ArgumentParser(description='')
parser.add_argument('directory')
parser.add_argument(
        "-t", "--tests",
        type=str,
        nargs='*',
        help='')

args = parser.parse_args()

subset_sum_main = os.path.join(
        "install",
        "bin",
        "subsetsumsolver")
subset_sum_data = os.environ['SUBSET_SUM_DATA']


if args.tests is None or "subset-sum-dynamic-programming-bellman-word-ram-rec" in args.tests:
    print("Subset sum problem / dynamic programming - Bellman - word RAM - recursive scheme")
    print("--------------------------------------------------------------------------------")
    print()

    data = [
            (os.path.join("pthree", "pthree_1000_1"), "")]
    for instance, instance_format in data:
        instance_path = os.path.join(subset_sum_data, instance)
        json_output_path = os.path.join(
                args.directory,
                "subset_sum",
                instance)
        if not os.path.exists(os.path.dirname(json_output_path)):
            os.makedirs(os.path.dirname(json_output_path))
        command = (
                subset_sum_main
                + "  --verbosity-level 1"
                + "  --input \"" + instance_path + "\""
                + " --format \"" + instance_format + "\""
                + "  --algorithm dynamic-programming-bellman-word-ram-rec"
                + "  --output \"" + json_output_path + "\"")
        print(command)
        status = os.system(command)
        if status != 0:
            sys.exit(1)
        print()
    print()
    print()
