#include <bits/stdc++.h>
using namespace std;
class Cau_1{
private:
    vector<int> nums;

    vector<int> longestLen(){
        vector<int>L(nums.size(),1);
        vector<int>prev(nums.size(),-1);

        int longest = 1;
        int maxIdx = 0;

        for(int i = 1 ;  i < nums.size();i++){
            for(int j = 0 ; j < i ; j++){
                if(nums[i] > nums[j]){
                    if(L[i] < L[j] +1){
                        L[i] = L[j]+1;
                        prev[i]=j;
                    }
                }
            }

            if(longest < L[i]){
                longest = L[i];
                maxIdx = i;
            }
        }

        vector<int> ans;
        int k = maxIdx;
        while(k != -1){
            ans.push_back(nums[k]);
            k = prev[k];
        }
        reverse(ans.begin(),ans.end());
        
        return ans;
    }
public:
    void solve(vector<int> vec){
        this->nums = vec;

        for(auto n : longestLen()){
            cout<<n<<" ";
        }
    }
};

class Cau_2{
private:
    int MaxSum(vector<int> nums){
        vector<int> dp (nums.size()+1);
        if (nums.size() == 0) {
            return 0; 
        }
        if (nums.size() == 1) {
            return nums[0]; 
        }
        dp[0]= nums[0];
        dp[1] =max(nums[0],nums[1]);
        for(int i = 2;  i < nums.size(); i++){
                dp[i] =  max(dp[i-1],dp[i-2]+nums[i]);
        }
        
        return dp[nums.size()-1];
    }
public: 
    void solve(vector<int> vec){
        cout<<MaxSum(vec);
    }
};

class Cau_3{
private:
    int n;
    int k;

    long long cal(){
        vector<vector<long long>> dp(n + 1  ,vector<long long>(k+1,0));

        for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        }

        for(int i = 1 ;  i<= n ; i++){
            for(int j = 1 ; j<= min(i,k);j++){
                dp[i][j] = dp[i-1][j] + j * dp[i-1][j-1];
            }
        }

        return dp[n][k];
    }
public:
    void solve(int N, int K){
        if(K < 0 || K > N){
            return;
        }
        this->n = N;
        this->k = K;
        
        cout<<cal();
    }
};

class Cau_4 {
private:
    string s1, s2;
    vector<vector<int>> dp;
    int n1, n2; 

    int maxLen() {
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n1][n2];
    }

public:
    void solve(string str1, string str2) {
        if (str1.empty() || str2.empty()) {
            cout << "Mang rong" << endl;
            return;
        }

        this->s1 = str1;
        this->s2 = str2;

        this->n1 = s1.length();
        this->n2 = s2.length();

        dp.resize(n1 + 1, vector<int>(n2 + 1, 0));

        
        cout << "" << maxLen() << endl;
    }
};

class Cau_5{
private:
    string s1, s2,s3;
    vector<vector<vector<int>>> dp;
    int n1, n2, n3; 

    int maxLen() {
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                for(int k = 1; k <= n3;k++){
                    if (s1[i - 1] == s2[j - 1] && s3[k-1] == s2[j-1]) {
                        dp[i][j][k] = dp[i - 1][j - 1][k-1] + 1;
                    } else {
                        dp[i][j][k] = max({ dp[i - 1][j][k],
                                            dp[i][j - 1][k],
                                            dp[i][j][k - 1]
                                        });
                    }
                }
            }
        }

        return dp[n1][n2][n3];
    }
    string findLCS() {
        string lcs_str = "";
        int i = n1, j = n2, k = n3;

        while (i > 0 && j > 0 && k > 0) {
            if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
                lcs_str += s1[i - 1];
                i--; j--; k--;
            }
            else {
                int max_val = dp[i][j][k];

                if (dp[i - 1][j][k] == max_val) {
                    i--;
                } else if (dp[i][j - 1][k] == max_val) {
                    j--;
                } else {
                    k--;
                }
            }
        }
        
        reverse(lcs_str.begin(), lcs_str.end());
        return lcs_str;
    }

public:
    void solve(string str1, string str2, string str3) {
        if (str1.empty() || str2.empty()) {
            cout << "Mang rong" << endl;
            return;
        }

        this->s1 = str1;
        this->s2 = str2;
        this->s3 = str3;

        this->n1 = s1.length();
        this->n2 = s2.length();
        this->n3 = s3.length();

        dp.resize(n1 + 1, vector<vector<int>>(n2 + 1,vector<int>(n3+1,0)));

        maxLen();
        cout << "" << findLCS() << endl;
    }
};

class Cau_6{
    private:
        vector<int> nums;

        void findMaxSubarray(){
            int n = nums.size();
            if (n == 0) {
                return;
            }

            int res = nums[0];
            int cur = nums[0];
            
            int max_start = 0;
            int max_end = 0;
            int cur_start = 0;

            for (int i = 1; i < n; i++) {
                
                if (nums[i] > cur + nums[i]) {
                    cur = nums[i];
                    cur_start = i;
                } else {
                    cur = cur + nums[i];
                }

                if (cur > res) {
                    res = cur;
                    max_start = cur_start;
                    max_end = i;
                }
                
            }
            for (int i = max_start; i <= max_end; i++) {
                    cout << nums[i] << " ";
                }
        }
    public:
    void solve(vector<int> vec){
        this->nums = vec;
        
        findMaxSubarray();
        
        return;
    }
};

class Cau_7 {
private:
    vector<int> pack;
    vector<int> S1_packets;
    vector<int> S2_packets;
    long long S1_sum = 0;
    long long S2_sum = 0;

    void Split() {
        S1_packets.clear();
        S2_packets.clear();
        S1_sum = 0;
        S2_sum = 0;

        long long S = 0;
        for (int candy : pack) {
            S += candy;
        }
        long long target = S / 2;
        int n = pack.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {
            int current_candy = pack[i - 1];
            
            for (long long j = 1; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];

                if (j >= current_candy) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - current_candy];
                }
            }
        }

        for (long long j = target; j >= 0; j--) {
            if (dp[n][j]) {
                S1_sum = j;
                break;
            }
        }

        S2_sum = S - S1_sum;

        long long current_sum = S1_sum;
        for (int i = n; i > 0; i--) {
            int current_candy = pack[i - 1];

            if (dp[i - 1][current_sum]) {
                S2_packets.push_back(current_candy);
            }
            else if (current_sum >= current_candy && dp[i - 1][current_sum - current_candy]) {
                S1_packets.push_back(current_candy);
                current_sum -= current_candy;
            }
            else {
                S2_packets.push_back(current_candy);
            }
        }
    }

public:
    void solve(vector<int> vec) {
        this->pack = vec;
        Split();

        cout << "Phan 1 : ";
        for (int p : S1_packets) cout << p << " ";
        cout << endl;

        cout << "Phan 2 : ";
        for (int p : S2_packets) cout << p << " ";
        cout << endl;
        
    }
};

int main(){
    Cau_7 sol;
    sol.solve({1,2,3,4,5,15});

    return 0;

}