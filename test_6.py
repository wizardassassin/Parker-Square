import math

lim = 30
max_lim = lim**2

print(lim, max_lim)

a = math.sqrt(max_lim / 2)
a2 = math.ceil(a)
print(a, a2)

print()

for i in range(a2, lim):
    i2 = math.sqrt(max_lim - i**2)
    i3 = math.ceil(i2)
    print(i, i2, i3)

print()

for i in range(0, lim):
    i2 = math.sqrt(max_lim - i**2)
    i3 = math.ceil(i2)
    if i > i3:
        print(i, i3)
    for j in range(i):
        t = i**2 + j**2
        if (t < max_lim):
            pass
        else:
            print(f"{i}^2 + {j}^2 = {t}")
            break
