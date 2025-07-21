#include <chess/pieces/rook.hpp>


Rook::Rook(Square* const square, const Side side)
	: Piece(square, side)
{}


bool Rook::validateMove(const Square& destination) const noexcept
{
	return true;
}


char Rook::getPieceChar() const noexcept { return getCasingFromSide('r'); }
