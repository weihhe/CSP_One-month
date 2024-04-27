#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int r, c, ex, ey, sx, sy, ct, cur, ed, tx, ty, ct_2;
bool fid = false;
char m[51][51];
bool hs[51][51];
bool hs_2[51][51];
vector<vector<int>> q;
vector<vector<int>> q_2;

int moves[][4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

vector<vector<char>> mo_fi{
    {'+', '|', '.','S'},
    {'+', '|','S'},
    {'-','+','S'},
    {'-','+','S'},
};
bool ov(int &x, int &y, char &c)
{
    if (x < 1 || x > r || y > c || y < 1 || c == '#' || hs[x][y] == 1)
    {
        return false;
    }
    else
    {
        if (m[x][y] == 'T')
        {
            ex = x;
            ey = y;
            fid = true;
        }
        ct++;
        return true;
    }
}
bool ch_fi(char m, int i, int x, int y)
{
    if (x < 1 || x > r || y > c || y < 1 || c == '#')
    {
        return false;
    }

    bool tp = false;
    for (auto temp : mo_fi[i])
    {
        if (temp == m)
        {
            tp = true;
            break;
        }
    }
    return tp;
}

void fi(int x, int y, int r, int c)
{
    for (int i = 0; i <= 3; i++)
    {
        tx = x + moves[i][0];
        ty = y + moves[i][1];
        if (hs[tx][ty] == 1 && ch_fi(m[tx][ty], i, tx, ty) && hs_2[tx][ty] == 0) // 满足从起点被遍历到,i表示是从那从上下左右的那种方式抵达
        {
            // 判断上下左右，是否能到当前点
            q_2.push_back({tx, ty});
            ct_2++;
            ed++;
            hs_2[tx][ty] = 1;
        }
    }
    cur++;
}

void bfs(int x, int y, int &r, int &c)
{
    if (m[x][y] == '-')
    {
        for (int i = 2; i <= 3; i++)
        {
            tx = x + moves[i][0];
            ty = y + moves[i][1];
            if (ov(tx, ty, m[x][y]))
            {
                q.push_back({tx, ty});
                ed++;
                hs[tx][ty] = 1;
            }
        }
    }
    if (m[x][y] == '|')
    {
        for (int i = 0; i <= 1; i++)
        {
            tx = x + moves[i][0];
            ty = y + moves[i][1];
            if (ov(tx, ty, m[x][y]))
            {
                q.push_back({tx, ty});
                ed++;
                hs[tx][ty] = 1;
            }
        }
    }
    if (m[x][y] == '.')
    {
        for (int i = 1; i <= 1; i++)
        {
            tx = x + moves[i][0];
            ty = y + moves[i][1];
            if (ov(tx, ty, m[x][y]))
            {
                q.push_back({tx, ty});
                ed++;
                hs[tx][ty] = 1;
            }
        }
    }
    if (m[x][y] == '+' || m[x][y] == 'S'|| m[x][y] == 'T')
    {
        for (int i = 0; i <= 3; i++)
        {
            tx = x + moves[i][0];
            ty = y + moves[i][1];
            if (ov(tx, ty, m[tx][ty]))
            {
                q.push_back({tx, ty});
                ed++;
                hs[tx][ty] = 1;
            }
        }
    }
    cur++;
}

int main()
{
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> m[i][j];
            if (m[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
        }
    }
    q.push_back({sx, sy});
    hs[sx][sy] = 1;
    while (cur <= ed)
        bfs(q[cur][0], q[cur][1], r, c);


    if(fid == false)
    {
        puts("I’m stuck!");
    }
    else{
    q_2.push_back({ex, ey});
    cur = 0;
    ed = 0;
    while (cur <= ed)
        fi(q_2[cur][0], q_2[cur][1], r, c);

    cout << ct - ct_2 -1;
    }
    return 0;
}