#include <chess/pieces/pawn.hpp>


Pawn::Pawn(Square* const square, const Side side)
	: Piece(square, side)
{}


bool Pawn::validateMove(const Square& destination) const noexcept
{
	return true;
}


char Pawn::getPieceChar() const noexcept { return getCasingFromSide('p'); }
