#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>

// VARIABLES
#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3

const int width = 65;
const int height = 31;

int score = 2, highscore;
int direction = 2;

char map[height][width];
char command;

bool gameIsRunning = true;

struct Snake
{
    std::vector<std::pair<int, int>> bodyCords;
    std::pair<int, int> head;
    std::pair<int, int> tail;

    void initSnake(char map[height][width])
    {
        tail = std::make_pair(1, 1);
        head = std::make_pair(2, 1);

        bodyCords.push_back(tail);
        bodyCords.push_back(head);

        map[tail.second][tail.first] = 'O';
        map[head.second][head.first] = 'O';
    }

    void move(char map[height][width], int dir)
    {
        switch (dir)
        {
            case UP:

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = ' ';
                }

                head.second--;
                bodyCords.push_back(head);
                bodyCords.erase(bodyCords.begin() + 0);
                tail = bodyCords[0];

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = 'O';
                }

                break;

            case LEFT:
                
                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = ' ';
                }

                head.first--;
                bodyCords.push_back(head);
                bodyCords.erase(bodyCords.begin() + 0);
                tail = bodyCords[0];

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = 'O';
                }

                break;

            case RIGHT:

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = ' ';
                }

                head.first++;
                bodyCords.push_back(head);
                bodyCords.erase(bodyCords.begin() + 0);
                tail = bodyCords[0];

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = 'O';
                }

                break;

            case DOWN:

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = ' ';
                }

                head.second++;
                bodyCords.push_back(head);
                bodyCords.erase(bodyCords.begin() + 0);
                tail = bodyCords[0];

                for (int i = 0; i < bodyCords.size(); i++)
                {
                    map[bodyCords[i].second][bodyCords[i].first] = 'O';
                }

                break;
        }
    }
};

struct Fruit
{
    std::pair<int, int> fruitCords;
    bool state = false;

    void placeFruit(char map[height][width])
    {
        fruitCords = std::make_pair(rand() % (width - 2) + 1, rand() % (height - 2) + 1);
        map[fruitCords.second][fruitCords.first] = 'X';
    }
};

// FUNCTIONS
void fillMapWalls(char map[height][width]);
void drawMap(char map[height][width]);
void logic(char map[height][width], Snake &snake, Fruit &fruit, int &score, bool &gameIsRunning);

int main()
{ 
    Snake snake;
    Fruit fruit;

    srand(time(NULL));
    fillMapWalls(map);
    snake.initSnake(map);

    while (gameIsRunning)
    {
        drawMap(map);

        if(kbhit())
        {
            switch (getch())
            {
                case 's':
                    if (direction == UP)
                    {
                        break;
                    }
                    direction = DOWN;
                    break;
                case 'd':
                    if (direction == LEFT)
                    {
                        break;
                    }
                    direction = RIGHT;
                    break;
                case 'a':
                    if (direction == RIGHT)
                    {
                        break;
                    }
                    direction = LEFT;
                    break;
                case 'w':
                    if (direction == DOWN)
                    {
                        break;
                    }
                    direction = UP;
                    break;
                case 'q':
                    gameIsRunning = false;
                    break;
            }
        }
        snake.move(map, direction);
        logic(map, snake, fruit, score, gameIsRunning);
    }

    highscore = score;
    std::cout << highscore << std::endl;

    return 0;
}

// Fill char map[][] with '#' for walls
void fillMapWalls(char map[height][width])
{
    for (int i = 0; i < width; i++)
    {
        map[0][i] = '#';
    }

    for (int i = 1; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (j)
            {
                case 0:
                    map[i][j] = '#';
                    break;
                case (width - 1):
                    map[i][j] = '#';
                    break;
                default:
                    map[i][j] = ' ';
                    break;
            }
        }
    }

    for (int i = 0; i < width; i++)
    {
        map[height - 1][i] = '#';
    }
}

// Draw the char map[][] on the screen
void drawMap(char map[height][width])
{
    system("cls");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

// Do logic :DD
void logic(char map[height][width], Snake &snake, Fruit &fruit, int &score, bool &gameIsRunning)
{
    if ((snake.head.first == 0 || snake.head.second == 0) || (snake.head.first == width - 1 || snake.head.second == height - 1))
    {
        gameIsRunning = false;
    }

    for (int i = 0; i < snake.bodyCords.size() - 1; i++)
    {
        if (snake.head == snake.bodyCords[i])
        {
            gameIsRunning = false;
        }
    }

    if (fruit.state == false)
    {
        fruit.placeFruit(map);
        fruit.state = true;
    }

    if (snake.head == fruit.fruitCords)
    {
        map[fruit.fruitCords.second][fruit.fruitCords.first] = ' ';
        snake.bodyCords.push_back(fruit.fruitCords);
        snake.head = fruit.fruitCords;
        fruit.placeFruit(map);
        score++;
    }
}