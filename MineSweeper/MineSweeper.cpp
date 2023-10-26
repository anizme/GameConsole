#include <iostream>
#include <ctime>

using namespace std;

int m, n, k;    //row, collunm, booms
bool gameOver = false;
int boom[101][101] = {};    //m x n maxtrix
bool drawBoom[101][101] = {};   //drawBoom[i][j] = true: cell at (i, j) checked
int checkX = 0, checkY = 0;     //position of upcoming-check cell
bool win = false;
int countWin = 0;   //number of checked cell

void SetUpBoom();
void SetUpMatrix();
void Draw();
void Input();
void Logic();
void Spread(int, int);
void OriginalMap();

int main()
{
    SetUpBoom();
    SetUpMatrix();
    while(!gameOver && !win){
        Draw();
        Input();
        Logic();
    }
    system("cls");
    OriginalMap();
    cout << endl;
    if(!win) cout << "YOU'RE DEAD!" ;
    else cout << "YOU WIN!";

    return 0;
}

void SetUpBoom()
{
    srand(time(0));
    cout << "Enter number of row, collunm and booms: ";
    cin >> m >> n >> k;
    //boomed-cell: boom[i][j] = -1
    for(int i = 0; i < k; i++){
        bool e = false;
        while(!e){
            int r = rand() % m + 1;
            int c = rand() % n + 1;
            if(boom[r][c] == 0){
                boom[r][c] = -1;
                e = true;
            }
        }
    }
}
//set up value for no-boom cells = number of boom arounded
void SetUpMatrix()
{
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(boom[i][j] >= 0){
                int BoomAround = 0;
                if(boom[i-1][j-1] < 0) BoomAround++;
                if(boom[i-1][j] < 0) BoomAround++;
                if(boom[i-1][j+1] < 0) BoomAround++;
                if(boom[i][j-1] < 0) BoomAround++;
                if(boom[i][j+1] < 0) BoomAround++;
                if(boom[i+1][j-1] < 0) BoomAround++;
                if(boom[i+1][j] < 0) BoomAround++;
                if(boom[i+1][j+1] < 0) BoomAround++;
                boom[i][j] = BoomAround;    //valued cell
            }

        }
    }
}
//Map of Boom
void OriginalMap()
{
    for(int i = 0; i <= m; i++)
        cout << i << ' ';
    cout << endl;
    cout << " " << "\xC9";
    for(int i = 1; i <= m; i++){
        cout << "\xCD" << "\xCD";
    }
    cout << endl;
    for(int i = 1; i <= m; i++){
        cout << i << "\xBA";
        for(int j = 1; j <= n; j++){
            if(boom[i][j] < 0) cout << "\xE9" << ' ';
            else cout << "\xB1" << ' ';
        }
        cout << endl << " " << "\xBA" << endl;
    }
}

void Draw()
{
    system("cls");
    //outline
    for(int i = 0; i <= m; i++)
        cout << i << ' ';
    cout << '\n' << " " << "\xC9";
    for(int i = 1; i <= m; i++)
        cout << "\xCD" << "\xCD";
    //main map
    for(int i = 1; i <= m; i++){
        cout << '\n' << i << "\xBA";
        for(int j = 1; j <= n; j++){
            if(drawBoom[i][j])  //checked cell
                cout << boom[i][j] << ' ';
            else //unchecked cell
                cout << "\xB1" << ' ';
        }
        cout << '\n' << " " << "\xBA";
    }
}

void Input()
{   //Chose which cell to check
    cout << '\n' << "Check Boom (row, col): ";
    int x, y;
    cin >> x >> y;
    checkX = x;
    checkY = y;
}

void Logic()
{
    if(boom[checkX][checkY] < 0)    //boom cell
        gameOver = true;
    else if(boom[checkX][checkY] == 0)  //safe cell (no boom arounded)
        Spread(checkX, checkY); //spread to all safe cell arounded
    else{   //danger cell (booms arounded)
        drawBoom[checkX][checkY] = true;
        countWin++;
    }
    //if no more no-boom cell left -> win
    if(countWin + k == m * n)
        win  = true;
}

void Spread(int i, int j)
{
    if(i >= 1 && i <= m && j >= 1 && j <= n && boom[i][j] == 0 && !drawBoom[i][j]){
        drawBoom[i][j] = true;
        countWin++;
        Spread(i-1, j-1);
        Spread(i-1, j);
        Spread(i-1, j+1);
        Spread(i, j-1);
        Spread(i, j+1);
        Spread(i+1, j-1);
        Spread(i+1, j);
        Spread(i+1, j+1);
    }
    return;
}
