#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

struct Tail{
    int x, y;
};

const int width = 30;
const int height = 20;
enum eDir {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDir dir;

bool gameOver;
int x, y, fruitX, fruitY, score;
int nTail;
Tail tail[100];

void Setup(){
    gameOver = false;
    score = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
    nTail = 0;
}

void Draw(){
    system("cls");
    for(int i = 0; i <= width + 1; i++) cout << "\xB2";
    cout << endl;
    for(int j = 1; j <= height; j++){
        for(int i = 0; i <= width + 1; i++){
            if(i == 0 || i == width + 1) cout << "\xB2";
            else if(i == x && j == y) cout << "O";
            else if(i == fruitX && j == fruitY) cout << "@";
            else {
                bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tail[k].x == i && tail[k].y == j){
                        cout << "o";
                        print = true;
                    }
                }
                if(!print) cout << " ";
            }
        }
        cout << endl;
    }
    for(int i = 0; i <= width + 1; i++) cout << "\xB2";
    cout << endl << "SCORE: " << score;
}

void Input(){
    if(_kbhit()){
        switch(_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'p':   //want to get out the GAME!
            gameOver = true;
            break;
        }
    }
}

void Logic(){
    int pre1X = tail[0].x;
    int pre1Y = tail[0].y;
    int pre2X, pre2Y;
    tail[0].x = x; tail[0].y = y;
    for(int i = 1; i < nTail; i++){
        pre2X = tail[i].x;
        pre2Y = tail[i].y;
        tail[i].x = pre1X;
        tail[i].y = pre1Y;
        pre1X = pre2X;
        pre1Y = pre2Y;
    }
    switch(dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if(x <= 0) x = width; else if(x > width) x = 0;
    if(y <= 0) y = height; else if(y > height) y = 0;
    for(int i = 1; i < nTail; i++){
        if(x == tail[i].x && y == tail[i].y) gameOver = true;
    }
    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width + 1;
        fruitY = rand() % height + 1;
        nTail++;
    }
}

int main()
{
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(20);
    }
    system("cls");

    cout << "GAME OVER!" << endl << "SCORE: " << score << endl;
    //system("pause");
    return 0;
}

