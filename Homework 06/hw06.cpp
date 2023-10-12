#include <iostream>
#include <algorithm>

using namespace std;

struct ConnectedPoints {
    int topLineVal;
    int bottomLineVal;
};

long long intersectionCounter = 0;

bool SortTopLine(const ConnectedPoints& a, const ConnectedPoints& b) {
    return a.topLineVal < b.topLineVal;
}

void Merge(ConnectedPoints* frontHalf, int fhLength, ConnectedPoints* backHalf, int bhLength, ConnectedPoints* result) {
    int fhCounter = 0, bhCounter = 0, mergedIndex = 0;

    while (fhCounter < fhLength || bhCounter < bhLength) {
        if (bhCounter == bhLength || (fhCounter < fhLength && frontHalf[fhCounter].bottomLineVal <= backHalf[bhCounter].bottomLineVal)) {
            result[mergedIndex++] = frontHalf[fhCounter++];
        } else {
            result[mergedIndex++] = backHalf[bhCounter++];
            intersectionCounter += fhLength - fhCounter;
        }
    }
}

void MergeSort(ConnectedPoints* toSort, int length) {
    if (length == 1) {
        return;
    }

    int halfLength = length / 2;

    ConnectedPoints frontHalf[halfLength];
    ConnectedPoints backHalf[length - halfLength];

    copy(toSort, toSort + halfLength, frontHalf);
    copy(toSort + halfLength, toSort + length, backHalf);

    MergeSort(frontHalf, halfLength);
    MergeSort(backHalf, length - halfLength);

    Merge(frontHalf, halfLength, backHalf, length - halfLength, toSort);
}

int main() {
    int numInstances;

    cin >> numInstances;

    for (int i = 0; i < numInstances; i++) {
        int numPairs;

        cin >> numPairs;

        ConnectedPoints lines[numPairs];

        for (int j = 0; j < numPairs; j++) {
            cin >> lines[j].topLineVal;
        }

        for (int j = 0; j < numPairs; j++) {
            cin >> lines[j].bottomLineVal;
        }

        sort(lines, lines + numPairs, SortTopLine);

        MergeSort(lines, numPairs);

        cout << intersectionCounter << endl;
        
        intersectionCounter = 0;
    }

    return 0;
}
