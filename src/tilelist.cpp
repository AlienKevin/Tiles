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
    if (back == nullptr) {
        back = new TileNode(x, y, width, height, color);
        front = back;
    } else {
        TileNode* oldBack = back;
        back = new TileNode(x, y, width, height, color);
        oldBack->next = back;
        back->prev = oldBack;
    }
}

void TileList::addFront(int x, int y, int width, int height, string color) {
    if (front == nullptr) {
        front = new TileNode(x, y, width, height, color);
        back = front;
    } else {
        TileNode* oldFront = front;
        front = new TileNode(x, y, width, height, color);
        oldFront->prev = front;
        front->next = oldFront;
    }
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

bool TileList::highlight(int x, int y) {
    TileNode* tempFront = front;
    while (tempFront != nullptr) {
        if (tempFront->contains(x, y)) {
            tempFront->color = "yellow";
            return true;
        }
        tempFront = tempFront->next;
    }
    return false;
}

bool TileList::lower(int x, int y) {
    // TODO: write this function
    return false;   // remove this
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
