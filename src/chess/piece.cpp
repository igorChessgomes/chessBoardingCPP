#include <chess/piece.hpp>


Piece::Piece(Square* const square) noexcept
	: m_square(square)
{}


Square* Piece::square() const noexcept { return m_square; }


void Piece::setSquare(Square* const square) noexcept { m_square = square; }
