/**
 * Tiles assignment for CS106B at Stanford Summer Session 2019.
 * Author: Kevin Li
 * Description:
 * This program simulates a graphic window manager of an operating sytem
 * and allows users to move windows (or tiles) to the front, back, highlight a window,
 * remove a window, merge multiple windows under the cursor.
 * Implementation:
 * Tiles are stored as a doubly-linked list with its x and y coordinate
 * on screen, width, height, and color.
 */
#include "tilelist.h"
#include <algorithm>
#include "strlib.h"
using namespace std;

TileList::TileList() {
    front = nullptr;
    back = nullptr;
}

TileList::~TileList() {
    clear();
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
        back->next = nullptr;
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
        front->prev = nullptr;
    }
}

void TileList::addFront(int x, int y, int width, int height, string color) {
    TileNode* newNode = new TileNode(x, y, width, height, color);
    addFront(newNode);
}

void TileList::clear() {
    while (front != nullptr) {
        TileNode* tempFront = front;
        front = front->next;
        delete tempFront;
    }
    back = nullptr;
}

void TileList::debug() {
    // empty function
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
    TileNode* topTile = front;
    std::string topColor = "";
    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;
    while (topTile != nullptr) {
        if (topTile->contains(x, y)) {
            int topMinX = topTile->x;
            int topMinY = topTile->y;
            int topWidth =topTile->width;
            int topHeight = topTile->height;
            int topMaxX = topMinX + topWidth;
            int topMaxY = topMinY + topHeight;
            if (topColor == "") {
                topColor = topTile->color;
                minX = topMinX;
                maxX = topMaxX;
                minY = topMinY;
                maxY = topMaxY;
            }
            if (topMinX < minX) {
                minX = topMinX;
            } else if (topMaxX > maxX) {
                maxX = topMaxX;
            }
            if (topMinY < minY) {
                minY = topMinY;
            } else if (topMaxY > maxY) {
                maxY = topMaxY;
            }
            remove(topTile);
        }
        topTile = topTile->next;
    }
    addFront(minX, minY, maxX - minX, maxY - minY, topColor);
}

bool TileList::raise(int x, int y) {
    TileNode* topTile = findTopTile(x, y);
    if (topTile != nullptr) {
        /******** tile is at the front *********/
        // tile is already raised
        if (topTile == front) {
            return true;
        }
        /******** tile is at the back *********/
        // no next tile
        if (topTile == back) {
            back = topTile->prev;
            back->next = nullptr;
            addFront(topTile);
            return true;
        }
        /******** tile is in the middle *********/
        // skipping the tile found
        topTile->prev->next = topTile->next;
        topTile->next->prev = topTile->prev;
        // move the tile to front
        addFront(topTile);
        return true;
    }
    return false;
}

bool TileList::remove(int x, int y) {
    TileNode* topTile = findTopTile(x, y);
    return remove(topTile);
}

bool TileList::remove(TileNode* tile) {
    if (tile != nullptr) {
        /******** only contains a single tile *********/
        if (tile == front && tile == back) {
            front = nullptr;
            back = nullptr;
            return true;
        }
        /******** tile is at front *********/
        if (tile == front) {
            front = front->next;
            front->prev = nullptr;
            delete tile;
            return true;
        }
        /******** tile is at back *********/
        if (tile == back) {
            back = back->prev;
            back->next = nullptr;
            delete tile;
            return true;
        }
        /******** tile is in the middle *********/
        // skipping the tile found
        tile->prev->next = tile->next;
        tile->next->prev = tile->prev;
        delete tile;
        return true;
    }
    return false;
}

int TileList::removeAll(int x, int y) {
    TileNode* tempFront = front;
    int totalRemoved = 0;
    while (tempFront != nullptr) {
        if (tempFront->contains(x, y)) {
            remove(tempFront);
            totalRemoved ++;
        }
        tempFront = tempFront->next;
    }
    return totalRemoved;
}
