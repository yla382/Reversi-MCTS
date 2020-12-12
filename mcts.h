#ifndef MCTS_H
#define MCTS_H

#include <iostream>
#include <vector>
#include <cstdlib> 
#include "node.h"

using namespace std;

class MCTS {
	public:
		Node *root;
		Node *current_node;
		int sim_num;

		MCTS() {
			root = NULL;
			current_node =NULL;
			sim_num = 0;
		}

		MCTS(Node *node, int num) {
			root = node;
			current_node = node;
			sim_num = num;
		}

		void displayBoard(char** arr) {
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

		void expand(Node *node, char piece, vector<vector<int>> mv, void (*update_board)(char**, char, vector<int>, int&, int&)) {
			vector<vector<int>> mvcopy(mv);
			if(mv.size() == 0) {
			} else {
				while(mvcopy.size() > 0) {
					char** new_state = node->copy_state(node->state, 8);
					vector<int> move_checker = mvcopy[mvcopy.size() - 1];
					mvcopy.pop_back(); 
					Node *n = new Node(node, new_state, piece);
					(*update_board)(n->state, piece, move_checker, n->ai_score, n->player_score);
		
					if(mvcopy.size() > 0) {
						int size = mvcopy.size();
						int i;
						for(i = 0; i < size; i++) {
							if(move_checker[0] == mvcopy[i][0] && move_checker[1] == mvcopy[i][1]) {
								(*update_board)(n->state, piece, mvcopy[i], n->ai_score, n->player_score);
								mvcopy.erase(mvcopy.begin() + i);
								i--;
								size = mvcopy.size();
							}
						}
					}
				(node->children).push_back(n);
				}
			}
		}


		void recursive_simulate(Node* no, int run_count, char ai_piece, char player_piece, int& score_ai, int& score_player, void (*update_board)(char**, char, vector<int>, int&, int&), vector<vector<int>> (*getValidMoveList)(char**, char), bool (*finish_cond)(int, int)) {
			vector<vector<int>> ai_moves = (*getValidMoveList)(no->state, ai_piece);
			vector<vector<int>> player_moves = (*getValidMoveList)(no->state, player_piece);


			if(ai_moves.size() == 0 && player_moves.size() == 0) {
				return;
			} else if((*finish_cond)(no->ai_score, no->player_score)) {
				return;
			} else if(run_count <= 0) {
				return;
			}else {
				if(no->turn == ai_piece) {
					if(player_moves.size() == 0) {
						expand(no, ai_piece, ai_moves, update_board);

						if(no->children.size() > 5) {
							for(int i = 0; i < no->children.size() / 3; i++) {
								int index =  rand() % no->children.size();
								score_ai = score_ai + no->children[index]->ai_score;
								score_player = score_player + no->children[index]->player_score;
								recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
							}
						} else {
							int index = rand() % no->children.size();
							score_ai = score_ai + no->children[index]->ai_score;
							score_player = score_player + no->children[index]->player_score;
							recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
						}
					} else {
						expand(no, player_piece, player_moves, update_board);
						
						if(no->children.size() > 5) {
							for(int i = 0; i < no->children.size() / 3; i++) {
								int index =  rand() % no->children.size();
								score_ai = score_ai + no->children[index]->ai_score;
								score_player = score_player + no->children[index]->player_score;
								recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
							}


						} else {
							int index = rand() % no->children.size();
							score_ai = score_ai + no->children[index]->ai_score;
							score_player = score_player + no->children[index]->player_score;
							recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
						}
					}
				} else {
					if(ai_moves.size() == 0) {
						expand(no, player_piece, player_moves, update_board);
						
						if(no->children.size() > 5) {
							for(int i = 0; i < no->children.size()/ 3; i++) {
								int index = rand() % no->children.size();
								score_ai = score_ai + no->children[index]->ai_score;
								score_player = score_player + no->children[index]->player_score;
								recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
							}

						} else {
							int index = rand() % no->children.size();
							score_ai = score_ai + no->children[index]->ai_score;
							score_player = score_player + no->children[index]->player_score;
							recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
						}
					} else {
						expand(no, ai_piece, ai_moves, update_board);

						if(no->children.size() > 5) {
							for(int i = 0; i < no->children.size() / 3; i++) {
								int index =  rand() % no->children.size();
								score_ai = score_ai + no->children[index]->ai_score;
								score_player = score_player + no->children[index]->player_score;
								recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
							}
						} else {
							int index = rand() % no->children.size();
							score_ai = score_ai + no->children[index]->ai_score;
							score_player = score_player + no->children[index]->player_score;
							recursive_simulate(no->children[index], run_count - 1, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
						}
					}
				}
			}
		}

		void simulate(char ai_piece, char player_piece, void (*update_board)(char**, char, vector<int>, int&, int&), vector<vector<int>> (*getValidMoveList)(char**, char), bool (*finish_cond)(int, int)) {
			vector<Node*> nodes = current_node->children;
			
			for(int i = 0; i < nodes.size(); i++) {
				int score_ai = 0;
				int score_player = 0;
				Node* sim_node = new Node(nodes[i]);				
				recursive_simulate(sim_node, sim_num, ai_piece, player_piece, score_ai, score_player, update_board, getValidMoveList, finish_cond);
				nodes[i]->ai_cumulative_score = score_ai;
				nodes[i]->player_cumulative_score = score_player;
			}
		}

		char** select() {
			vector<Node*> nodes = current_node->children;
			if(nodes.size() > 0) {
				current_node = nodes[0];
				for(int i = 1; i < nodes.size(); i++) {
					int current_score = current_node->ai_cumulative_score * 0.4 + current_node->player_cumulative_score * 0.6;
					int new_score = nodes[i]->ai_cumulative_score * 0.4 + nodes[i]->player_cumulative_score * 0.6;
					if(current_score > new_score) {
						current_node = nodes[i];
					}
				}
			}
			return current_node->state;
		}

		char** select_with_heuristics(int (*heuristic)(Node*)) {
			vector<Node*> nodes = current_node->children;
			if(nodes.size() > 0) {
				current_node = nodes[0];
				for(int i = 1; i < nodes.size(); i++) {
					int current_score = (*heuristic)(current_node);
					int new_score = (*heuristic)(nodes[i]);
					if(current_score < new_score) {
						current_node = nodes[i];
					}
				}
			}
			return current_node->state;
		}

		bool compare_state(Node *n, char **board) {
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					if(n->state[i][j] != board[i][j]){
						return false;
					}
				}
			}
			return true;
		}

		void update_current_node(char **board, char ai_piece, char player_piece, void (*update_board)(char**, char, vector<int>, int&, int&), vector<vector<int>> (*getValidMoveList)(char**, char)) {
			if(compare_state(current_node, board) == false) {
				vector<vector<int>> player_moves = (*getValidMoveList)(current_node->state, player_piece);
				expand(current_node, player_piece, player_moves, update_board);

				if(current_node->children.size() > 0) {
					for(int i = 0; i < current_node->children.size(); i++) {
						if(compare_state(current_node->children[i], board)) {
							current_node = current_node->children[i];
							break;
						}
						cout << "no matching\n";
					}
				}
			}
		}
};

#endif
