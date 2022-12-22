#include "Header.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

block::block(int in_x, int in_y, char in_pr) {
    x = in_x;
    y = in_y;
    pr = in_pr;
}

bool block::operator==(const block& s) const {
    return x == s.x && y == s.y;
}


bool exist_block(vector< block>& vec, block b) {
    vector< block>::iterator item;
    item = find(vec.begin(), vec.end(), b);
    if (item != vec.end())
        return true;
    else
        return false;

}

Figures::Figures(block bl) {
    b.x = bl.x;
    b.y = bl.y;
    srand((unsigned int)time(NULL));
    health = 10;
    attack = (rand() % 3) + 1;
    medical = (rand() % 3);
    defence = (rand() % 2) + 1;
}

block Figures::get_block() const {
    return b;
}

void Figures::set_block(block bl) {
    b = bl;
}
int Figures::get_health()const {
    return health;
}
void Figures::set_health(int in_health) {
    health = in_health;
}
int Figures::get_attack() const {
    return attack;
}
int Figures::get_defence() const {
    return defence;
}
void Figures::set_defence(int in_defence) {
    defence = in_defence;
}
void Figures::set_medical(int in_medical) {
    medical = in_medical;

}
int Figures::get_medical() const {
    return medical;
}


void Figures::Move(vector< block>& map, vector<block>& players_position) {
    block previous_block, destination;
    previous_block = this->get_block();

    //cout << "Warewolve previous block: " << previous_block.x << "," << previous_block.y << endl;


    int move = (rand() % 5); //5 possible moves
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
        destination.x = previous_block.x + 1,
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

    }

    if (!exist_block(players_position, destination) && exist_block(map, destination)) {

        //cout << "Warewolve current block: " << destination.x << "," << destination.y << endl;
        this->set_block(destination);
        players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
        players_position.push_back(destination);
    }
    //else {
        //cout << "Stay in position" << endl;
        // << "Warewolve current block: " << previous_block.x << "," << previous_block.y << endl;
    //}

}

void Figures::Attack(Figures* enemy) {
    if (this->get_attack() - enemy->get_defence() <= 0)
        enemy->set_defence(enemy->get_defence() - 1);


    int new_health = enemy->get_health() - (this->get_attack() - enemy->get_defence());
    enemy->set_health(new_health);
    //cout << "Attack " << endl;

}
void Avatar::set_team(char team) {
    Team = team;
}

char Avatar::get_team()const {
    return Team;
}

void Avatar::set_potion(int in_potions) {
    potions = in_potions;

}
int Avatar::get_potions()const {
    return potions;
}

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

void Figures::Heal(Figures* ally) {
    if (ally->get_health() < 10 && this->get_medical() > 0) {
        ally->set_health(ally->get_health() + 1);
        this->set_medical(this->get_medical() - 1);
        //cout << "heal" << endl;
    }

}

void Vampires::Move(vector< block>& map, vector<block>& players_position) {
    block previous_block = this->get_block(), destination;
    //cout << "Vampire previous block: " << previous_block.x << "," << previous_block.y << endl;


    int move = (rand() % 9); //9 possible moves
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
        destination.x = previous_block.x + 1,
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
        destination.x = previous_block.x - 1,
            destination.y = previous_block.y + 1;
        break;
    case 8:
        //right down
        destination.x = previous_block.x + 1;
        destination.y = previous_block.y + 1;
        break;
    }

    if (!exist_block(players_position, destination) && exist_block(map, destination)) {

        //cout << "Vampire current block: " << destination.x << "," << destination.y << endl;
        this->set_block(destination);
        players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
        players_position.push_back(destination);
    }
    //else {
    //    cout << "Stay in position" << endl;
    //    cout << "Vampire current block: " << previous_block.x << "," << previous_block.y << endl;
    //}




}

void Avatar::Move(vector< block>& map, vector<block>& players_position) {
    int c = _getch();
    block previous_block = this->get_block(), destination;
    srand((unsigned int)time(NULL));

    //cout << "Avatar previous block: " << previous_block.x << "," << previous_block.y << endl;
    if (c == 224) {
        c = _getch();
        switch (c) {
        case KEY_UP:
            destination.x = previous_block.x - 1;
            destination.y = previous_block.y;

            break;
        case KEY_DOWN:
            destination.x = previous_block.x + 1;
            destination.y = previous_block.y;
            break;
        case KEY_LEFT:
            destination.x = previous_block.x;
            destination.y = previous_block.y - 1;
            break;
        case KEY_RIGHT:
            destination.x = previous_block.x;
            destination.y = previous_block.y + 1;
            break;
        default:
            cout << "Stay in position" << endl;
            break;
        }


    }
    if (!exist_block(players_position, destination) && exist_block(map, destination)) {

        //cout << "Avatar current block: " << destination.x << "," << destination.y << endl;
        this->set_block(destination);
        players_position.erase(std::remove(players_position.begin(), players_position.end(), previous_block), players_position.end());
        players_position.push_back(destination);
    }
    //else {
    //    cout << "Stay in position" << endl;
    //    cout << "Vampire current block: " << previous_block.x << "," << previous_block.y << endl;
    //}
}


block start(int x, int y, vector<block>& map, vector<block>& erased, vector<block>& players_position, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& pl) {
    int map_size = x * y;
    int counter = 0;
    char team;


    block random;
    srand((unsigned int)time(NULL));

    //set the sea and the trees
    for (int i = 0; i < map_size / 10; i++) {
        do {
            int temp_x = (rand() % x);
            int temp_y = (rand() % y);
            random.x = temp_x;
            random.y = temp_y;
        } while (!exist_block(map, random));
        cout << "Erased: " << random.x << "," << random.y << endl; //test
        erased.push_back(random);
        map.erase(std::remove(map.begin(), map.end(), random), map.end());//delete the block from the vector
    }

    vector<block>same_position = vector<block>();

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
    pl.set_team(team);

    block magic_filter = find_random(x, y, map, same_position);
    return magic_filter;

}


block near_creature_block(block creature, vector< block>& map, vector<block>& players_position) {

    block up(creature.x - 1, creature.y);
    block down(creature.x + 1, creature.y);
    block left(creature.x, creature.y - 1);
    block right(creature.x, creature.y + 1);
    block left_up(creature.x - 1, creature.y - 1);
    block left_down(creature.x + 1, creature.y - 1);
    block right_up(creature.x - 1, creature.y + 1);
    block right_down(creature.x + 1, creature.y + 1);

    if (exist_block(players_position, up))
        return up;
    else if (exist_block(players_position, down))
        return down;
    else if (exist_block(players_position, left))
        return left;
    else  if (exist_block(players_position, left))
        return right;
    else  if (exist_block(players_position, left_up))
        return left_up;
    else  if (exist_block(players_position, left_down))
        return left_down;
    else  if (exist_block(players_position, right_up))
        return right_up;
    else  if (exist_block(players_position, right_down))
        return right_down;
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
    Warewolves* nul = NULL;
    return nul;
}
Vampires* in_vampires(vector<Vampires*>& vam, block neighboor) {
    for (int i = 0; i < vam.size(); i++) {
        if (vam[i]->get_block() == neighboor) {
            return vam[i];
        }
    }
    Vampires* nul = NULL;
    return nul;
}

void play(vector<block>& map, vector<Warewolves*>& war, vector<Vampires*>& vam, Avatar& player, vector<block>& players_position) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < war.size(); i++) {
        war[i]->Move(map, players_position);
        block neighboor = near_creature_block(war[i]->get_block(), map, players_position);

        if (!(neighboor == war[i]->get_block())) {

            if (exist_warewolve(war, neighboor)) {
                Warewolves* ware = in_werewolves(war, neighboor);
                if (ware != NULL) {
                    int option = (rand() % 2);
                    if (option == 0) {
                        war[i]->Heal(ware);
                        //cout << "Heal Warewolve" << endl;
                    }
                }

            }
            else if (exist_vampire(vam, neighboor)) {

                Vampires* vamp = in_vampires(vam, neighboor);
                if (vamp != NULL) {
                    if (war[i]->get_attack() >= vamp->get_attack()) {
                        war[i]->Attack(vamp);
                        //cout << "Attack Vampire" << endl;
                        if (vamp->get_health() <= 0)
                            vam.erase(std::remove(vam.begin(), vam.end(), vamp), vam.end());
                    }
                    else
                        war[i]->Move(map, players_position);
                }

            }

        }
    }
    for (int i = 0; i < vam.size(); i++) {
        vam[i]->Move(map, players_position);
        block neighboor = near_creature_block(vam[i]->get_block(), map, players_position);
        if (!(neighboor == (vam[i]->get_block()))) {

            if (exist_vampire(vam, neighboor)) {
                Vampires* vamp = in_vampires(vam, neighboor);
                if (vamp != NULL) {
                    int option = (rand() % 2);
                    if (option == 0) {
                        vam[i]->Heal(vamp);
                        //cout << "Heal Vampire"<< endl;
                    }
                }

            }
            else if (exist_warewolve(war, neighboor)) {
                Warewolves* ware = in_werewolves(war, neighboor);
                if (ware != NULL) {
                    if (vam[i]->get_attack() >= ware->get_attack()) {
                        vam[i]->Attack(ware);
                        //cout << "Attack Werewolve" << endl;
                        if (ware->get_health() <= 0)
                            war.erase(std::remove(war.begin(), war.end(), ware), war.end());
                    }
                    else
                        vam[i]->Move(map, players_position);
                }

            }

        }
    }
    cout << "Please make a move(arrow keys): " << endl;
    player.Move(map, players_position);


}

void print_map(int x, int y, vector<block>& map, vector<block>& erased, Avatar& player, block& magic_filter) {
    block pl = player.get_block();
    for (int i = 0; i < x; i++) {
        cout << endl;
        for (int j = 0; j < y; j++) {
            block temp;
            temp.x = i;
            temp.y = j;
            if (exist_block(erased, temp))
                cout << 'X';
            else if (temp == pl)
                cout << player.get_team();
            else if (temp == magic_filter)
                cout << magic_filter.pr;
            else
                cout << map[i].pr;
        }
    }
}