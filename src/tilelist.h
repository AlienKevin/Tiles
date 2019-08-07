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
#ifndef _tilelist_h
#define _tilelist_h

#include <iostream>
#include <string>
#include "gwindow.h"
#include "tilenode.h"
using namespace std;

class TileList {
public:
    /**
     * @brief Constructor for the doubly-linked list storing tiles
     */
    TileList();
    /**
     * @brief Destructor for this class that clears all allocated memory
     */
    ~TileList();
    /**
     * @brief Add a tile to the back of the screen
     * @param x the x coordinate of the tile
     * @param y the y coordinate of the tile
     * @param width the width of the tile
     * @param height the height of the tile
     * @param color the color of the tile
     */
    void addBack(int x, int y, int width, int height, string color);
    /**
     * @brief Add a tile to the front of the screen
     * @param x the x coordinate of the tile
     * @param y the y coordinate of the tile
     * @param width the width of the tile
     * @param height the height of the tile
     * @param color the color of the tile
     */
    void addFront(int x, int y, int width, int height, string color);
    /**
     * @brief Clear all tiles on screen
     */
    void clear();
    /**
     * @brief method used for debugging
     */
    void debug();
    /**
     * @brief Draw all tiles on screen
     * @param window the window to draw on
     */
    void drawAll(GWindow& window) const;
    /**
     * @brief Get the back-most tile on the screen
     * @return a pointer to the back-most tile
     */
    TileNode* getBack() const;
    /**
     * @brief Get the front-most tile on the screen
     * @return a pointer to the front-most tile
     */
    TileNode* getFront() const;
    /**
     * @brief Highlight the top-most tile yellow that contains position (x, y)
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return true if a tile is found and highlighted, false otherwise
     */
    bool highlight(int x, int y);
    /**
     * @brief Lower the top-most tile that contains position (x, y) to the back of the screen
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return true if a tile is found and lowered, false otherwise
     */
    bool lower(int x, int y);
    /**
     * @brief Merge all tiles that contains position (x, y) under a single bounding box
     * with the color of the top-most tile
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     */
    void merge(int x, int y);
    /**
     * @brief Raise the top-most tile that contains position (x, y) to the front of the screen
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return true if a tile is found and raised, false otherwise
     */
    bool raise(int x, int y);
    /**
     * @brief Remove the top-most tile that contains position (x, y)
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return true if a tile is found and removed, false otherwise
     */
    bool remove(int x, int y);
    /**
     * @brief Remove all tiles that contains position (x, y)
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return the number of tiles removed
     */
    int removeAll(int x, int y);

private:
    /**
     * @brief Pointer to the front of the doubly-linked list
     */
    TileNode* front;
    /**
     * @brief Pointer to the back of the doubly-linked list
     */
    TileNode* back;
    /**
     * @brief Find the top-most tile that contains the position (x, y)
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return true if a tile is found, false otherwise
     */
    TileNode* findTopTile(int x, int y);
    /**
     * @brief Remove a tile from the doubly-linked list
     * @param tile the tile to remove
     * @return true if the tile is removed (not a nullptr), false otherwise
     */
    bool remove(TileNode* tile);
    /**
     * @brief Add a tile to the back of the doubly-linked list
     * @param tile the tile to add to the back
     */
    void addBack(TileNode* tile);
    /**
     * @brief Add a tile to the front of the doubly-linked list
     * @param tile the tile to add to the front
     */
    void addFront(TileNode* tile);
};

#endif // _tilelist_h
