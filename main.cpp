
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <algorithm>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;



class block {

public:
    int x, y;

    block(int in_x = 0, int in_y = 0) {
        x = in_x;
        y = in_y;
    }
    bool operator==(const block& s) const {
        return x == s.x && y == s.y;
    }



};

bool exist_block(vector< block>& vec, block b) {
    vector< block>::iterator item;
    item = find(vec.begin(), vec.end(), b);
    if (item != vec.end())
    {
        //cout << endl << "Legal block";
        return true;
    }
    else
    {
        // << endl << "Not legal block";
        return false;
    }
}




class Figures {
private:
    block b;
    int health;
    int attack;
    int defence;
    int medical;

public:
    Figures(block bl) {
        b.x = bl.x;
        b.y = bl.y;
        srand((unsigned int)time(NULL));
        health = 10;
        attack = (rand() % 3) + 1;
        medical = (rand() % 3);
        defence = (rand() % 2) + 1;
    }
    block get_block() {
        return b;
    }
    void set_block(block bl) {
        b = bl;
    }
    int get_health() {
        return health;
    }
    void set_health(int in_health) {
        health = in_health;
    }
    int get_attack() {
        return attack;
    }
    int get_defence() {
        return defence;
    }
    void set_medical(int in_medical) {
        medical = in_medical;

    }
    int get_medical() {
        return medical;
    }
    void Move(vector< block>& map, vector<block>& players_position) {
        block previous_block, destination;
        previous_block = this->get_block();

        cout << "Warewolve previous block: " << previous_block.x << "," << previous_block.y << endl;


        int move = (rand() % 5); //5 possible moves
        cout << move << endl;
        switch (move) {

        case 0://stay in position
            destination.x = previous_block.x;
            destination.y = previous_block.y;
            break;
        case 1:
            //up
            destination.x = previous_block.x - 1;
            destination.y = previous_block.y;
            break;
        case 2:
            //down
            destination.x = previous_block.x + 1;
            destination.y = previous_block.y;
            break;
        case 3:
            //left
            destination.x = previous_block.x;
            destination.y = previous_block.y - 1;
            break;
        case 4:
            //right
            destination.x = previous_block.x;
            destination.y = previous_block.y + 1;
            break;


        }

        if (!exist_block(players_position, destination) && exist_block(map, destination)) {

            cout << "Warewolve current block: " << destination.x << "," << destination.y << endl;
            this->set_block(destination);
            players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
            players_position.push_back(destination);
        }
        else {
            cout << "Stay in position" << endl;
            cout << "Warewolve current block: " << previous_block.x << "," << previous_block.y << endl;
        }

    }
    void Attack(Figures* enemy) {
        int new_health = enemy->get_health() - (this->get_attack() - enemy->get_defence());
        enemy->set_health(new_health);
        cout << "Attack " << endl;

    }
    void Heal(Figures* ally) {
        if (ally->get_health() < 10 && this->get_medical() > 0) {
            ally->set_health(ally->get_health() + 1);
            this->set_medical(this->get_medical() - 1);
            cout << "heal" << endl;
        }

    }


};

class Warewolves :public Figures {
public:
    Warewolves(block b) : Figures(b) {
        b = get_block();
        cout << "Make a warewolf" << " " << b.x << " " << b.y << endl;
    }
    void Move(vector< block>& map, vector<block>& players_position) {
        Figures::Move(map, players_position);
    }

};

class Vampires :public Figures {
public:

    Vampires(block b) :Figures(b) {
        b = get_block();
        cout << "Make a Vampire" << " " << b.x << " " << b.y << endl;
    }
    void Move(vector< block>& map, vector<block>& players_position) {
        block previous_block = this->get_block(), destination;
        cout << "Vampire previous block: " << previous_block.x << "," << previous_block.y << endl;
        srand((unsigned int)time(NULL));


        int move = (rand() % 9); //9 possible moves
        cout << move << endl;
        switch (move) {

        case 0://stay in position
            destination.x = previous_block.x;
            destination.y = previous_block.y;
            break;
        case 1:
            //up
            destination.x = previous_block.x - 1;
            destination.y = previous_block.y;
            break;
        case 2:
            //down
            destination.x = previous_block.x + 1;
            destination.y = previous_block.y;
            break;
        case 3:
            //left
            destination.x = previous_block.x;
            destination.y = previous_block.y - 1;
            break;
        case 4:
            //right
            destination.x = previous_block.x;
            destination.y = previous_block.y + 1;
            break;
        case 5:
            //left up
            destination.x = previous_block.x - 1;
            destination.y = previous_block.y - 1;
            break;
        case 6:
            //left down
            destination.x = previous_block.x + 1;
            destination.y = previous_block.y - 1;
            break;
        case 7:
            //right up
            destination.x = previous_block.x - 1;
            destination.y = previous_block.y + 1;
            break;
        case 8:
            //right down
            destination.x = previous_block.x + 1;
            destination.y = previous_block.y + 1;
            break;
        }

        if (!exist_block(players_position, destination) && exist_block(map, destination)) {

            cout << "Vampire current block: " << destination.x << "," << destination.y << endl;
            this->set_block(destination);
            players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
            players_position.push_back(destination);
        }
        else {
            cout << "Stay in position" << endl;
            cout << "Vampire current block: " << previous_block.x << "," << previous_block.y << endl;
        }




    }

};


class Avatar :public Figures {
private:
    char Team = ' ';

public:
    Avatar(block b) :Figures(b) {
        b = get_block();
    }

    void Set_team(char team) {
        Team = team;
    }

    char Get_team() {
        return Team;
    }
    void Move(vector< block>& map, vector<block>& players_position) {
        int c = _getch();
        cout << c << endl;
        cout << "Please make a move: " << endl;
        block previous_block = this->get_block(), destination;
        srand((unsigned int)time(NULL));

        //cout << "Avatar previous block: " << previous_block.x << "," << previous_block.y << endl;
        if (c == 224) {
            c = _getch();
            switch (c) {
            case KEY_UP:
                destination.x = previous_block.x - 1;
                destination.y = previous_block.y;
                std::cout << "Up arrow key pressed" << std::endl;

                break;
            case KEY_DOWN:
                destination.x = previous_block.x + 1;
                destination.y = previous_block.y;
                std::cout << "Down arrow key pressed" << std::endl;
                break;
            case KEY_LEFT:
                destination.x = previous_block.x;
                destination.y = previous_block.y - 1;
                std::cout << "Left arrow key pressed" << std::endl;
                break;
            case KEY_RIGHT:
                //right
                destination.x = previous_block.x;
                destination.y = previous_block.y + 1;
                std::cout << "Right arrow key pressed" << std::endl;
                break;
            default:
                cout << "Stay in position" << endl;
                break;
            }


        }
        if (!exist_block(players_position, destination) && exist_block(map, destination)) {

            cout << "Avatar current block: " << destination.x << "," << destination.y << endl;
            this->set_block(destination);
            players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
            players_position.push_back(destination);
        }
        else {
            cout << "Stay in position" << endl;
            cout << "Vampire current block: " << previous_block.x << "," << previous_block.y << endl;
        }
    }
};


block find_random(int x, int y, vector<block>& map, vector<block>& same_position) {
    block random;
    srand((unsigned int)time(NULL));
    do {

        int temp_x = (rand() % x);
        int temp_y = (rand() % y);
        random.x = temp_x;
        random.y = temp_y;
        //if (exist_block(same_position, random))
            //cout << "Someone exists in this position: "<< random.x<< ","<<random.y << endl;
    } while (!exist_block(map, random) || exist_block(same_position, random));
    same_position.push_back(random);
    return random;

}


vector<block> start(int x, int y, vector<block>& map, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& pl) {
    int map_size = x * y;
    int counter = 0;
    char team;


    block random;
    srand((unsigned int)time(NULL));

    ////set the sea and the trees
    //for (int i = 0; i < map_size / 5; i++) {
    //    do {
    //        int temp_x = (rand() % x);
    //        int temp_y = (rand() % y);
    //        random.x = temp_x;
    //        random.y = temp_y;
    //    } while (!exist_block(map, random) );
    //    cout << "Erased: " << random.x << "," << random.y << endl; //test
    //    map.erase(std::remove(map.begin(), map.end(), random), map.end());//delete the block from the vector
    //}

    vector<block>same_position = vector<block>();
    vector <block>players_position = vector<block>();

    //Warewolves set to a start position
    for (int i = 0; i < (map_size / 15); i++) {
        random = find_random(x, y, map, same_position);
        Warewolves* w = new Warewolves(random);
        players_position.push_back(random);
        war.push_back(w);

    }

    //Vampires set to a start position
    for (int i = 0; i < (map_size / 15); i++) {
        random = find_random(x, y, map, same_position);
        Vampires* v = new Vampires(random);
        players_position.push_back(random);
        vam.push_back(v);
    }



    //Make Avatar and place it to a start position
    random = find_random(x, y, map, same_position);
    pl.set_block(random);
    players_position.push_back(random);
    cout << "Make an Avatar" << " " << random.x << " " << random.y << endl;
    cout << "Please choose your team. W or V?" << endl;
    cin >> team;
    pl.Set_team(team);
    cout << pl.Get_team() << endl;
    return players_position;
}


block near_creature_block(block creature, vector< block>& map, vector<block>& players_position) {

    block up(creature.x - 1, creature.y);
    block down(creature.x + 1, creature.y);
    block left(creature.x, creature.y - 1);
    block right(creature.x, creature.y + 1);

    if (exist_block(players_position, up))
        return up;
    else if (exist_block(players_position, down))
        return down;
    else if (exist_block(players_position, left))
        return left;
    else  if (exist_block(players_position, left))
        return right;
    else
        return creature;


}


bool exist_warewolve(vector< Warewolves*>& vec, block b) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->get_block() == b)
            return true;
    }
    return false;
}

bool exist_vampire(vector< Vampires*>& vec, block b) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->get_block() == b)
            return true;
    }
    return false;
}

Warewolves* in_werewolves(vector<Warewolves*>& war, block neighboor) {

    for (int i = 0; i < war.size(); i++) {
        if (war[i]->get_block() == neighboor)
        return war[i];
    }

}
Vampires* in_vampires(vector<Vampires*>& vam, block neighboor) {

    for (int i = 0; i < vam.size(); i++) {
        if (vam[i]->get_block() == neighboor) {
            return vam[i];
        }
    }
}
void play(vector<block>& map, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& player, vector<block>& players_position) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < war.size(); i++) {
        war[i]->Move(map, players_position);
        block neighboor = near_creature_block(war[i]->get_block(), map, players_position);

        if (!(neighboor == war[i]->get_block())) {

            if (exist_warewolve(war, neighboor)){
                Warewolves* ware = in_werewolves(war, neighboor);
                int option = (rand() % 2);
                if (option == 0) {
                    war[i]->Heal(ware);
                }
            }
            else if (exist_vampire(vam,neighboor)) {

                Vampires* vamp = in_vampires(vam, neighboor);
                if (war[i]->get_attack() >= vamp->get_attack()) {
                    cout << "Attack" << vamp->get_attack() << "Health" << vamp->get_health() << endl;
                    war[i]->Attack(vamp);
                    if (vamp->get_health() == 0)
                        vam.erase(std::remove(vam.begin(), vam.end(), vamp), vam.end());
                }
                else
                    war[i]->Move(map, players_position);
            }

        }
    }
    for (int i = 0; i < vam.size(); i++) {
        vam[i]->Move(map, players_position);
        block neighboor = near_creature_block(vam[i]->get_block(), map, players_position);
        if (!(neighboor == (vam[i]->get_block()))) {
            
            if (exist_vampire(vam,neighboor)) {
                Vampires* vamp = in_vampires(vam, neighboor);
                int option = (rand() % 2);
                if (option == 0) {
                    vam[i]->Heal(vamp);
                }
            }
            else if (exist_warewolve(war, neighboor)) {
                Warewolves* ware = in_werewolves(war, neighboor);
                if (vam[i]->get_attack() >= ware->get_attack()) {
                    cout << "Attack" << ware->get_attack() << "Health" << ware->get_health() << endl;
                    vam[i]->Attack(ware);
                    if (ware->get_health() == 0)
                        war.erase(std::remove(war.begin(), war.end(), ware), war.end());
                }
                else
                    vam[i]->Move(map, players_position);
            }

        }
    }

    player.Move(map, players_position);

}




int main()
{
    int x, y, map_size;
    block p;
    Avatar player(p);
    vector<Warewolves*> war = vector <Warewolves*>();
    vector<Vampires*> vam = vector <Vampires*>();

    cout << "Please initialize the map" << endl << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    map_size = x * y;
    vector<block> map = vector<block>();//keeps the empty blocks of the map available
    for (int i = 0; i < x; i++) {
        //cout << endl;
        for (int j = 0; j < y; j++) {

            block p;
            p.x = i;
            p.y = j;
            //cout << "- ";
            map.push_back(p);
        }
    }
    vector<block> players_position = vector<block>();
    players_position = start(x, y, map, war, vam, player);

    //test oi syntetagenes kai o vector einai swstes kai meta thn synarthsh
    p = player.get_block();
    cout << endl << "Avatar position " << p.x << "," << p.y;
    cout << endl << "Ground blocks in map: " << map.size() << endl;

    while (!vam.empty() && !war.empty()) {
        cout << "Epomenos gyros" << endl;
        play(map, war, vam, player, players_position);
    }

    cout << "Game ends ";

    return 0;
}

