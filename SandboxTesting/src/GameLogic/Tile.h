#pragma once
#include "Pieces.h"

namespace Chess
{
	class Tile {
	public:
		Tile();
		~Tile() {}

		int GetX() { return x; }
		int GetY() { return y; }

	private:
		Piece* piece;
		int x;
		int y;
	};
}