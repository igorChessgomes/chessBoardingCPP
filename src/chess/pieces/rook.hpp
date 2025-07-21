#pragma once

#include <chess/piece.hpp>


class Rook : public Piece
{
public:
	Rook(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
