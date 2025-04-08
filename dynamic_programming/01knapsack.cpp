#include <stdio.h>
#include <iostream>
#include <algorithm> //for max() function

using namespace std;

#define MAX_N 100
#define MAX_W 500

// Các mảng đầu vào
int w[MAX_N];
int v[MAX_N];

// Các mảng đầu ra
int K[MAX_N][MAX_W];

// Cài đặt thuật toán unbounded_knapsack cho bài toán cái ba lô phiên bản không giới hạn.
int zero_one_knapsack(int W, int n) {
    
    // Khởi tạo:
    // Gán K[j, 0] = 0
    // Gán K[0, x] = 0
    for (int j = 0; j <= n; j++)                      
        K[j][0] = 0;                                  
    for (int x = 0; x <= W; x++)                      
        K[0][x] = 0;                                  

    // Lặp
    for (int j = 1; j <= n; j++) {
        for (int x = 1; x <= W; x++) {
            // Điền giá trị vào ô K[j][x]
            // Với mỗi x, ta có thể chọn hoặc không chọn đồ vật j
        
            // Không chọn đồ vật j, K[j, x] = K[j-1, x]
            K[j][x] = K[j-1][x];                              
            
            // Chọn đồ vật j, chỉ chọn được khi x > w_j
            // Nếu x >= w_j
            if ( x >= w[j]            )
                // Cập nhật K[j, x] = max(K[j, x], K[j-1, x - w_i] + v_i)
                // Nếu chọn đồ vật j tốt hơn giá trị hiện có, cập nhật lại
                if ( K[j][x] < K[j-1][x - w[j]] + v[j] )
                        K[j][x] = K[j-1][x - w[j]] + v[j];
        }
    }

    // Trả về giá trị của phương án tối ưu
    return K[n][W];                                   
}

// Kiểm thử
int main() {
    int n, W;
    cin >> n >> W;

    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    cout << "Optimal value = " << zero_one_knapsack(W, n) << endl;

    return 0;
}
