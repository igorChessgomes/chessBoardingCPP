#include <chess/pieces/bishop.hpp>


Bishop::Bishop(Square* const square, const Side side)
	: Piece(square, side)
{}


bool Bishop::validateMove(const Square& destination) const noexcept
{
	return true;
}


char Bishop::getPieceChar() const noexcept { return getCasingFromSide('b'); }
