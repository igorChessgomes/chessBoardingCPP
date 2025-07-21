#pragma once

#include <chess/piece.hpp>


class King : public Piece
{
public:
	King(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
