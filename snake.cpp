#include<iostream>
#include<conio.h>


using namespace std;

bool gameOver;

const int width  = 20;
const int height = 20;

int x,y,fruitX,fruitY,score;
int tailX[200],tailY[200];
int nTail;
enum eDirection {Stop=0,Left,Right,Up,Down};
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = Stop;
    x = width/2;
    y = width/2;
    fruitX = rand() % (width-2);
    fruitY = rand() % (height-2);
    nTail = 0;

}

void Draw()
{   system("cls");
    bool print = false;
    for(int j=0; j <= height ;  j++)      
    {
        for(int i=0; i <= width; i++)
        {   
            for(int k=0; k < nTail; k++)        // checking for tail section
            {
                if(i==tailX[k] &&  j== tailY[k])
                 { cout << "o"; 
                   print = true; 
                 }
            }
            if(i==width){cout << "#" << endl;}
            else if(j==0){cout << "#";}
            else if(i==0) {cout << "#";} 
            else if(j==height){cout << "#";}
            else if(i==x && j==y){cout << "O";}                     // Head
            else if(i==fruitX && j==fruitY){ cout << "*";} // fruit section
            else if (print == false) {cout << " ";}         // empty space
            print = false;
        }
    }
    cout << endl;
    cout << "Score:" << " " << score << endl;
}

void Input()
{
    if (_kbhit())
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
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{   
    /*Logic for tail movement*/
    int prevx=tailX[0] , prevy=tailY[0];
    tailX[0]=x; tailY[0]=y;
    int prev2x, prev2y;
    for(int k=1; k < nTail; k++)
    {   prev2x = tailX[k];
        prev2y =  tailY[k];
        tailX[k]=prevx; tailY[k]=prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch(dir)
    {
        case Left:
            x--;
            break;

        case Right:
            x++;
            break; 

        case Up:
            y--;
            break;

        case Down:
            y++;
            break;

        default:
            break;
    }
    /*Food eating logic*/
    if(x == fruitX && y == fruitY)
    {  
        fruitX = rand() % (width-1);
        fruitY = rand() % (height-1);
        nTail++;
        score +=10;
        
    }

    /* Gameover Check */
    if(x >= width || x <= 0 || y >= height || y <= 0 ){ gameOver = true;}
    for(int k=0; k< nTail; k++)
    {
        if(x == tailX[k] && y == tailY[k]){ gameOver = true;}
    }

    

}

int main()
{   bool exit = false;
    int x;
    Setup();
    while(!exit){
        while(!gameOver)
        {
            Draw();

            Input();
            Logic();
            _sleep(80);
            
        }
        cout << " GAME IS OVER !!!" << endl;
        cout << " Your score is: " << score << endl;
        cout << " Press 1 to play again" << endl << " Press 2 to exit" << endl;
        cin >> x;
        if (x == 1) { Setup();}
        else {exit = true;}
    }
    return 0;
}