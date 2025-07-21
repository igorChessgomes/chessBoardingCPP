#pragma once

#include <chess/piece.hpp>


class Knight : public Piece
{
public:
	Knight(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
