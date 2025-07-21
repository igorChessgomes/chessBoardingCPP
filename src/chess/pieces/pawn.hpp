#pragma once

#include <chess/piece.hpp>


class Pawn : public Piece
{
public:
	Pawn(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
