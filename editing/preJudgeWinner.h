////////////////////////////
//
// ルール：
// 　・ユーザー１とユーザー２は交互にコマを進め，先に全てのコマが相手陣地へ移動した方の勝ち
// 　・前にいるコマは幾つでも飛び越えられる（空マスは飛び越えられない）
//
////////////////////////////

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node_t{
	int turn;
	std::string  board;
	pair<bool, bool> sumMoveDistance;
	vector<int> next;
};

class GameBoard
{
		int row;
		vector<node_t> tree;

	public:
		GameBoard(void);
		~GameBoard(void);
		void setBoard(void);
		void printBoard(void);
		bool movePieace(int, node_t *, int, int);
		void makeNode(int);
		void addNode(int, node_t, int);
		void makeTree(void);
		bool judgeWinner(node_t *);
};
