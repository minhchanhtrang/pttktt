#include <stdio.h>
#include <iostream>
#include <stack>
#include <algorithm> //for max() function

using namespace std;

#define MAX_W 100

// Các mảng đầu vào
int w[MAX_W];
int v[MAX_W];

// Các mảng đầu ra
int K[MAX_W];
int P[MAX_W];


// Cài đặt thuật toán unbounded_knapsack cho bài toán cái ba lô phiên bản không giới hạn.
int unbounded_knapsack(int W, int n) {
    
    // Khởi tạo:
    // - Gán K[0] = 0
    // - Gán P[0] = -1, không chọn gì cả
    K[0] = 0;                                         
    P[0] =-1;                                         

    // Lặp
    for (int x = 1; x <= W; x++) {
        // Điền giá trị vào ô K[i]
        // Với mỗi x, ta có thể chọn các đồ vật có khối lượng <= x
        // Nếu không có K[x] = 0
        K[x] = 0;
        P[x] = -1; // Không chọn đồ vật nào cả
        for (int i = 1; i <= n; i++)
            // Nếu x >= w_i
            if ( x >= w[i]            )
                // Cập nhật K[x] = max(K[x], K[x - w_i] + v_i)
                // Nếu chọn đồ vật i tốt hơn giá trị hiện có, cập nhật lại
                if ( K[x] < K[x - w[i]] + v[i]      ) {
                    // Cập nhật lại K[x]
                    K[x] = K[x - w[i]] + v[i];    
                
                    // Cập nhật lại P[x]
                    P[x] = i;                     
                }
    }

    // Trả về giá trị của phương án tối ưu
    return K[W];                                      
}

// Kiểm thử
int main() {
    int n, W;
    cin >> n >> W;

    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    cout << "Optimal value = " << unbounded_knapsack(W, n) << endl;
    
    // Truy vết tìm phương án tối ưu theo chiều ngược
    stack<int> S;
    
    int x = W;
    while (x > 0) {
        int item = P[x];
        if (item == -1) break; //Không có lựa chọn nào cho x
        S.push(item);
        x = x - w[item];
    }

    // In phương án theo thứ tự xuôi 
    int sum_v = 0;
    while (!S.empty()) {
        int item = S.top();
        S.pop();
        cout << "- Select " << item << " with w = " << w[item] << " and v = " << v[item] << endl;
        sum_v += v[item]; // Cộng dồn giá trị để kiểm tra
    }
    
    cout << "Total value = " << sum_v << endl;
    
    return 0;
}
