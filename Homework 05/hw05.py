class CountInversion:
    def __init__(self, arr):
        self.array = arr

    def mergeCount(self, start, mid, end):
        temp = [0] * (end-start+1)
        i, j, k, inv_count = start, mid + 1, 0, 0

        while i <= mid and j <= end:
            if self.array[i] <= self.array[j]:
                temp[k] = self.array[i]
                i += 1
            else:
                temp[k] = self.array[j]
                j += 1
                inv_count += (mid - i + 1)
            k += 1

        while i <= mid:
            temp[k] = self.array[i]
            i += 1
            k += 1

        while j <= end:
            temp[k] = self.array[j]
            j += 1
            k += 1

        for i in range(len(temp)):
            self.array[start + i] = temp[i]

        return inv_count

    def countSort(self, start, end):
        if start >= end:
            return 0
        
        mid = (start + end) // 2
        left_inv = self.countSort(start, mid)
        right_inv = self.countSort(mid + 1, end)
        merge_inv = self.mergeCount(start, mid, end)

        return left_inv + right_inv + merge_inv
    
    def getCount(self):
        return self.countSort(0, len(self.array) - 1)


def main():
    num_tests = int(input())
    results = []

    for _ in range(num_tests):
        _ = int(input())
        array = list(map(float, input().split()))
        inv_counter = CountInversion(array)
        results.append(inv_counter.getCount())
        
    for result in results:
        print(result)

if __name__ == "__main__":
    main()