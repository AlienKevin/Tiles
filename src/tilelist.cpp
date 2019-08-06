#include "tilelist.h"
#include <algorithm>
#include "strlib.h"
using namespace std;

TileList::TileList() {
    front = nullptr;
    back = nullptr;
}

TileList::~TileList() {
    while (front != nullptr) {
        TileNode* tempFront = front;
        front = front->next;
        delete tempFront;
    }
}

void TileList::addBack(int x, int y, int width, int height, string color) {
    TileNode* newNode = new TileNode(x, y, width, height, color);
    addBack(newNode);
}

void TileList::addBack(TileNode* tile) {
    if (back == nullptr) {
        back = tile;
        front = back;
    } else {
        TileNode* oldBack = back;
        back = tile;
        oldBack->next = back;
        back->prev = oldBack;
    }
}

void TileList::addFront(TileNode* tile) {
    if (front == nullptr) {
        front = tile;
        back = front;
    } else {
        TileNode* oldFront = front;
        front = tile;
        oldFront->prev = front;
        front->next = oldFront;
    }
}

void TileList::addFront(int x, int y, int width, int height, string color) {
    TileNode* newNode = new TileNode(x, y, width, height, color);
    addFront(newNode);
}

void TileList::clear() {
    // TODO: write this function

}

void TileList::debug() {
    // TODO: write this function (optional)

}

void TileList::drawAll(GWindow& window) const {
    TileNode* tempBack = back;
    while (tempBack != nullptr) {
        tempBack->draw(window);
        tempBack = tempBack->prev;
    }
}

TileNode* TileList::getBack() const {
    return back;
}

TileNode* TileList::getFront() const {
    return front;
}

TileNode* TileList::findTopTile(int x, int y) {
    TileNode* tempFront = front;
    while (tempFront != nullptr) {
        if (tempFront->contains(x, y)) {
            return tempFront;
        }
        tempFront = tempFront->next;
    }
    return nullptr;
}

bool TileList::highlight(int x, int y) {
    TileNode* topTile = findTopTile(x, y);
    if (topTile != nullptr) {
        topTile->color = "yellow";
        return true;
    }
    return false;
}

bool TileList::lower(int x, int y) {
    TileNode* topTile = findTopTile(x, y);
    if (topTile != nullptr) {
        /******** tile is at the back *********/
        // tile is already lowered
        if (topTile == back) {
            return true;
        }
        /******** tile is at the front *********/
        // no previous tile
        if (topTile == front) {
            front = topTile->next;
            front->prev = nullptr;
            addBack(topTile);
            return true;
        }
        /******** tile is in the middle *********/
        // skipping the tile found
        topTile->prev->next = topTile->next;
        topTile->next->prev = topTile->prev;
        // move the tile to back
        addBack(topTile);
        return true;
    }
    return false;
}

void TileList::merge(int x, int y) {
    // TODO: write this function
    
}

bool TileList::raise(int x, int y) {
    // TODO: write this function
    return false;   // remove this
}

bool TileList::remove(int x, int y) {
    // TODO: write this function
    return false;   // remove this
}

int TileList::removeAll(int x, int y) {
    // TODO: write this function
    return 0;   // remove this
}
