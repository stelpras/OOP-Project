
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <array>
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
    int medical;

public:
    Figures(int x=0, int y=0) {
        srand(time(NULL));
        posx = x;
        posy = y;
        health = 10;
        attack = (rand() % 3) + 1;
        medical = (rand() % 3);
        defence = (rand() % 2) + 1;
        //cout << "Make a Figure" << endl;
    }
    int get_x() {
        return posx;
    }
    int get_y() {
        return posy;
    }
    void set_x(int in_x) {
        posx = in_x;
    }
    void set_y(int in_y) {
        posy = in_y;
    }
};

class Warewolves :public Figures {
public:
    Warewolves(int x=0, int y=0) :Figures(x, y) {
        x = get_x();
        y = get_y();
        cout << "Make a warewolf" << " " << x << " " << y << endl;
    }
};

class Vampires :public Figures {
public:
    Vampires(int x=0, int y=0) :Figures(x, y) {
        x = get_x();
        y = get_y();
        cout << "Make a Vampire" << " " << x << " " << y << endl;
    }
};

class Avatar :public Figures {
private:
    char Team=' ';

public:
    Avatar(int x=0, int y=0) :Figures(x, y) {
        x = get_x();
        y = get_y();
    }

    void Set_team(char team) {
        Team = team;
    }

    char Get_team() {
        return Team;
    }

};


vector< array<int, 2 >> start(vector<Figures *> &war, vector<Figures *> &vam, Avatar &pl) {
    
    int x, y;
    int counter = 0;
    char team;

    cout << "Please initialize the map" << endl << "x:";
    cin >> x;
    cout << "y: ";
    cin >> y;

    vector < array<int, 2 >> pos = vector<array<int, 2>>();

    for (int i = 0; i < x; i++) {
        //cout << endl;
        for (int j = 0; j < y; j++) {

            array<int, 2> p;
            p[0] = i;
            p[1] = j;
            //cout << "- ";
            pos.push_back(p);

            counter++;

        }
    }

    srand(time(NULL));
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

    //Warewolves set to a start position
    for (int i = 0; i < ((x * y) / 15); i++) {

        int xy = (rand() % pos.size()) - 1;
        array<int, 2> posxy = pos.at(xy);
        array<int, 2> temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);

        Figures* w = new Warewolves(posxy[0], posxy[1]);
        war.push_back(w);
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

        Figures* v = new Vampires(posxy[0], posxy[1]);
        vam.push_back(v);
    }
    //Make Avatar and place it to a start position
    int xy = (rand() % pos.size()) - 1;
    array<int, 2> posxy = pos.at(xy);
    array<int, 2> temp = pos.at(xy);

    pos.at(xy) = pos.at(pos.size() - 1);
    pos.push_back(temp);
    pos.pop_back();
    pos.resize(pos.size() - 1);

    pl.set_x(posxy[0]);
    pl.set_y(posxy[1]);
    cout << "Make an Avatar" << " " << posxy[0] << " " << posxy[1] << endl;
    cout << "Please choose your team" << endl;
    cin >> team;
    pl.Set_team(team);
    cout << pl.Get_team() << endl;

    return pos;
}

int main()
{


    vector<Figures*> w,v= vector <Figures*>();
    Avatar player;
    vector< array<int, 2 >> empty_coor = start(w,v,player);

    //test
    cout << endl <<"Avatar " << player.get_x() << "," << player.get_y();




    return 0;
}


