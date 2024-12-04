#pragma once
#include <string>
#include <fstream>
namespace Constants {
	const std::string WallBreakablePNGPath = "../Bomberman.API/Assets/wall_breakable.png";
	const std::string WallUnbreakablePNGPath = "../Bomberman.API/Assets/wall_unbreakable.png";
	const std::string GrassPNGPath = "../Bomberman.API/Assets/grass.png";
	const std::string Player1PNGPath = "../Bomberman.API/Assets/player1.png";
	const std::string Player2PNGPath = "../Bomberman.API/Assets/player2.png";
	const std::string FirePNGPath = "../Bomberman.API/Assets/fire.png";
	const std::string BoardTxtPath = "../Bomberman.API/Assets/board.txt";
	const std::string BombPNGPath = "../Bomberman.API/Assets/bomb.png";
	const std::string GameOverPath= "../Bomberman.API/Assets/game_over.jpg";
	const std::string fontArialPath = "../Bomberman.API/Assets/arial.ttf";


	static bool isValidPath(std::string path)
	{
		std::ifstream file(path);
		return file.good();
	}
};

