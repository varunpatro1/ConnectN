//
//  Support.h
//  Project3
//
//  Created by Varun Patro on 5/11/21.
//

#ifndef Support_h
#define Support_h

#include "provided.h"
#include <stack>


class Coord
{
    public:
        Coord(int r, int c) : m_row(r), m_col(c) {}
    
        int r() const
        {
            return m_row;
        }
        int c() const
        {
            return m_col;
            
        }
    private:
        int m_row;
        int m_col;
};








#endif /* Support_h */
