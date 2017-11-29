#ifndef SUDOKUBASICOPERATIONS_H
#define SUDOKUBASICOPERATIONS_H

#include"probables.h"

void readInput(long row[], int grid[][9], int grid2[][9]);

void fillProbables(int row, int column, struct probables* tail[][9]);

void removeProbable(int i, int j, int value, struct probables* tail[][9]);

void probableCandidate(struct probables* tail[][9], int grid[][9]);

void printProbables(struct probables* tail[][9], int grid[][9]);

void printGrid(int grid[][9]);

int checkIfDone(int grid[][9]);

void setNull(struct probables* tail[][9]);

void createInfoGrid(long infoGrid[], struct probables* tail[][9], int grid[][9]);

void createInfoGridRow(long infoGridRow[], struct probables* tail[][9], int grid[][9]);

void createInfoGridColumn(long infoGridCol[], struct probables* tail[][9], int grid[][9]);

void printInfoGrid(long infoGrid[]);

void assign(int i, int j, int value, struct probables* tail[][9], int grid[][9]);

#endif
