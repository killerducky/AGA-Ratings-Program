#include <iostream>
#include <cmath>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_sf_erf.h>
#include <mysql++/mysql++.h>
#include "player.h"
#include "game.h"
#include "collection.h"

using namespace std;

int main(void) {
	collection c;
	player p;
	game g;
	
        p.seed = 5.5;
        p.id   = 1;
        p.sigma = 0.01;			
        c.playerHash[p.id] = p;
	
        p.seed = 5.6;
        p.id   = 2;
        p.sigma = 9000.0;			
        c.playerHash[p.id] = p;

        g.white     = 1;
        g.black     = 2;
        g.handicap  = 0;
        g.komi      = 7;
        g.whiteWins = 0;
        
        for (int i=0; i<10; i++){
          c.gameList.push_back(g);		
        }
	
	// Run the faster algorithm first; use the slower one as a backup.
	if (c.calc_ratings_fdf() != 0) {
		cout << "fdf failed" << endl;
		c.calc_ratings();
        } else {
		cout << "fdf success" << endl;
        }
		
	for (map<int, player>::iterator It = c.playerHash.begin(); It != c.playerHash.end(); It++) {
		cout << It->second.id << '\t' << It->second.rating << '\t' << It->second.sigma << endl;
	}
		
	return 0;
}
