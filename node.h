#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node {
	public:
		Node *parent;
		vector<Node*> children;
		char **state;
		char turn = ' ';
		int depth;
		int ai_score;
		int player_score;
		int ai_cumulative_score = 0;
		int player_cumulative_score = 0;


		Node() { //For testing 
			parent = NULL;
			children = {};
			state = NULL;
		}

		Node(char** s, char piece, int s1, int s2) { //Creating root node
			parent = NULL;
			children = {};
			state = s;
			turn = piece;
			depth = 0;
			ai_score = s1;
			player_score = s2;
		}

		Node(Node *n) {
			parent = n->parent;
			children = n->children;
			state = copy_state(n->state, 8);
			depth = n->depth;
			ai_score = n->ai_score;
			player_score = n->player_score;
		}

		Node(Node *p, char **s, char piece) { 
			parent = p;
			state = s; 
			children = {};
			turn = piece;
			int depth = p->depth + 1;
			ai_score = p->ai_score; 
			player_score = p->player_score; 
		}

		void freeState() {
			for(int i = 0; i < 8; i++) {
				delete[] state[i];
			}
				delete[] state;
			state = NULL;
		}

		char **copy_state(char** s, int size) {
			char **new_board = new char*[size];
			for(int i = 0; i < size; i++) {
				char *row = new char[size];
				for(int j = 0; j < 8; j++) {
					row[j] = s[i][j];
				}
				new_board[i] = row;
			}
			return new_board;
		}
};

#endif
