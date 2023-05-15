# The Quick Sort Algorithm

arr = [3, -2, -1, 0, 2, 4, 1]

# sorted in ascending order
# [-2, -1, 0, 1, 2, 3, 4]


def qs(arr, l, r):
    if l >= r:
        return

    pivot = arr[r]
    i = l
    j = r - 1

    while i <= j:
        if arr[i] <= pivot:
            i += 1
        elif arr[j] > pivot:
            j -= 1
        else:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
            j -= 1

    arr[i], arr[r] = arr[r], arr[i]

    qs(arr, l, i - 1)
    qs(arr, i + 1, r)
