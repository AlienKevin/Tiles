// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#ifndef _tilelist_h
#define _tilelist_h

#include <iostream>
#include <string>
#include "gwindow.h"
#include "tilenode.h"
using namespace std;

class TileList {
public:
    TileList();
    ~TileList();
    void addBack(int x, int y, int width, int height, string color);
    void addFront(int x, int y, int width, int height, string color);
    void clear();
    void debug();
    void drawAll(GWindow& window) const;
    TileNode* getBack() const;
    TileNode* getFront() const;
    bool highlight(int x, int y);
    bool lower(int x, int y);
    void merge(int x, int y);
    bool raise(int x, int y);
    bool remove(int x, int y);
    int removeAll(int x, int y);

private:
    // TODO: add specified member variable
    
    // TODO: add any helper functions necessary

};

#endif // _tilelist_h
