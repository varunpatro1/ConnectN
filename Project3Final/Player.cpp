// Player.cpp

#include "provided.h"
#include "Support.h"
#include <string>
#include <iostream>
#include <stack>


using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

bool isComplete(Scaffold &s, int N, int &winner)
{
    if (s.numberEmpty() == (s.cols() * s.levels())) // if empty grid, then we haven't completed
    {
        return false;
    }

    Scaffold copy = s; // copy the grid exacly
    int last_col = copy.undoMove(); // undo the most recent move on the copied grid
    int last_color = -1;
    int c = 0;
    int r = 0;
    stack <Coord> moves;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //FIND WHERE LAST TOKEN WAS PLACED
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < s.levels(); i++)
    {
        if (s.checkerAt(last_col+1, s.levels()-i) != VACANT) // top-down search of the column
        {
            last_color = s.checkerAt(last_col+1, s.levels()-i); // winning color
            c = last_col+1; // c and r are board coordinates
            r = s.levels()-i;
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
        if ((r >= 1) && (s.checkerAt(c,r) == last_color)) // not lower bottom row and spot is same color
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
        if ((c <= s.cols()) && (s.checkerAt(c,r) == last_color)) // if c is still in the board and the correct color
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
        if ((c >= 1) && (s.checkerAt(c,r) == last_color))
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
        if ((c <= s.cols()) && (r <= s.levels()) && (s.checkerAt(c,r) == last_color))
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
        if ((c >= 1) && (r >= 1) && (s.checkerAt(c,r) == last_color))
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
        if ((c <= s.cols()) && (r >= 1) && (s.checkerAt(c,r) == last_color))
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
        if ((c >= 1) && (r <= s.levels()) && (s.checkerAt(c,r) == last_color))
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

    if (s.numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
    
    
}

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    int c;
    while (true)
    {
        cout << "Enter the column you wish to drop in" << endl;
        cin >> c;
        //cin.ignore();
        if (c >= 1 && c <= s.cols()) // if valid move
        {
            for (int r = 1; r <= s.levels(); r++)
            {
                if (s.checkerAt(c,r) == VACANT)
                {
                    return c;
                }
            }
            return 0;
        }
    }
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    for (int c = 1; c <= s.cols(); c++)
    {
        for (int r = 1; r <= s.levels(); r++)
        {
            if (s.checkerAt(c,r) == VACANT)
            {
                return c;
            }
        }
    }
    // if no vacancies
    return 0;
}

int rate (Scaffold &s, int N, int color, int toPlay, bool isMax, int depth, AlarmClock& ac)
{
    int nextToPlay;
    if (toPlay == RED){ // if red moved last
        nextToPlay = BLACK;
    }
    else{
        nextToPlay = RED;
    }
    int winner = -50;
    
    // base case
    if (isComplete(s, N, winner)){ // if game is over
        if (winner == TIE_GAME){ // tie case
//            for(int i = 0; i < depth; i++){
//                cout << " ";
//            }
            //cout << "TIE GAME: " << depth << endl;
            return 0;
        }
        else if (winner != color){ // smart player loses
//            for(int i = 0; i < depth; i++){
//                cout << " ";
//            }
            //cout << "WE LOSE: " << depth << " rating: " << (-100000 - s.numberEmpty()) << endl;
            return (-100000 - s.numberEmpty());
            //return (-1*(100 - depth));
        }
        else{ // smart player wins
//            for(int i = 0; i < depth; i++){
//                cout << " ";
//            }
            //cout << "WE WON: " << depth << " rating: " << (100000 + s.numberEmpty())<< endl;
            return (100000 + s.numberEmpty());
            //return (100 - depth);
        }
    }
    else{ // game is not complete, so recurse
        Scaffold copy = s; // copy scaffold
        stack<int> potential_moves; // for viable moves
        int bestRating = -100;;
        if (ac.timedOut())
        {
            return bestRating;
        }
        for (int c = 1; c <= s.cols(); c++){ // checks each column
            if (s.checkerAt(c, s.levels()) == VACANT){ // if a column is vacant, push onto stack
                potential_moves.push(c);
            }
        }
        if (ac.timedOut()) // if time is up, return best currently found move
        {
            return bestRating;
        }
        while (!(potential_moves.empty())){ // iterate through each possible column
//            for(int i = 0; i < depth; i++){
//                cout << " ";
//            }
            //cout << "internal move for color " << toPlay << ": " << potential_moves.top() << " with d=" << depth << "and isMax=" << isMax << endl;
            copy.makeMove(potential_moves.top(), toPlay);
            //cout << potential_moves.top() << endl;
            //cout << "Calling rate" << endl;
            if (ac.timedOut())
            {
                return bestRating;
            }
            int rating = rate(copy,N,color,nextToPlay,!isMax, depth+1,ac);
            if (ac.timedOut())
            {
                return bestRating;
            }
            //cout << "rating: "<< potential_moves.top() <<" " << rating << endl;
            //cout << "Ending rate" << endl;
            if (bestRating == -100){
                bestRating = rating;
            }
            else if(isMax){ // if we are maximizing
                if (rating > bestRating){
                    bestRating = rating;
                }
            }
            else{ // if we are minimizing
                if (rating < bestRating){
                    bestRating = rating;
                }
            }
            copy.undoMove(); // undo the move and pop it
            potential_moves.pop();
        }
//        s.display();
//        copy.display();
        return bestRating;
    }
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    AlarmClock ac (9900);
    stack <int> potential_moves; // to keep track of viable moves
    Scaffold copy = s;
    
    int toPlay; // create a variable that represent the opposite color
    if (color == RED){ // if red moved last
        toPlay = BLACK;
    }
    else{
        toPlay = RED;
    }

    for (int c = 1; c <= s.cols(); c++){ // checks each column
        if (s.checkerAt(c, s.levels()) == VACANT){ // if a column is vacant, push onto stack
            potential_moves.push(c);
        }
    }

    int maxMove = 0;
    int maxRating = -1000000;
    while (!(potential_moves.empty())){ // iterate through each possible column
        copy.makeMove(potential_moves.top(), color); // make the move on copy
        int rating = rate(copy, N, color, toPlay, false, 0, ac); // rate down tree to get current scaffold rating
        //cout << "CHECKING MOVE: " << potential_moves.top() << " rating: " << rating << endl;
        if (rating > maxRating){
            maxRating = rating; // set value
            maxMove = potential_moves.top(); // set value to move we are examining
        }
        potential_moves.pop(); // move on to examining next move
        copy.undoMove(); // undo the move
    }
    return maxMove;
}



//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

