
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

class GameBoard
{
        int turn = 0;
        int row = 1;
        int select;
        int oneSumMoveDistance = 0;
        int twoSumMoveDistance = 0;
        int DoalDistance = row * 18;
        vector<ventor<int> *> Boards;
  
    public:
        GameBoard(void);
        ~GameBOard(void);
        void movePieace(void);
        void judgeWinner(void);
};

GameBoard::GameBoard(void){
    vector<int> *board;
    board = {1,1,1,0,0,0,2,2,2};
    Boards.push_back(board);  
}

GameBoard::~Gameboard(){}
  


int main(){
    
    int GoalDistance = row * 18;
    while(oneSumMoveDistance < GoalDistance && twoSumMoveDistance < GoalDistance){
        turn++;
        cout << "  0 1 2 3 4 5 6 7 8" << endl << "[ ";
        for (int n = 0; n < array.size(); n++) {
            cout << array[n] << ' ';
        }
        cout << "]" << endl;

        if(turn % 2 == 1){
            if(array[select] == 1){
                for(int i = select + 1; i < array.size();i++){
                    if(array[i] == 0){
                        iter_swap(array.begin()+select, array.begin()+i);
                        oneSumMoveDistance += i-select;
                        break;
                    }
                    //else if(i == array.size()-1) turn--;
                }
            }
            else turn--;
        }
        else{
            if(array[select] == 2){
                for(int i = select - 1; i >= 0;i--){
                    if(array[i] == 0){
                        iter_swap(array.begin()+select, array.begin()+i);
                        twoSumMoveDistance += select - i;
                        break;
                    }
                    //else if(i == 0) turn--;
                }
            }
            else turn--;
        }
        cout << "1:" << oneSumMoveDistance << " " << "2:" << twoSumMoveDistance << endl;
    }

    if(oneSumMoveDistance == GoalDistance) cout << "1 win" << endl;
    if(twoSumMoveDistance == GoalDistance) cout << "2 win" << endl;

    return 0;
}
