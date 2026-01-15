#ifndef BOARDRENDER_H
#define BOARDRENDER_H

#include <fstream>
#include <queue>
#include <string>

#include "../Board/Board.h"
#include "../Board/Coordinate.h"
#include "../Console/Colors.h"
#include "../Console/Console.h"
#include "../Console/Constants.h"
#include "../Console/Renderer.h"

using namespace std;

class BoardRenderer {
protected:
    int cell_width = 10;
    int cell_height = 4;
    int x_offset;
    int y_offset;
    string *background;
    string bg_info;
    int height, width;
    Board *board; // Reference to board for getting letters

public:
    BoardRenderer(Board *gameBoard, int difficulty);
    virtual ~BoardRenderer();

    // Loading the corresponding background based on difficulty
    void loadBackground(int difficulty);

    // Display methods
    // Display the board in the terminal
    void displayBoard();
    // Display the letter in the terminal
    void displayLetter();

    // Highlight methods
    // Highlight the cell at position pos with color specified
    void highlightCell(Coordinate pos, string bg_color,
                       string text_color = Colors::txtHighlightLetter);
    // Unhighlight the cell at position pos
    void unhighlightCell(Coordinate pos);
    // Highlighting the cursor at pos
    void highlightCursor(Coordinate pos);
    // Highlight the selected cell at pos
    void highlightSelected(Coordinate pos);
    // Highlight the correct pair with green color
    void highlightCorrectPair(Coordinate pos1, Coordinate pos2);
    // Highlight the wrong pair with red color
    void highlightWrongPair(Coordinate pos1, Coordinate pos2);
    // Highlight the hinted pair with color purple
    void highlightHintPair(Coordinate pos1, Coordinate pos2);

    // Animation methods
    // Draw the path between the two valid cells
    queue<Coordinate> drawPath(vector<Coordinate> path);
    // Delete the path after displaying
    virtual void deletePath(queue<Coordinate> drawn_pixels, Coordinate pos1,
                            Coordinate pos2);
    // Animating the shuffle effect
    void animateShuffle();
    // Render the removed cell with appropriate display
    virtual void renderRemovedCell(Coordinate pos);

    // Getters
    string getBackgroundInfo() const { return bg_info; }
};

#endif