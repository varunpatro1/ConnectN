// Scaffold.cpp

#include "provided.h"
#include "Support.h"
#include <vector>
#include <iostream>
#include <stack>
using namespace std;



class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
private:
    int m_cols;
    int m_levels;
    vector<vector<int>> m_grid;
    stack<Coord> move_board;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    // initialize data members
    m_cols = nColumns;
    m_levels = nLevels;
    if ((m_cols < 1) || (m_levels < 1)) // if either input is negative
    {
        cerr << "Invalid input" << endl;
        exit(0);
    }
    
    m_grid.resize(m_levels); // grid with desired number of rows
    for (int i = 0; i < m_levels; i++){
        m_grid[i].resize(m_cols); // desired number of cols
    }
    
    for (int i = 0; i < m_levels; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            m_grid[i][j] = VACANT; // make each spot in the grid vacant
        }
    }
}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    int count = 0;
    for (int i = 0; i < m_levels; i++) // iterate through and count vacancies
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (m_grid[i][j] == VACANT)
            {
                count++;
            }
        }
    }
    return count;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    return (m_grid[m_levels-level][column-1]); // map the given coordinates to the vector
}

void ScaffoldImpl::display() const
{
        
    vector<vector<char>> display_grid;
    display_grid.resize(m_levels+1); // expanded grid with desired number of columns
    for (int i = 0; i < (m_levels+1); i++){
        display_grid[i].resize((2*m_cols)+1); // desired number of rows in expanded form
    }
    
    for (int i = 0; i < ((2*m_cols)+1); i++)
    {
        if (i % 2 == 0)
        {
            display_grid[m_levels][i] = '+'; //set bottom row elements
        }
        else
        {
            display_grid[m_levels][i] = '-';
        }
    }
    
    for (int i = 0; i < m_levels; i++)
    {
        for (int j = 0; j < ((2*m_cols)+1); j++)
        {
            if (j % 2 == 0)
            {
                display_grid[i][j] = '|'; // display board lines
            }
        }
    }
    

    for (int i = 0; i < m_levels; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (m_grid[i][j] == VACANT)
            {
                display_grid[i][j + (j+1)] = ' '; // add in vacancies and R and B
            }
            if (m_grid[i][j] == RED)
            {
                display_grid[i][j + (j+1)] = 'R';
            }
            if (m_grid[i][j] == BLACK)
            {
                display_grid[i][j + (j+1)] = 'B';
            }
        }
    }
    
    for (int i = 0; i < m_levels+1; i++)
    {
        for (int j = 0; j < ((2*m_cols)+1); j++)
        {
            cout << display_grid[i][j]; // display everything
        }
        cout << "" << endl;
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    for (int i = m_levels-1; i >= 0; i--) // go through all levels
    {
        if (m_grid[i][column-1] == VACANT) // if vacancy, insert and return true
        {
            if (color == RED || color == BLACK)
            {
                m_grid[i][column-1] = color; // set color
                move_board.push(Coord(i,column-1)); // push the grid coordinate onto the stack
                return true;
            }
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    
    if (numberEmpty() == (m_cols*m_levels)) // if everything is empty, then don't undo anything
    {
        return 0;
    }
    
    m_grid[move_board.top().r()][move_board.top().c()] = VACANT; // make the last move a vacant spot
    int c = move_board.top().c(); // set the correct grid column
    move_board.pop(); // remove the coordinate from stack
    return c; // return in grid coordinates
    
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}

