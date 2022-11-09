#ifndef _HEADER_H_
#define _HEADER_H_
#include <iostream>

namespace NR {
	class Game {
	private:
		static const int SZ = 5;
		int field[SZ][SZ];
		//orange - 2
		//red - 3
		//yellow - 4
		//empty - 1

	public:
		Game();
		int GetRandomNumber();
		int Getfield() { 
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					std::cout << field[i][j] << "  ";
				}
				std::cout << std::endl;
			}
			return 0;
		}
		int Step(int, int);
		int check_possibility(int, int, int, int);
		int change(int, int, int, int);
		int win();
	};


	class Settings {
	private:
		std::istream& is = std::cin;
		std::ostream& os = std::cout;
		Game game;
		bool show();
		int step();


	public:
		void dialog();
		int analysis();
		int winS();
		template <class T>
		int getNum(T& a) {
			std::cin >> a;
			if (!std::cin.good() || (std::cin.peek() != '\n')) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return -1;
			}
			return 1;
		}
	};
}

#endif