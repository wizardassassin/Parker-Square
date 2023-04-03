from multiprocessing.pool import ThreadPool


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
interval = 100


def calc(start: int, stop: int):
    for i in range(start, stop):
        for j in range(i + 1, max_val):
            a = i**2+j**2
            if a not in dict:
                dict[a] = []
            dict[a].append((i**2, j**2))


threads = 8

pool = ThreadPool(processes=threads)

wait_arr = []
for i in range(0, max_val, interval):
    res = pool.apply_async(calc, args=(i, i + interval))
    wait_arr.append(res)

for v in wait_arr:
    v.wait()

for k in dict:
    arr = dict[k]
    if len(arr) < 4:
        continue
    res = pool.apply_async(compute, args=(arr, ))
    wait_arr.append(res)

for v in wait_arr:
    v.wait()
