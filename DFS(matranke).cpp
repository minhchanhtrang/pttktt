#include <stdio.h>
#include <iostream>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp ma trận kề (adjacency matrix)
#define MAX_N 101         // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {            // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;             // n: số đỉnh, m: số cung
    int A[MAX_N][MAX_N];  // Ma trận kề: (A[u][v] == 1) <=> u kề với v
};

//Bước 2: Khai báo các hằng và biến hỗ trợ (biến toàn cục):
#define UNVISITED   0    // Chưa duyệt
#define IN_PROGRESS 1    // Đang duyệt
#define ALL_DONE    2    // Duyệt xong

int mark[MAX_N];         // Trạng thái của các đỉnh trong quá trình duyệt
int start_time[MAX_N];   // Thời điểm bắt đầu duyệt của các đỉnh
int finish_time[MAX_N];  // Thời điểm duyệt xong của các đỉnh


//Bước 3: Cài đạt DFS
int DFS(Graph *pG, int w, int currentTime) {
    // Gán start time của w = current time
    start_time[w] = currentTime;                      
    currentTime++;                         // Tăng curent time
    // Đánh dấu w đang duyệt (Mark w as IN PROGRESS)
    mark[w] = IN_PROGRESS;                            
    
    // Lần lượt xét qua các đỉnh kề v của w
    for (int v = 1; v <= pG->n; v++)
        if ( pG -> A[w][v] == 1   ) {                                 // Nếu u kề với v
            if ( mark[v] == UNVISITED           ) {                             // Nếu v chưa duyệt
                currentTime = DFS(pG, v, currentTime);  // Gọi đệ quy duyệt v, trả về finish time của v
                currentTime++;
            }
       }
       
    // Gán finish time của w = current time
    finish_time[w] = currentTime;                     
    
    // Đánh dâu w đã duyệt xong (Mark w as ALL DONE)
     mark[w] = ALL_DONE;                              
    return currentTime;
}

//Bước 4: Kiểm thử
int main() {
    Graph G;
    
    cin >> G.n >> G.m;
    for (int u = 1; u <= G.n; u++)
        for (int v = 1; v <= G.n; v++)
            G.A[u][v] = 0;
        
    for (int e = 1; e <= G.m; e++) {
        int u, v;
        cin >> u >> v;
        G.A[u][v] = 1;
        G.A[v][u] = 1; // Giả sử G là đồ thị vô hướng
    }
    
    for (int u = 1; u <= G.n; u++)
        mark[u] = UNVISITED;
        
    DFS(&G, 1, 0);

    for (int u = 1; u <= G.n; u++)
        printf("Vertex %d: start time = %d, finish time = %d\n", u, start_time[u], finish_time[u]);
    
    
    return 0;
}
