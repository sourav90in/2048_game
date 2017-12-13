/*
 * 2048_impl.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: Sourav
 */


#include "2048.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace pzl;

void puzl_brd::Show_Board()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0; j<4; j++)
		{
			cout<<(int)this->board[i][j]<<" ";
		}
		cout<<"\n";
	}

	cout<<"\n"<<"\n";
}

void puzl_brd::ExecuteMove(Direction dir)
{
	/* If direction is up or down
	 * for each column move all thr rows up or down
	 */
	int firstInvalidPos;
	int ValidPos;
	int StartPos;
	int EndPos;
	int j = 0;
	if ( (  dir == Up ) || (dir == Down ) )
	{
		for( int i=0; i<4; i++ )
		{
			firstInvalidPos = -1 ;
			ValidPos = -1 ;

			if( dir == Up )
			{
				StartPos = 0;
				EndPos = 3;
			}
			else
			{
				StartPos = 3;
				EndPos = 0;
			}

			j = StartPos;
			while(1)
			{
				if( this->board[j][i] == Invalid )
				{
					if( firstInvalidPos == -1 )
						firstInvalidPos = j;
				}
				else
				{
					ValidPos = j;
					/* Valid pos is found, check if there is an empty space to move
					 * the valid space upward to
					 */
					if( firstInvalidPos != -1 )
					{
						this->board[firstInvalidPos][i] = this->board[ValidPos][i];
						/* Fill all entries from first invalid pos+1/invalid_pos-1 to first valid pos with zeros */
						if( dir == Up ){
							for( int k=firstInvalidPos+1; k <= ValidPos; k++ )
							{
								this->board[k][i] = Invalid;
							}
							firstInvalidPos = firstInvalidPos+1;
						}
						else
						{
							for( int k=firstInvalidPos-1; k >= ValidPos; k-- )
							{
								this->board[k][i] = Invalid;
							}
							firstInvalidPos = firstInvalidPos-1;
						}
					}
				}

				if( dir == Up )
				{
				    j++;
				    if( j > EndPos) break;
				}
				else
				{
					j--;
					if( j < EndPos ) break;
				}
			}
		}
	}
	else if ( (  dir == Left ) || (dir == Right ) )
	{
		int i=0;
		for( int j=0; j<4; j++ )
		{
			firstInvalidPos = -1 ;
			ValidPos = -1 ;

			if( dir == Left )
			{
				StartPos = 0;
				EndPos = 3;
			}
			else
			{
				StartPos = 3;
				EndPos = 0;
			}

			i = StartPos;
			while(1)
			{
				if( this->board[j][i] == Invalid )
				{
					if( firstInvalidPos == -1 )
						firstInvalidPos = i;
				}
				else
				{
					ValidPos = i;
					/* Valid pos is found, check if there is an empty space to move
					 * the valid space upward to
					 */
					if( firstInvalidPos != -1 )
					{
						this->board[j][firstInvalidPos] = this->board[j][ValidPos];
						/* Fill all entries from first invalid pos+1/invalid_pos-1 to first valid pos with zeros */
						if( dir == Left ){
							for( int k=firstInvalidPos+1; k <= ValidPos; k++ )
							{
								this->board[j][k] = Invalid;
							}
							firstInvalidPos = firstInvalidPos+1;
						}
						else
						{
							for( int k=firstInvalidPos-1; k >= ValidPos; k-- )
							{
								this->board[j][k] = Invalid;
							}
							firstInvalidPos = firstInvalidPos-1;
						}
					}
				}

				if( dir == Left )
				{
					i++;
					if( i > EndPos) break;
				}
				else
				{
				   i--;
				   if( i < EndPos ) break;
				}
			}
		}
	}

}

void puzl_brd::board_init()
{
	for(int i=0; i< 4; i++)
	{
		for(int j=0; j<4; j++)
		{
			this->board[i][j] = Invalid;
		}
	}
}

void pzl::ExecuteMoveUnitest()
{
	puzl_brd* c_ptr = new puzl_brd;

	c_ptr->Show_Board();
	c_ptr->ExecuteMove(Up);
	c_ptr->Show_Board();

}

void pzl::NGCUnitest()
{
	puzl_brd* c_ptr = new puzl_brd;

	c_ptr->Show_Board();
	c_ptr->ExecuteMove(Down);
	c_ptr->nonGreedyCombine(Down);
	c_ptr->Show_Board();

}

void puzl_brd::nonGreedyCombine(Direction dir)
{
	/* If direction of movement is up
	 * a) Find same consecutive digits across rows in each col
	 * b) Combine one such instance and move all other digits one row up
	 */
	int StartPos;
	int EndPos;

	if( ( dir == Up ) || ( dir == Down) )
	{
		int k =0;
		int j;
		if( dir == Up )
		{
			StartPos = 0;
			EndPos = 3;
		}
		else
		{
			StartPos = 3;
			EndPos = 0;
		}
		for(int i=0; i<4; i++)
		{
			j = StartPos;
			while(1)
			{
				if( ( ( this->board[j][i] == this->board[j+1][i] ) &&
					  ( this->board[j][i] != Invalid ) && ( dir == Up ) ) ||
				    ( ( this->board[j][i] == this->board[j-1][i] ) &&
				       ( this->board[j][i] != Invalid ) && ( dir == Down) ) )
				{
					this->board[j][i] = (brd_val)( this->board[j][i] + this->board[j][i] );
					if( dir == Up )
					{
						for(k=j+1;k<3;k++)
						{
							this->board[k][i] = this->board[k+1][i];
						}

						this->board[3][i] = Invalid;
					}
					else
					{
						for(k=j-1;k>0;k--)
						{
							this->board[k][i] = this->board[k-1][i];
						}

						this->board[0][i] = Invalid;
					}

				}

				if( dir == Up )
				{
					j++;
					if( j > EndPos ) break;
				}
				else
				{
					j--;
					if( j < EndPos ) break;
				}
			}
		}
	}
	else if( ( dir == Left ) || ( dir == Right ) )
	{
		int k =0;
		int i=0;
		if( dir == Left )
		{
			StartPos = 0;
			EndPos = 3;
		}
		else
		{
			StartPos = 3;
			EndPos = 0;
		}
		for(int j=0; j<4; j++)
		{
			i = StartPos;
			while(1)
			{
				if( ( ( this->board[j][i] == this->board[j][i+1] ) &&
						( this->board[j][i] != Invalid ) && ( dir == Left ) ) ||
						( ( this->board[j][i] == this->board[j][i-1] ) &&
								( this->board[j][i] != Invalid ) && ( dir == Right) ) )
				{
					this->board[j][i] = (brd_val)( this->board[j][i] + this->board[j][i] );
					if( dir == Left )
					{
						for(k=i+1;k<3;k++)
						{
							this->board[j][k] = this->board[j][k+1];
						}

						if( k == i+1 )
						{
							this->board[j][3] = Invalid;
						}
					}
					else
					{
						for(k=i-1;k>0;k--)
						{
							this->board[j][k] = this->board[j][k-1];
						}

						if( k == i-1 )
						{
							this->board[j][0] = Invalid;
						}
					}
				}

				if( dir == Left )
				{
					i++;
					if( i > EndPos ) break;
				}
				else
				{
					i--;
					if( i < EndPos ) break;
				}
			}
		}
	}
}

verdict puzl_brd::GameCond()
{
	/* Detect Continue condition:
	 * a) Invalid spaces exist
	 * b) No Invalid spaces exist but consecutive spaces down and left(automatically checks for up and right) are same.
	 */
	/* Detect Win condition that any of the tiles has the value 2048 */
	for(int i=0; i<4; i++)
	{
		for(int j=0;j<4;j++)
		{
			if( this->board[i][j] == TwothousandFortyEight ) return Win;
			else if ( this->board[i][j] == Invalid ) return Continue;
			else if(j != 3)
			{
				if( this->board[i][j] == this->board[i][j+1]) return Continue;
			}
			else if(i != 3)
			{
				if( this->board[i][j] == this->board[i+1][j]) return Continue;
			}
		}
	}

	/* If verdict is not Win nor is it continue, delcare as Loss */
	return Loss;
}

/* Helper random function */
int RIndexGen()
{
	return rand()%3;
}

/* Borrowed from geeksforgeeks website
 * Generating a random number with given prob distribution */
// Utility function to find ceiling of r in arr[l..h]
int findCeil(int arr[], int r, int l, int h)
{
    int mid;
    while (l < h)
    {
         mid = l + ((h - l) >> 1);  // Same as mid = (l+h)/2
        (r > arr[mid]) ? (l = mid + 1) : (h = mid);
    }
    return (arr[l] >= r) ? l : -1;
}

// The main function that returns a random number from arr[] according to
// distribution array defined by freq[]. n is size of arrays.
int myRand(int arr[], int freq[], int n)
{
    // Create and fill prefix array
    int prefix[n], i;
    prefix[0] = freq[0];
    for (i = 1; i < n; ++i)
        prefix[i] = prefix[i - 1] + freq[i];

    // prefix[n-1] is sum of all frequencies. Generate a random number
    // with value from 1 to this sum
    int r = (rand() % prefix[n - 1]) + 1;

    // Find index of ceiling of r in prefix arrat
    int indexc = findCeil(prefix, r, 0, n - 1);
    return arr[indexc];
}

void Rand2_4_Unitest()
{
	int r_arr[2] = {2,4};
	int r_freq[2] = {9,1};
	for(int i=0; i < 10; i++)
	{
		cout<<myRand(r_arr, r_freq, 2);
		cout<<" ";
	}
}

void pzl::Play2048Game()
{
	int i_rd, j_rd;
	int move;
	verdict ver;
	char p_a_g;
	int insert_r_no;
	puzl_brd* c_ptr = new puzl_brd;
	srand(time(NULL));

	int r_arr[2] = {2,4};
	int r_freq[2] = {9,1};

	new_g_label:

	c_ptr->board_init();
	/* Insert two 2's at rand positions on the board
	 * to begin the game.
	 */
	i_rd = RIndexGen();
	j_rd = RIndexGen();

	c_ptr->board[i_rd][j_rd] = Two;

	while(1)
	{
		i_rd = RIndexGen();
		j_rd = RIndexGen();
		if( c_ptr->board[i_rd][j_rd] != Invalid) continue;
		else
		{
			c_ptr->board[i_rd][j_rd] = Two;
			break;
		}
	}

	cout<<"Game is starting now, Current board is \n";
	c_ptr->Show_Board();

	while(1)
	{
		cout<<"Enter move 0(Up), 1(Down), 2(Left), 3(Right):";
		cin>>move;
		if( ( move != 0) && (move != 1) && (move != 2) && (move != 3) ) continue;

		c_ptr->ExecuteMove((Direction)move);
		c_ptr->nonGreedyCombine((Direction)move);

		ver = c_ptr->GameCond();
		if( ver == Continue )
		{
			/* Generate the random number first either 2 or 4*/
			insert_r_no = myRand(r_arr,r_freq,2);
			//cout<<insert_r_no<<"\n";

			while(1)
			{
				/* Generate the indexes where to insert */
				i_rd = RIndexGen();
				j_rd = RIndexGen();
				if( c_ptr->board[i_rd][j_rd] != Invalid) continue;
				else
				{
					c_ptr->board[i_rd][j_rd] = (brd_val)insert_r_no;
					break;
				}
			}
			c_ptr->Show_Board();
			continue;
		}
		else if( ver == Win)
		{
			cout<<"You Won wohoo \n";
			c_ptr->Show_Board();
		}
		else
		{
			cout<<"Boo you lost \n";
			c_ptr->Show_Board();
		}

		cout<<"Play another game? N(no)";
		cin>>p_a_g;

		if(p_a_g == 'N') break;
		else goto new_g_label;
	}
}

int main() {
	//ExecuteMoveUnitest();
	//NGCUnitest();
	//Rand2_4_Unitest();
	Play2048Game();
}


