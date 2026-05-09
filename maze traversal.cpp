#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <fstream>

using namespace std;

#define slp 100

struct coordinates
{
    int x;
    int y;

    void assignment(int &i, int &j)
    {
        i = x;
        j = y;
    }
};

void full_screen_mode();
void gotoxy(short, short);
void change_char(short, short, char);
vector<vector<char>> choose_map(short, coordinates &, coordinates &);
vector<vector<char>> create_map(coordinates &, coordinates &);
void print_maze(vector<vector<char>>);
bool maze_traverse(vector<vector<char>>, coordinates, coordinates);
void save_map(string, vector<vector<char>>, coordinates, coordinates);
void get_map(string, vector<vector<char>> &, coordinates &, coordinates &);

#define wall_ch '#'
#define road_ch '.'
#define guide_ch 'o'
#define empty_ch ' '

int main()
{

    full_screen_mode();

    coordinates starter;
    coordinates end;
    vector<vector<char>> maze;

    short which_map;

    while (1)
    {
        system("cls");

        cout << "----------------------------------------\n";
        cout << "              maze traverse             \n";
        cout << "----------------------------------------\n\n";

        cout << "1 - first map \n";
        cout << "2 - same first map but problematic \n";
        cout << "3 - second map \n";
        cout << "4 - spiral map \n\n";
        cout << "5 - create map your self \n";
        cout << "6 - saved map \n\n";
        cout << "0 - exit \n\n";
        cout << "which one do you want : ";

        cin >> which_map;

        system("cls");

        if (which_map != 0)
        {
            maze = choose_map(which_map, starter, end);
        }
        else
        {
            return 0;
        }

        if (maze[0][0] == 'n')
        {
            system("cls");
            cout << "there isn't map .";
            cout << endl;
            cout << endl;
            system("pause");
            continue;
        }

        if (maze[0][0] == 'd')
        {
            system("cls");
            cout << "your map has a problem .";
            cout << endl;
            cout << endl;
            system("pause");
            continue;
        }

        bool is_solve = maze_traverse(maze, starter, end);

        if (is_solve)
        {
            gotoxy(maze.size(), 0);
            cout << endl;
            cout << "          END";
            cout << endl;
            cout << endl;
        }
        else
        {
            gotoxy(maze.size(), 0);
            cout << endl;
            cout << "      CAN'T SOLVE";
            cout << endl;
            cout << endl;
        }

        cout << "\n\n";
        system("pause");
    }
}

void full_screen_mode()
{
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);

    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

void gotoxy(short x, short y)
{
    static HANDLE h = NULL;
    if (!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    // x -> for my program : number of row
    // y -> for my program : bumber of col
    COORD c = {y, x};
    SetConsoleCursorPosition(h, c);
}

void change_char(short x, short y, char ch)
{
    gotoxy(x, y);
    cout << ' ';

    gotoxy(x, y);
    cout << ch;
}

vector<vector<char>> choose_map(short level, coordinates &starter, coordinates &end)
{
    vector<vector<char>> map;
    if (level == 1)
    {
        map = {
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch},
            {road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, road_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch}};
        starter = {2, 0};
        end = {4, 11};
    }
    else if (level == 2)
    {
        map = {
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch},
            {road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch}};
        starter = {2, 0};
        end = {0, 0};
    }
    else if (level == 3)
    {
        map = {
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch},
            {road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch}};
        starter = {1, 0};
        end = {10, 11};
    }
    else if (level == 4)
    {
        map = {
            {wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, road_ch, wall_ch},
            {wall_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, road_ch, wall_ch},
            {wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch, wall_ch}};
        starter = {0, 1};
        end = {0, 0};
    }
    else if (level == 5)
    {
        map = create_map(starter, end);
    }
    else if (level == 6)
    {
        get_map("save.txt", map, starter, end);
    }

    return map;
}

vector<vector<char>> create_map(coordinates &starter, coordinates &end)
{
    short size_x, size_y;
    short st_row, st_col;
    short en_row, en_col;
    short ro_row, ro_col;

    bool isOK;

    cout << "----------------------------------------\n";
    cout << "               set size                 \n";
    cout << "----------------------------------------\n\n";

    isOK = false;
    while (!isOK)
    {
        cout << "\nheight (6-40) : ";
        cin >> size_x;
        if (size_x < 6 || size_x > 40)
        {
            cout << " - this is out of the range !!!\n";
            isOK = false;
        }
        else
        {
            isOK = true;
        }
    }

    isOK = false;
    while (!isOK)
    {
        cout << "\nwidth (6-70) : ";
        cin >> size_y;
        if (size_y < 6 || size_y > 70)
        {
            cout << " - this is out of the range !!!\n";
            isOK = false;
        }
        else
        {
            isOK = true;
        }
    }

    vector<vector<char>> map(size_x, vector<char>(size_y, wall_ch));

    system("cls");

    print_maze(map);

    cout << "\n[RIGHT ARROW] : go right ";
    cout << "\n[LEFT ARROW]  : go left";
    cout << "\n[DOWN ARROW]  : go down";
    cout << "\n[UP ARROW]    : go up";
    cout << "\n[SPACE]       : next (set end location)";
    cout << "\n --> notice : can't choose corner";

    // starter coordinates

    st_row = 0;
    st_col = 0;

    while (1)
    {
        change_char(st_row, 2 * st_col, guide_ch);

        getch();

        if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
        {
            if ((st_row == 0 || st_col + 1 == 0) && (st_row <= size_x - 1 && st_col + 1 <= size_y - 1))
            {
                change_char(st_row, 2 * st_col, wall_ch);
                st_col++;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
        {
            if ((st_row == 0 || st_col - 1 == 0) && (st_row >= 0 && st_col - 1 >= 0))
            {
                change_char(st_row, 2 * st_col, wall_ch);
                st_col--;
            }
        }
        else if (GetAsyncKeyState(VK_UP) & 0x0001)
        {
            if ((st_row - 1 == 0 || st_col == 0) && (st_row - 1 >= 0 && st_col >= 0))
            {
                change_char(st_row, 2 * st_col, wall_ch);
                st_row--;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
        {
            if ((st_row + 1 == 0 || st_col == 0) && (st_row + 1 <= size_x - 1 && st_col <= size_y - 1))
            {
                change_char(st_row, 2 * st_col, wall_ch);
                st_row++;
            }
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            if (!(st_row == 0 && st_col == 0) && !(st_row == size_x - 1 && st_col == 0) && !(st_row == 0 && st_col == size_y - 1))
            {
                starter = {st_row, st_col};
                map[st_row][st_col] = road_ch;
                change_char(st_row, 2 * st_col, road_ch);
                break;
            }
        }
    }

    // end coordinates

    en_row = size_x - 1;
    en_col = size_y - 1;

    while (1)
    {
        change_char(en_row, 2 * en_col, guide_ch);

        getch();

        if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
        {
            if ((en_row == size_x - 1 || en_col + 1 == size_y - 1) && (en_row <= size_x - 1 && en_col + 1 <= size_y - 1))
            {
                change_char(en_row, 2 * en_col, wall_ch);
                en_col++;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
        {
            if ((en_row == size_x - 1 || en_col - 1 == size_y - 1) && (en_row >= 0 && en_col - 1 >= 0))
            {
                change_char(en_row, 2 * en_col, wall_ch);
                en_col--;
            }
        }
        else if (GetAsyncKeyState(VK_UP) & 0x0001)
        {
            if ((en_row - 1 == size_x - 1 || en_col == size_y - 1) && (en_row - 1 >= 0 && en_col >= 0))
            {
                change_char(en_row, 2 * en_col, wall_ch);
                en_row--;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
        {
            if ((en_row + 1 == size_x - 1 || en_col == size_y - 1) && (en_row + 1 <= size_x - 1 && en_col <= size_y - 1))
            {
                change_char(en_row, 2 * en_col, wall_ch);
                en_row++;
            }
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            if (!(en_row == size_x - 1 && en_col == size_y - 1) && !(en_row == 0 && en_col == size_y - 1) && !(en_row == size_x - 1 && en_col == 0))
            {
                end = {en_row, en_col};
                map[en_row][en_col] = road_ch;
                change_char(en_row, 2 * en_col, road_ch);
                break;
            }
        }
    }

    system("cls");

    print_maze(map);

    cout << "\n[RIGHT ARROW] : put " << road_ch << " and go right ";
    cout << "\n[LEFT ARROW]  : put " << road_ch << " and go left";
    cout << "\n[DOWN ARROW]  : put " << road_ch << " and go down";
    cout << "\n[UP ARROW]    : put " << road_ch << " and go up";
    cout << "\n[D]           : put " << wall_ch << " and go right ";
    cout << "\n[A]           : put " << wall_ch << " and go left";
    cout << "\n[S]           : put " << wall_ch << " and go down";
    cout << "\n[W]           : put " << wall_ch << " and go up";
    cout << "\n[SPACE]       : end create map";

    // road

    ro_row = starter.x;
    ro_col = starter.y;

    while (1)
    {
        change_char(ro_row, 2 * ro_col, guide_ch);

        getch();

        if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
        {
            if (ro_row <= size_x - 2 && ro_col + 1 <= size_y - 2)
            {
                map[ro_row][ro_col] = road_ch;
                change_char(ro_row, 2 * ro_col, road_ch);
                ro_col++;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
        {
            if (ro_row >= 1 && ro_col - 1 >= 1)
            {
                map[ro_row][ro_col] = road_ch;
                change_char(ro_row, 2 * ro_col, road_ch);
                ro_col--;
            }
        }
        else if (GetAsyncKeyState(VK_UP) & 0x0001)
        {
            if (ro_row - 1 >= 1 && ro_col >= 1)
            {
                map[ro_row][ro_col] = road_ch;
                change_char(ro_row, 2 * ro_col, road_ch);
                ro_row--;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
        {
            if (ro_row + 1 <= size_x - 2 && ro_col <= size_y - 2)
            {
                map[ro_row][ro_col] = road_ch;
                change_char(ro_row, 2 * ro_col, road_ch);
                ro_row++;
            }
        }
        if (GetAsyncKeyState('D') & 0x0001)
        {
            if (ro_row <= size_x - 2 && ro_col + 1 <= size_y - 2)
            {
                map[ro_row][ro_col] = wall_ch;
                change_char(ro_row, 2 * ro_col, wall_ch);
                ro_col++;
            }
        }
        else if (GetAsyncKeyState('A') & 0x0001)
        {
            if (ro_row >= 1 && ro_col - 1 >= 1)
            {
                map[ro_row][ro_col] = wall_ch;
                change_char(ro_row, 2 * ro_col, wall_ch);
                ro_col--;
            }
        }
        else if (GetAsyncKeyState('W') & 0x0001)
        {
            if (ro_row - 1 >= 1 && ro_col >= 1)
            {
                map[ro_row][ro_col] = wall_ch;
                change_char(ro_row, 2 * ro_col, wall_ch);
                ro_row--;
            }
        }
        else if (GetAsyncKeyState('S') & 0x0001)
        {
            if (ro_row + 1 <= size_x - 2 && ro_col <= size_y - 2)
            {
                map[ro_row][ro_col] = wall_ch;
                change_char(ro_row, 2 * ro_col, wall_ch);
                ro_row++;
            }
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            map[ro_row][ro_col] = road_ch;
            change_char(ro_row, 2 * ro_col, road_ch);
            break;
        }
    }

    system("cls");

    int choose;

    print_maze(map);

    cout << "\nthis is result , do you want save it ? \n";
    cout << " --> if you already have a saved map , it will be lost . \n";
    cout << "1 - yes\n";
    cout << "2 - no\n";
    cout << " choose : ";

    cin >> choose;

    switch (choose)
    {
    case 1:
        save_map("save.txt", map, starter, end);
        cout << "\nit save in the \"save.txt\" file !!!\n\n";
        system("pause");
        break;
    case 2:
        cout << "\nit didn't save !!!\n\n";
        system("pause");
        break;
    default:
        cout << "\nerror , it didn't save !!!\n\n";
        cout << "\nit didn't save !!!\n\n";
        system("pause");
        break;
    }

    return map;
}

void print_maze(vector<vector<char>> map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

bool maze_traverse(vector<vector<char>> map, coordinates starter, coordinates end)
{
    bool is_solve;
    vector<coordinates> node;

    int i, j;
    starter.assignment(i, j);

    system("cls");
    print_maze(map);
    Sleep(slp);

    while (1)
    {
        if (map[i][j] == road_ch)
        {
            map[i][j] = empty_ch;
            change_char(i, 2 * j, empty_ch);
            Sleep(slp);
            if (!(i + 1 < map.size() && j + 1 < map[i].size()))
            {
                // end of game
                break;
            }

            if (map[i][j + 1] == road_ch)
            {
                if (i == 0)
                {
                    if (map[i + 1][j] == road_ch || map[i][j - 1] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                else if (j == 0)
                {
                    if (map[i + 1][j] == road_ch || map[i - 1][j] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                else
                {
                    if (map[i + 1][j] == road_ch || map[i - 1][j] == road_ch || map[i][j - 1] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                j++;
            }
            else if (map[i + 1][j] == road_ch)
            {
                if (i == 0)
                {
                    if (map[i][j - 1] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                else if (j == 0)
                {
                    if (map[i - 1][j] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                else
                {
                    if (map[i - 1][j] == road_ch || map[i][j - 1] == road_ch)
                    {
                        node.push_back({i, j});
                    }
                }
                i++;
            }
            else if (map[i - 1][j] == road_ch)
            {
                if (map[i][j - 1] == road_ch)
                {
                    node.push_back({i, j});
                }
                i--;
            }
            else if (map[i][j - 1] == road_ch)
            {
                j--;
            }
            else if (!node.empty())
            {
                i = node.back().x;
                j = node.back().y;
                map[i][j] = road_ch;
                node.pop_back();
            }
        }
        else
        {
            break;
        }
    }

    if (i == end.x && j == end.y)
    {
        is_solve = true;
    }
    else
    {
        is_solve = false;
    }

    return is_solve;
}

void save_map(string path, vector<vector<char>> map, coordinates starter, coordinates end)
{
    fstream file;
    file.open(path, ios::out);
    string str;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            str += map[i][j];
        }
        str += "\n";
    }

    file << map.size() << "\n";
    file << map[0].size() << "\n";
    file << str;
    file << starter.x << "\n";
    file << starter.y << "\n";
    file << end.x << "\n";
    file << end.y << "\n";

    file.close();
}

void get_map(string path, vector<vector<char>> &map, coordinates &starter, coordinates &end)
{

    fstream file;
    file.open(path, ios::in);

    if (!file.is_open())
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'n';
        return;
    }

    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    int size_x;
    int size_y;
    char ch;

    file >> size_x;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    file >> size_y;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    map.resize(size_x);

    for (int i = 0; i < size_x; i++)
    {
        map[i].resize(size_y);
    }

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            file >> ch;

            map[i][j] = ch;

            if (!file)
            {
                map.resize(1);
                map[0].resize(1);
                map[0][0] = 'd';
                return;
            }
        }
    }

    file >> starter.x;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    file >> starter.y;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    file >> end.x;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    file >> end.y;
    if (!file)
    {
        map.resize(1);
        map[0].resize(1);
        map[0][0] = 'd';
        return;
    }

    file.close();
}
