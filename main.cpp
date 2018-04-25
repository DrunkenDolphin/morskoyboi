#include <clocale>
#include <stdlib.h>
#include <iostream>

using namespace std;

//направление корабля
enum direction {horiz,vertik};

class player
{
public:
    int hits[10][10]; // массив выстрелов
    int ships[10][10]; // массив кораблей
int ship_check(int x, int y, direction dir, int deck)
{

        int e = 0;
        if(dir==horiz){
            if ((ships[x-1][y-1] == 2)||(ships[x-1][y+deck] == 2)||(ships[x+1][y-1] == 2)||(ships[x+1][y+deck] == 2)||(ships[x+1][y+deck] == 2)||(ships[x][y-1] == 2)||(ships[x][y+deck] == 2))
            {
                e = 1;
            }
            for (int i = 0; i < deck; i++)
            {
                if ((ships[x-1][y+i] == 2)||(ships[x+1][y+i] == 2))
                {
                    e = 1;
                }
            }
    }
        else if(dir==vertik){
            if ((ships[x-1][y-1] == 2)||(ships[x-1][y+1] == 2)||(ships[x+deck][y-1] == 2)||(ships[x+deck][y+1] == 2)||(ships[x-1][y] == 2)||(ships[x+deck][y] == 2))
            {
                e = 1;
            }
            for (int i = 0; i < deck; i++)
            {
                if (ships[x+i][y-1] == 2)
                {
                    e = 1;
                }
                if (ships[x+i][y+1] == 2)
                {
                    e = 1;
                }
            }
        }
        return e;
    }
void ships_init()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j< 10; j++)
            {
                ships[i][j] = 1;
                hits[i][j] = 0;
            }
        }
        set(4); // передача размера корабля в deck
        set(3);
        set(3);
        set(2);
        set(2);
        set(2);
        set(1);
        set(1);
        set(1);
        set(1);
    }
    void set(int deck)
    {
        bool isset = 0;
        int x,y;
        direction dir;
        while (isset == 0)
        {
            dir = static_cast<direction>(rand()%2); // Направление корабля задается случайным образом
            x = rand()%10;
            y = rand()%10;
            int e = 0;
            if(dir==horiz)
                if (ships[x][y+deck-1] == 1)
                {
                    e = ship_check(x,y,dir,deck); // Проверка смежных клеток
                    if (e == 0)
                    {
                        for (int i = 0; i < deck; i++)
                        {
                            ships[x][y+i] = 2; // Добавление корабля в массив
                        }
                        isset = 1;
                    }
                }
                else if(dir==vertik)
                    if (ships[x+deck-1][y] == 1)
                    {
                        e = ship_check(x,y,dir,deck);
                        if (e == 0)
                        {
                            for (int i = 0; i < deck; i++)
                            {
                                ships[x+i][y] = 2;
                            }
                            isset = 1;
                        }
                    }
        }
    }
void turn(player &enemy, int x, int y)
{
    hits[x][y] = 1;
    if (enemy.ships[x][y] == 2)
    {
        enemy.ships[x][y] = 3;
    }
}
void turn(player &enemy)
{
    bool flag = 0;
    while (flag == 0)
    {
        int x = rand()%10;
        int y = rand()%10;
        if (hits[x][y] != 1)
        {
            hits[x][y] = 1;
            flag = 1;
            if (enemy.ships[x][y] == 2)
            {
                enemy.ships[x][y] = 3;
            }
        }
    }
}
};
const int s = 13, c = 14;
 char map[s][c] = {
		"  0123456789 ",
		" #----------#",
		"0|          |",
		"1|          |",
		"2|          |",
		"3|          |",
		"4|          |",
		"5|          |",
		"6|          |",
		"7|          |",
		"8|          |",
		"9|          |",
		" #----------#" };
 char map_enemy[s][c] = {
		"  0123456789 ",
		" #----------#",
		"0|          |",
		"1|          |",
		"2|          |",
		"3|          |",
		"4|          |",
		"5|          |",
		"6|          |",
		"7|          |",
		"8|          |",
		"9|          |",
		" #----------#" };

player human;
player computer;

void map_init(char map[s][c]);
void show_map(char map[s][c],char map_enemy[s][c]);
int check_ending();

int main()
{
    setlocale(LC_CTYPE, "Russian");
    int final = 0;
    human.ships_init();
    computer.ships_init();

    map_init(map);
    while (final != 1)
    {
        system("cls");
        show_map(map,map_enemy);
        int x,y;
        cin>>x>>y;
        human.turn(computer,x, y);
        computer.turn(human);
        final = check_ending();
    }
    return 0;
}

void map_init(char map[s][c])
{
    for (int i=0; i < 10; i++)
    {
        for (int j=0; j < 10; j++)
        {
            if (human.ships[i][j] == 2)
                map[i+2][j+2] = '2';
        }
    }
}

void show_map(char map[s][c], char map_enemy[s][c])
{
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (computer.hits[i][j] == 1 && human.ships[i][j] == 3)
            {
                map[i+2][j+2] = '1';
            }
            else if (computer.hits[i][j] == 1 && human.ships[i][j] != 3)
            {
                map[i+2][j+2] = '0';
            }
            if (computer.ships[i][j] == 3 && human.hits[i][j] == 1)
            {
                map_enemy[i+2][j+2] = '1';
            }
            else if (computer.ships[i][j] != 3 && human.hits[i][j] == 1)
            {
                map_enemy[i+2][j+2] = '0';
            }
        }
    }

    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << map[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << map_enemy[i][j];
        }
        cout << "\n";
    }
}

int check_ending()
{
    int flag = 0;
    int human_flag = 0;
    int computer_flag = 0;
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (human.ships[i][j] == 2)
                human_flag = 1;
            if (computer.ships[i][j] == 2)
                computer_flag = 1;
        }
    }
    if (human_flag == 0)
        flag = 2;
    if (computer_flag == 0)
        flag = 1;
    if (flag == 1)
    {
        cout << "Победил игрок!\n";
        return 1;
    }
    if (flag == 2)
    {
        cout << "Победил компьютер!\n";
        return 1;
    }
    return 0;
}
