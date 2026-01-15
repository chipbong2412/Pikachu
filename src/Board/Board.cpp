#include "Board.h"

bool Board::isInBoard(Coordinate p) {
    return !(p.x <= 0 || p.y <= 0 || p.y >= height + 1 || p.x >= width + 1);
}

bool Board::isBoardEmpty() {
    for (int i = 1; i < height + 1; i++) {
        for (int j = 1; j < width + 1; j++) {
            if (getLetter({j, i}) != 0)
                return false;
        }
    }
    return true;
}

bool Board::isValid(Coordinate pos) { return (getLetter(pos) != '#'); }

bool Board::isVisited(Coordinate point, vector<Coordinate> path) {
    while (!path.empty()) {
        if (point == path.back())
            return true;
        path.pop_back();
    }
    return false;
}

bool Board::bfs(Coordinate start, Coordinate end, vector<Coordinate> &path) {
    struct CurPoint {
        vector<Coordinate> path;
        Direction cur_dir;
        short turn_cnt;
    };

    //* bfs queue
    queue<CurPoint> q;

    //* store all valid paths from start to end
    queue<vector<Coordinate>> paths;

    Coordinate direction[] = {
        {0, -1}, // up
        {1, 0},  // right
        {-1, 0}, // left
        {0, 1}   // down
    };

    // push the first point into the queue
    q.push({{start}, NEUTRAL, 0});

    while (!q.empty()) {
        Coordinate cur_point = q.front().path.back(); // getting current point
        vector<Coordinate> cur_path =
            q.front().path; // getting the path leading up to the current point
        Direction cur_dir = q.front().cur_dir; // getting the current direction
        int cur_point_turn = q.front().turn_cnt; // getting the number of turns
        q.pop();

        // return the true and the path if the end point is reached
        if (cur_point == end) {
            paths.push(cur_path);
            path = cur_path;
            return 1;
        }

        // cheking all four neighboring points
        for (int i = 0; i < 4; i++) {
            Coordinate next_point =
                cur_point + direction[i]; // getting the next point
            vector<Coordinate> next_path =
                cur_path; // getting the path leading up to the next point
            Direction next_dir = (Direction)i; // getting the next direction
            short next_point_turn =
                cur_point_turn; // getting the number of turns

            if (0 <= next_point.y &&
                next_point.y <
                    height + 2 && // check if the next point is in the board
                0 <= next_point.x &&
                next_point.x < width + 2 &&
                (getLetter({next_point.x, next_point.y}) == '#' ||
                 next_point == end) && // check if it is valid to traverse (not
                                       // a normal letter)
                !isVisited(
                    next_point,
                    cur_path) // check if the next point has not been visited
            ) {
                // check if there is a change in direction
                if (cur_dir != NEUTRAL && cur_dir != next_dir) {
                    // if the number of turns is equal to two, skip this point
                    if (cur_point_turn == 2)
                        continue;
                    else
                        next_point_turn = cur_point_turn + 1;
                }

                next_path.push_back(next_point);
                q.push({next_path, next_dir, next_point_turn});
            }
        }
    }
    return 0;
}

bool Board::findValidPair(Coordinate &pos1, Coordinate &pos2) {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (isValid({j, i})) {
                char piece = getLetter({j, i});
                for (int k = i; k <= height; k++) {
                    for (int l = 0; l <= width; l++) {
                        vector<Coordinate> temp;
                        if (getLetter({l, k}) == piece && !(i == k && j == l) &&
                            bfs({j, i}, {l, k}, temp)) {
                            pos1 = {j, i};
                            pos2 = {l, k};
                            return 1;
                        }
                    }
                }
            }
        }
    }

    pos1 = {-1, -1};
    pos2 = {-1, -1};
    return 0;
}

void Board::printBoard() {
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            cout << getLetter({j, i}) << " ";
        }
        cout << endl;
    }
}