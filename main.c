#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define SIZE 9

void wyswietl(int tab[SIZE][SIZE], int lastRow, int lastCol){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0;i < SIZE;i++){
        if(i%3 == 0){
            printf("-------------------------\n");
        }
        for(int j = 0; j < SIZE; j++){
            if(j%3 == 0){
                printf("| ");
            }
            if (i == lastRow && j == lastCol) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("%d ", tab[i][j]);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                printf("%d ", tab[i][j]);
            }
        }printf("|\n");
    }
    printf("-------------------------\n");
}
int ruch(int tab[SIZE][SIZE],int row, int col, int num)
{
    for(int i = 0;i < SIZE;i++){
        if(tab[row][i] == num || tab[i][col] == num)
        {
            return 0;
        }
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for(int i =0; i < 3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(tab[startRow+i][startCol+j] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int tab[SIZE][SIZE]){
    for(int i = 0;i < SIZE; i++){
        for(int j = 0; j< SIZE;j++){
            if(tab[i][j] == 0){
                for(int num = 1; num <= SIZE; num++)
                {
                    if(ruch(tab,i,j,num)){
                        tab[i][j]=num;
                        if(solve(tab)) return 1;
                        tab[i][j] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}
void losujplansze(int tab[SIZE][SIZE], int cell){
    solve(tab);

    while(cell > 0 )
    {
        int row = rand()%9;
        int col = rand()%9;
        if(tab[row][col]!= 0){
            tab[row][col] = 0;
            cell--;
        }
    }
}
int win(int tab[SIZE][SIZE])
{
    for(int i = 0;i < SIZE; i++){
        for(int j = 0; j< SIZE;j++) {
            if(tab[i][j] == 0) return 0;
            if(!ruch(tab,i,j,tab[i][j])) return 0;
        }
    }
    return 1;
}
int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int board[SIZE][SIZE] = {0};
    int board1[SIZE][SIZE];
    int r,c,n;
    int lastRow = -1, lastCol = -1;
    srand(time(NULL));

    losujplansze(board,1);

    for(int i = 0;i < SIZE; i++){
        for(int j = 0; j< SIZE;j++) {
            board1[i][j] = board[i][j];
        }
    }
    while(!win(board)) {
        printf("Aktualna plansza\n");
        int temp = 81;
        for(int i = 0;i < SIZE; i++){
            for(int j = 0; j< SIZE;j++) {
                if(board[i][j] != 0){
                    temp--;
                }
            }
        }
        if(temp == 0){
            SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
            printf("Wygrales");
            return 0;
        }
        temp = 0;

        wyswietl(board,lastRow,lastCol);
        printf("Podaj wiersz(0-9),kolumne(0-9) i liczbe (1-9)\n");
        scanf("%d %d %d", &c, &r, &n);
        if (r < 1 || r > 9 || c < 1 || c > 9 || n < 1 || n > 9) {
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
            printf("Zle dane");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            continue;
        }
        r--;
        c--;

        if (board1[r][c] != 0) {
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
            printf("To pole jest zajete\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            continue;
        }
        if (ruch(board, r, c, n)) {
            board[r][c] = n;
            lastRow = r;
            lastCol = c;
            continue;
        } else {
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
            printf("zly ruch\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            continue;
        }

    }
}