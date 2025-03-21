#include <stdio.h>
#include <iostream>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp ma trận trọng số (adjacency matrix)
#define NO_EDGE -1        // Không có cung giữa hai đỉnh
#define MAX_N 101         // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {            // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;             // n: số đỉnh, m: số cung
    int W[MAX_N][MAX_N];  // Ma trận trọng số: W[u][v] == edge weight (u, v)
};

//Bước 2: Khai báo các hằng và biến hỗ trợ (biến toàn cục):
#define NOT_SURE    0                   // Chưa chắc chắn
#define SURE        1                   // Chắc chắn
#define oo          999999999           // Xem như vô cùng

int mark[MAX_N];                        // Trạng thái đánh dấu của các đỉnh
int d[MAX_N];                           // Chiều dài đường đi ngắn nhất

//Bước 3: Cài đặt Dijkstra tìm đường đi ngắn nhất từ đỉnh s
void Moore_Dijkstra(Graph *pG, int s) {
    // Đánh dấu tất cả các đỉnh đều NOT_SURE
    for (int u = 1; u <= pG->n; u++)                  
    mark[u] = NOT_SURE;                               

    // Gán d[v] = oo với mọi v trong V
     for (int v = 1; v <= pG->n; v++)                 
    d[v] = oo;                                        

    // Gán d[s] = 0
    d[s] = 0;                                         

    // Lặp n lần (mỗi lần chọn một đỉnh và đánh dấu nó là SURE)
    for (int it = 1; it <= pG->n; it++) {
        // Tìm đỉnh u NOT_SURE có d[u] nhỏ nhất
        int u = -1;
        int min_d = oo;
        for (int v = 1; v <= pG->n; v++)
            // Nếu v NOT_SURE
            if ( mark[v] == NOT_SURE            )
                if (d[v] < min_d) {
                    //Gán min_d = d[v]
                    min_d = d[v];                                     
                    
                    u = v; // Cho u = v
                }
        
        if (u == -1) //Không tìm được u
            break;
            
        // Xét các đỉnh kề v của u và cập nhật d[v]
        for (int v = 1; v <= pG->n; v++)
            // Nếu u kề với v
            if ( pG->W[u][v] != NO_EDGE         )
                // Nếu d[v] lớn hơn d[u] + edgeWeight(u, v)
                if ( d[v] > d[u] + pG->W[u][v]      )
                    //Cập nhật d[v] = d[u] + edgeWeight(u, v)
                    d[v] = d[u] + pG->W[u][v];                        

        // Đánh dấu u là SURE
        mark[u] = SURE;                                   
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

        // Gán weight(v, u) = w      (Giả sử G là đồ thị vô hướng)
         G.W[v][u] = w;                                   
    }
    
    Moore_Dijkstra(&G, 1);
    
    for (int u = 1; u <= G.n; u++)
        cout << "d[" << u << "] = " << d[u] << endl;

    return 0;
}
