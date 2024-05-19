def search(ls: list, target: int):
    l, r = 0, len(ls) - 1

    while l <= r:
        mid = (l + r) // 2

        if ls[mid] == target:
            print(mid)
            break
        elif ls[mid] < target:
            l = mid + 1
        else:
            r = mid - 1


ls = sorted([10, 4, 6, 2, 7, 5, 1, 6, 9, 3, 8])
print('LS', ls)

search(ls, 4)
