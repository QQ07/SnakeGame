#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameover;
const int width = 50;
const int height = 20;
int x, y, fruitX, fruitY, score;
int nTail, tailX[100], tailY[100];

enum Direction
{
    stop = 0,
    Left,
    Right,
    up,
    down
} dir;

void setup()
{
    gameover = false;
    dir = stop;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
}

void draw(char g)
{
    // Sleep(20);
    system("cls");
    for (int i = 0; i < width; i++)
        cout << "_"; // top border
    cout << endl;

    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
                cout << "|"; // walls
            else if (i == y && j == x)
                cout << "O"; // head of the snake
            else if (i == fruitY && j == fruitX)
                cout << a; // fruit's location
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {

                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // space between walls
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++)
        cout << "T"; // bottom border
    cout << endl;

    cout << "Score = " << score;
}

void input()
{
    if (_kbhit()) //_kbhit() tells that if any key is pressed or not
    {
        switch (_getch())
        {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'w':
            dir = up;
            break;
        case 's':
            dir = down;
            break;
        case 'x':
            gameover = true;
            break;
        case 'p':
            dir = stop;
            break;
        }
    }
}
void logic()
{                                      //  AOoooo
    int prevX = tailX[0];              //  Oooooo
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)     // i   nTail = 5, prev2X  ,   prev2Y,    tailX[i],    tailY[i],    prevX,    prevY,
    {                                   // 1              tailX[1]    tailY[1]   tailX[1],                 tailX[1]                 
        prev2X = tailX[i];              // 2              tailX[2]               tailX[1]                  tailX[2]
        prev2Y = tailY[i];              //
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    // tailX[0] = x;
    // tailY[0] = y;
    // for (int i = nTail; i > 0; i--)
    // {
    //     tailX[i] = tailX[i - 1];
    //     tailY[i] = tailY[i - 1];
    // }
    switch (dir)
    {
    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    case up:
        y--;
        break;
    case down:
        y++;
        break;

    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        gameover = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
playagain:
    setup();
    char a;
    cout << "what's your favorite fruit? :";
    cin >> a;
    cout << "Make sure that the caps lock is turned OFF and use the below keys to navigate"
         << "\n   w\na  s  d\n"
         << "(Press any key to start the game)";
    getch();

    while (!gameover)
    {
        draw(a);
        input();
        logic();
        Sleep(100);
    }
    cout << endl
         << "Uh-Oh.. Game Over \n better luck next time";
    cout << "\n Do you Want to play again? \n(press 1 to play again..)  ";
    int b;
    cin >> b;
    if (b == 1)
    {
        gameover = false;
        goto playagain;
    }
    cout << "\n press any key to exit the game..";
    getch();
    return 0;
}