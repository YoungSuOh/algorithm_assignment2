#include<iostream>
#include<vector>
#define MAX 100000000
#define endl "\n"
using namespace std;
int matrixNum, num;
int mod(int x, int y) { // ������ ���ǿ� ���� ��ⷯ �������ִ� �Լ�
    return ((x*x) + (y*y)) % num;
}
int cal_Result(vector<vector<int>>& s, int start, int end) { // ������ ���ǿ� �´� ����� ���� �Լ��� �����߽��ϴ�. ��� ���������� ����Ͽ� inorder������� �����߽��ϴ�.
    if (start == end) { // leaf�� �����ϸ� start���� return�ϵ��� ��������ϴ�. end�� return�ص� �����մϴ�.        
        return start;
    }
    else {        
        int num1= cal_Result(s, start, s[start][end]); // Ʈ���� ���� �ڽ������� leaf�� ���������� ��������� �� �ݴϴ�. ���� ��ȯ�� ���� ������ ���� num1�� ����������ϴ�.
        int num2= cal_Result(s, s[start][end]+1, end); // Ʈ���� ���� �ڽ� ��ȸ�� �������� ������ �ڽ������� leaf�� ���������� ��������� �� �ݴϴ�. ���� ��ȯ�� ���� ������ ���� num2�� ����������ϴ�.
        return mod(num1, num2); // �� �ڽ��� ��ȸ�� ��� �������� num1�� num2�� mod�Լ��� ���� ���� ��ȯ�ް� �θ� ��� ������ ��ȯ�� ���� return �˴ϴ�.
    }        
}
int computeOptimalCost(vector<vector<int>>&m,vector<int>&p, vector<vector<int>>& s) { // ���� ������ Matrix-Chain-Order�� �������� ������ �Լ��Դϴ�. �ٸ����� ���Ǳ��翡���� �ִ밢���� 0���� �ʱ�ȭ ��������, ���� 2���� vector�� ����Ͽ� �ڵ����� 0�ʱ�ȭ ���� ���, for���� ������ ���� �ִ밢���� �� �غκ��� ������� �ʰ� �����߱⿡ ���� ���� �ʾҽ��ϴ�.  
    for (int l = 2; l <= matrixNum; l++) {                                            // (1)
        for (int i = 1; i <= matrixNum - l + 1;i++) {                                 // (2)
            int j = i + l - 1;                                                        // (3) -> (1), (2), (3) ���� �ּ� ������ Ƚ���� ����ϱ� ���� ��� ������ ��ܽ����� ����� ���� �����Դϴ�.  
            m[i][j] = MAX;              // �ּڰ��� ã�� ���� �ּҿ��� Ƚ�� ����ϴ� ���� MAX�� �����߽��ϴ�. MAX�� �����ؾ� � ���� ������ ó���� ������ �ʱ�ȭ �Ǳ� �����Դϴ�.
            for (int k = i;k<=j-1;k++) { // ��İ��� ���� �󸶳� �Ǿ��ִ����� ���� �ݺ��� �ݴϴ�. ���� ��� ���� ��İ��� A1A2A3 �� ����� ���� �ּ� ���� ���� Ȯ���ϰ� �ִٸ� (A1A2)*A3 / A1*(A2A3) �� 2���� case�̹Ƿ� 2�� for���� �ݺ��մϴ�.
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]); // �ּ� ����Ƚ���� case���� �����ִ� ���Դϴ�.
                if (q < m[i][j]) { // ���� case���� �� �۴ٸ�
                    m[i][j] = q; // ���� case�� �ʱ�ȭ ���� �ּ� ���� Ƚ���� �������ݴϴ�.
                    s[i][j] = k; // �ּҿ����� ���� ��� �������ϴ����� ��ġ k�� s martrix�� �����߽��ϴ�.
                }
            }
        }
    }
    return m[1][matrixNum]; // �׻� ���� ��İ� �ּ� ������ ���� �ش� ��ġ�� ������ �ǰ� ������ �߱⿡ m[1][matrixNum]�� ��ȯ���׽��ϴ�.
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); // ���� �ӵ��� ������� ���� �����߽��ϴ�. �¶��� ���� ����Ʈ(����, ���α׷��ӽ�)�� �̿��� �� ����߾����ϴ�. 
    int testCase, num1, i; // testCase�� ���� ��, num�� D
    cin >> testCase;
    while (testCase--) {
        vector<int>vec; //               
        cin >> matrixNum >> num;  // matrixNum�� ����� ����, num�� �������� �־��� D input��       
        vector<vector<int>>s(matrixNum + 1, vector<int>(matrixNum + 1)); // �ּ� ������ ���� ������ �ϴ� ��ġ�� �����ϴ� 2���� matrix s, ����� k ���� ����
        vector<vector<int>>m(matrixNum+1, vector<int>(matrixNum+1)); // �ּ� ���� Ƚ�� ����� ���� 2���� matrix
        for (i = 0; i < matrixNum + 1; i++) { // ����� data �Է�, �̶� ����� ũ��+1 ��ŭ �ݺ��մϴ�. �ֳ��ϸ� ������ n x m ��İ� m x a ��� 2���� �ִ���, ������ n x a�� �ɶ� ��Ұ� n, m ,a �� 3���� ��Ұ� �ʿ��ϱ� �����Դϴ�.
            cin >> num1;
            vec.push_back(num1); 
        }
        cout<<computeOptimalCost(m,vec,s)<<endl; // ���Ǳ����� matrix-chain-order �Լ��� �����Ͽ� �����߽��ϴ�.WWWWW
        cout << cal_Result(s, 1, matrixNum) << endl; // ������ ���ǿ� �´� ����� ���� �Լ��� �����߽��ϴ�.
    }
    return 0;
}