#pragma once

#include <chess/piece.hpp>


class Bishop : public Piece
{
public:
	Bishop(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
