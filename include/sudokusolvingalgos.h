#ifndef SUDOKUSOLVINGALGOS_H
#define SUDOKUSOLVINGALGOS_H

#include"probables.h"

void soleCandidate(struct probables* tail[][9], int grid[][9]);

void uniqueCandidate(long int infoGrid[], long int infoGridRow[], long int infoGridCol[], struct probables* tail[][9], int grid[][9]);

void bcrInteraction(long int infoGrid[], struct probables* tail[][9], int grid[][9]);

void nakedPair(long int infoGrid[], struct probables* tail[][9]);
#endif
