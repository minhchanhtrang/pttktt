#include <stdio>
#include <iostream>
#include <vector>
using namespace std;

//Bước 1: Biểu diễn bằng phương pháp danh sách đỉnh kề (list of neighbors)
#define MAX_N 101            // Tối đa 100 đỉnh, đánh số đỉnh từ 1
struct Graph {               // Khai báo struct kiểu C++, không cần dùng typedef
    int n, m;                // n: số đỉnh, m: số cung
    vector<int> adj[MAX_N];  // adj[u]: danh sách các đỉnh kề của u
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
    for (int i = 0; i < pG->adj[w].size(); i++) {
        int v;
        
        //Gán v = phần thử thứ i của danh sách pG->adj[w]
        v = pG->adj[w][i];  
        
        // Nếu v chưa duyệt
        if ( mark[v] == UNVISITED           ) {
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

    for (int e = 1; e <= G.m; e++) {
        int u, v;
        cin >> u >> v;
        G.adj[u].push_back(v);
        G.adj[v].push_back(u);  // Giả sử G là đồ thị vô hướng
    }
    
    for (int u = 1; u <= G.n; u++)
        mark[u] = UNVISITED;
        
    DFS(&G, 1, 0);

    for (int u = 1; u <= G.n; u++)
        printf("Vertex %d: start time = %d, finish time = %d\n", u, start_time[u], finish_time[u]);
    
    
    return 0;
}
