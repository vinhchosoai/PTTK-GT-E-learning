#include <bits/stdc++.h>
using namespace std;

//Câu 1
string decToBin(int n){
    if(n <=1){
        return to_string(n);
    }

    return decToBin(n/2) + to_string(n%2);
}

//Câu 2
string rsv(string s){
    if(s.empty()){
        return "";
    }
    string nxt = "";
    
    for(int i = 0 ; i < s.length()-1; i++){
        nxt += s[i];
    }

    char c = s.back();
    return c + rsv(nxt);
}

//Câu 3 
int sumOfN (int n ){
    if(n <= 0)
        return n ;
    return n%10 + sumOfN(n/10);
}

//Câu 4
bool isSymmetry(vector<int> vec){
    if(vec.size() <=1 )
        return true;
    if(vec.front() != vec.back()){
        return false;
    }

    vector<int> nxt(vec.begin() +1, vec.end()-1);

    return isSymmetry(nxt);
}

//Câu 5 
void thapHaNoi(int n , char A, char B, char C){
    if( n == 1){
        cout<<"Chuyen 1 dia tu "<< A <<"-->"<<C<<endl;
        return;
    }

    thapHaNoi(n-1,A,C,B);

    cout<<"Chuyen dia " << n-1  <<" tu " <<A <<"-->"<<C<<endl;
    thapHaNoi(n-1,B,A,C);
}
int main (){
    int soDia =5;
    thapHaNoi(soDia,'A','B','C');

    return 0;
}