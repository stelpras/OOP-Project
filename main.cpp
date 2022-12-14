
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
    Figures() {}
    Figures(int px, int py) {
        srand(time(NULL));
        posx = px;
        posy = py;
        health = 10;
        attack = (rand() % 3) + 1;
        medical = (rand() % 3);
        defence = (rand() % 2) + 1;
        //cout << "Make a Figure" << endl;
    }
    int get_position() {
        return posx;
    }
    void set_x(int in_x) {
        posx = in_x;
    }
    void set_y(int in_y) {
        posx = in_y;
    }


};

class Warewolves :public Figures {
public:
    Warewolves() {};
    Warewolves(int px, int py) :Figures(px, py) {
        Warewolves* w = new Warewolves;
        cout << "Make a warewolf" << " " << px << " " << py << endl;
    }

};

class Vampires :public Figures {
public:
    Vampires() {};
    Vampires(int px, int py) :Figures(px, py) {
        cout << "Make a Vampire" << " " << px << " " << py << endl;
    }
};

class Avatar :public Figures {
private:
    char Team;

public:
    Avatar() {}
    Avatar(int x, int y) :Figures(x, y) {
        cout << "Make an Avatar" << " " << x << " " << y << endl;
    }

    void Set_team(char team) {
        Team = team;
    }

    char Get_team() {
        return Team;
    }

};


vector< array<int, 2 >> start(vector<Warewolves*> &war, vector<Vampires*> &vam, Avatar &pl) {

    srand(time(NULL));
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

        Warewolves* w = new Warewolves;
        Warewolves x(posxy[0], posxy[1]);
        w = &x;
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

        Vampires * v = new Vampires;
        Vampires  x(posxy[0], posxy[1]);
        v = &x;
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

    Avatar player(posxy[0], posxy[1]);
    cout << "Please choose your team" << endl;
    cin >> team;
    player.Set_team(team);
    cout << player.Get_team() << endl;



    return pos;
}

int main()
{


    vector<Warewolves*> w= vector <Warewolves *>();
    vector<Vampires *> v = vector <Vampires *>();
    Avatar player;
    //Make the map and put the players in vector or coordinates
    vector< array<int, 2 >> empty_coor = start(w,v,player);
    

    
    cout << endl << w.size();
    cout << endl << v.size();
    cout << endl << empty_coor.size();




}


