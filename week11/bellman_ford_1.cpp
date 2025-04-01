#include <stdio.h>
#include <iostream>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp ma trận trọng số (adjacency matrix)
//Mục tiêu của bài tập này chỉ để minh hoạ việc cài đặt thuật toán Bellman-Ford
//với các phương pháp biểu diễn đồ thị khác nhau. Độ phức tạp của bản cài đặt này
//khá cao so với lý thuyết: O(n^3)

#define NO_EDGE -1        // Không có cung giữa hai đỉnh
#define MAX_N 101         // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {            // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;             // n: số đỉnh, m: số cung
    int W[MAX_N][MAX_N];  // Ma trận trọng số: W[u][v] == edge weight (u, v)
};

//Bước 2: Khai báo các hằng và biến hỗ trợ (biến toàn cục):
#define oo          999999999           // Xem như vô cùng

int mark[MAX_N];                        // Trạng thái đánh dấu của các đỉnh
int d[MAX_N];                           // Chiều dài đường đi ngắn nhất

//Bước 3: Cài đặt thuật toán Bellman-Ford tìm đường đi ngắn nhất từ đỉnh s
void Bellman_Ford(Graph *pG, int s) {
    // Gán d[v] = oo với mọi v trong V
    for(int v = 1; v <= pG->n; v++){                  
    d[v] = oo; }                                      

    // Gán d[s] = 0
    d[s] = 0;                                         

    // Lặp n-1 lần từ 0 đến n - 2
    for (int it = 0; it <= pG->n - 2; it++) {
        // Duyệt qua tất cả các đỉnh u
        for (int u = 1; u <= pG->n; u++) {
            
            // Xét các đỉnh kề v của u và cập nhật d[v]
            for (int v = 1; v <= pG->n; v++)
                // Nếu u kề với v
                if ( pG->W[u][v] != NO_EDGE )
                    // Nếu d[v] lớn hơn d[u] + edgeWeight(u, v), chú ý d[u] phải khác vô cùng
                    if ( d[u] != oo && d[v] > d[u] + pG->W[u][v] )
                        //Cập nhật d[v] = d[u] + edgeWeight(u, v)
                        d[v] = d[u] + pG->W[u][v];                        

        }
    }
}

//Bước 4: Kiểm thử
int main() {
    Graph G;
    
    cin >> G.n >> G.m;
    for (int u = 1; u <= G.n; u++)
        for (int v = 1; v <= G.n; v++)
            // Gán weight(u, v) = NO_EDGE
            G.W[u][v] = NO_EDGE;                              
    
    
    //Đọc các cung và thêm vào đồ thị
    for (int e = 1; e <= G.m; e++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Gán trọng số cung (u, v) là w
         G.W[u][v] = w;                                   

    }
    
    Bellman_Ford(&G, 1);
    
    for (int u = 1; u <= G.n; u++)
        cout << "d[" << u << "] = " << d[u] << endl;

    return 0;
}
