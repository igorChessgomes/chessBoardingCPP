#pragma once


enum class Side
{
	White,
	Black
};


class Square;


class Piece
{
protected:
	Square* m_square;
	const Side m_side;


public:
	Piece(Square* square, Side side) noexcept;

	virtual ~Piece() = default;


	Square* square() const noexcept;
	Side side() const noexcept;

	void setSquare(Square* square) noexcept;


	virtual bool validateMove(const Square& destination) const noexcept = 0;


	virtual char getPieceChar() const noexcept = 0;


protected:
	char getCasingFromSide(char ch) const noexcept;
};
