#include "header.h"

GameBoard::GameBoard(void) {
	row = 1;
}

GameBoard::~GameBoard() {}

void GameBoard::setBoard() {
	node_t setBoard;
	setBoard.turn = 0;
	cin >> setBoard.board;
	setBoard.winState.first = false;
	setBoard.winState.second = false;
	tree.push_back(setBoard);
}


void GameBoard::printBoard(void) {
	cout << tree.size() << endl;
	for (int i = 0; i < tree.size(); i++) {
		cout << i << ':' << tree[i].board <<  ".....";
		if(tree[i].next.size() == 0){
			if(tree[i].winState.first) cout << "player1 won";
			else cout << "player2 won";
		}
		else{
			for (int j = 0; j < tree[i].next.size(); j++) {
				cout << tree[i].next[j] << "=>" << tree[tree[i].next[j]].board << ':';
			}
		}
		cout << endl;
	}
}

bool GameBoard::movePieace(int itr, node_t* nextNode, int turn, int posi) {
	if (turn % 2 == 0) {
		if (tree[itr].board[posi] == '1' && posi < 6) {
			for (int i = posi + 1; i < tree[itr].board.size(); i++) {
				if (tree[itr].board[i] == '-') {
					char tmp = nextNode->board[i];
					nextNode->board[i] = nextNode->board[posi];
					nextNode->board[posi] = tmp;
					bool flag = judgeWinner(nextNode);
					return true;
				}
			}
		}
	}
	else {
		if (tree[itr].board[posi] == '2' && posi > 2) {
			for (int i = posi - 1; i >= 0; i--) {
				if (tree[itr].board[i] == '-') {
					char tmp = nextNode->board[i];
					nextNode->board[i] = nextNode->board[posi];
					nextNode->board[posi] = tmp;
					bool flag = judgeWinner(nextNode);
					return true;
				}
			}
		}
	}

	return false;
}

void GameBoard::addNode(int itr, node_t nextNode, int posi) {
	// 重複を判定
	for (int i = 0; i < tree[itr].next.size(); i++) {
		if (nextNode.board == tree[tree[itr].next[i]].board) return;
	}

	nextNode.turn++;
	tree.push_back(nextNode);
	tree[itr].next.push_back(tree.size() - 1);

	// if (nextNode.winState.first)cout << "user1 win" << endl;
	// if (nextNode.winState.second)cout << "user2 win" << endl;
}

void GameBoard::makeNode(int itr) {
	node_t nextNode;
	for (int i = 0; i < 3; i++) {
		int j = 0;
		for (int k = 0; k < 9; k++) {
			if (tree[itr].turn % 2 == 0) {
				if (tree[itr].board[k] == '1') {
					if (i == j) {
						nextNode = tree[itr];
						nextNode.next.clear();
						if (movePieace(itr, &nextNode, tree[itr].turn, k)) {
							cout << tree[itr].board << ":" << nextNode.board << endl;
							addNode(itr, nextNode, i);
							break;
						}
						else if (i == 2 && k == 8 && tree[itr].next.size() == 0) {
							nextNode.turn++;
							tree.push_back(nextNode);
							tree[itr].next.push_back(tree.size() - 1);
							return;
						}
					}
					else j++;
				}
			}
			else {
				if (tree[itr].board[8 - k] == '2') {
					if (i == j) {
						nextNode = tree[itr];
						nextNode.next.clear();
						if (movePieace(itr, &nextNode, tree[itr].turn, 8 - k)) {
							cout << tree[itr].board << ":" << nextNode.board << endl;
							addNode(itr, nextNode, i);
							break;
						}
						else if (i == 2 && k == 8 && tree[itr].next.size() == 0) {
							nextNode.turn++;
							tree.push_back(nextNode);
							tree[itr].next.push_back(tree.size() - 1);
							return;
						}
					}
					else j++;
				}
			}
		}
	}
}

void GameBoard::makeTree() {
	node_t node;
	vector<node_t> way{ tree[0] };

	int i = 0;
	while (i < tree.size()) {
		node = tree[i];
		if (judgeWinner(&node)) {
			i++;
			continue;
		}
		makeNode(i);
		i++;
	}
	
}


bool GameBoard::judgeWinner(node_t *node) {
	if (node->board[6] == '1' && node->board[7] == '1' && node->board[8] == '1') {
		node->winState.first = true;
	}
	if (node->board[0] == '2' && node->board[1] == '2' && node->board[2] == '2') {
		node->winState.second = true;
	}

	return (node->winState.first || node->winState.second) ? true : false;
}

int main() {
	GameBoard Game;
	Game.setBoard();
	Game.makeTree();
	Game.printBoard();
	

	return 0;
}
