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
	map<int, player> ph;
	map<string, int> pidh;
	int id = 0;

	// Anchor 2d
	p.seed = 2.5;
	p.id   = pidh["2d"] = id++;
	p.sigma = 0.01;
	c.playerHash[p.id] = p;

	// Anchor 50d
	p.seed = 50.5;
	p.id   = pidh["50d"] = id++;
	p.sigma = 0.01;
	c.playerHash[p.id] = p;

	// test player, day 0
	p.seed = 3.0;
	p.id   = pidh["test0"] = id++;
	p.sigma = 9000;
	c.playerHash[p.id] = p;

	// test player, day X
	p.seed = 3.0;
	p.id   = pidh["testX"] = id++;
	p.sigma = 9000;
	c.playerHash[p.id] = p;

	ph = map<int, player> (c.playerHash);

	g.handicap  = 0;
	g.komi      = 7;
	g.whiteWins = false;

	g.white     = pidh["2d"];
	g.black     = pidh["test0"];

	for (int i=0; i<10; i++){
		c.gameList.push_back(g);
		int tmp = g.white;
		g.white = g.black;
		g.black = tmp;
		c.gameList.push_back(g);
		tmp = g.white;
		g.white = g.black;
		g.black = tmp;
	}

	g.white     = pidh["50d"];
	g.black     = pidh["testX"];

	for (int i=0; i<10; i++){
		c.gameList.push_back(g);
		int tmp = g.white;
		g.white = g.black;
		g.black = tmp;
		c.gameList.push_back(g);
		tmp = g.white;
		g.white = g.black;
		g.black = tmp;
	}

	g.white     = pidh["test0"];
	g.black     = pidh["testX"];

	for (int i=0; i<2000; i++){
		c.gameList.push_back(g);
		int tmp = g.white;
		g.white = g.black;
		g.black = tmp;
		c.gameList.push_back(g);
		tmp = g.white;
		g.white = g.black;
		g.black = tmp;
	}

	// Run the faster algorithm first; use the slower one as a backup.
	if (c.calc_ratings_fdf() != 0) {
	//if (false) {
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
