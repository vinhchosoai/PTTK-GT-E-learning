#include <bits/stdc++.h>   
using namespace std;

class Cau_1{
private:
    vector<int> nums;

    long long calculateMaxWeightedSum() {
        sort(nums.begin(), nums.end());

        long long maxSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            maxSum += (long long)nums[i] * i;
        }
        return maxSum;
    }

public:
    void solve(vector<int> vec) {
        this->nums = vec;
        
        cout << calculateMaxWeightedSum() << endl;
    }
};

class Cau_2 {
private:

    vector<int> nums;

    long long buildMinSum() {
        sort(nums.begin(), nums.end());

        string s1 = "";
        string s2 = "";

        for (int i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) {
                s1 += to_string(nums[i]);
            } else {
                s2 += to_string(nums[i]);
            }
        }

        long long num1 = stoll(s1);
        long long num2 = stoll(s2);

        return num1 + num2;
    }

public:
    void solve(vector<int> vec) {
        if(vec.empty()){
            cout<<0;
            return;
        }
        this->nums = vec;

        cout << buildMinSum() << endl;
    }
};

class Cau_3 {
private:
    int A; 
    int B; 
    int C; 

    int findMinShoppingDays() {
        long long stock = 0;
        int trips = 0;

        for (int day = 1; day <= 1000000; ++day) {
            int day_of_week = (day - 1) % 7; 

            if (day_of_week != 6) { 
                stock += A;
                trips++;
            }

            if (stock >= B) {
                return trips;
            }

            stock -= C;

            if (stock < 0) {
                return -1;
            }
        }
        
        return -1; 
    }

public:
    void solve(int a, int b, int c) {
        this->A = a;
        this->B = b;
        this->C = c;
        
        cout << findMinShoppingDays() << endl;
    }
};

class Cau_4 {
private:
    string S;

    bool canRearrange() {
        map<char, int> freq;
        for (char c : this->S) {
            freq[c]++;
        }

        int max_freq = 0;
        for (auto const& pair : freq) {
            if (pair.second > max_freq) {
                max_freq = pair.second;
            }
        }

        int N = this->S.length();

        if (max_freq > (N + 1) / 2) {
            return false;
        }
        
        return true;
    }

public:
    void solve(string s) {
        this->S = s;
        if (canRearrange()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
};

class Cau_5 {
private:
    vector<int> coins;
    int T;
    int findMinCoinsUsingGreedy() {
        sort(coins.rbegin(), coins.rend());
        
        int count = 0;
        int remaining = this->T;

        for (int coin : coins) {
            if (remaining == 0) break;
            
            count += remaining / coin;
            remaining = remaining % coin;
        }

        if (remaining != 0) {
            return -1; 
        }
        return count;
    }
    int findMinCoinsUsingDP() {
        vector<int> dp(T + 1, T + 1);
        
        dp[0] = 0;

        for (int i = 1; i <= T; ++i) {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != T + 1) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        if (dp[T] == T + 1) {
            return -1; 
        }
        return dp[T];
    }
};
struct Item {
    int id;
    int weight;
    int value;
    double ratio;

    Item(int i, int w, int v) : id(i), weight(w), value(v) {
        ratio = (double)value / weight;
    }
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}
class Knapsack_Greedy {
private:
    vector<int> wt;
    vector<int> val;
    int W;
    int N;

    int solveGreedy() {
        vector<Item> items;
        for (int i = 0; i < N; ++i) {
            items.push_back(Item(i, wt[i], val[i]));
        }

        sort(items.begin(), items.end(), compareItems);

        int currentWeight = 0;
        int currentValue = 0;

        for (int i = 0; i < N; ++i) {
            if (currentWeight + items[i].weight <= this->W) {
                currentWeight += items[i].weight;
                currentValue += items[i].value;
            }
        }
        return currentValue;
    }

public:
    void solve(vector<int> weights, vector<int> values, int capacity) {
        this->wt = weights;
        this->val = values;
        this->W = capacity;
        this->N = weights.size();
        
        cout << solveGreedy() << endl;
    }
};
class Cau_Knapsack_DP {
private:
    vector<int> wt;
    vector<int> val;
    int W;
    int N;

    int solveDP() {
        vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= W; ++j) {
                
                dp[i][j] = dp[i - 1][j];

                if (j >= wt[i - 1]) {
                    dp[i][j] = max(dp[i][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
                }
            }
        }
        return dp[N][W];
    }

public:
    void solve(vector<int> weights, vector<int> values, int capacity) {
        this->wt = weights;
        this->val = values;
        this->W = capacity;
        this->N = weights.size();
        
        cout << solveDP() << endl;
    }
};

struct ItemBB {
    int weight;
    int value;
    double ratio;

    ItemBB(int w, int v) : weight(w), value(v) {
        ratio = (double)value / weight;
    }
};

bool compareItemsBB(const ItemBB& a, const ItemBB& b) {
    return a.ratio > b.ratio;
}

class Cau_Knapsack_BB {
private:
    vector<ItemBB> items;
    int W;
    int N;
    int bestValue;

    double calculateBound(int index, int currentWeight, int currentValue) {
        double bound = currentValue;
        int remainingWeight = W - currentWeight;
        int i = index;

        while (i < N && items[i].weight <= remainingWeight) {
            remainingWeight -= items[i].weight;
            bound += items[i].value;
            i++;
        }

        if (i < N) {
            bound += items[i].ratio * remainingWeight;
        }

        return bound;
    }

    void backtrack(int index, int currentWeight, int currentValue) {
        if (currentWeight > W) {
            return;
        }

        if (currentValue > bestValue) {
            bestValue = currentValue;
        }

        if (index == N) {
            return;
        }
        
        double bound = calculateBound(index, currentWeight, currentValue);
        if (bound <= bestValue) {
            return;
        }

        backtrack(index + 1, currentWeight + items[index].weight, currentValue + items[index].value);

        backtrack(index + 1, currentWeight, currentValue);
    }

public:
    void solve(vector<int> weights, vector<int> values, int capacity) {
        this->W = capacity;
        this->N = weights.size();
        this->bestValue = 0;
        this->items.clear();

        for (int i = 0; i < N; ++i) {
            this->items.push_back(ItemBB(weights[i], values[i]));
        }

        sort(items.begin(), items.end(), compareItemsBB);

        backtrack(0, 0, 0);
        
        cout << this->bestValue << endl;
    }
};
class Cau_TSP_Greedy {
private:
    int N;
    vector<vector<int>> graph;

    int solveGreedy() {
        vector<bool> visited(N, false);
        int currentCity = 0;
        visited[currentCity] = true;
        
        int totalCost = 0;
        int citiesVisited = 1;

        while (citiesVisited < N) {
            int nearestNeighbor = -1;
            int minCost = INT_MAX;

            for (int i = 0; i < N; ++i) {
                if (!visited[i] && graph[currentCity][i] > 0 && graph[currentCity][i] < minCost) {
                    minCost = graph[currentCity][i];
                    nearestNeighbor = i;
                }
            }

            if (nearestNeighbor != -1) {
                visited[nearestNeighbor] = true;
                totalCost += minCost;
                currentCity = nearestNeighbor;
                citiesVisited++;
            } else {
                break;
            }
        }

        totalCost += graph[currentCity][0]; 
        
        return totalCost;
    }

public:
    void solve(vector<vector<int>> g) {
        this->graph = g;
        this->N = g.size();
        
        cout << solveGreedy() << endl;
    }
};
class Cau_TSP_BB {
private:
    int N;
    vector<vector<int>> graph;
    vector<bool> visited;
    int bestCost;

    void backtrack(int currentCity, int count, int currentCost) {
        if (currentCost >= bestCost) {
            return;
        }

        if (count == N) {
            int costToStart = graph[currentCity][0];
            if (costToStart > 0) {
                bestCost = min(bestCost, currentCost + costToStart);
            }
            return;
        }

        for (int i = 0; i < N; ++i) {
            if (!visited[i] && graph[currentCity][i] > 0) {
                visited[i] = true;
                backtrack(i, count + 1, currentCost + graph[currentCity][i]);
                visited[i] = false; 
            }
        }
    }

    int solveBB() {
        this->visited.assign(N, false);
        this->bestCost = INT_MAX;

        visited[0] = true;
        backtrack(0, 1, 0);

        return bestCost;
    }

public:
    void solve(vector<vector<int>> g) {
        this->graph = g;
        this->N = g.size();
        
        cout << solveBB() << endl;
    }
};
int main(){
    Cau_4 sol;

    sol.solve("AAABBC");

    return 0;
}