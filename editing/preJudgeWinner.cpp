#include "preJudgeWinner.h"

GameBoard::GameBoard(void){
	turn = 0;
	row = 1;
	num = 0;
	GoalDistance = row * 18;
	setBoard();
}

GameBoard::~GameBoard(){}

void GameBoard::setBoard(){
	node_t setBoard;
	setBoard.board = {1,1,1,0,0,0,2,2,2};
	setBoard.sumMoveDistance.first = 0;
	setBoard.sumMoveDistance.second = 0;
	tree.push_back(&setBoard);
}
void GameBoard::getNumber(){ //GameBoard()後に予期せぬ値に更新されているため修正用
	tree[0]->board[0] = 1;
	tree[0]->board[1] = 1;
}

void GameBoard::printBoard(void){
	for(int i = 0;i < 9; i++){
		cout << tree[0]->board[i] << ' ';
	}
	cout << endl;
}

bool GameBoard::movePieace(node_t node, node_t *nextNode, int &turn, int posi){
	*nextNode = node;
	turn++;

	if(turn % 2 == 1){
		if(node.board[posi] == 1){
			for(int i = posi + 1; i < node.board.size();i++){
				if(node.board[i] == 0){
					num++;
					iter_swap(nextNode->board.begin()+posi, nextNode->board.begin()+i);
					nextNode->sumMoveDistance.first += i-posi;
					return true;
				}
				//else if(i == node->board.size()-1) turn--;
			}
		}
	}
	else{
		if(node.board[posi] == 2){
			for(int i = posi - 1; i >= 0;i--){
				if(node.board[i] == 0){
					iter_swap(nextNode->board.begin()+posi, nextNode->board.begin()+i);
					nextNode->sumMoveDistance.second += posi - i;
					return true;
				}
				//else if(i == 0) turn--;
			}
		}
	}

	return &nextNode;
}

void GameBoard::addNode(node_t *node, node_t *nextNode, int posi){
		tree.push_back(nextNode);
		node->next[posi] = tree.size() - 1;
}

void GameBoard::makeNode(node_t *node){
	node_t *nextNode;
	bool opt;

	for(int i = 0;i < 3;i++){
		int j = 0;
		for(int k = 0;k < 9;k++){
			if(turn % 2 == 1){
				if(node->board[k] == 1){
					if(i == j){
						opt = movePieace(*node, nextNode, turn, k);
						addNode(node, nextNode, i);
						break;
					}
					else j++;
				}
			}
			else if(turn % 2 == 0){
				if(node->board[8-k] == 2){
					if(i == j){
						opt = movePieace(*node, nextNode, turn, 8-k);
						addNode(node, nextNode, i);
						break;
					}
					else j++;
				}
			}
		}
	}
}

void GameBoard::makeAllNode(){
	node_t *node;
	vector<node_t *> way{tree[0]};

	while(1){
		node = way[way.size() - 1];
		makeNode(node);
		// 再帰関数

		if(!judgeWinner(*node)) break;
	}
}


bool GameBoard::judgeWinner(node_t node){
	if(node.sumMoveDistance.first == GoalDistance) cout << "1 win" << endl;
	if(node.sumMoveDistance.second == GoalDistance) cout << "2 win" << endl;
	// どちらかの移動距離の合計が18*rowになったらtrue
	return (node.sumMoveDistance.first == GoalDistance || node.sumMoveDistance.second == GoalDistance)? true: false;
}

/*void GameBoard::movePieace(){
	while(oneSumMoveDistance < GoalDistance && twoSumMoveDistance < GoalDistance){
		turn++;

		for(int j = 0;j < 3;j++){
			
		}
	}

	return;
}*/
  


int GameBoard::Size(){
	return tree.size();
}

int main(){
	GameBoard Game;
	Game.getNumber();



	return 0;
}
