#pragma once

#include <chess/piece.hpp>


class Queen : public Piece
{
public:
	Queen(Square* square, Side side);


	bool validateMove(const Square& destination) const noexcept override;


	char getPieceChar() const noexcept override;
};
