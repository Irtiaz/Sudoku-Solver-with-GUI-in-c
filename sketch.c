#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "sketch.h"
#include "sudoku.h"


float w;
ALLEGRO_FONT *font;

int **board;

//This code in setup will be run only once
void setup() {
	w = (float)width / 9.0;
	font = al_load_ttf_font("arial.ttf", w/2, 0);

	board = (int **)malloc(9 * sizeof(int *));
	for (int i = 0; i < 9; ++i) {
		board[i] = (int *)malloc(9 * sizeof(int));
		for (int j = 0; j < 9; ++j) {
			board[i][j] = 0;
		}
	}
}


//This code in draw will run every frame
void draw() {
	al_clear_to_color(al_map_rgb(255, 255, 255));

	int selectedI = mouseY / w;
	int selectedJ = mouseX / w;
	al_draw_filled_rectangle(selectedJ * w, selectedI * w, selectedJ * w + w, selectedI * w + w, al_map_rgb(200, 200, 200));

	for (int i = 0; i < 9; ++i) {
		float x = i * w;
		float thickness = i % 3 == 0 ? 2 : 1;
		al_draw_line(x, 0, x, height, al_map_rgb(0, 0, 0), thickness);
		al_draw_line(0, x, width, x, al_map_rgb(0, 0, 0), thickness);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] != 0) {
				char *str = (char *)malloc(2 * sizeof(char));
				str[0] = '0' + board[i][j];
				al_draw_text(font, al_map_rgb(0, 0, 0), j * w + w / 2, i * w + w / 4, ALLEGRO_ALIGN_CENTER, str);
			}
		}
	}
}



void mousePressed(bool lmb) {
	//Handle mouse click events here
}
	


void keyPressed(int keyCode) {
	//Handle key press events
	if (keyCode >= 27 && keyCode <= 46) {
		int num = keyCode <= 36 ? keyCode - 27 : keyCode - 37;

		int i = mouseY / w;
		int j = mouseX / w;

		board[i][j] = num;
	}

	else if (keyCode == 75) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				board[i][j] = 0;
			}
		}
	}

	else if (keyCode == 67) {
		solve(board);
	}
}