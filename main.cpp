// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
//    string name;
//    cout << "What's your name?  ";
//
//    getline(cin, name);
    HumanPlayer hp("Sam");
    SmartPlayer sp("Noe");
    Game g1(3,3,3, &hp, &sp);
    g1.play();
//    cout << endl << "This time I'll go first." << endl;
//    Game g2(4, 3, 3, &sp, &hp);
//    g2.play();
    
//    Scaffold s(3, 2);
//        s.makeMove(2, RED);
//        s.makeMove(1, BLACK);
//        s.makeMove(1, RED);
//        s.display();
//        //  |R| | |
//        //  |B|R| |
//        //  +-+-+-+
//        s.undoMove();
//        s.display();
//        //  | | | |
//        //  |B|R| |
//        //  +-+-+-+
//        s.undoMove();
//        s.display();
//        //  | | | |
//        //  | |R| |
//        //  +-+-+-+
}

//#include "provided.h"
//    #include <iostream>
//    #include <cassert>
//    using namespace std;
//
//    void doScaffoldTests()
//    {
//        Scaffold s(3, 2);
//        assert(s.cols() == 3  &&  s.levels() == 2  &&
//                        s.numberEmpty() == 6);
//        assert(s.makeMove(1, RED));
//        assert(s.makeMove(1, BLACK));
//        assert(!s.makeMove(1, RED));
//        assert(s.numberEmpty() == 4);
//        assert(s.checkerAt(1, 1) == RED  &&  s.checkerAt(1, 2) == BLACK);
//        assert(s.checkerAt(2, 1) == VACANT);
//        s.display();
//    }
//
//    int main()
//    {
//        doScaffoldTests();
//        cout << "Passed all tests" << endl;
//    }

//#include "provided.h"
//    #include <iostream>
//    #include <cassert>
//    using namespace std;
//
//    void doPlayerTests()
//    {
//        HumanPlayer hp("Marge");
//        assert(hp.name() == "Marge"  &&  hp.isInteractive());
//        BadPlayer bp("Homer");
//        assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//        SmartPlayer sp("Lisa");
//        assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//        Scaffold s(3, 2);
//        s.makeMove(1, RED);
//        s.makeMove(1, BLACK);
//        cout << "=========" << endl;
//        int n = hp.chooseMove(s, 3, RED);
//        cout << "=========" << endl;
//        assert(n == 2  ||  n == 3);
//        n = bp.chooseMove(s, 3, RED);
//        assert(n == 2  ||  n == 3);
//        n = sp.chooseMove(s, 3, RED);
//        assert(n == 2  ||  n == 3);
//    }
//
//    int main()
//    {
//        doPlayerTests();
//        cout << "Passed all tests" << endl;
//    }

//#include "provided.h"
//    #include <iostream>
//    #include <cassert>
//    using namespace std;
//
//    void doGameTests()
//    {
//        BadPlayer bp1("Bart");
//        BadPlayer bp2("Homer");
//        Game g(2, 2, 2, &bp1, &bp2);
//        int winner;
//        assert(!g.completed(winner));
//        g.takeTurn();  // Red's first move
//        assert(!g.completed(winner)  &&
//                    (g.checkerAt(1, 1) == RED  ||  g.checkerAt(2, 1) == RED));
//        g.takeTurn();  // Black's first move
//        assert(!g.completed(winner));
//        g.takeTurn();  // Red's second move; Red must win
//        assert(g.completed(winner)  &&  winner == RED);
//    }
//
//    int main()
//    {
//        doGameTests();
//        cout << "Passed all tests" << endl;
//    }

