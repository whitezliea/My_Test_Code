/*
有一个n * m大小的迷宫。其中字符’S’表示起点，字符’D’表示出口，字符’X’表示墙壁，字符’.'表示平地。
你需要从’S’走到‘D’,每次只能向上下左右相邻的位置移动，并且不能走出地图，也不能走进墙壁
每次移动消耗1时间，走过路都会塌陷，因此不能走回头路或原地不动。
现在已知出口的大门会在T时间打开，判断在0时间从起点出发能否逃离迷宫。
数据范围n,m <= 10, T <= 50
*/
#include<iostream>
using namespace std;
const int N =10;
char mp[N][N];
bool vis[N][N];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

bool ok; //ok说明是否到达终点
int n,m,T; //t,T 是时间
int ans=0;
void dfs(int x,int y, int t)
{
    if(ok) //
    {
        return;
    }

    if (t<=T) //时间耗尽
    {
        
        if(mp[x][y]=='D')
        {
            ok = true; 
            cout<<t<<endl;
        }
        return ;
    }
    vis[x][y]=true;
    for(int i =0;i<4;++i)
    {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if(tx<0||tx>=n||ty<0||ty>=m||mp[tx][ty]=='X'||vis[tx][ty])
        {
            continue;
        }
        dfs(tx,ty,t+1);// 时间+1s
    }
    vis[x][y]=false;
}

int main()
{
    cin >> n >> m >> T;
	for (int i = 0; i < n; ++i) {
    
		cin >> mp[i];
	}
    int sx,sy,ex,ey;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;++j)
        {
            if(mp[i][j] == 'S')
            {
                sx=i,sy=j;
            }
            if(mp[i][j] == 'D')
            {
                ex=i,ey=j;
            }
        }
    }
/*
那么如果起点和终点的颜色一样，
而T是奇数的话，就不可能离开迷宫。
同理，如果终点和起点颜色不一样，
而T是偶数的话，那么也不可能逃离迷宫。
*/
    //奇偶性剪枝
    cout<<sx<<sy<<ex<<ey<<endl;
    if((sx+sy+ex+ey+T)%2 !=0)
    {
        cout<<"1-NO"<<endl;
    }
    else
    {
        ok = false;
        dfs(sx,sy,0);
        cout<<"ans: "<<ans<<endl;
        if (ok)
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"2-NO"<<endl;
        }
    }
    return 0;
}

/*
4 5 8
S.X..
...X.
D..X.
.....
*/
//(0,0) , (2,4)