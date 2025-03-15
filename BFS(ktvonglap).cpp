#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp ma trận kề (adjacency matrix)
#define MAX_N 101         // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {            // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;             // n: số đỉnh, m: số cung
    int A[MAX_N][MAX_N];  // Ma trận kề: (A[u][v] == 1) <=> u kề với v
};

//Bước 2: Khai báo các hằng và biến hỗ trợ (biến toàn cục):
#define UNVISITED   0    // Chưa duyệt
#define VISITED     1    // Đã duyệt

int mark[MAX_N];         // Trạng thái của các đỉnh trong quá trình duyệt


//Bước 3: Cài đạt DFS
void BFS(Graph *pG, int w) {
    vector<int> L[MAX_N];  // Khai báo các danh sách
    mark[w] = VISITED;     // Đánh dấu w đã duyệt

    // Thêm w vào L[0]
    L[0].push_back(w);                                
    for (int i = 0; i < n; i++) {
        // Kiểm tra nếu số phần tử của L[i] == 0 thì thoát vòng lặp.
        if ( L[i].size() == 0)
            break;
        
        for (int j = 0; j < L[i].size(); j++) {
            int u;
            // Gán u = phần tử thứ j của danh sách L[i]
            u = L[i][j];                                      
            for (int v = 1; v <= pG->n; v++)
                if ( pG -> A[u][v]                  )               // Nếu u kề với v
                    if ( mark[v] == UNVISITED           ) {         // Nếu v chưa duyệt
                        // Đánh dấu v đã duyệt
                        mark[v] = VISITED;                                
                        
                        // Thêm v vào danh sách L[i+1]
                        L[i+1].push_back(v);                              
                    }
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
        mark[u] = UNVISITED;
    
    //Gọi BFS nhiều lần để duyệt toàn bộ đồ thị
    int cnt = 0;
    for (int u = 1; u <= G.n; u++)
        if (mark[u] == UNVISITED) {
            BFS(&G, u);
            cnt++;      // Đếm số bộ phần liên thông
        }

    cout << "G has " << cnt << " connected component(s)" << endl;

    return 0;
}
