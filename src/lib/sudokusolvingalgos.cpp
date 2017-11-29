#include<iostream>
#include"probables.h"
#include"sudokubasicoperations.h"

void extractInfo(int i, int &row1, int &row2, int &col1, int &col2, int block)
{
	int divisor=1000000000, pos;
	for(pos=0;pos<9;pos++)
	{
		divisor/=10;
		std::cout<<i/divisor<<std::endl;
		if(i/divisor)
		{
			if(row1<0)
			{
				row1=(block/3)*3+pos/3;
				col1=(block%3)*3+pos%3;
			}
			else
			{
				row2=(block/3)*3+pos/3;
				col2=(block%3)*3+pos%3;
			}
		}
		i=i%divisor;
	}
}

int thereAreTwoOnes(int infoLine)
{
	int divisor=100000000, counter=0;
	while(infoLine!=0)
	{
		if(infoLine/divisor) counter++;
		divisor/=10;
		infoLine=infoLine%divisor;
	}
	if(counter==2) return 1;
	return 0; 
}

/*void soleCandidate()
*If there is only one probable candidate in any unit, then it's there
*/
void soleCandidate(struct probables* tail[][9], int grid[][9])
{
	int count, i, j, k, l, a, b;
	struct probables* temp;
	for(i=0;i<9;i++)										//for a given row i
	{
		for(j=0;j<9;j++)									//traversing in the column
		{
			count=0;										//count is the variable that keeps count
			if(!grid[i][j])									//If number is to be filled (i.e. val is 0) in the grid then start counting
			{
				count=1;
				temp=tail[i][j];
				while(temp->next!=NULL)
				{
					count++;
					temp=temp->next;
				}
			}
			if(count==1)
			{
				grid[i][j]=temp->val;						//If only 1 candidate is present, fill it in the grid
				for(k=0;k<9;k++)							//Since new number is added, it is removed from the probables list of it's...
				{											//...row, column and box (the 3x3 one)
					if(!grid[k][j])							//for row
						removeProbable(k, j, grid[i][j], tail);
					if(!grid[i][k])							//for column
						removeProbable(i, k, grid[i][j], tail);
				}
				for(k=0;k<3;k++)							//for box
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

void uniqueCandidate(long infoGrid[], long infoGridRow[], long infoGridCol[], struct probables* tail[][9], int grid[][9])
{
	//If the unique candi is in the box
	int i, memo;
	for(i=0;i<81;i++)
	{
		memo = -1;
		switch(infoGrid[i])
		{
			case 1 : memo=8; break;	 
			case 10 : memo=7; break;
			case 100 : memo=6; break;
			case 1000 : memo=5; break;
			case 10000 : memo=4; break;
			case 100000 : memo=3; break;
			case 1000000 : memo=2; break;
			case 10000000 : memo=1; break;
			case 100000000 : memo=0; break;
		}
		
		//extract number and position from i
		if(memo+1)
		{
			int number =1+(i/9);
			int column=((i%9)*3)%9+memo%3;
			int row=((i%9)/3)*3+memo/3;

			assign(row, column, number, tail, grid);
		}
	}
	
	//if the unique candi is in the row
	for(i=0;i<81;i++)
	{
		memo = -1;
		switch(infoGridRow[i])
		{
			case 1 : memo=8; break;	 
			case 10 : memo=7; break;
			case 100 : memo=6; break;
			case 1000 : memo=5; break;
			case 10000 : memo=4; break;
			case 100000 : memo=3; break;
			case 1000000 : memo=2; break;
			case 10000000 : memo=1; break;
			case 100000000 : memo=0; break;
		}
		
		if(memo+1)
		{
			int number = 1+(i/9);
			int column = memo;
			int row = i%9;

			assign(row, column, number, tail, grid);
		}
	}
	
	//if the unique candi is in the column
	for(i=0;i<81;i++)
	{
		memo = -1;
		switch(infoGridCol[i])
		{
			case 1 : memo=8; break;	 
			case 10 : memo=7; break;
			case 100 : memo=6; break;
			case 1000 : memo=5; break;
			case 10000 : memo=4; break;
			case 100000 : memo=3; break;
			case 1000000 : memo=2; break;
			case 10000000 : memo=1; break;
			case 100000000 : memo=0; break;
		}
		
		//extract number and position from i
		if(memo+1)
		{
			int number = 1+(i/9);
			int column = i%9;
			int row = memo;

			assign(row, column, number, tail, grid);
		}
	}
}

void bcrInteraction(long infoGrid[], struct probables* tail[][9], int grid[][9])
{
	int i, j, number, row, column;
	for(i=0;i<81;i++)
	{
		number = 1+ (i/9);
		column = ((i%9)%3)*3;
		row=-10;
		switch(infoGrid[i])
		{
			case 111 :
			case 101 :	row = ((i%9)/3)*3+2;
						break;
			case 111000  :
			case 101000  :	row = ((i%9)/3)*3+1;
							break;
			case 111000000  :
			case 101000000  :	row = ((i%9)/3)*3;
								break;
		}
		
		if(row>=0)
		switch(column)
		{
			case 0 :	for(j=3;j<9;j++)
						{
							if(!grid[row][j])
							{
								removeProbable(row, j, number, tail);
							}
						}
						break;
			case 3 :	for(j=0;j<9;j++)
						{
							if(!grid[row][j])
							{
								removeProbable(row, j, number, tail);
							}
							j=(j==2)?5:j;
						}
						break;
			case 6 :	for(j=0;j<6;j++)
						{
							if(!grid[row][j])
							{
								removeProbable(row, j, number, tail);
							}
						}
						break;
		}
	}

	for(i=0;i<81;i++)
	{
		number = 1 + (i/9);
		column=-12;
		row = ((i%9)/3)*3;
		switch(infoGrid[i])
		{
			case 100100100  :
			case 100000100  :   column = ((i%9)%3)*3;
								break;
			case 010010010  :
			case 010000010  :	column = ((i%9)%3)*3 + 1;
								break;
			case 001001001  :
			case 001000001  :	column = ((i%9)%3)*3 + 2;
								break;
		}
		if(column>=0)
		switch(row)
		{
			case 0 :	for(j=3;j<9;j++)
						{
							if(!grid[j][column])
							{
								removeProbable(j, column, number, tail);
							}
						}
						break;
			case 3 :	for(j=0;j<9;j++)
						{
							if(!grid[j][column])
							{
								removeProbable(j, column, number, tail);
							}
							if(j==2) j=5;
						}
						break;
			case 6 :	for(j=0;j<6;j++)
						{
							if(!grid[j][column])
							{
								removeProbable(j, column, number, tail);
							}
						}
						break;
		}
	}
}

void nakedPair(long infoGrid[], struct probables* tail[][9])
{
	int block, curNum, numSift, row1=-1, row2=0, col1=0, col2=0;
	//Naked pairs in blocks
	for(block=0;block<9;block++)
	{
		for(curNum=1;curNum<9;curNum++)
		{
			for(numSift=curNum+1;numSift<=9;numSift++)
			{
				row1=-1;
				if(infoGrid[block+9*(curNum-1)]==infoGrid[block+9*(numSift-1)])
				{
					if(thereAreTwoOnes(infoGrid[block+9*(curNum-1)])){
						extractInfo(infoGrid[block+9*(curNum-1)], row1, row2, col1, col2, block);
						std::cout<<"row1 "<<row1<<" col1 "<<col1<<" row2 "<<row2<<" col2 "<<col2<<std::endl;
					
							//these two numbers are naked pairs
							//remove all other numbers from the probables list
											
									struct probables* temp= tail[row1][col1];
									while(temp->next!=NULL)
									{
										if(temp->val!=curNum||temp->val!=numSift)
										{
											removeProbable(row1, col1, temp->val, tail);
											temp=temp->next;
										}
									}
									if(temp->val!=curNum||temp->val!=numSift)
										{
											removeProbable(row1, col1, temp->val, tail);
											temp=temp->next;
										}
									
									temp = tail[row2][col2];
									while(temp->next!=NULL)
									{
										if(temp->val!=curNum||temp->val!=numSift)
										{
											removeProbable(row2, col2, temp->val, tail);
											temp=temp->next;
										}
									}
									if(temp->val!=curNum||temp->val!=numSift)
									{
										removeProbable(row2, col2, temp->val, tail);
										temp=temp->next;
									}
					}
				}
			}
		}
	}
}






