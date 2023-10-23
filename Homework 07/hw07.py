def latestJob(jobs, currentIndex):
    start, end = 0, currentIndex - 1

    while start <= end:
        mid = (start + end) // 2

        if jobs[mid][1] <= jobs[currentIndex][0]:
            if mid == currentIndex - 1 or jobs[mid + 1][1] > jobs[currentIndex][0]:
                return mid
            
            start = mid + 1
        else:
            end = mid - 1

    return -1

def MaxScheduleWeight(jobs):
    jobs.sort(key = lambda x: x[1])
    
    numJobs = len(jobs)
    maxWeights = [0] * numJobs
    maxWeights[0] = jobs[0][2]

    for index in range(1, numJobs):
        includedWeight = jobs[index][2]

        nonConflictIndex = latestJob(jobs, index)
        
        if nonConflictIndex != -1:
            includedWeight += maxWeights[nonConflictIndex]
        
        maxWeights[index] = max(includedWeight, maxWeights[index - 1])

    return maxWeights[-1]

def main():
    numInput = int(input())
    results = []

    for _ in range(numInput):
        numJobs = int(input())
        jobs = [list(map(int, input().split())) for _ in range(numJobs)]
        results.append(MaxScheduleWeight(jobs))

    for result in results:
        print(result)

if __name__ == "__main__":
    main()
