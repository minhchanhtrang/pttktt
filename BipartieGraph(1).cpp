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
#define SUM         (ORANGE + YELLOW)   // Dùng SUM để tìm màu ngược

int color[MAX_N];                       // Màu của các đỉnh
int conflict;

//Bước 3: Cài đạt DFS kết hợp tô màu
void DFS(Graph *pG, int w, int c) {
    // Tô màu c cho w
    color[w] = c;                                     

    // Lần lượt xét các đỉnh kề của w
    for (int v = 1; v <= pG->n; v++)
        if ( pG->A[w][v] == 1               )               // Nếu w kề với v
            if ( color[v] == NO_COLOR           ) {         // Nếu màu của v là NO_COLOR
                // Gọi đệ quy duyệt v với màu ngược của w
                DFS(pG, v, SUM - color[w]                );
            } else if ( color[v] == color[w]           ) {   // Nếu màu của v trùng với màu của w
                conflict = 1;
                return;
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
    //Gọi DFS nhiều lần để duyệt toàn bộ đồ thị
    for (int u = 1; u <= G.n; u++)
        if (color[u] == NO_COLOR) {
            DFS(&G, u);
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
