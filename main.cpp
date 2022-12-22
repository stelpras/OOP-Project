#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <conio.h>


#include "Header.h"



using namespace std;


int main()
{
    int x, y, map_size;
    block pl;
    Avatar player(pl);
    vector<Warewolves*> war = vector <Warewolves*>();
    vector<Vampires*> vam = vector <Vampires*>();

    cout << "Please initialize the map" << endl << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    map_size = x * y;

    vector<block> map = vector<block>();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {

            block p;
            p.x = i;
            p.y = j;
            p.pr = '-';
            map.push_back(p);
        }
    }



    //Place characters in the map
    vector<block> erased = vector<block>();
    vector<block> players_position = vector<block>();
    block magic_filter = start(x, y, map, erased, players_position, war, vam, player);

    magic_filter.pr = 'M';


    bool day = true;
    int round_counter = 0;
    while (!vam.empty() && !war.empty()) {
        cout << endl << endl << "Next round" << endl;
        if (day == true)
            cout << "Day round" << endl;
        else
            cout << "Evening round" << endl;

        play(map, war, vam, player, players_position);
        pl = player.get_block();
        if (pl == magic_filter) {
            magic_filter.pr = '-';
            player.set_potion(player.get_potions() + 1);
        }
        print_map(x, y, map, erased, player, magic_filter);
        round_counter = round_counter + 1;



        if (round_counter % 5 == 0)//Every 5 rounds switch from day to night
            day = !day;

        cout << endl << "Press s to stop the game" << endl;
        char stop = _getch();
        if (stop == 's')
            break;

        cout << "Press p to pause the game" << endl;
        char pause = _getch();
        if (pause == 'p') {
            cout << "Warewolves: " << war.size() << endl;
            cout << "Vampires " << vam.size() << endl;
            cout << "Avatar Potions: " << player.get_potions() << endl;

            cout << endl << "Press h to heal teammates" << endl;
            char input = _getch();
            if (input == 'h' && player.get_potions() > 0) {
                if (player.get_team() == 'W' && day == false) {
                    for (int i = 0; i < war.size(); i++) {
                        war[i]->set_health(war[i]->get_health() + 1);
                        cout << "Healed Warewolve" << endl;
                    }
                    player.set_potion(player.get_potions() - 1);
                }
                if (player.get_team() == 'V' && day == true) {
                    for (int i = 0; i < vam.size(); i++) {
                        vam[i]->set_health(vam[i]->get_health() + 1);
                        cout << "Healed Vampire" << endl;

                    }
                    player.set_potion(player.get_potions() - 1);
                }

            }

        }


    }
    if (vam.size() == 0) {
        war.clear();
        cout << endl << "Werewolves won" << endl;
    }
    else if (war.size() == 0) {
        vam.clear();
        cout << endl << "Vampires won" << endl;
    }
    cout << "Game ends ";

    return 0;
}
