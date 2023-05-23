#include<iostream>
#include<vector>
#define MAX 100000000
#define endl "\n"
using namespace std;
int matrixNum, num;
int mod(int x, int y) { // 문제의 조건에 따른 모듈러 연산해주는 함수
    return ((x*x) + (y*y)) % num;
}
int cal_Result(vector<vector<int>>& s, int start, int end) { // 문제의 조건에 맞는 출력을 위한 함수를 구현했습니다. 행렬 곱셈순서를 고려하여 inorder방식으로 구현했습니다.
    if (start == end) { // leaf에 도착하면 start값을 return하도록 만들었습니다. end로 return해도 무관합니다.        
        return start;
    }
    else {        
        int num1= cal_Result(s, start, s[start][end]); // 트리의 왼쪽 자식쪽으로 leaf를 만날때까지 재귀적으로 들어가 줍니다. 이후 반환된 값을 임의의 변수 num1에 저장해줬습니다.
        int num2= cal_Result(s, s[start][end]+1, end); // 트리의 왼쪽 자식 순회가 끝났으면 오른쪽 자식쪽으로 leaf를 만날때까지 재귀적으로 들어가 줍니다. 이후 반환된 값을 임의의 변수 num2에 저장해줬습니다.
        return mod(num1, num2); // 두 자식의 순회가 모두 끝났으면 num1과 num2와 mod함수를 통해 값을 반환받고 부모 노드 쪽으로 반환된 값이 return 됩니다.
    }        
}
int computeOptimalCost(vector<vector<int>>&m,vector<int>&p, vector<vector<int>>& s) { // 강의 교재의 Matrix-Chain-Order를 바탕으로 구현한 함수입니다. 다른점은 강의교재에서는 주대각선을 0으로 초기화 해줬지만, 저는 2차원 vector를 사용하여 자동으로 0초기화 시켜 줬고, for문의 조건을 보면 주대각선과 그 밑부분은 사용하지 않게 구현했기에 굳이 넣지 않았습니다.  
    for (int l = 2; l <= matrixNum; l++) {                                            // (1)
        for (int i = 1; i <= matrixNum - l + 1;i++) {                                 // (2)
            int j = i + l - 1;                                                        // (3) -> (1), (2), (3) 번은 최소 연산의 횟수를 계산하기 위해 계산 순서를 계단식으로 만들기 위한 과정입니다.  
            m[i][j] = MAX;              // 최솟값을 찾기 위해 최소연산 횟수 계산하는 곳을 MAX로 설정했습니다. MAX로 설정해야 어떤 수가 들어오던 처음엔 무조건 초기화 되기 때문입니다.
            for (int k = i;k<=j-1;k++) { // 행렬곱이 현재 얼마나 되어있는지에 따라 반복해 줍니다. 예를 들어 현재 행렬곱이 A1A2A3 이 적용된 곳의 최소 연산 수를 확인하고 있다면 (A1A2)*A3 / A1*(A2A3) 총 2가지 case이므로 2번 for문을 반복합니다.
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]); // 최소 연산횟수를 case마다 구해주는 식입니다.
                if (q < m[i][j]) { // 기존 case보다 더 작다면
                    m[i][j] = q; // 현재 case로 초기화 해줘 최소 연산 횟수를 유지해줍니다.
                    s[i][j] = k; // 최소연산을 위해 어디서 나눠야하는지의 위치 k를 s martrix에 저장했습니다.
                }
            }
        }
    }
    return m[1][matrixNum]; // 항상 최종 행렬곱 최소 연산의 수는 해당 위치에 저장이 되고 구현을 했기에 m[1][matrixNum]를 반환시켰습니다.
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); // 빠른 속도로 입출력을 위해 선언했습니다. 온라인 저지 사이트(백준, 프로그래머스)를 이용할 때 사용했었습니다. 
    int testCase, num1, i; // testCase는 질의 수, num은 D
    cin >> testCase;
    while (testCase--) {
        vector<int>vec; //               
        cin >> matrixNum >> num;  // matrixNum은 행렬의 갯수, num은 문제에서 주어진 D input값       
        vector<vector<int>>s(matrixNum + 1, vector<int>(matrixNum + 1)); // 최소 연산을 위해 나눠야 하는 위치를 저장하는 2차원 matrix s, 계산한 k 값을 저장
        vector<vector<int>>m(matrixNum+1, vector<int>(matrixNum+1)); // 최소 연산 횟수 계산을 위한 2차원 matrix
        for (i = 0; i < matrixNum + 1; i++) { // 행렬의 data 입력, 이때 행렬의 크기+1 만큼 반복합니다. 왜냐하면 간략히 n x m 행렬과 m x a 행렬 2개가 있더라도, 곱셈이 n x a가 될때 요소가 n, m ,a 즉 3개의 요소가 필요하기 때문입니다.
            cin >> num1;
            vec.push_back(num1); 
        }
        cout<<computeOptimalCost(m,vec,s)<<endl; // 강의교재의 matrix-chain-order 함수를 구현하여 실행했습니다.WWWWW
        cout << cal_Result(s, 1, matrixNum) << endl; // 문제의 조건에 맞는 출력을 위한 함수를 구현했습니다.
    }
    return 0;
}