////////////////////////////
//
// ルール：
// 　・ユーザー１とユーザー２は交互にコマを進め，先に全てのコマが相手陣地へ移動した方の勝ち
// 　・前にいるコマは幾つでも飛び越えられる（空マスは飛び越えられない）
//
////////////////////////////

#include <iostream>
#include <vector>

using namespace std;
#define uint unsigned int

struct node_t{
	vector<int>  board;
	pair<int, int> sumMoveDistance;
	uint next[3] = {NULL, NULL, NULL};
};

class GameBoard
{
		int turn;
		int row;
		int num;
		int GoalDistance;
		vector<node_t *> tree;

	public:
		GameBoard(void);
		~GameBoard(void);
		int Size(void);
		void setBoard(void);
		void getNumber(void);
		void printBoard(void);
		bool movePieace(node_t, node_t *, int &, int);
		void makeNode(node_t *);
		void addNode(node_t *, node_t *, int);
		void makeAllNode(void);
		bool judgeWinner(node_t);
};
