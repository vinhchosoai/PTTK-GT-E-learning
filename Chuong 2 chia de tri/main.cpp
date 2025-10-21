#include <bits/stdc++.h>
using namespace std;

class Cau_1{
private:
    vector<int> num;
    void Print(){
        for(auto n : num){
            cout<<n<<" ";
        }
    }

    void merge ( int l , int m , int r){
        int n1 = m -l+1;
        int n2 = r-m;

        vector<int> L(n1);
        vector<int> R(n2);

        for(int i = 0 ; i < n1;i++){
            L[i] = num[l+i];
        }
        
        for(int i = 0 ; i < n2;i++){
            R[i] = num[m+1+i];
        }

        int i = 0; 
        int j = 0;
        int k = l;

        while(i < n1 && j < n2){
            if(L[i] <= R[j]){
                num[k] = L[i];
                i++;
            }
            else {
                num[k] = R[j];
                j++;
            }
            k++;
        }

        while(i < n1){
            num[k] = L[i];
            i++;
            k++;
        }

        while(j < n2){
            num[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSort( int l, int r){
        if(l < r){
            int m = l + (r-l)/2;

            mergeSort(l,m);
            mergeSort(m + 1,r);

            merge(l,m,r);
        }else return;
    }
public:
    void solve(vector<int> vec){
        this->num = vec;
        mergeSort(0,num.size()-1);
        Print();
        
        return;
    }
};

class Cau_2{
private:
    vector<int> num;

    int partition(int low, int high){
        int pilot = num[high];
        int i = (low-1);

        for(int j = low; j < high;j++){
            if(num[j] <= pilot){
                i++;
                swap(num[j], num[i]);
            }
        }
        swap(num[i+1], num[high]);

        return (i+1);
    }

    void quickSort(int low, int high){
        if(low < high){
            int pi = partition(low,high);

            quickSort(low, pi-1);
            quickSort(pi+1, high);
        }
    }
public:

    void Print(){
        for(int n : num){
            cout<<n<<" ";
        }
    }

    void solve (vector<int> vec){
        this->num = vec;

        quickSort(0,num.size()-1);
        Print();
    }
};

class Cau_3{
private:
    vector<int> num;

    int findMin(int l, int r){
        if(l == r){
            return num[l];
        }    
        int m = l+(r-l)/2;

        return min(findMin(l,m),findMin(m+1,r));
        
    }
public:
    void Print(){
        cout<<findMin(0,num.size()-1);
    }

    void solve(vector<int> vec){
        this->num = vec;
        Print();
    }
};

class Cau_4{
private:
    vector<int> num;

    long long cal_sum(int l, int r){
        if(l == r){
            return num[l];
        }    
        int m = l+(r-l)/2;

        return (cal_sum(l,m)+cal_sum(m+1,r));
        
    }
public:
    void Print(){
        long long total = (cal_sum(0,num.size()-1));

        double res = static_cast<double>(total) / num.size();
        cout<<res;
    }

    void solve(vector<int> vec){
        this->num = vec;
        Print();
    }
};

class Cau_5{
private:
    struct res{
        int val;
        int idx;
    };
    int N;
    vector<int> num;

    void genRandomValue(){
        mt19937 gen(static_cast<unsigned int>(time(0)));
        uniform_int_distribution<> dis(-N/2,N/2 -1);

        for(int i =0 ; i < N;i++){
            num.push_back(dis(gen));
        }
    }

    bool isPrime(int n){
        if(n <= 1) return false;
        if(n == 2) return true;
        if(n % 2 == 0) return false;

        for(int i = 0 ; i*i <n;i++){
            if(n%i == 0) return false;
        }

        return true;
    }

    res FindPositive(int l, int r){
        if( l > r){
            return{-1,-1};
        }
        if(l == r){
            if(num[l] > 0){
                return {num[l],l};
            }
            else return{-1,-1};
        }
        int m = l + (r-l)/2;
        res leftRes = FindPositive(l,m);

        if(leftRes.idx != -1){
            return leftRes;
        }
        return FindPositive(m+1,r);
    }

    res FindPrime(int l ,int r){
        if(l > r){
            return {-1,-1};
        }
        if(l == r){
            if(isPrime(num[l]))
                return {num[l],l};
            else 
                return {-1,-1};
        }

        int m = l + (r-l)/2;

        res rightRes = FindPrime(m+1,l);
        if(rightRes.idx != -1){
            return rightRes;
        }
        return FindPrime(l,m);
    }
public:
    void Print(){
        cout<<"Mang duoc tao :";
        for(auto n : num){
            cout<<n<<" ";
        }
        cout<<endl;

        cout<<"So nguyen duong dau tien : "<<FindPositive(0,num.size()-1).val<<" tai vi tri : "<<FindPositive(0,num.size()-1).idx<<endl;
        cout<<"So nguyen to cuoi cung : "<<FindPrime(0,num.size()-1).val<<" tai vi tri : "<<FindPrime(0,num.size()-1).idx<<endl;
    }

    void solve(int n){
        this->N = n;
        genRandomValue();
        Print();
    }
};

class Cau_6{
private: 

    double power(double a ,int n){
        if(n == 0){
            return 1.0;
        }

        double temp = power(a,n/2);

        if(n%2 == 0) {
            return temp* temp;
        }else 
            return a * temp * temp;
    }
public:
    void solve(double a , int n){
        cout<<power(a,n);
    }
};

class Cau_7{
private:
    vector<int> num;
    int n,val;
    int k,x,y;

    int countEqualK(int l , int r){
        if(l == r){
            if(num[l] == k)
                return 1;
            else return 0;
        }

        int m = l+(r-l)/2;

        return countEqualK(l,m) + countEqualK(m+1,r); 
    }

    int countBetween(int l, int r){
        if(l == r){
            if(num[l] > x && num[l] < y)
                return 1;
            else return 0;
        }

        int m = l + (r-l)/2;

        return countBetween(l,m) + countBetween(m+1,r);
    }
public:
    void solve(){

        cout<<"Nhap so phan tu mang :";
        cin>>this->n;
        cout<<"Nhap gia tri mang :";
        for(int i = 0 ; i < n ;  i++){
            this->val = NULL;
            cin>>this->val;
            this->num.push_back(this->val);
        }

        cout<<"Mang da nhap : "<<endl;
        for(int n : num){
            cout<< n<< " ";
        }
        cout<<endl;

        cout<<"Nhap k: "<<endl;
        cin>>this->k;
        cout<<"So phan tu bang k :"<<countEqualK(0,num.size()-1)<<endl;

        cout<<"Nhap x va y :"<<endl;
        cin>>this->x>>this->y;
        cout<<"So phan tu lon hon x va nho hon y : "<<countBetween(0,num.size()-1);
    }
};

class Cau_8{
private: 
    vector<int> num;
    int k;

    int partition(int l, int r){
        int pivot = num[r];
        int i = l -1 ;

        for(int j =l ; j < r;j++){
            if(num[j] <= pivot ){
                i++;
                swap(num[j],num[i]);
            }
        }

        swap(num[i+1],num[r]);
        return i+1;
    }

    int quickSelect(int l , int r){
        if(l == r){
            return num[r];
        }

        int pi = partition(l,r);

        if(pi == k){
            return num[pi];
        }

        if(pi < k){
            return quickSelect(pi+1,r);
        }else return quickSelect(l,pi-1);
    }
public:
    void solve(vector<int> vec,int K){
        this->num = vec;
        this->k = vec.size()-K;

        cout<<quickSelect(0,num.size()-1);
    }
};
int main(){
    Cau_2 sol;

    sol.solve({3, 2, 1, 5, 6, 4});

    return 0;
}

