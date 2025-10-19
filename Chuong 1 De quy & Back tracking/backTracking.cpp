#include <bits/stdc++.h>
using namespace std;

class Cau_6{
public:
    vector<int>cur;
    vector<int> N;
    int k;

    void printArr(){
        sort(cur.begin(), cur.end());
        cout<<"{ ";
        for(int i = 0;  i < cur.size(); i++){
            cout<< cur[i] << (i == cur.size() -1 ? "" : ", " );
        }
        cout<<" } \n";
    }

    void findArr(int p){
        if(cur.size()==k){
            printArr();
            return;
        }

        for(int i =p ; i < N.size(); i++){
            cur.push_back(N[i]);

            findArr(i+1);
            cur.pop_back();
        }
    }
};

class Cau_7{
public:
    int N ;
    vector<int> cur;
    vector<bool> used ;

    void printArr(){
        cout<< "{ ";
        for(int i = 0 ; i < cur.size(); i++){
            cout<<cur[i] << (i == cur.size()-1 ? "":", ") ;
        }

        cout<<" }";
    }

    void findArr(){
        if(cur.size() == N){
            printArr();
            return;
        }

        for(int i = 1 ; i <= N; i++){
            if(!used[i]){
                used[i] = true;

                cur.push_back(i);
                
                findArr();
                used[i] = false;
                cur.pop_back();
            }
        }


    }
};

void Cau_8( string cur){
    if(cur.length() == 5){
        cout<<cur<<endl;
        return;
    }
    
    if(cur.empty() || cur.back() == '1'){
        Cau_8(cur+'1');
        Cau_8(cur+'0');
    }
    else Cau_8(cur+'1');
}

class Cau_9 {
private:
    int preSum;
    vector<int> cur;
    vector<int> A;
    int B;

    void printArray() {
        cout << "{ ";
        for (size_t i = 0; i < cur.size(); ++i) {
            cout << cur[i] << (i == cur.size() - 1 ? "" : ", ");
        }
        cout << " }\n";
    }

    void findArray(int idx) {
        if (preSum == B) {
            printArray();
            return;
        }
        if (preSum > B) {
            return;
        }

        for (size_t i = idx; i < A.size(); ++i) {
            if (preSum + A[i] > B) {
                break;
            }

            cur.push_back(A[i]);
            preSum += A[i];
            
            findArray(i);
            
            preSum -= A[i];
            cur.pop_back();
        }
    }

public:
    Cau_9(const vector<int>& inputArray, int target) {
        A = inputArray;
        B = target;
        preSum = 0;
        sort(A.begin(), A.end());
    }

    void findArray() {
        findArray(0);
    }
};

struct val{
    vector<int> num;
    vector<char> ops;
    vector<bool> used;
};
class Cau_10 {
private:
    string s;
    string res;
    val be;
    val ae;
    
    //Xử lí dữ liệu
   void parseInput() {
        bool beforeEquals = true;
        string cur = "";
        string temp_s = this->s + " "; 

        for (size_t i = 0; i < temp_s.length(); ++i) {
        char c = temp_s[i];

        if (isdigit(c)) {
            cur += c;
        } else {
            if (!cur.empty()) {
                int number = stoi(cur);
                if (beforeEquals) {
                    be.num.push_back(number);
                } else {
                    ae.num.push_back(number);
                }
                cur = ""; 
            }

            if (c == '(') {
                while (i < temp_s.length() && temp_s[i] != ')') {
                    i++;
                }
            }
            
            if (c == '=') {
                beforeEquals = false;
            }
        }
    }
        
        be.used.assign(be.num.size(), false);
        ae.used.assign(ae.num.size(), false);
    }

    map<double, string> lhs_results;
    char operators[4] = {'+','-','*','/'};

    //Tạo các kết quả khả thi của vế trái
    void generateLHS(int k , vector<int>& p_nums, vector<char>& p_ops){
        if(k == be.num.size()){
            double cur_val = p_nums[0];
            string expr_str = to_string(p_nums[0]);

            for(int i = 0 ; i < p_ops.size(); i++){
                expr_str += " " + string(1, p_ops[i]) + " " + to_string(p_nums[i+1]);

                switch (p_ops[i])
                {
                    case '+': cur_val += p_nums[i+1]; break;
                    case '-': cur_val -= p_nums[i+1]; break;
                    case '*': cur_val *= p_nums[i+1]; break;
                    case '/': 
                        if (p_nums[i+1] == 0) return; 
                        cur_val /= p_nums[i+1]; 
                        break;
                }
            }

            lhs_results[cur_val] = expr_str;
            return;
        }

        for(int i = 0 ; i < 4;++i){
            p_ops.push_back(operators[i]);
            generateLHS(k+1, p_nums, p_ops);
            p_ops.pop_back();
        }
    }

    //Tìm biểu thức cho vế phải từ kết quả của vế trái
    bool backTrackRHS(double target, int k, vector<int>& p_nums, vector<char>& p_ops){
        if(k == ae.num.size()){
            double cur_val = p_nums[0];
            string expr_str = to_string(p_nums[0]);

            for(int i = 0 ; i < p_ops.size(); i++){
                expr_str += " " + string(1, p_ops[i]) + " " + to_string(p_nums[i+1]);

                switch (p_ops[i])
                {
                    case '+': cur_val += p_nums[i+1]; break;
                    case '-': cur_val -= p_nums[i+1]; break;
                    case '*': cur_val *= p_nums[i+1]; break;
                    case '/': 
                        if (p_nums[i+1] == 0) return false; 
                        cur_val /= p_nums[i+1]; 
                        break;
                }
            }

            //Nếu tìm thấy giá trị trùng khớp
            if(abs(cur_val - target) < 1e-9){
                res = to_string(p_nums[0]);
                for(int i = 0 ;  i< p_ops.size(); i++){
                    res += " " + string(1, p_ops[i]) + " " + to_string(p_nums[i+1]);
                }

                return true;
            }

            return false;
        }

        for(int i =0; i < 4; i++){
            p_ops.push_back(operators[i]);
            if(backTrackRHS(target,k +1, p_nums, p_ops)) return true;
            p_ops.pop_back();
        }

        return false;
    }
public:
    Cau_10(string input_s) {
        this->s = input_s;
    }

    void solve() {
        parseInput();
        vector<int> p_be_nums;
        function<void(void)> permuteLHS = [&]() {
            if (p_be_nums.size() == be.num.size()) {
                vector<char> p_ops;
                generateLHS(1, p_be_nums, p_ops);
                return;
            }
            for (size_t i = 0; i < be.num.size(); ++i) {
                if (!be.used[i]) {
                    be.used[i] = true;
                    p_be_nums.push_back(be.num[i]);
                    permuteLHS();
                    p_be_nums.pop_back();
                    be.used[i] = false;
                }
            }
        };
        permuteLHS();
        bool done = false;
        vector<int> p_ae_nums;
        
        function<bool(double)> solTarget = [&](double target) {
            vector<char> p_ops;
            return backTrackRHS(target, 1, p_ae_nums, p_ops);
        };

        function<void(void)> permuteRHS = [&]() {
            if (p_ae_nums.size() == ae.num.size()) {
                for (auto const& [val, expr] : lhs_results) {
                    if (solTarget(val)) {
                        cout << "Ket qua: " << expr << " = " << res << endl;
                        done = true;
                    }
                }
                return;
            }
             for (size_t i = 0; i < ae.num.size(); ++i) {
                if (!ae.used[i]) {
                    ae.used[i] = true;
                    p_ae_nums.push_back(ae.num[i]);
                    permuteRHS();
                    p_ae_nums.pop_back();
                    ae.used[i] = false;
                }
            }
        };

        permuteRHS();

        if (!done) {
            cout << "Khong tim thay loi giai." << endl;
        }
    }

};



int main() {
    string s = "1 (x1) 2 (x2) 3 (x3) 4 = 1";
    Cau_10 sol(s);
    sol.solve();

    return 0;
}