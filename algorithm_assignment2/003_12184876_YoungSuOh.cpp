#include<iostream>
#include<vector>
#define MAX 100000000
#define endl "\n"
using namespace std;
int matrixNum, num;
int mod(int x, int y) { 
    return ((x*x) + (y*y)) % num;
}
int cal_Result(vector<vector<int>>& s, int start, int end) { 
    if (start == end) {      
        return start;
    }
    else {        
        int num1= cal_Result(s, start, s[start][end]); 
        int num2= cal_Result(s, s[start][end]+1, end); 
        return mod(num1, num2); 
    }        
}
int computeOptimalCost(vector<vector<int>>&m,vector<int>&p, vector<vector<int>>& s) {  
    for (int l = 2; l <= matrixNum; l++) {                                           
        for (int i = 1; i <= matrixNum - l + 1;i++) {                                
            int j = i + l - 1;                                                         
            m[i][j] = MAX;             
            for (int k = i;k<=j-1;k++) { 
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]); 
                if (q < m[i][j]) { 
                    m[i][j] = q;
                    s[i][j] = k; 
                }
            }
        }
    }
    return m[1][matrixNum]; 
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    int testCase, num1, i; 
    cin >> testCase;
    while (testCase--) {
        vector<int>vec;                
        cin >> matrixNum >> num;        
        vector<vector<int>>s(matrixNum + 1, vector<int>(matrixNum + 1)); 
        vector<vector<int>>m(matrixNum+1, vector<int>(matrixNum+1)); 
        for (i = 0; i < matrixNum + 1; i++) { 
            cin >> num1;
            vec.push_back(num1); 
        }
        cout<<computeOptimalCost(m,vec,s)<<endl;
        cout << cal_Result(s, 1, matrixNum) << endl; 
    }
    return 0;
}
