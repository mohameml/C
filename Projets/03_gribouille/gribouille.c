#include <stdlib.h>
#include <stdio.h>
#include "motif.h"

int main(void)
{
	struct droite diag;
	struct cercle bil;

	// Nounours
	// tete
	struct motif *test = creer_motif(300, 300, 0xFFFFFF);
	if (test == NULL) {
		fprintf(stderr, "E: no mem for creer_motif\n");
		exit(1);
	}
	//visage
	bil.centre.x = 0.5;
	bil.centre.y = 0.5;
	bil.depart.x = 0.;
	bil.depart.y = 0.5;
	bil.ang = 360;
	bil.coul = 0x333366;
	tracer_cercle(test, &bil);
	remplir(test, &bil.centre, 0x333366);

	//oeil droit
	bil.centre.x = 0.3;
	bil.centre.y = 0.65;
	bil.depart.x = 0.25;
	bil.depart.y = 0.65;
	bil.coul = 0xFFFFFF;;
	tracer_cercle(test, &bil);
	remplir(test, &bil.centre, bil.coul);
	//oeil gauche
	bil.centre.x = 0.7;
	bil.centre.y = 0.65;
	bil.depart.x = 0.65;
	bil.depart.y = 0.65;
	tracer_cercle(test, &bil);
	remplir(test, &bil.centre, bil.coul);

	//nez 
	diag.depart.x = 0.5;
	diag.depart.y = 0.6;
	diag.arrivee.x = 0.45;
	diag.arrivee.y = 0.4;
	diag.coul = 0x9966FF;
	tracer_droite(test, &diag);
	diag.arrivee.x = 0.55;
	tracer_droite(test, &diag);
	diag.depart.x = 0.45;
	diag.depart.y = 0.4;
	tracer_droite(test, &diag);
	bil.centre.x = 0.5;
	bil.centre.y = 0.5;
	remplir(test, &bil.centre, diag.coul);

	// bouche
	bil.ang = 120.;
	bil.centre.x = 0.5;
	bil.centre.y = 0.5;
	bil.depart.y = 0.35;
	bil.depart.x = 0.24;
	bil.coul = 0x9966FF;
	tracer_cercle(test, &bil);

	// oreille gauche
	bil.ang = 360.;
	bil.centre.x = bil.centre.y = 0.86;
	bil.depart.y = 0.78;
	bil.depart.x = 0.89;
	bil.coul = 0x333366;
	tracer_cercle(test, &bil);
	remplir(test, &bil.centre, diag.coul);
	// oreille droite
	bil.centre.x = 0.14;
	bil.depart.x = 0.11;
	tracer_cercle(test, &bil);
	remplir(test, &bil.centre, diag.coul);
	exporter_PPM(test, "gribouille.ppm");

	detruire_motif(test);
	return 0;
}
