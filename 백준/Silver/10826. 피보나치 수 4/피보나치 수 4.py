n = int(input())

if n == 0:
    print(0)
else:
    old, new = 1, 1
    for _ in range(n - 2):
        old, new = new, old + new
    print(new)
