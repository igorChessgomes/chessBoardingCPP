#include <chess/pieces/king.hpp>


King::King(Square* const square, const Side side)
	: Piece(square, side)
{}


bool King::validateMove(const Square& destination) const noexcept
{
	return true;
}


char King::getPieceChar() const noexcept { return getCasingFromSide('K'); }
