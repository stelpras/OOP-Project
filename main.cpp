
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <array>
#include <conio.h>


using namespace std;


class Figures {
private:
    int px;
    int py;
    int health;
    int attack;
    int defence;
    int medical;

public:
    Figures(int x=0, int y=0) {
        srand(time(NULL));
        px = x;
        py = y;
        health = 10;
        attack = (rand() % 3) + 1;
        medical = (rand() % 3);
        defence = (rand() % 2) + 1;
        //cout << "Make a Figure" << endl;
    }
    int get_x() {
        return px;
    }
    int get_y() {
        return py;
    }
    void set_x(int in_x) {
        px = in_x;
    }
    void set_y(int in_y) {
        py = in_y;
    }
};

class Warewolves :public Figures {
public:
    char team ='W';
    Warewolves(int x=0, int y=0) :Figures(x, y) {
        x = get_x();
        y = get_y();
        cout << "Make a warewolf" << " " << x << " " << y << endl;
    }
};

class Vampires :public Figures {
public:
    char team = 'V';
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




class block {
    public:
        int x, y;
        block(int in_x= 0, int in_y = 0) {
            x = in_x;
            y = in_y;
        }
        bool operator==(const block& s) const {
            return x == s.x && y == s.y;
        }
        int get_x() {
            return x;
        }
        int get_y() {
            return y;
        }
        void set_x(int in_x) {
            x = in_x;
        }
        void set_y(int in_y) {
            y = in_y;
        }

};

vector<block> start(vector<Figures*>& war, vector<Figures*>& vam, Avatar& pl) {

    int x, y;
    int counter = 0;
    char team;

    cout << "Please initialize the map" << endl << "x:";
    cin >> x;
    cout << "y: ";
    cin >> y;

    vector < block> pos = vector<block>();

    for (int i = 0; i < x; i++) {
        //cout << endl;
        for (int j = 0; j < y; j++) {

            block p;
            p.set_x(i);
            p.set_y(j);
            //cout << "- ";
            pos.push_back(p);

            counter++;

        }
    }

    srand(time(NULL));
    //set the sea and the trees
    for (int i = 0; i < (x * y) / 5; i++) {
        int xy = (rand() % pos.size()) - 1;
        block posxy = pos.at(xy);
        block temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);
    }

    //Warewolves set to a start position
    for (int i = 0; i < ((x * y) / 15); i++) {

        int xy = (rand() % pos.size()) - 1;
        block posxy = pos.at(xy);
        block temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);

        Figures* w = new Warewolves(posxy.get_x(), posxy.get_y());
        war.push_back(w);
    }

    //Vampires set to a start position
    for (int i = 0; i < ((x * y) / 15); i++) {
        int xy = (rand() % pos.size()) - 1;
        block posxy = pos.at(xy);
        block temp = pos.at(xy);

        pos.at(xy) = pos.at(pos.size() - 1);
        pos.push_back(temp);
        pos.pop_back();
        pos.resize(pos.size() - 1);

        Figures* v = new Vampires(posxy.get_x(), posxy.get_y());
        vam.push_back(v);
    }
    //Make Avatar and place it to a start position
    int xy = (rand() % pos.size()) - 1;
    block posxy = pos.at(xy);
    block temp = pos.at(xy);

    pos.at(xy) = pos.at(pos.size() - 1);
    pos.push_back(temp);
    pos.pop_back();
    pos.resize(pos.size() - 1);

    pl.set_x(posxy.get_x());
    pl.set_y(posxy.get_y());
    cout << "Make an Avatar" << " " << posxy.get_x() << " " << posxy.get_y() << endl;
    cout << "Please choose your team" << endl;
    cin >> team;
    pl.Set_team(team);
    cout << pl.Get_team() << endl;

    return pos;
}

bool Legal_move(vector< block>& empty_blocks, block b) {
    vector< block>::iterator item;
    item = find(empty_blocks.begin(), empty_blocks.end(), b);
    if (item != empty_blocks.end())
    {
        cout << endl << "Element found";
        return true;
    }
    else
    {
        cout << endl << "Element not found";
        return false;
    }
}


int main()
{


    vector<Figures*> w,v= vector <Figures*>();
    Avatar player;
    vector<block> empty_coor = start(w,v,player);

    //test oi syntetagenes kai o vector einai swstes kai meta thn synarthsh
    cout << endl <<"Avatar " << player.get_x() << "," << player.get_y();
    cout << endl << empty_coor.size();


    //test an h legal move doyleyei
    block b;
    b.set_x(player.get_x());
    b.set_y(player.get_y());
    Legal_move(empty_coor, b); 



    return 0;
}


