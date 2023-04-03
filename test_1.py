import math
from tqdm import tqdm


# def compute3(a: int, b: int, c: int, d: int, x: int, y: int):
#     v_1 = a + b - c - d
#     v_2 = v_1 == x - y
#     v_3 = v_1 == y - x
#     vert_1 = "0"
#     if v_2 and v_3:
#         vert_1 = "3"
#     elif v_2:
#         vert_1 = "1"
#     elif v_3:
#         vert_1 = "2"
#     h_1 = a + c - b - d
#     h_2 = h_1 == x - y
#     h_3 = h_1 == y - x
#     hori_1 = "0"
#     if h_2 and h_3:
#         hori_1 = "3"
#     elif h_2:
#         hori_1 = "1"
#     elif h_3:
#         hori_1 = "2"
#     return vert_1 + hori_1

def compute3(a: int, b: int, c: int, d: int, x: int, y: int):
    v_1 = a + b - c - d
    vert_1 = v_1 == x - y
    h_1 = a + c - b - d
    hori_1 = h_1 == x - y
    return str(int(vert_1)) + str(int(hori_1))


def compute(arr: list[tuple[int, int]]):
    arr_len = len(arr)
    for i in range(0, arr_len):
        for j in range(i + 1, arr_len):
            val1 = arr[i]
            val2 = arr[j]
            a, d = val1
            b, c = val2
            arr2 = arr.copy()
            arr2.remove(val1)
            arr2.remove(val2)
            arr2_len = len(arr2)
            arr3 = []
            for i2 in range(0, arr2_len):
                val3 = arr2[i2]
                x1, y1 = val3
                com1 = compute3(a, b, c, d, x1, y1)
                if com1 == "00":
                    continue
                arr3.append(val3 + (com1, ))
            if len(arr3) > 0:
                print(val1, val2, '|', ' '.join([str(v) for v in arr3]))


dict = {}
max_val = 5000
for i in tqdm(range(0, max_val)):
    for j in range(i + 1, max_val):
        a = i**2+j**2
        if a not in dict:
            dict[a] = []
        dict[a].append((i**2, j**2))

for k in tqdm(dict):
    arr = dict[k]
    if len(arr) < 4:
        continue
    compute(arr)
