// WnV_the_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;


class Figures {
public:
    int posx;
    int posy;
    int health;
    int attack;
    int defence;
    int healthpoisons;

public:
    Figures(int px, int py) {
        srand(time(0));
        posx = px;
        posy = py;
        health = 10;
        attack = (rand() % 3) + 1;
        healthpoisons = (rand() % 3);
        defence = (rand() % 2) + 1;
        cout << "Make a Figure" << endl;
    }

    int get_position() {
        return posx;
    }

};

class Warewolves :public Figures {
public:
    Warewolves(int px, int py) :Figures(px, py) {
        cout << "Make a warewolf" << endl;
    }

};

class Vampires : Figures {
public:
    Vampires(int px, int py) :Figures(px, py) {
        cout << "Make a warewolf" << endl;
    }
    /*int get_position() {
        return Figures.get_position();
    }*/

};



int main()
{
    int t;
    Warewolves w(1, 1);
    cout << w.posx << " " << w.posy << " " << w.attack << " " << w.defence << endl;
    Vampires v(1, 1);

    cin >> t;
    cout << t;
    return 0;

}


