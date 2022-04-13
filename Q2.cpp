#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// For searching in all 8 direction
int x[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // dir 0 2 5 7
int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// This function searches in
// all 8-direction from point
// (row, col) in grid[][]
bool search2D(char *grid, int row, int col, string word, int R, int C, int &filer, int &filec, int &lastr, int &lastc)
{
    // If first character of word doesn't
    // match with given starting point in grid.
    if (*(grid + row * C + col) != word[0])
        return false;

    int len = word.length();

    // Search word in all 8 directions
    // starting from (row, col)
    for (int dir = 0; dir < 8; dir++)
    {
        // Initialize starting point
        // for current direction
        int k, rd = row + x[dir], cd = col + y[dir];

        // First character is already checked,
        // match remaining characters
        for (k = 1; k < len; k++)
        {
            // If out of bound break
            if (rd >= R || rd < 0 || cd >= C || cd < 0)
            {
                break;
            }
            // If not matched,  break
            if (*(grid + rd * C + cd) != word[k])
            {
                break;
            }

            // Moving in particular direction
            rd += x[dir], cd += y[dir];
        }

        // If all character matched, then value of k must
        // be equal to length of word
        if (k == len)
        {
            if (dir == 0)
            {
                rd = rd + 1;
                cd = cd + 1;
            }
            else if (dir == 1)
            {
                rd = rd + 1;
            }
            else if (dir == 2)
            {
                rd = rd + 1;
                cd = cd - 1;
            }
            else if (dir == 3)
            {
                cd = cd + 1;
            }
            else if (dir == 4)
            {
                cd = cd - 1;
            }
            else if (dir == 5)
            {
                rd = rd - 1;
                cd = cd + 1;
            }
            else if (dir == 6)
            {
                rd = rd - 1;
            }
            else
            {
                cd = cd - 1;
                rd = rd - 1;
            }
            lastr = rd;
            lastc = cd;
            return true;
        }
    }
    return false;
}

// Searches given word in a given
// matrix in all 8 directions
void patternSearch(char *grid, string word,
                   int R, int C, int &filer, int &filec, int &lastr, int &lastc, int &chk)
{
    // Consider every point as starting
    // point and search given word
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            if (search2D(grid, row, col, word, R, C, filer, filec, lastr, lastc))
            {
                
                filer = row;
                filec = col;
            }
        }
    }
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            if (search2D(grid, row, col, word, R, C, filer, filec, lastr, lastc))
            {
                chk = 1;
                return;
            }
            else
            {
                chk++;
            }
        }
    }
}

int main()
{
    int exist = 69;
    char option;
    string word;
    int R = 10, C = 10;
    int filer = 0, filec = 0, lastr = 0, lastc = 0;
    char grid[10][10];
    ifstream fin("puzzle.txt", ios::in);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fin >> grid[i][j];
        }
    }

    fin.close();

    cout << "Enter 1 to exit or any key to continue" << endl;
    cin >> option;
    ofstream fout("pzloutput.txt");
    while (option != '1')
    {
        int chk = 0;
        cout << "Enter guess word inside the puzzle" << endl;
        cin >> word;
        patternSearch((char *)grid, word, R, C, filer, filec, lastr, lastc, chk);
        if (chk == 1)
        {
            fout << "The starting index of the word is " << filer << " " << filec << endl;
            fout << "The ending index of the word is " << lastr << " " << lastc << endl;
        }
        else if(chk > 1)
        {
            fout << "Word not found" << endl;
        }
        cout << "Enter 1 to exit or any key to continue" << endl;
        cin >> option;
    }
    fout.close();
    cout << endl;
    return 0;
}