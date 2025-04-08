#include <stdio.h>
#include <iostream>
#include <algorithm> //for max() function

using namespace std;

#define MAX_W 100

// Các mảng đầu vào
int w[MAX_W];
int v[MAX_W];

// Các mảng đầu ra
int K[MAX_W];

// Cài đặt thuật toán unbounded_knapsack cho bài toán cái ba lô phiên bản không giới hạn.
int unbounded_knapsack(int W, int n) {
    
    // Khởi tạo:
    // Gán K[0] = 0
    K[0] = 0;                                         

    // Lặp
    for (int x = 1; x <= W; x++) {
        // Điền giá trị vào ô K[i]
        // Với mỗi x, ta có thể chọn các đồ vật có khối lượng <= x
        // Nếu không có K[x] = 0
        K[x] = 0;
        for (int i = 1; i <= n; i++)
            // Nếu x >= w_i
            if ( x >= w[i]            )
                // Cập nhật K[x] = max(K[x], K[x - w_i] + v_i)
                // Nếu chọn đồ vật i tốt hơn giá trị hiện có, cập nhật lại
                if ( K[x] < K[x - w[i]] + v[i]      )
                    K[x] = K[x - w[i]] + v[i];    
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

    cout << "optimal value = " << unbounded_knapsack(W, n) << endl;

    return 0;
}
