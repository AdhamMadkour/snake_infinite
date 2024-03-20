#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int n = 30, m = 50;
int extra_row = 5, extra_col = 5;
deque<pair<int, int>> snake;
char M[n][m];

bool check_eat(pair<int, int> head) {
    if(head.first == extra_row && head.second == extra_col)
        return true;
    else
        return false;
}
bool searchFoodNoSnake(int x, int y) {
  bool flag = true;
  for (auto it:snake) {
    flag &= (it.first != x && it.second != y);
  }
  return flag;
}
bool eat() {
    while (!searchFoodNoSnake(extra_row, extra_col)) {
        extra_row = rand() % n;
        extra_col = rand() % m;
    }
}

void print() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << M[i][j];
    }
    cout << '\n';
  }
}

void initMatrix() {
  for (int i = 0; i < n; ++i) {
    for  (int j = 0; j < m; ++j) {
      M[i][j] = '.';
    }
  }
  M[extra_row][extra_col] = '~';
}

int getKeyStrike() {
    int c = 0;
    // up, down, right, left
    //  1, 2,     3,     4
    if (_kbhit()) {
        switch((c = getch())) {
        case KEY_UP:
            return 1;
            break;
        case KEY_DOWN:
            return 2;
            break;
        case KEY_LEFT:
            return 4;
            break;
        case KEY_RIGHT:
            return 3;
            break;
        default:
            return 0;
            break;
        }
    }
}
void snakeInit() {
    snake.push_back({0, 0});
}
void drawSnake() {
    M[snake.back().first][snake.back().second] = '@';
    for (int i = 0; i < snake.size() - 1; ++i) {
        M[snake[i].first][snake[i].second] = '+';
    }
}
void moveSnakeRight() {
    pair<int, int> head = snake.back();
    pair<int, int> tail = snake.front();
    // x + 0, y + 1
    for (int i = 0; i < snake.size() - 1; ++i) {
        snake[i] = snake[i + 1];
    }

    head.second++;
    head.second %= m;
    if (check_eat(head)) {
        snake.push_front(tail);
    }
    snake.back() = head;
    if (check_eat(head)) {
        eat();
    }
}
void moveSnakeDown() {
    pair<int, int> head = snake.back();
    pair<int, int> tail = snake.front();
    // x + 1, y + 0
    for (int i = 0; i < snake.size() - 1; ++i) {
        snake[i] = snake[i + 1];
    }
    head.first++;
    head.first %= n;
    if (check_eat(head)) {
        snake.push_front(tail);
    }
    snake.back() = head;
    if (check_eat(head)) {
        eat();
    }
}

void moveSnakeLeft() {
    pair<int, int> head = snake.back();
    pair<int, int> tail = snake.front();
    // x + 0, y - 1
    for (int i = 0; i < snake.size() - 1; ++i) {
        snake[i] = snake[i + 1];
    }

    head.second--;
    head.second += m;
    head.second %= m;
    if (check_eat(head)) {
        snake.push_front(tail);
    }
    snake.back() = head;
    if (check_eat(head)) {
        eat();
    }
}

void moveSnakeUp() {
    pair<int, int> head = snake.back();
    pair<int, int> tail = snake.front();
    // x - 1, y + 0
    for (int i = 0; i < snake.size() - 1; ++i) {
        snake[i] = snake[i + 1];
    }

    head.first--;
    head.first += n;
    head.first %= n;
    if (check_eat(head)) {
        snake.push_front(tail);
    }
    snake.back() = head;
    if (check_eat(head)) {
        eat();
    }
}

int cur_dir = 3;
int main(){
    snakeInit();
    while (true) {
        initMatrix();
        drawSnake();
        print();
        int c = getKeyStrike();

        if (c) {
            cur_dir = c;
        }

        if (cur_dir == 3) {
            moveSnakeRight();
        } else if (cur_dir == 2) {
            moveSnakeDown();
        } else if (cur_dir == 4) {
            moveSnakeLeft();
        } else if (cur_dir == 1) {
            moveSnakeUp();
        }
        sleep_for(10ms);
        system("cls");
    }
    return 0;
}
