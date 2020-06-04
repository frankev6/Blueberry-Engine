#pragma once
#include "Tile.h"


namespace Chess
{
	class Board {
	public:

		void InitializeBoard();
		Tile* GetTileAt(int x, int y) { return &m_Tiles[x][y]; }

	private:
		Tile m_Tiles[8][8];
	};
}