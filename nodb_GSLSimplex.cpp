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
	player p0;
	player p1;
	game g;
	
	p0.seed = 50.5;
	p0.id   = 1;
	p0.sigma = 0.01;			
	c.playerHash[p0.id] = p0;
	
	p1.seed = 0.0;
	p1.id   = 2;
	p1.sigma = 9000.0;			
	c.playerHash[p1.id] = p1;

	g.white     = 1;
	g.black     = 2;
	g.handicap  = 0;
	g.komi      = 7;
	g.whiteWins = 0;

	for (int i=0; i<10; i++){
		c.gameList.push_back(g);		
		g.whiteWins = !g.whiteWins;
		c.gameList.push_back(g);		
		g.whiteWins = !g.whiteWins;
	}
	
	// Run the faster algorithm first; use the slower one as a backup.
	if (c.calc_ratings_fdf() != 0) {
		cout << "fdf failed" << endl;
		c.calc_ratings();
		} else {
		cout << "fdf success" << endl;
		c.playerHash[p0.id] = p0;
		c.playerHash[p1.id] = p1;
		c.calc_ratings();
	}
		
	for (map<int, player>::iterator It = c.playerHash.begin(); It != c.playerHash.end(); It++) {
		cout << It->second.id << '\t' << It->second.rating << '\t' << It->second.sigma << endl;
	}
		
	return 0;
}
