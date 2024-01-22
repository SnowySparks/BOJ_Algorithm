#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
struct info{
    int x,y,dir; 
};
info tmp;
int dx[8]={0,-1,-1,-1,0,1,1,1};
int dy[8]={-1,-1,0,1,1,1,0,-1};
info fish[17];
int result=0;
int arr[4][4];  //1~16: 물고기, 0: Shark, -1: 죽은 물고기

void move() {
    //이동
    int x,y,d,nx,ny,nd,idx;
    for (int i = 1 ; i < 17; i++) {
        //가장 낮은 번호 순으로 이동시행
        x = fish[i].x; y = fish[i].y; d = fish[i].dir;
        //죽은경우 다음 번호로 이동
        if (d == -1) continue;
        //방향따라 이동,
        for (int j = 0 ; j < 8 ; j++) {
            nd = (d + j) %8;
            nx = x + dx[nd]; ny = y + dy[nd];
            if (nx >=0 && ny >=0 && nx <4 && ny <4) {
                idx = arr[ny][nx];
                if (idx == 0) continue; //상어자리
                //교환 (자리이동, 방향은 주체만 변경)
                arr[ny][nx] = i; fish[i].x = nx; fish[i].y = ny;
                fish[i].dir = nd;
                arr[y][x] = idx; fish[idx].x = x; fish[idx].y = y;
                break;
            }
        }
    }
}

void dfs(int y, int x, int dir, int sum){
    info fdup[17];
    int dup[4][4];
    //복사
    for(int i=1;i<17;i++)
        fdup[i] = fish[i];
    memcpy(dup,arr,sizeof(dup));
    //물고기 이동
    move();
    //상어 이동
    int nx = x;
    int ny = y;
    while(1){
        nx+=dx[dir];
        ny+=dy[dir];
        if(nx>=0 && ny>=0 && nx<4 && ny<4){
            int idx = arr[ny][nx];
            if(idx==-1)   continue;     //물고기가 없어서 이동 불가
            //물고기
            int fd = fish[idx].dir;
            //죽임 처리 + 상어 자리이동
            fish[idx].dir = -1;
            arr[y][x] = -1;
            arr[ny][nx] = 0;
            dfs(ny,nx,fd,sum+idx);
            //원복
            fish[idx].dir = fd;
            arr[y][x] = 0;
            arr[ny][nx] = idx;
        }
        else break;
    }
    result = max(result,sum);
    
    //원복
    memcpy(arr,dup,sizeof(dup));
    for(int i=1;i<17;i++)
        fish[i] = fdup[i];
    return;
}

int main() {
    int a, b,val;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            cin>>a>>b;
            arr[i][j]=a;
            fish[a].x=j;
            fish[a].y=i;
            fish[a].dir=b-1;
        }
    val = arr[0][0];
    int sd = fish[val].dir;
    fish[val].dir=-1;
    arr[0][0]=0;
    dfs(0,0,sd,val);   
    cout<<result;
    return 0;
}