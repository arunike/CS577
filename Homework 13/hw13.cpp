#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

struct clause {
    int literal1, literal2, literal3;
};

vector<clause> processInput(int numClauses) {
    vector<clause> clauses;
    string temp;

    for (int i = 0; i < numClauses; ++i) {
        int v1, v2, v3;
        cin >> v1 >> v2 >> v3;
        clause clause = {v1, v2, v3};
        clauses.push_back(clause);
    }

    return clauses;
}

inline int sign(int x) {
    return (x > 0) ? 1 : -1;
}

bool verifySolution(const vector<clause>& clauses, const vector<int>& solution) {
    int satisfiedClauses = 0;

    for (size_t i = 0; i < clauses.size(); ++i) {
        const clause& clause = clauses[i];
        if ((sign(clause.literal1) == solution[abs(clause.literal1) - 1]) ||
            (sign(clause.literal2) == solution[abs(clause.literal2) - 1]) ||
            (sign(clause.literal3) == solution[abs(clause.literal3) - 1])) {
            satisfiedClauses++;
        }
    }

    return (satisfiedClauses * 8 >= clauses.size() * 7);
}

int main() {
    int numVariables, numClauses;
    cin >> numVariables >> numClauses;

    vector<clause> clauses = processInput(numClauses);

    vector<int> solution(numVariables);
    srand(static_cast<unsigned>(time(NULL)));

    do {
        for (int i = 0; i < numVariables; ++i) {
            solution[i] = (rand() % 2) * 2 - 1;
        }
    } while (!verifySolution(clauses, solution));

    for (int i = 0; i < numVariables; ++i) {
        cout << solution[i] << " ";
    }
    cout << endl;

    return 0;
}