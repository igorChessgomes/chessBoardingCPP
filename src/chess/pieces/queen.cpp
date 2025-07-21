#include <chess/pieces/queen.hpp>


Queen::Queen(Square* const square, const Side side)
	: Piece(square, side)
{}


bool Queen::validateMove(const Square& destination) const noexcept
{
	return true;
}


char Queen::getPieceChar() const noexcept { return getCasingFromSide('Q'); }
