#pragma once

namespace Chess
{
	class Piece {
	public:

		Tile* GetPosition() { return &m_Position; }
		static void Create(Piece& piece);
	protected:
	Tile m_Position;
	};
}