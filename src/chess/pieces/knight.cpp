#include <chess/pieces/knight.hpp>


Knight::Knight(Square* const square, const Side side)
	: Piece(square, side)
{}


bool Knight::validateMove(const Square& destination) const noexcept
{
	return true;
}


char Knight::getPieceChar() const noexcept { return getCasingFromSide('n'); }
