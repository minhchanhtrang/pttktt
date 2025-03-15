#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
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
list<int> L;             // Danh sách các đỉnh theo tứ tự topo


//Bước 3: Cài đạt DFS
void BFS(Graph *pG, int w) {
    queue<int> Q;          // Khai báo hàng đợi
    mark[w] = VISITED;     // Đánh dấu w đã duyệt

    // Đưa w vào cuối danh sách L
    L.push_back(w);                                   

    // Thêm w vào Q
     Q.push(w);                                       
    while ( !Q.empty()                     ) { //Trong khi Q chưa rỗng
        int u;
        //Gán u = phần tử đầu hàng đợi
        u = Q.front();                                    
        
        //Xoá bỏ phần tử đầu hàng đợi
        Q.pop();                                          

        for (int v = 1; v <= pG->n; v++)
            if ( pG->A[u][v] == 1               )               // Nếu u kề với v
                if ( mark[v] == UNVISITED           ) {         // Nếu v chưa duyệt
                    // Đánh dấu v đã duyệt
                    mark[v] = VISITED;                                
                    
                    // Đưa v vào cuối danh sách L
                     L.push_back(v);                                  
                    
                    // Thêm v vào hàng đợi Q
                     Q.push(v);                                       
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
        G.A[u][v] = 1;    // G là đồ thị có hướng
    }
    
        
    // Gán tất cả các đỉnh đều chưa duyêt
    for (int u = 1; u <= G.n; u++)
        mark[u] = UNVISITED;
    
    //Gọi BFS nhiều lần để duyệt toàn bộ đồ thị
    int cnt = 0;
    for (int u = 1; u <= G.n; u++)
        if (mark[u] == UNVISITED) {
            BFS(&G, u);
        }

    list<int>::iterator it;
    cout << "A possible topological order is: ";
    for (it = L.begin(); it != L.end(); it++)
        cout << (*it) << ' ';
    
    cout << endl;

    return 0;
}
