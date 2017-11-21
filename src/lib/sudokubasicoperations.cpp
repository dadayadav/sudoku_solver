#include<iostream>
#include<iomanip>
#include<string>
#include"probables.h"	//Contains declaration of struct probables

/**	readInput(long int[], int [][9])
*	User enters the data of the rows in the form of 9 digit numbers
*	The data of 9 rows are stored in row[9]
*	The grid is the 9x9 matrix which contains the sudoku puzzle
*	The function puts the data from rows to grid[][]
*/
void readInput(long int row[], int grid[][9], int grid2[][9])
{
	int i, j;
	for(i=0;i<=8;i++)
		for(j=8;j>=0;j--)
		{
			grid[i][j]=row[i]%10;
			grid2[i][j]=row[i]%10;
			row[i]/=10;
		}
}

/** fillProbables(int, int)
*	Probables are the numbers that can be filled in that unit
*	The initial move would be to fill probables of all the vacant spots with all 9 digits
*/

void fillProbables(int row, int column, struct probables* tail[][9])
{
	int k;
	for(k=9;k>0;k--)
	{
		struct probables* temp=new struct probables;
		temp->val=k;
		if(tail[row][column]==NULL)
		{
			tail[row][column]=temp;
			temp->next=NULL;
		}
		else
		{
			temp->next=tail[row][column];
			tail[row][column]=temp;
		}
	}
}

/*void remove_candidate(int, int, int)
*Given the coordinates of an unit, remove a given value from the probable candidates
*/
void removeProbable(int i, int j, int value, struct probables* tail[][9])
{
	struct probables* temp=tail[i][j];
	struct probables* temp1;
	if(value==tail[i][j]->val)	//if the first value is the given value
		tail[i][j]=temp->next;
	else
	{							//else
		while(temp->next!=NULL)
		{
			if((temp->next)->val==value)
			{
				temp1=temp->next;
				temp->next=temp1->next;
				break;
			}
			temp=temp->next;
		}
	}
}

/*void probable_candidate()
*Prepares the list of probable candidates for the first time
*/
void probableCandidate(struct probables* tail[][9], int grid[][9])
{
	int i, j, k, l, a, b;
	
	for(i=0;i<9;i++)												//first fill probables of all the vacant spots with 1 to 9
	{
		for(j=0;j<9;j++)
		{
			if(!grid[i][j])
			{
				fillProbables(i, j, tail);
			}
		}
	}
	
	for(i=0;i<9;i++)												//if grid element is non-zero, remove it from probable candidates...
	{																//...of respective row, column and box
		for(j=0;j<9;j++)
		{
			if(grid[i][j])
			{														//remove grid[i][j] from row, column and box probable candidates
				for(k=0;k<9;k++)
				{
					if(!grid[k][j])									//for row
						removeProbable(k, j, grid[i][j], tail);
					if(!grid[i][k])									//for column
						removeProbable(i, k, grid[i][j], tail);
				}
				for(k=0;k<3;k++)									//for box
				{
					for(l=0;l<3;l++)
					{
						a=3*(i/3)+k;
						b=3*(j/3)+l;
						if(!grid[a][b])
							removeProbable(a, b, grid[i][j], tail);
					}
				}
			}
		}
	}
}

void printProbables(struct probables* tail[][9], int grid[][9])
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(!grid[i][j])
			{
				std::cout<<"The Probable candidates for "<< i<<" ,"<< j<<" are ";
				struct probables* temp=tail[i][j];
				std::cout<<temp->val;
				while(temp->next!=NULL)
				{
					temp=temp->next;
					std::cout<<temp->val<<", ";
				}
				std::cout<<std::endl;
			}
		}
	}
}

void printGrid(int grid[][9])
{
	int i, j;
	std::cout<<"The Solution:"<<std::endl;
	for(i=0;i<9;i++)
	{
		if(i%3==0) std::cout<<"-------------------------"<<std::endl;
		std::cout<<"| ";
		for(j=0;j<9;j++)
		{
			std::cout<<grid[i][j]<<" ";
			if(j%3==2) std::cout<<"| ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"-------------------------"<<std::endl;
}

int checkIfDone(int grid[][9])
{
	int i, j, count=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(!grid[i][j])
				count=1;
		}
	}
	return count;
}

void setNull(struct probables* tail[][9])
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			tail[i][j]=NULL;
		}
	}
}

void createInfoGrid(long int infoGrid[], struct probables* tail[][9], int grid[][9])
{
	int i, row, cols, drows, dcols, flag=-1;
	for(i=0;i<81;i++)
		infoGrid[i]=0;
	
	for(i=1;i<=9;i++)
	{
		for(row=0;row<9;row+=3)
		{
			for(cols=0;cols<9;cols+=3)
			{
				flag++;
				for(drows=0;drows<3;drows++)
				{
					for(dcols=0;dcols<3;dcols++)
					{
						infoGrid[flag]*=10;
						if(!grid[row+drows][cols+dcols])
						{
							struct probables* temp = tail[row+drows][cols+dcols];
							while(temp->next!=NULL)
							{
								if(temp->val==i)
								{
									infoGrid[flag]+=1;
								}
								temp=temp->next;
							}
							if(temp->val==i)
								{
									infoGrid[flag]+=1;
								}
						}
					}
				}
			}
		}
	}
}

void createInfoGridRow(long int infoGridRow[], struct probables* tail[][9], int grid[][9])
{
	int i, j, num, flag=-1;
	for(i=0;i<81;i++)
		infoGridRow[i]=0;
		
	for(num=1;num<=9;num++)
	{
		for(i=0;i<9;i++)
		{
			flag++;
			for(j=0;j<9;j++)
			{
				infoGridRow[flag]*=10;
				if(!grid[i][j])
				{
					struct probables* temp = tail[i][j];
					while(temp->next!=NULL)
					{
						if(temp->val==num)
						{
							infoGridRow[flag]+=1;
						}
						temp=temp->next;
					}
					if(temp->val==num)
					{
						infoGridRow[flag]+=1;
					}
				}
			}	
		}
	}
}

void createInfoGridColumn(long int infoGridCol[], struct probables* tail[][9], int grid[][9])
{
	int i, j, num, flag=-1;
	for(i=0;i<81;i++)
		infoGridCol[i]=0;
		
	for(num=1;num<=9;num++)
	{
		for(j=0;j<9;j++)
		{
			flag++;
			for(i=0;i<9;i++)
			{
				infoGridCol[flag]*=10;
				if(!grid[i][j])
				{
					struct probables* temp = tail[i][j];
					while(temp->next!=NULL)
					{
						if(temp->val==num)
						{
							infoGridCol[flag]+=1;
						}
						temp=temp->next;
					}
					if(temp->val==num)
					{
						infoGridCol[flag]+=1;
					}
				}
			}	
		}
	}
}

void printInfoGrid(long int infoGrid[])
{
	int i;
	std::cout<<"infoGrid: "<<std::endl;
	for(i=0;i<81;i++)
	{
		if(!(i%9)) std::cout<<std::endl;
		std::cout<<std::setfill('0')<<std::setw(9)<<infoGrid[i]<<std::endl;
	}
}

void assign(int i, int j, int value, struct probables* tail[][9], int grid[][9])
{
	grid[i][j]=value;
	int a, b, k, l;
	for(k=0;k<9;k++)							//Since new number is added, it is removed from the probables list of it's...
	{											//...row, column and box (the 3x3 one)
		if(!grid[k][j])							//for row
			removeProbable(k, j, value, tail);
		if(!grid[i][k])							//for column
			removeProbable(i, k, value, tail);
	}
	for(k=0;k<3;k++)							//for box
	{
		for(l=0;l<3;l++)
		{
			a=3*(i/3)+k;
			b=3*(j/3)+l;
			if(!grid[a][b])
				removeProbable(a, b, value, tail);
		}
	}
}
