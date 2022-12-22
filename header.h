#pragma once

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <conio.h>


using namespace std;


class block {

public:
    int x, y;
    char pr;
    block(int in_x = 0, int in_y = 0, char in_pr = ' ');
    bool operator==(const block& s) const;


};



class Figures {
private:
    block b;
    int health;
    int attack;
    int defence;
    int medical;

public:
    Figures(block bl);

    block get_block() const;
    void set_block(block bl);
    int get_health() const;
    void set_health(int in_health);
    int get_attack() const;
    int get_defence() const;
    void set_defence(int in_defence);
    void set_medical(int in_medical);
    int get_medical() const;

    void Move(vector< block>& map, vector<block>& players_position);
    void Attack(Figures* enemy);
    void Heal(Figures* ally);
};

class Warewolves :public Figures {
public:
    Warewolves(block b) : Figures(b) {
        cout << "Make a warewolf" << " " << b.x << " " << b.y << endl;

    }
    void Move(vector< block>& map, vector<block>& players_position) {
        Figures::Move(map, players_position);
    }



};

class Vampires :public Figures {
public:

    Vampires(block b) :Figures(b) {
        cout << "Make a Vampire" << " " << b.x << " " << b.y << endl;
    }
    void Move(vector< block>& map, vector<block>& players_position);
};


class Avatar :public Figures {
private:
    char Team;
    int potions;

public:
    Avatar(block b) :Figures(b) {
        b = get_block();
        Team = ' ';
    }

    void set_team(char team);
    char get_team() const;
    void set_potion(int in_potions);
    int get_potions() const;
    void Move(vector< block>& map, vector<block>& players_position);

};

block start(int x, int y, vector<block>& map, vector<block>& erased, vector<block>& players_position, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& pl);
void play(vector<block>& map, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& player, vector<block>& players_position);
void print_map(int x, int y, vector<block>& map, vector<block>& erased, Avatar& player, block& magic_filter);