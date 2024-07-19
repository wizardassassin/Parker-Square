import re

files = [
    "../results/aggregated_00_05mil.txt",
    "../results/aggregated_05_10mil.txt",
    "../results/aggregated_10_15mil.txt",
    "../results/aggregated_15_20mil.txt",
    "../results/aggregated_20_25mil.txt",
    "../results/aggregated_25_30mil.txt",
    "../results/aggregated_30_35mil.txt",
    "../results/aggregated_35_40mil.txt",
    "../results/aggregated_40_45mil.txt",
    "../results/aggregated_45_50mil.txt"
]

vals = set()


def parse_line(line: str):
    a = re.search("^\\d+\\((\\d+), (\\d+)\\) .+$", line)
    assert a is not None
    val1 = a.group(1)
    val2 = a.group(2)
    val3 = int(val1) ** 2 + int(val2) ** 2
    assert val3 not in vals
    vals.add(val3)


for file_path in files:
    print(file_path)
    with open(file_path, "r") as file:
        for line in file:
            parse_line(line)
