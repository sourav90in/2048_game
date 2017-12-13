/*
 * 2048.h
 *
 *  Created on: Dec 10, 2017
 *      Author: Sourav
 */

//#ifndef 2048_H_
//#define 2048_H_

namespace pzl
{
using namespace std;
class puzl_brd;
enum brd_val
{
	Invalid = 0,
	Two = 2,
	Four = 4,
	Eight = 8,
	Sixteen = 16,
	Thirtytwo = 32,
	SixtyFour = 64,
	OneTwentyEight = 128,
	TwoFiftySix = 256,
	FiveHundredtwelve = 512,
	OneThousandTwentyFour = 1024,
	TwothousandFortyEight = 2048
};
enum verdict
{
	Continue = 0,
	Win = 1,
	Loss = 2
};
enum Direction
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3
};
void ExecuteMoveUnitest();
void NGCUnitest();
void Play2048Game();

}


class pzl::puzl_brd
{
private:
	brd_val board[4][4] =  { {Invalid,Invalid,Two,Invalid},
	                         {Invalid,Invalid,Invalid,Invalid},
	                         {Invalid,Two,Invalid,Invalid},
	                         {Invalid,Invalid,Invalid,Invalid} };
	void board_init();
	bool isMoveValid();
	void ExecuteMove(Direction);
	void nonGreedyCombine(Direction);
	verdict GameCond();
	void Show_Board();
public:
	puzl_brd() { board_init(); }
    friend void pzl::ExecuteMoveUnitest();
    friend void pzl::NGCUnitest();
    friend void pzl::Play2048Game();
};

//#endif /* 2048_H_ */
