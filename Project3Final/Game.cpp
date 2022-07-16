// Game.cpp

#include "provided.h"
#include "Support.h"
#include <stack>
#include <iostream> //REMOVE LATER
using namespace std;


class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
    
private:
    Scaffold m_scaff;
    Player* red;
    Player* black;
    int N;
    
};


GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black):m_scaff(nColumns,nLevels)
{
    this->red = red;
    this->black = black;
    this->N = N;
}

bool GameImpl::completed(int& winner) const
{
    if (m_scaff.numberEmpty() == (m_scaff.cols() * m_scaff.levels())) // if empty grid, then we haven't completed
    {
        return false;
    }

    Scaffold copy = m_scaff; // copy the grid exacly
    int last_col = copy.undoMove(); // undo the most recent move on the copied grid
    int last_color = -1;
    int c = 0;
    int r = 0;
    stack <Coord> moves;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //FIND WHERE LAST TOKEN WAS PLACED
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < m_scaff.levels(); i++)
    {
        if (m_scaff.checkerAt(last_col+1, m_scaff.levels()-i) != VACANT) // top-down search of the column
        {
            last_color = m_scaff.checkerAt(last_col+1, m_scaff.levels()-i); // winning color
            c = last_col+1; // c and r are board coordinates
            r = m_scaff.levels()-i;
            break; // break so we don't keep going down the board
        }
    }

    // saved here because c and r will change but their values can be saved this way
    int save_c = c; // board coordinates of the last (winnning?) move
    int save_r = r;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //CHECK IF TOKENS BELOW ARE SAME COLOR
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Coord last(save_r,save_c);
    moves.push(last); // stack contains board coordinates
    int count = 0; // counter

    while (!(moves.empty()))
    {
        moves.pop();
        if ((r >= 1) && (m_scaff.checkerAt(c,r) == last_color)) // not lower bottom row and spot is same color
        {
            moves.push(Coord(r,c)); // push coordinate onto stack
            r = r-1; // decrease row by 1
            count++; // count the token
        }
    }
    if (count == N) // if we have N in a row
    {
        winner = last_color; // set winner appropriately
        return true; // game is complete
    } // if not, we check other directions


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //CHECK IF TOKENS RIGHT/LEFT ARE SAME COLOR
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    moves.push(last); // put last Coord on an empty stack
    count = 0; // reset counter because we're checking new direction
    c = save_c; // reset these values because they may have changed
    r = save_r;

    while (!(moves.empty()))
    {
        moves.pop();
        if ((c <= m_scaff.cols()) && (m_scaff.checkerAt(c,r) == last_color)) // if c is still in the board and the correct color
        {
            moves.push(Coord(r,c)); // store the coordinate
            c = c+1; // advance to the right
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }
    // if we haven't reached N, then look to the left
    moves.push(last);
    c = save_c-1; // start one space to the left of our starting Coord
    while (!(moves.empty()))
    {
        moves.pop();
        if ((c >= 1) && (m_scaff.checkerAt(c,r) == last_color))
        {
            moves.push(Coord(r,c)); // if same color, then push onto stack
            c = c-1; // move to the left
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //CHECK IF TOKENS DIAGONALLY(RU and LD) ARE SAME COLOR
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    moves.push(last);
    count = 0;
    c = save_c;
    r = save_r;

    while (!(moves.empty()))
    {
        moves.pop();
        if ((c <= m_scaff.cols()) && (r <= m_scaff.levels()) && (m_scaff.checkerAt(c,r) == last_color))
        {
            moves.push(Coord(r,c));
            c = c+1; // move to the right
            r = r+1; // move up
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }
    c = save_c-1; // reset our c and r but diagonally one down to the left
    r = save_r-1;
    moves.push(last);
    while (!(moves.empty()))
    {
        moves.pop();
        if ((c >= 1) && (r >= 1) && (m_scaff.checkerAt(c,r) == last_color))
        {
            moves.push(Coord(r,c));
            c = c-1;
            r = r-1;
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //CHECK IF TOKENS DIAGONALLY(RD and LU) ARE SAME COLOR
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    moves.push(last);
    count = 0;
    c = save_c;
    r = save_r;
    while (!(moves.empty()))
    {
        moves.pop();
        if ((c <= m_scaff.cols()) && (r >= 1) && (m_scaff.checkerAt(c,r) == last_color))
        {
            moves.push(Coord(r,c));
            c = c+1;
            r = r-1;
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }
    c = save_c-1;
    r = save_r+1;

    moves.push(last);
    while (!(moves.empty()))
    {
        moves.pop();
        if ((c >= 1) && (r <= m_scaff.levels()) && (m_scaff.checkerAt(c,r) == last_color))
        {
            moves.push(Coord(r,c));
            c = c-1;
            r = r+1;
            count++;
        }
    }
    if (count == N)
    {
        winner = last_color;
        return true;
    }

    if (m_scaff.numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
    
    
    // check if full
}

bool GameImpl::takeTurn()
{
    int winner;
    if (completed(winner)) // if completed, don't take turn
    {
        return false;
    }
    
    if (m_scaff.numberEmpty() == (m_scaff.cols()*m_scaff.levels())) // if board is empty
    {
        m_scaff.makeMove(red->chooseMove(m_scaff, N, RED), RED); // red goes first
    }
    else // if not empty
    {
        Scaffold copy = m_scaff; // create copy
        int last_col = copy.undoMove(); // find column of last move
        int last_player = -5;
        
        for (int i = m_scaff.levels(); i >= 1; i--) //
        {
            if (m_scaff.checkerAt(last_col+1, i) != VACANT)
            {
                last_player = m_scaff.checkerAt(last_col+1, i); // find color of last move and save it
                break;
            }
        }
        if (last_player == RED) // if it was red
        {
            m_scaff.makeMove(black->chooseMove(m_scaff, N, BLACK), BLACK); // make black play
        }
        else // if not
        {
            m_scaff.makeMove(red->chooseMove(m_scaff, N, RED), RED); // make red play
        }
    }
    return true;
}

void GameImpl::play()
{
    int winner;
    while (!(completed(winner))) // as long as the game is not done
    {
        takeTurn(); // make someone play
        m_scaff.display(); // display the board

        string s;
        cout << "Press any key to continue" << endl;
        cin >> s;
    }
    cout << winner << endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return (m_scaff.checkerAt(c, r));
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}

