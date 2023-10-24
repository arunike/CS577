#include <iostream>
#include <vector>

using namespace std;

struct Knapsack {
    int numItems;
    int weightCapacity;
    vector<pair<int, int> > items;
    vector<vector<int> > m;
};

void initializeKnapsack(Knapsack &k, int numItems, int weightCapacity) {
    k.numItems = numItems;
    k.weightCapacity = weightCapacity;
    k.items.resize(numItems + 1);
    k.m.resize(numItems + 1, vector<int>(weightCapacity + 1, 0));
}

void addItem(Knapsack &k, int weight, int value) {
    for (int i = 1; i < k.items.size(); ++i) {
        if (k.items[i].first == 0 && k.items[i].second == 0) {
            k.items[i] = make_pair(weight, value);
            break;
        }
    }
}

int getMaxValue(const Knapsack &k) {
    vector<vector<int> > m = k.m;
    for (int i = 1; i <= k.numItems; ++i) {
        for (int w = 1; w <= k.weightCapacity; ++w) {
            if (k.items[i].first > w) {
                m[i][w] = m[i - 1][w];
            } else {
                m[i][w] = max(m[i - 1][w], k.items[i].second + m[i - 1][w - k.items[i].first]);
            }
        }
    }
    return m[k.numItems][k.weightCapacity];
}

vector<Knapsack> parse_input() {
    int numInstances;
    cin >> numInstances;

    vector<Knapsack> instances(numInstances);
    for (int i = 0; i < numInstances; ++i) {
        int numItems, weightCapacity;
        cin >> numItems >> weightCapacity;

        initializeKnapsack(instances[i], numItems, weightCapacity);
        for (int j = 0; j < numItems; ++j) {
            int weight, value;
            cin >> weight >> value;
            addItem(instances[i], weight, value);
        }
    }
    return instances;
}

int main() {
    try {
        vector<Knapsack> instances = parse_input();
        for (size_t i = 0; i < instances.size(); ++i) {
            cout << getMaxValue(instances[i]) << endl;
        }
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}
