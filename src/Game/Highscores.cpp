#include "Highscores.h"

#include <fstream>
#include <string>
#include <sstream>

#include "../Console/Colors.h"
#include "../Console/Constants.h"
#include "../Console/Input.h"
#include "../Console/Renderer.h"

void Highscores::loadHighscores() {
    ifstream fin("highscores.csv");
    records.clear();

    if (!fin.is_open()) {
        return;
    }

    string line;
    int record_count = 0;

    while (getline(fin, line) && record_count < 5) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string name, score_str, min_str, sec_str;

        if (getline(ss, name, ',') && getline(ss, score_str, ',') &&
            getline(ss, min_str, ':') && getline(ss, sec_str)) {

            if (!name.empty() && !score_str.empty() && !min_str.empty() &&
                !sec_str.empty()) {

                try {
                    Result temp;
                    temp.name = name;
                    temp.score = stoi(score_str);
                    temp.play_time.min = stoi(min_str);
                    temp.play_time.sec = stoi(sec_str);

                    if (temp.score >= 0 && temp.play_time.min >= 0 &&
                        temp.play_time.sec >= 0 && temp.play_time.sec < 60) {
                        records.push_back(temp);
                        record_count++;
                    }
                } catch (...) {
                    continue;
                }
            }
        }
    }
    fin.close();
}

void Highscores::updateHighscores(Result result) {
    bool isUpdated = false;

    for (int i = 0; i < records.size(); i++) {
        if (result > records[i]) {
            records.insert(records.begin() + i, result);
            isUpdated = true;
            break;
        }
    }

    if (!isUpdated && records.size() < 5) {
        records.push_back(result);
    }

    // remove top 6
    if (records.size() > 5) {
        records.pop_back();
    }

    // print score again
    ofstream fout("highscores.csv");
    for (int i = 0; i < records.size(); i++) {
        fout << records[i].toCSV() << endl;
    }
    fout.close();
}

void Highscores::displayHighscores() {
    Renderer::goTo((CONSOLE_WIDTH - 10) / 2, 17);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
    cout << "Highscores";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    Renderer::drawBox((CONSOLE_WIDTH - 70) / 2, 20, 70, 13);
    Renderer::goTo(52, 22);
    cout << string(68, HORIZONTAL_EDGE);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    Renderer::goTo(55, 21);
    cout << "Rank";
    Renderer::goTo(65, 21);
    cout << "Name";
    Renderer::goTo(100, 21);
    cout << "Score";
    Renderer::goTo(110, 21);
    cout << "Time";
    for (int i = 0; i < records.size(); i++) {
        if (i == 0) {
            Renderer::changeTextColor(Colors::bgMainBg, TEXT_ORANGE);
        } else {
            Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
        }
        Renderer::goTo(55, 23 + 2 * i);
        cout << i + 1;
        Renderer::goTo(65, 23 + 2 * i);
        cout << records[i].name;
        Renderer::goTo(100, 23 + 2 * i);
        cout << records[i].score;
        Renderer::goTo(110, 23 + 2 * i);
        cout << records[i].play_time;
    }

    Renderer::goTo(70, 35);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PINK);
    cout << "Press ESC to go back to the main menu";
    while (InputHandler::getInput() != Input::ESCAPE)
        ;

    // clean up
    for (int i = 17; i <= 35; i++) {
        Renderer::goTo(50, i);
        cout << string(100, ' ');
    }
}