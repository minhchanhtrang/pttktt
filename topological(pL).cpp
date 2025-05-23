#include <stdio.h>
#include <iostream>
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
#define IN_PROGRESS 1    // Đang duyệt
#define ALL_DONE    2    // Duyệt xong

int mark[MAX_N];         // Trạng thái của các đỉnh trong quá trình duyệt
int start_time[MAX_N];   // Thời điểm bắt đầu duyệt của các đỉnh
int finish_time[MAX_N];  // Thời điểm duyệt xong của các đỉnh


//Bước 3: Cài đạt DFS
int DFS(Graph *pG, int w, int currentTime, list<int> *pL) {
    // Gán start time của w = current time
    start_time[w] = currentTime;                      
    currentTime++;                         // Tăng curent time
    // Đánh dấu w đang duyệt (Mark w as IN PROGRESS)
    mark[w] = IN_PROGRESS;                            
    
    // Lần lượt xét qua các đỉnh kề v của w
    for (int v = 1; v <= pG->n; v++)
        if ( pG -> A[w][v]        ) {                                 // Nếu u kề với v
            if ( mark[v] == UNVISITED           ) {                             // Nếu v chưa duyệt
                currentTime = DFS(pG, v, currentTime, pL);  // Gọi đệ quy duyệt v, trả về finish time của v
                currentTime++;
            }
       }
       
    // Gán finish time của w = current time
    finish_time[w] = currentTime;                     
    
    // Đánh dâu w đã duyệt xong (Mark w as ALL DONE)
    mark[w] = ALL_DONE;                               
    
    //Bổ sung lệnh thêm phần tử w vào đầu danh sách pL
    pL->push_front(w);                                
    
    return currentTime;
}

//Bước 4: Kiểm thử
int main() {
    Graph G;
    
    cin >> G.n >> G.m;
    for (int u = 1; u <= G.n; u++)
        for (int v = 1; v <= G.n; v++)
            G.A[u][v] = 0;
    
    
    int in_degree[MAX_N]; //lưu bậc vào của các đỉnh
    for (int u = 1; u <= G.n; u++)
        in_degree[u] = 0;
    
    //Đọc các cung và thêm vào đồ thị
    for (int e = 1; e <= G.m; e++) {
        int u, v;
        cin >> u >> v;
        G.A[u][v] = 1;    // Giả sử G là đồ thị có hướng
        in_degree[v]++;   // Tăng bậc vào của v lên 1
    }
    
        
    // Gán tất cả các đỉnh đều chưa duyêt
    for (int u = 1; u <= G.n; u++)
        mark[u] = UNVISITED;
    
    list<int> L;


    int currentTime = 0;
    for (int u = 1; u <= G.n; u++)
        if (in_degree[u] == 0) {     // Tìm đỉnh có bậc vào = 0 mà duyệt
            currentTime = DFS(&G, u, currentTime, &L);
            currentTime++;
        }

    for (int u = 1; u <= G.n; u++)
        printf("Vertex %d: start time = %d, finish time = %d\n", u, start_time[u], finish_time[u]);
    
    list<int>::iterator it;
    for (it = L.begin(0; it != L.end(); it++)
        cout << *it << ' ';
    cout << endl;
    
    return 0;
}
