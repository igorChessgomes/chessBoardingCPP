#include <chess/piece.hpp>

#include <cctype>

#include <chess/square.hpp>


Piece::Piece(Square* const square, const Side side) noexcept
	: m_side(side)
{
	square->setPiece(this);
}


Square* Piece::square() const noexcept { return m_square; }
Side Piece::side() const noexcept { return m_side; }


void Piece::setSquare(Square* const square) noexcept { m_square = square; }


char Piece::getCasingFromSide(const char ch) const noexcept
{
	return m_side == Side::White ? toupper(ch) : tolower(ch);
}
