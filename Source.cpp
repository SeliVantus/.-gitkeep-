#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "header.h"

namespace NR {
	Game::Game() {
		field[0][1] = 0;
		field[0][3] = 0;
		field[2][1] = 0;
		field[2][3] = 0;
		field[4][1] = 0;
		field[4][3] = 0;
		for (int i = 0; i < SZ; i++) {
			for (int j = 0; j < SZ; j++) {
				if (field[i][j] != 0)
					field[i][j] = 1;
			}
		}
		GetRandomNumber();
	}

	int Game::GetRandomNumber() {
			int flag1 = 0;
			int min = 2;
			int max = 4;
			srand(time(NULL));
			int count2 = 0;
			int count3 = 0;
			int count4 = 0;
			do {			
				for (int i = 0; i < SZ; i++) {
					for (int j = 0; j < 5; j += 2) {
						if (field[i][j] == 1) {
							flag1 = min + rand() % (max - min + 1);
							if (count2 < 5) {
								if (flag1 == 2) {
									field[i][j] = 2;
									count2++;
								}
							}
							if (count3 < 5) {
								if (flag1 == 3) {
									field[i][j] = 3;
									count3++;
								}
							}
							if (count4 < 5) {
								if (flag1 == 4) {
									field[i][j] = 4;
									count4++;
								}
							}
						}
					}
				}
				
			} while ((count2 < 5) || (count3 < 5) || (count4 < 5) );
			return 0;		
	}
	int Game::Step(int i, int j) {
		if ((i < 0) || (i >= SZ) || (j < 0) || (j >= SZ)) {
			throw std::exception("Bad item");
		}
		else {
			if ((field[i][j] == 0) || (field[i][j] == 1)) {
				std::cout << "It cannot be selected" << std::endl;
				return 1;
			}
		}
		return 0;
	}

	void Settings::dialog() {
		os << "1: Show -->" << std::endl << "2: Make a move" << std::endl;
	}
	int Settings::analysis() {
		int flag = -1;
		do {
			std::cout << "Select function" << std::endl;
			if (getNum(flag) < 0) {
				os << "Input incorrect!" << std::endl;
				flag = -1;
				continue;
			}
			if (flag > 2) {
				os << "No such feature!" << std::endl;
				flag = -1;
			}

		} while (flag < 0);
		if (flag == 1) {
			return show();
		}
		if (flag == 2) {
			return step();
		}
		return flag;

		winS();
	}
	int Settings::winS() {
		return game.win();
	}
	int Game::win() {
		for (int i = 0; i < SZ; i++) {
			for (int j = 0; j < SZ; j += 2) {
				if ((field[i][j] == field[i + 1][j + 1]) && (field[i + 1][j + 1] == field[i + 2][j + 2]) && (field[i + 2][j + 2] == field[i + 3][j + 3]) && (field[i + 3][j + 3] == field[i + 4][j + 4])) {
					std::cout << "You WIN !!!!" << std::endl;
				
				}
			}
		}
		return 0;
	}
	bool Settings::show() {
		game.Getfield();
		return 1;
	}
	int Game::check_possibility(int tmpi, int tmpj, int i, int j) {
		if ((tmpi < 0) || (tmpi >= SZ) || (tmpj < 0)|| (tmpj >= SZ)) {
			throw std::exception("Bad item");
		}
		else {
			if ((field[tmpi][tmpj] == 0) || (field[tmpi][tmpj] == 1)) {
				std::cout << "It cannot be selected" << std::endl;
				return 1;
			}
			if ((field[tmpi][tmpj] == 2) || (field[tmpi][tmpj] == 3) || (field[tmpi][tmpj] == 4)) {
				std::cout << "It cannot be selected" << std::endl;
				return 1;
			}
			int a = 0;
			a = abs(tmpi - i) + abs(tmpj - j);
			if (a > 1) {
				throw std::exception("too far away");
			}

		}
		return 0;
	}
	int Settings::step() {
		os << "Choose a item. Enter the row number(i) and column number(j):" << std::endl;
		int i, j;
		if ((getNum(i) > 0) && (getNum(j) > 0)) {
			try {
				game.Step(i,j);
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
				return 1;
			}
		}
		os << "Select the coordinate where to take a step (i and j):" << std::endl;
		int tmpi, tmpj;
		if ((getNum(tmpi) > 0) && (getNum(tmpj) > 0)) {
			try {
				game.check_possibility(tmpi, tmpj, i, j);
				return 1;
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
				return 1;
			}
		}
		
		game.change(i, j, tmpi, tmpj);
		return 1;
	}
	int Game::change(int i, int j, int tmpi, int tmpj) {
		field[tmpi][tmpj] = field[i][j];
		field[i][j] = 1;
		return 0;
	}
}