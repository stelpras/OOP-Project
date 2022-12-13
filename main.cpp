
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include<array>
#include <conio.h>


using namespace std;

#define KEY_UP 256+ 72
#define KEY_DOWN 256+ 80
#define KEY_LEFT 256+75
#define KEY_RIGHT 256+77

class Figures {
private:
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
        //cout << "Make a Figure" << endl;
    }

    int get_position() {
        return posx;
    }

};

class Warewolves :public Figures {
public:
    Warewolves(int px, int py) :Figures(px, py) {
        cout << "Make a warewolf" << " " << px << " " << py << endl;
    }

};

class Vampires : Figures {
public:
    Vampires(int px, int py) :Figures(px, py) {
        cout << "Make a Vampire" << " " << px << " " << py << endl;
    }
};

class Avatar :public Figures {
private:
    char Team;

public:
    Avatar(int px, int py) :Figures(px, py) {
        cout << "Make an Avatar" << " " << px << " " << py << endl;
    }

    void Set_team(char team) {
        Team = team;
    }

    char Get_team() {
        return Team;
    }



    void Move() {

        long int c = 0;
        c = _getch();
        cout << c << endl;
        switch ((c = _getch())) {

        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }


    }
};



int main()
{
    srand(time(0));
    int t, x, y;
    int counter = 0;
    char team;

    cout << "Please initialize the the map" << endl << "x:";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << "Please choose your team" << endl;
    cin >> team;
    vector<Warewolves> War = vector<Warewolves>();
    vector<Vampires> Vam = vector<Vampires>();
    vector < array<int, 2 >> pos = vector<array<int, 2>>();

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            array<int, 2> p;
            p[0] = i;
            p[1] = j;
            pos.push_back(p);


            counter++;

        }
    }



    //Warewolves set to a start position
    for (int i = 0; i < ((x * y) / 15); i++) {

        int xy = (rand() % pos.size()) - 1;
        array<int, 2> posxy = pos.at(xy);
        array<int, 2> temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);

        Warewolves w(posxy[0], posxy[1]);
        War.push_back(w);
    }

    //Vampires set to a start position
    for (int i = 0; i < ((x * y) / 15); i++) {
        int xy = (rand() % pos.size()) - 1;
        array<int, 2> posxy = pos.at(xy);
        array<int, 2> temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);

        Vampires v(posxy[0], posxy[1]);
        Vam.push_back(v);
    }

    //set the sea and the trees
    for (int i = 0; i < (x * y) / 5; i++) {
        int xy = (rand() % pos.size()) - 1;
        array<int, 2> posxy = pos.at(xy);
        array<int, 2> temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);
    }

    //Make Avatar
    int xy = (rand() % pos.size()) - 1;
    array<int, 2> posxy = pos.at(xy);
    array<int, 2> temp = pos.at(xy);

    pos.at(xy) = pos.at(pos.size() - 1);
    pos.push_back(temp);
    pos.pop_back();
    pos.resize(pos.size() - 1);

    Avatar player(posxy[0], posxy[1]);
    player.Set_team(team);
    cout << player.Get_team() << endl;

    player.Move();


    cin >> t;
    cout << t;

}


