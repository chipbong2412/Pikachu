#ifndef RESULT_H
#define RESULT_H

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// defining the time struct to count time elapsed
struct Time {
    int min, sec;

    Time() = default;

    Time(int seconds) {
        min = seconds / 60;
        sec = seconds % 60;
    }

    friend ostream &operator<<(ostream &os, const Time &t) {
        os << setfill('0') << setw(2) << t.min << ':' << setfill('0') << setw(2)
           << t.sec;
        return os;
    }

    bool operator<(Time &t) {
        return (((this->min) * 60 + this->sec) < (((t.min) * 60 + t.sec)));
    }
};

// define a record struct to save the information of the leaderboard
struct Result {
    string name;
    int score;
    Time play_time;

    bool operator>(Result &r) { // better score, if equal: better play time
        return ((score > r.score) ||
                ((score == r.score) && (play_time < r.play_time)));
    }

    string toCSV() {
        return (name + "," + to_string(score) + "," + to_string(play_time.min) +
                ":" + to_string(play_time.sec));
    };
};

#endif