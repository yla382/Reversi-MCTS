#include <iostream>
#include <vector>
#include <ctime>
#include "node.h"
#include "mcts.h"

using namespace std;

//Global Variable declarations
int ai_score = 2;
int player_score = 2;

char ai_piece = 'W';
char player_piece = 'B';

char board[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					{' ', ' ', ' ', 'W', 'B', ' ', ' ', ' '},
					{' ', ' ', ' ', 'B', 'W', ' ', ' ', ' '},
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
					};

void Menu(){

}

void displayBoard(char** arr) {
	cout << "   0   1   2   3   4   5   6   7\n";
	cout << "----------------------------------\n";
	for(int i = 0; i < 8; i++) {
		cout << i << "|";
		for(int j = 0; j < 8; j++) {
			cout << " ";
			cout << arr[i][j];
			cout << " |";
		}
		cout << "\n";
		cout << "----------------------------------\n";
	}
}

char **hard_copy(char s[8][8]) {
	char **new_board = new char*[8];
	for(int i = 0; i < 8; i++) {
		char *row = new char[8];
		for(int j = 0; j < 8; j++) {
			row[j] = s[i][j];
		}
		new_board[i] = row;
	}
	return new_board;
}

vector<vector<int>> getValidMoveList(char** board, char piece) {
	vector<vector<int>> totalmove = {};
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(board[i][j] == 'W' || board[i][j] == 'B') {
				if(j - 1 > -1 && board[i][j - 1] == ' ') { //left side check
					vector<int> move = {};
					int k = j;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k < 8 && board[i][k] != piece && board[i][k] != ' ') {
							k++;
							distance++;
						}
						move = {i, j - 1, distance, 0};
					}
					if(k > -1 && k < 8 && move.size() > 0 && board[i][k] != ' '){
						totalmove.push_back(move);
					}
				}

				if(j + 1 < 8 && board[i][j + 1] == ' ') { //check right side
					vector<int> move = {};
					int k = j;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k > -1 && board[i][k] != piece && board[i][k] != ' ') {
							k--;
							distance++;
						}
						move = {i, j + 1, distance, 1};
					}
					if(k > -1 && k < 8 && move.size() > 0 && board[i][k] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i - 1 > -1 && board[i - 1][j] == ' ') { //check up side
					vector<int> move = {};
					int k = i;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k < 8 && board[k][j] != piece && board[k][j] != ' ') {
							k++;
							distance++;
						}
						move = {i - 1, j, distance, 2};
					}
					if(k > -1 && k < 8 && move.size() > 0 && board[k][j] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i + 1 < 8 && board[i + 1][j] == ' ') { //check down side
					vector<int> move = {};
					int k = i;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k > -1 && board[k][j] != piece && board[k][j] != ' ') {
							k--;
							distance++;
						}
						move = {i + 1, j, distance, 3};
					}
					if(k > -1 && k < 8 && move.size() > 0 && board[k][j] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i - 1 > -1 && j - 1 > -1 && board[i - 1][j - 1] == ' ') { //left diag from top
					vector<int> move = {};
					int k = i;
					int b = j;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k < 8 && b < 8 && board[k][b] != piece && board[k][b] != ' ') {
							k++;
							b++;
							distance++;
						}
						move = {i - 1 , j - 1, distance, 4};
					}
					if(k > -1 && k < 8 && b > -1 && b < 8 && move.size() > 0 && board[k][b] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i + 1 < 8 && j + 1 < 8 && board[i + 1][j + 1] == ' ') { //left diag from bottom
					vector<int> move = {};
					int k = i;
					int b = j;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k > -1 && b > -1 && board[k][b] != piece && board[k][b] != ' ') {
							k--;
							b--;
							distance++;
						}
						move = {i + 1 , j + 1, distance, 5};
					}
					if(k > -1 && k < 8 && b > -1 && b < 8 && move.size() > 0  && board[k][b] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i - 1 > -1 && j + 1 < 8 && board[i - 1][j + 1] == ' ') { //right diag from top
					vector<int> move = {};
					int k = i;
					int b = j;
					int distance = 0;
					if(board[i][j] != piece) {
						while(k < 8 && b > -1 && board[k][b] != piece && board[k][b] != ' ') {
							k++;
							b--;
							distance++;
						}
						move = {i - 1 , j + 1, distance, 6};
					}
					if(k > -1 && k < 8 && b > -1 && b < 8 && move.size() > 0 && board[k][b] != ' '){
						totalmove.push_back(move);
					}
				}

				if(i + 1 < 8 && j - 1 > - 1 && board[i + 1][j - 1] == ' ') { //right diag from bottom
					vector<int> move = {};
					int k = i;
					int b = j;
					int distance = 0;

					if(board[i][j] != piece) {
						while(k > -1 && b < 8 && board[k][b] != piece && board[k][b] != ' ') {
							k--;
							b++;
							distance++;
						}
						move = {i + 1 , j - 1, distance, 7};
					}
					if(k > -1 && k < 8 && b > -1 && b < 8 && move.size() > 0 && board[k][b] != ' '){
						totalmove.push_back(move);
					}
				}
			}
		}
	}
	return totalmove;
}

void update_scores(char** board, int &score1, int &score2) {
	int new_score_1 = 0;
	int new_score_2 = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(board[i][j] == 'W') {
				new_score_1++;
			}

			if(board[i][j] == 'B') {
				new_score_2++;
			}
		}
	}

	score1 = new_score_1;
	score2 = new_score_2;
}


void changeBoard(char** board,char piece, vector<int> matched_move, int &score1, int &score2) {
		board[matched_move[0]][matched_move[1]] = piece;
		if(matched_move[3] == 0) { //left
			int jump = 1;
			for(int j = 1; j <= matched_move[2]; j++) {
				board[matched_move[0]][matched_move[1] + jump] = piece;
				jump++;
			}

		} else if(matched_move[3] == 1) { //right
			int jump = 1;
			for(int j = matched_move[2]; j > 0; j--) {
				board[matched_move[0]][matched_move[1] - jump] = piece;
				jump++;
			}

		} else if(matched_move[3] == 2) { //up
			int jump = 1;
			for(int j = 1; j <= matched_move[2]; j++) {
				board[matched_move[0] + jump][matched_move[1]] = piece;
				jump++;
			}

		} else if(matched_move[3] == 3) { //down
			int jump = 1;
			for(int j = matched_move[2]; j > 0; j--) {
				board[matched_move[0] - jump][matched_move[1]] = piece;
				jump++;
			}

		} else if(matched_move[3] == 4) { //left-diag up
			int jump = 1;
			for(int j = 1; j <= matched_move[2]; j++) {
				board[matched_move[0] + jump][matched_move[1] + jump] = piece;
				jump++;
			}

		} else if(matched_move[3] == 5) { //left-diag down
			int jump = 1;
			for(int j = matched_move[2]; j > 0; j--) {
				board[matched_move[0] - jump][matched_move[1] - jump] = piece;
				jump++;
			}

		} else if(matched_move[3] == 6) { // right-diag up
			int jump = 1;
			for(int j = 1; j <= matched_move[2]; j++) {
				board[matched_move[0] + jump][matched_move[1] - jump] = piece;
				jump++;
			}
		} else { //right diag down
			int jump = 1;
			for(int j = matched_move[2]; j > 0; j--) {
				board[matched_move[0] - jump][matched_move[1] + jump] = piece;
				jump++;
			}

	}
	update_scores(board, score1, score2);

}

vector<vector<int>> get_matching_move(int ro, int co, vector<vector<int>> available_moves) {
	vector<vector<int>> matching_moves = {};
	for(int i = 0; i < available_moves.size(); i++) {
		if(ro == available_moves[i][0] && co == available_moves[i][1]) {
			matching_moves.push_back(available_moves[i]);
		}
	}
	return matching_moves;
}

void makeMove(char** b, char piece, vector<vector<int>> available_moves, int& s1, int& s2) {
	if(available_moves.size() > 0) {
		int row;
		cout << "Type a row: ";
		cin >> row;

		int column;
		cout << "Type a column: ";
		cin >> column;
		vector<vector<int>> matched_move = get_matching_move(row, column, available_moves);
		while(matched_move.size() <= 0) {
			cout << "This is invalid move!\n";

			cout << "Type a row: ";
			cin >> row;

			cout << "Type a column: ";
			cin >> column;
			matched_move = get_matching_move(row, column, available_moves);
		}

		for(int i = 0; i < matched_move.size(); i++) {
			changeBoard(b, piece, matched_move[i], s1, s2);
		}

	} else {
		cout << "No available moves, pass\n";
	}
}

bool game_end(int score1, int score2) {
	if(score1 + score2 == 64) {
		return true;
	} else {
		return false;
	}
}

//Heuristics
int CumulativeSum(Node *node){ //Heuristic One
	int cumSum = 0;
	int playerScore = node->player_cumulative_score;
	int aiScore = node-> ai_cumulative_score; 
	cumSum = playerScore + aiScore;
	return cumSum; 
}

int CumulativeDiff(Node *node){ //Heuristic One
	int cumDiff = 0;
	int playerScore = node->player_cumulative_score;
	int aiScore = node-> ai_cumulative_score; 
	cumDiff = playerScore - aiScore;
	return cumDiff; 
}

int PercentCoverage(Node *node){ //Heuristic Two
	int sum = CumulativeSum(node);
	int diff = CumulativeDiff(node);
	int percentageCov = 0;
	if(diff<0){
		percentageCov = -(node->ai_cumulative_score/sum)* 100;
	} else {
		percentageCov = (node->player_cumulative_score/sum) * 100;
	}
	return percentageCov;
}

int percentageMove(Node *node){ //Heuristic Three
	int percentMove = 0;
	int sum = CumulativeSum(node);
	int diff = CumulativeDiff(node);
	char currTurn = node->turn;
	char opponentTurn = ' ';
	if(currTurn == 'W'){
		opponentTurn = 'B';
	} else {
		opponentTurn = 'W';
	}

	int currMoves = getValidMoveList(node->state,currTurn).size();
	int opponentMoves = getValidMoveList(node->state, opponentTurn).size();

	if(diff<0){
		percentMove = -(opponentMoves/sum) * 100;
	} else {
		percentMove = (currMoves/sum) * 100;
	}
	return percentMove;	
}

int staticAssignment(Node *node){ //Heuristic Four
	int sum = 0;
	char currTurn = node->turn;
	char opponentTurn = ' ';
	if(currTurn == 'W'){
		opponentTurn = 'B';
	} else {
		opponentTurn = 'W';
	}

	int staticWeights[8][8] = {{4, -3, 2, 2, 2, 2, -3, 4},
					{-3, -4, -1, -1, -1, -1, -4, -3},
					{2, -1, 1, 0, 0, 1, -1, 2},
					{2, -1, 0, 1, 1, 0, -1, 2},
					{2, -1, 0, 1, 1, 0, -1, 2},
					{2, -1, 1, 0, 0, 1, -1, 2},
					{-3, -4, -1, -1, -1, -1, -4, -3},
					{-4, -3, 2, 2, 2, 2, -3, 4}
					};

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if (board[i][j] == currTurn) {
				sum += staticWeights[i][j];
			} else if(board[i][j] == opponentTurn) {
				sum += staticWeights[i][j];
			}
		}
	}
	return sum;
}

//All Heuristic Functions
int HeuristicEvaluation (Node *node){
	char currPiece = node->turn;
	char opponentPiece = ' ';
	if(currPiece == 'W'){
		opponentPiece = 'B';
	} else {
		opponentPiece = 'W';
	}

	//H1 - Difference Heuristic Initialization - Select function in mcts.h
	int scoreDifference = 0;
	int scoreSum = 0;
	int H1Weight = 1;

	//H2 - Percentage Coverage Initialization
	int percentageCoverage = 0;
	int H2Weight = 10;

	//H3 - Valid Move Heuristic
	int percentageMoves = 0;
	int currMoves = getValidMoveList(node->state,currPiece).size();
	int opponentMoves = getValidMoveList(node->state,opponentPiece).size();
	int H3Weight = 20;

	if(currPiece == 'W'){
		scoreDifference = ai_score - player_score; //Calculated difference in score for H1
		scoreSum = ai_score + player_score; //Find sum of scores
		if(scoreDifference < 0) { //White player is losing in this state
			percentageCoverage = -(player_score/scoreSum)* 100; //Calculate percentage cover
			percentageMoves = -(opponentMoves/scoreSum) * 100; //Calculate percentage of each move
		} else { //White player is winning
			percentageCoverage = (ai_score / scoreSum) * 100;
			percentageMoves = (currMoves / scoreSum) * 100;
		}
	} else { //Current piece is black
		scoreDifference = player_score - ai_score;
		scoreSum = player_score + ai_score;
		if(scoreDifference < 0) { //Black payer is losing in this state
			percentageCoverage = -(ai_score/scoreSum) * 100;
			percentageMoves = -(opponentMoves/scoreSum) * 100;
		} else {//Black player is winning 
			percentageCoverage = (player_score/scoreSum) * 100;
			percentageMoves = (currMoves/scoreSum) * 100;
		}
	}

	//H4 - Static Weights Heuristic Function (See references)
	int H4Weight = 10;
	int staticWeights[8][8] = {{4, -3, 2, 2, 2, 2, -3, 4},
					{-3, -4, -1, -1, -1, -1, -4, -3},
					{2, -1, 1, 0, 0, 1, -1, 2},
					{2, -1, 0, 1, 1, 0, -1, 2},
					{2, -1, 0, 1, 1, 0, -1, 2},
					{2, -1, 1, 0, 0, 1, -1, 2},
					{-3, -4, -1, -1, -1, -1, -4, -3},
					{-4, -3, 2, 2, 2, 2, -3, 4}
					};

	
	int boardSum = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if (board[i][j] == currPiece) {
				boardSum += staticWeights[i][j];
			} else if(board[i][j] == opponentPiece) {
				boardSum += staticWeights[i][j];
			}
		}
	}

	int HeuristicSum = (H1Weight*scoreDifference) + (H2Weight*percentageCoverage) + (H3Weight*percentageMoves) + (H4Weight*boardSum);
	return HeuristicSum;
}

//Human vs AI Version 
int main() { //Human vs AI
	clock_t time_req;
	cout << "\nWelcome to our CMPT 310 Final Project - Reversi with Monte-Carlo Tree Search" << endl;
	cout << "This is the Human Versus AI Version" << endl;
	cout << "The Black Player goes first and the layout of the board is as follows:\n" << endl;

	char** copied_board = hard_copy(board);
	displayBoard(copied_board);
	cout << "AI score: " << ai_score << "\n";
	cout << "Player score: " << player_score << "\n\n";
	cout << "Player's Turn (B)\n";

	Node* root = new Node(copied_board, ' ', ai_score, player_score);
	MCTS* AI = new MCTS(root, 10);

	while(true) {
		bool AI_pass = false;
		bool Player_pass = false;

		vector<vector<int>> player_moves = getValidMoveList(copied_board, player_piece);
		makeMove(copied_board, player_piece, player_moves, ai_score, player_score);

		if(player_moves.size() <= 0) {
			Player_pass = true;
		}

		displayBoard(copied_board);

		cout << "AI score: " << ai_score << "\n";
		cout << "Player score: " << player_score << "\n\n";
		
		if(ai_score + player_score >= 64) {
			if(ai_score >player_score){
				cout << "AI (W) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;
			} else if(ai_score < player_score){
				cout << "Player (B) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;	
			} else{
				cout << "It is a tie!" << endl;
				cout << "Ending Program." << endl;
				break;	
			}
		}
		cout << "AI's Turn (W)\n";

		time_req = clock();

		AI->current_node = new Node(copied_board, player_piece, ai_score, player_piece);
		vector<vector<int>> ai_moves =getValidMoveList(AI->current_node->state, ai_piece);
		(AI->expand)(AI->current_node, ai_piece, ai_moves, changeBoard);
		(AI->simulate)(ai_piece, player_piece, changeBoard, getValidMoveList, game_end);
		copied_board = (AI->select_with_heuristics)(HeuristicEvaluation);
		//copied_board = (AI->select)();  
		update_scores(copied_board, ai_score,player_score);
		
		time_req = clock() - time_req;
		cout << "The playout took " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;
 		
 		if(ai_moves.size() <= 0) {
			AI_pass = true;
		}

		displayBoard(copied_board);
		cout << "AI score: " << ai_score << "\n";
		cout << "Player score: " << player_score << "\n\n";

		if(ai_score + player_score >= 64) {
			if(ai_score >player_score){
				cout << "AI (W) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;
			} else if(ai_score < player_score){
				cout << "Player (B) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;	
			} else{
				cout << "It is a tie!" << endl;
				cout << "Ending Program." << endl;
				break;	
			}
		} else if(AI_pass && Player_pass) {
			break;
		}
		cout << "Player's Turn (B)\n";
	}
}

/*
//AI vs AI Version
int main() { 
	clock_t time_req;
	char** copied_board = hard_copy(board); 
	Node* root = new Node(copied_board, ' ', ai_score, player_score);

	MCTS* AI1 = new MCTS(root, 10);
	MCTS* AI2 = new MCTS(root, 10);

	cout << "\nWelcome to our CMPT 310 Final Project - Reversi with Monte-Carlo Tree Search" << endl;
	cout << "This is the AI Versus AI Version" << endl;
	cout << "The First AI (White)goes first and the layout of the board is as follows:\n" << endl;
	displayBoard(copied_board);

	cout << "First AI score: " << ai_score << "\n";
	cout << "Second AI score: " << player_score << "\n\n";
	cout << "First AI's Turn (W)\n";

	while(true) {
		bool AI_1_pass = false;
		bool AI_2_pass = false;
		time_req = clock();

		// FIRST AI1's turn
		vector<vector<int>> AI_1_moves = getValidMoveList(AI1->current_node->state, ai_piece);
		(AI1->expand)(AI1->current_node, ai_piece, AI_1_moves, changeBoard);
		(AI1->simulate)(ai_piece, player_piece, changeBoard, getValidMoveList, game_end);
		//copied_board = (AI1->select)();
		copied_board = (AI1->select_with_heuristics)(HeuristicEvaluation);

		time_req = clock() - time_req;
		cout << "The playout took " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;

		if(AI_1_moves.size() == 0) {
			AI_1_pass = true;
		}

		update_scores(copied_board, ai_score,player_score);

		displayBoard(copied_board);
		cout << "First AI score: " << ai_score << "\n";
		cout << "Second AI score: " << player_score << "\n\n";

		if(ai_score + player_score >= 64) {
			if(ai_score >player_score){
				cout << "First AI (W) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;
			} else if(ai_score < player_score){
				cout << "Second AI (B) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;	
			} else{
				cout << "It is a tie!" << endl;
				cout << "Ending Program." << endl;
				break;	
			}
		}
		cout << "Second AI's Turn (B)\n";


		// SECOND AI2's turn
		AI2->current_node = AI1->current_node;
		vector<vector<int>> AI_2_moves = getValidMoveList(AI2->current_node->state, player_piece);
		(AI2->expand)(AI2->current_node, player_piece, AI_2_moves, changeBoard);
		(AI2->simulate)(ai_piece, player_piece, changeBoard, getValidMoveList, game_end);
		//copied_board = (AI2->select)();
		copied_board = (AI2->select_with_heuristics)(HeuristicEvaluation);

		if(AI_2_moves.size() == 0) {
			AI_2_pass = true;
		}

		update_scores(copied_board, ai_score,player_score);

		displayBoard(copied_board);
		cout << "First AI score: " << ai_score << "\n";
		cout << "Second AI score: " << player_score << "\n\n";

		//Second game condition Check
		if(ai_score + player_score >= 64) {
			if(ai_score >player_score){
				cout << "First AI (W) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;
			} else if(ai_score < player_score){
				cout << "Second AI (B) Wins!" << endl;
				cout << "Ending Program." << endl;
				break;	
			} else{
				cout << "It is a tie!" << endl;
				cout << "Ending Program." << endl;
				break;	
			}
		} else if(AI_1_pass && AI_2_pass) {
			break;
		} else {

		}
		cout << "First AI's Turn (W)\n";

		//UPDATE AI1's current node
		AI1->current_node = AI2->current_node;

		cout << "Press Enter to continue\n";
		getchar();

		cout << "-----------------------------------------\n";
	}
}
*/
