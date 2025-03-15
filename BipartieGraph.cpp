#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp ma trận kề (adjacency matrix)
#define MAX_N 101         // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {            // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;             // n: số đỉnh, m: số cung
    int A[MAX_N][MAX_N];  // Ma trận kề: (A[u][v] == 1) <=> u kề với v
};

//Bước 2: Khai báo các hằng và biến hỗ trợ (biến toàn cục):
#define NO_COLOR    0                   // Chưa duyệt
#define ORANGE      1                   // Màu cam
#define YELLOW      2                   // Màu vàng
#define SUM         (ORANGE + YELLOW)  

int color[MAX_N];                       // Màu của các đỉnh
int conflict;

//Bước 3: Cài đạt DFS
void BFS(Graph *pG, int w) {
    queue<int> Q;           // Khai báo hàng đợi
    color[w] = ORANGE;      // Tô màu ORANGE cho w

    // Thêm w vào Q
    Q.push(w);                                        
    while ( !Q.empty()                     ) { //Trong khi Q chưa rỗng
        int u;
        //Gán u = phần tử đầu hàng đợi
        u = Q.front();                                    
        
        //Xoá bỏ phần tử đầu hàng đợi
        Q.pop();                                          

        for (int v = 1; v <= pG->n; v++)
            if ( pG -> A[u][v] == 1             )               // Nếu u kề với v
                if ( color[v] == NO_COLOR           ) {         // Nếu màu của v là NO_COLOR
                    // Tô màu cho v ngược với màu của u
                    color[v] = SUM - color[u];                        
                    
                    // Đưa v vào hàng đợi
                    Q.push(v);                                        
                } else if ( color[v] == color[u]           ) {   // Nếu màu của v trùng với màu của u
                    conflict = 1;
                    return;
                }
    }
}

//Bước 4: Kiểm thử
int main() {
    Graph G;
    
    cin >> G.n >> G.m;
    for (int u = 1; u <= G.n; u++)
        for (int v = 1; v <= G.n; v++)
            G.A[u][v] = 0;
    
    
    //Đọc các cung và thêm vào đồ thị
    for (int e = 1; e <= G.m; e++) {
        int u, v;
        cin >> u >> v;
        G.A[u][v] = 1;    
        G.A[v][u] = 1;    // Giả sử G là đồ thị vô hướng
    }
    
        
    // Gán tất cả các đỉnh đều chưa duyêt
    for (int u = 1; u <= G.n; u++)
        color[u] = NO_COLOR;
    
    conflict = 0;
    //Gọi BFS nhiều lần để duyệt toàn bộ đồ thị
    for (int u = 1; u <= G.n; u++)
        if (color[u] == NO_COLOR) {
            BFS(&G, u);
        }

    if (conflict)
        cout << "G is not bipartite." << endl;
    else {
        cout << "G is bipartite." << endl;
        for (int u = 1; u <= G.n; u++)
            cout << "color[" << u << "] = " << color[u] << endl;
    }

    return 0;
}
