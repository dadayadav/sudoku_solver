#ifndef SUDOKUSOLVINGALGOS_H
#define SUDOKUSOLVINGALGOS_H

#include"probables.h"

void soleCandidate(struct probables* tail[][9], int grid[][9]);

void uniqueCandidate(long infoGrid[], long infoGridRow[], long infoGridCol[], struct probables* tail[][9], int grid[][9]);

void bcrInteraction(long infoGrid[], struct probables* tail[][9], int grid[][9]);

void nakedPair(long infoGrid[], struct probables* tail[][9]);
#endif
