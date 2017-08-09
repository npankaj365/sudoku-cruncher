/********************************************************************************************
*                      ******** SUDOKU CRUNCHER ********                                    *
*             First Semester Project of 'Fundamentals of Programming'                       *
*         Implemented by Anlisha Maharjan, Pankaj Niroula and Rohit Nepali                  *
********************************************************************************************/

#define FULL 9 //FULL stands for No. of Rows or Cols in a full grid
#define PART 3 //PART stands for No. of Rows or Cols in a region
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//Function Prototypes
void input(int grid[][FULL]); // For reading grid from file
void output(int grid[][FULL]); //For saving output in file
void display(int grid[][FULL]); // For displaying sudoku grid
int emptycells(int grid[][FULL], int free[][2]); // For finding the free cells
int isvalid(int grid[][FULL], int row, int col); // For checking if the filling is valid
int recur(int grid[][FULL], int free[][2], int f, int k); // For filling free cells, changing and backtracking

int main(void)
{
    int grid[FULL][FULL];
    int free[70][2];
    int row,col,i,j,f,k=0;

    printf("*************************** SUDOKU CRUNCHER ************************************");
    input(grid);
    printf("Before Solving the Sudoku puzzle: \n \n");
    display(grid);

    //To know the number and location of empty cells
    f=emptycells(grid,free);

	if((recur(grid,free,f,k))==0)
		printf("\n Solution can't be found ");
	else
	{
		printf("\n \n The solution is: \n \n");
		display(grid);
		output(grid);
    }
    getch();
    return 0;
}

void input(int grid[][FULL])
{
    int row, col;
    FILE *fpt;
    printf("\n Input the numbers in the notepad window, save and exit \
            \n Press any key to continue ");
    getch();
    fpt = fopen("question.txt","w");
    fclose(fpt);
    system("notepad question.txt");
    if((fpt = fopen("question.txt","r"))==NULL)
    {
        printf("\n Error getting the grid \n \
                \n Please save the grid in the notepad window correctly \n");
        exit(1);
    }
    else
    {
        for(row=0; row<FULL; row++)
        {
            for(col=0; col<FULL; col++)
            {
                fscanf(fpt, "%d", &grid[row][col]);
            }
        }
    }
    fclose(fpt);
}

void display(int grid[][FULL])
{
	int row ,col;
	for (row=0; row<FULL; row++)
	{
		for(col=0; col<FULL; col++)
		{
			printf("%d ",grid[row][col]);
		}
	printf("\n");
	}
}

void output(int grid[][FULL])
{
    int row, col;
    FILE *fpt;
	fpt = fopen("answer.txt","w");
	for(row=0; row<FULL; row++)
	{
		for(col=0; col<FULL; col++)
			fprintf(fpt,"%d ",grid[row][col]);
		fprintf(fpt,"%c",'\n');
	}
	fclose(fpt);
	system("notepad answer.txt");
}

int emptycells(int grid[][FULL], int free[][2])
{
    int row, col, f=0; // f counts the number of free cells
    for(row=0; row<FULL; row++)
    {
        for(col=0; col<FULL; col++)
        {
            if(grid[row][col]==0) // if the selected cell is empty, we store the location of free cell
            {
                free[f][0]=row;
                free[f][1]=col;
                f++;
            }
        }
    }
    return f; // To know number of empty cells found
}

int isvalid(int grid[][FULL], int row, int col)
{
    int p,i,j;
    //checking if filled number is valid at the same row
    for(p=0; p<FULL; p++)
    {
        if((p!=col) && (grid[row][col]==grid[row][p]))
            return 0;
    }

    //checking if filled number is valid at the same column
    for(p=0; p<FULL; p++)
    {
        if((p!=row) && (grid[row][col]==grid[p][col]))
            return 0;
    }

    //checking if filled number is valid in the region
    for(i=(row/PART)*PART; i<(row/PART)*PART + PART; i++ )
    {
        for(j=(col/PART)*PART; j<(col/PART)*PART + PART; j++ )
        {
            if((i!=row)&&(j!=col)&&(grid[row][col]==grid[i][j]))
                return 0;
        }
    }
    return 1; //No rules breached
}


int recur(int grid[][FULL], int free[][2], int f, int k)
{
    int row, col,i,j;
    if (f==0) // No free Cell
        return 1; //Returning solved

    while (1) //Setting up a simple condition for looping continuously
    {
        row = free[k][0];
        col = free[k][1];
        if(grid[row][col]==0) //Checking if the selected free cell hasn't been filled
            grid[row][col]=1; //Filling free cell as 1

        if(isvalid(grid, row, col)) //Checking if filling is valid
        {
            if((k+1) == f)  // Checking if there are no more free cells
                return 1;  // Solution found
            else
                k++;        //Going to the next free cell
        }

        else if(grid[row][col]<FULL) // Checking if the invalid filled number is less than maximum possible value
            grid[row][col]++; //Filling with next possible value

        else
        {
            while(grid[row][col]==FULL) // Checking if the invalid filled number is equal to maximum possible value
            {
                if(k==0) // Checking if the cell is the first free cell
                    return 0; //No possible value

                // For cases when selected free cell is not the first one
                grid[row][col]=0; //Resetting the current free cell to 0

                k--;  // Backtracking or Going to the previous free cell
                row=free[k][0];
                col=free[k][1];
            }

            //Filling the free cell with next possible value
            grid[row][col]++;
            //The loop continues from this free cell pointed by k
      }
   }
}
