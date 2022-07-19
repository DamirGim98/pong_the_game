// compile with -lncurses flag!!!!
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define height 25
#define width 80
#define left -1
#define rigth 1
#define up -1
#define down 1
#define straight 2
int iteration = 0;

void InitField(char[][width]);
void ShowField(char[][width]);
void ShowFirstRacket(int, int, char[][width]);
void ShowSecondRacket(int, int, char[][width]);
void ShowBall(int, int, char[][width]);
char GetUserInput(int *x1, int *x2);
void MovesBallX(int * x, int * dir);
void MovesBallY(int * y, int * dir);
void BallLogic(int * BallX, int * BallY, int * BallDirX, int * BallDirY, int *x1,
int* y1, int *x2, int *y2, int * CountPlayer1, int * CountPlayer2);
void ShowScore(int * , int * , char[][width]);
void ExitCondition(int CountPlayer1, int CountPlayer2);
void ShowWelcome();
void GameLoop();
void ShowPong();

int main(void) {
    ShowPong();
    ShowWelcome();
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    scrollok(stdscr, 1);
    GameLoop();
    refresh();
    endwin();
    printf("\033[2J");
    printf("\033[0;0f");
    return 0;
}

void InitField(char mas[][width]) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                mas[i][j] = ' ';
            }
        }
        for (int i = 0; i < width; i++) {
            mas[0][i] = '#';
            mas[height - 1][i] = '#';
            if (i > 0 && i < height - 1) {
                mas[i][0]  = '.';
                mas[i][width - 1] = '.';
                mas[i][width / 2 - 1] = '|';
            }
        }
}

void ShowWelcome() {
    char mas[height][width];
    char firstline[] = "Welcome to PONG";
    char secondline[] = "First player gonna PRESS A or Z";
    char thirdline[] = "Second player gonna PRESS K or M";
    char fourthline[] =  "Enter s to start and . to exit";
    char key;
    do {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                mas[i][j] = ' ';
            }
        }
        for (int i = 0; i < width; i++) {
            mas[0][i] = '#';
            mas[height - 1][i] = '#';
            if (i > 0 && i < height - 1) {
                mas[i][0]  = '.';
                mas[i][width - 1] = '.';
            }
        }
        int k = 0;
        for (int j = width / 2 - 10; firstline[k] != '\0'; j++) {
            mas[6][j] = firstline[k];
            k++;
        }
        k = 0;
        for (int j = width / 2 - 18; secondline[k] != '\0'; j++) {
            mas[7][j] = secondline[k];
            k++;
        }
        k = 0;
        for (int j = width / 2 - 18; thirdline[k] != '\0'; j++) {
            mas[8][j] = thirdline[k];
            k++;
        }
        k = 0;
        for (int j = width / 2 - 18; fourthline[k] != '\0'; j++) {
            mas[9][j] = fourthline[k];
            k++;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%c", mas[i][j]);
            }
            printf("\n");
        }
        key = getchar();
        if (key == '.') {
            printf("\033[2J");
            printf("\033[0;0f");
            exit(0);
        }
    } while (key != 's');
}

void ShowField(char mas[][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printw("%c", mas[i][j]);
        }
        printw("\n");
    }
}

void ShowFirstRacket(int x, int y, char mas[][width]) {
    mas[x - 1][y + 1] = '|';
    mas[x][y + 1] = '|';
    mas[x + 1][y + 1] = '|';
}

void ShowSecondRacket(int x, int y, char mas[][width]) {
    mas[x - 1][y - 1] = '|';
    mas[x][y - 1] = '|';
    mas[x + 1][y - 1] = '|';
}

void ShowScore(int * CountPlayer1, int * CountPlayer2, char mas[][width]) {
    // player 2
    mas[height / 7 - 1][(width - 1) / 2 + 4] = 'P';
    mas[height / 7 - 1][(width - 1) / 2 + 5] = '2';
    mas[height / 7][(width - 1) / 2 + 4] = 48 + *CountPlayer2 / 10;
    mas[height / 7][(width - 1) / 2 + 5] = 48 + *CountPlayer2 % 10;
    // player 1
    mas[height / 7 - 1][(width - 1) / 2 - 5] = 'P';
    mas[height / 7 - 1][(width - 1) / 2 - 4] = '1';
    mas[height / 7][(width - 1) / 2 - 5] = 48 + *CountPlayer1 / 10;
    mas[height / 7][(width - 1) / 2 - 4] = 48 + *CountPlayer1 % 10;
}
void ShowBall(int x, int y, char mas[][width]) {
    mas[x][y] = 'o';
}
char GetUserInput(int *x1, int *x2) {
    char key = getch();
    if (key != ERR) {
        if (key == 'a' || key == 'A') {
            if (*x1 - 2 != 0) {
                (*x1)--;
            }
        }
        if (key == 'z'|| key == 'Z') {
            if (*x1 + 1 != height - 2) {
                (*x1)++;
            }
        }
        if (key == 'k' || key == 'K') {
            if (*x2 - 2 != 0) {
                (*x2)--;
            }
        }
        if (key == 'm'|| key == 'M') {
            if (*x2 + 1 != height - 2) {
                (*x2)++;
            }
        }
    }
    return key;
}

void  MovesBallX(int *x, int *direction) {
    if (*direction == down)
        *x = *x + 1;
    else if (*direction == up)
        *x = *x - 1;
    else if (*direction == straight)
        *x = *x;
}

void  MovesBallY(int *y, int *direction) {
    if (*direction == rigth)
        *y = *y + 1;
    else if (*direction == left)
        *y = *y - 1;
}

void BallLogic(int * BallX, int * BallY, int * BallDirX, int * BallDirY, int *x1,
int* y1, int *x2, int *y2, int * CountPlayer1, int * CountPlayer2) {
    // first racket
    if (*BallX == *x1 && *BallY == *y1 + 2) {
        if (*BallDirY == left) {
            *BallDirY = rigth;
            *BallDirX = straight;
        }
    }
    if (*BallX == *x1 - 1 && *BallY == *y1 + 2) {
        if (*BallDirY == left) {
            *BallDirY = rigth;
            *BallDirX = up;
        }
    }
    if (*BallX == *x1 + 1 && *BallY == *y1 + 2) {
        if (*BallDirY == left) {
            *BallDirY = rigth;
            *BallDirX = down;
        }
    }
    // second racket
    if (*BallX == *x2 && *BallY == *y2 - 2) {
        if (*BallDirY == rigth) {
            *BallDirY = left;
            *BallDirX = straight;
        }
    }
    if (*BallX == *x2 - 1 && *BallY == *y2 - 2) {
        if (*BallDirY == rigth) {
            *BallDirY = left;
            *BallDirX = up;
        }
    }
    if (*BallX == *x2 + 1 && *BallY == *y2 - 2) {
        if (*BallDirY == rigth) {
            *BallDirY = left;
            *BallDirX = down;
        }
    }
    // walls
    if (*BallX <= 1) {
        *BallDirX = down;
    }
    if (*BallX >= height - 2) {
        *BallDirX = up;
    }
    if (*BallY <= 0) {
        *BallX = height / 2;
        *BallY = width / 2;
        srand(iteration);
        if (rand() % 3 == 0) {
            *BallDirX = up;
        } else if (rand() % 3 == 1) {
            *BallDirX = down;
        } else {
            *BallDirX = straight;
        }
        *CountPlayer2 = *CountPlayer2 + 1;
    }
    if (*BallY >= width - 1) {
        srand(iteration);
        *BallX = height / 2;
        *BallY = width / 2;
        if (rand() % 3 == 0) {
            *BallDirX = up;
        } else if (rand() % 3 == 1) {
            *BallDirX = down;
        } else {
            *BallDirX = straight;
        }
        // *BallDirY = rigth;
        *CountPlayer1 = *CountPlayer1 + 1;
    }
}

void GameLoop() {
    int CountPlayer1 = 0;
    int CountPlayer2 = 0;
    int BallX = height / 2;
    int BallY = width / 2;
    int BallDirX = straight;
    int BallDirY = left;
    int x1 = height / 2;
    int y1 = 0;
    int x2 = height / 2;
    int y2 = width - 1;
    char key;
    char mas[height][width];
    do {
        InitField(mas);
        ShowFirstRacket(x1, y1, mas);
        ShowSecondRacket(x2, y2, mas);
        ShowBall(BallX, BallY, mas);
        ShowScore(&CountPlayer1, &CountPlayer2, mas);
        MovesBallX(&BallX, &BallDirX);
        MovesBallY(&BallY, &BallDirY);
        ShowField(mas);
        key = GetUserInput(&x1, &x2);
        BallLogic(&BallX, &BallY, &BallDirX, &BallDirY, &x1, &y1, &x2, &y2, &CountPlayer1, &CountPlayer2);
        ExitCondition(CountPlayer1, CountPlayer2);
        usleep(50000);
        iteration++;
    } while (key != '.');
}

void ExitCondition(int CountPlayer1, int CountPlayer2) {
    if (CountPlayer2 == 21) {
        endwin();
        printf("\033[2J");
        printf("\033[0;0f");
        printf("Player 2 won!\n");
        exit(0);
    }
    if (CountPlayer1 == 21) {
        endwin();
        printf("\033[2J");
        printf("\033[0;0f");
        printf("Player 1 won!\n");
        exit(0);
    }
}

void ShowPong() {
    char key;
    printf("\033[2J");
    printf("\033[0;0f");
    printf("              ########:::'#######::'##::: ##::'######:::\n");
    printf("              ##.... ##:'##.... ##: ###:: ##:'##... ##::\n");
    printf("              ##:::: ##: ##:::: ##: ####: ##: ##:::..:::\n");
    printf("              ########:: ##:::: ##: ## ## ##: ##::'####:\n");
    printf("              ##.....::: ##:::: ##: ##. ####: ##::: ##::\n");
    printf("              ##:::::::: ##:::: ##: ##:. ###: ##::: ##::\n");
    printf("              ##::::::::. #######:: ##::. ##:. ######:::\n");
    printf("              ..:::::::::.......:::..::::..:::......::::\n");
    printf("              ..:::::::::Press ANY KEY to START.....::::\n");
    printf("              ..:::::::::.......F for EXIT..........::::\n");
    key = getchar();
    if (key == 70 || key == 102) {
        printf("\033[2J");
        printf("\033[0;0f");
        exit(0);
    }
    printf("\033[2J");
    printf("\033[0;0f");
}
