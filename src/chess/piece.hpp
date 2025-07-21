#pragma once


class Square;


class Piece
{
protected:
	Square* m_square;


public:
	Piece(Square* square) noexcept;

	virtual ~Piece() = default;


	Square* square() const noexcept;

	void setSquare(Square* square) noexcept;


	virtual bool validateMove(const Square& destination) const noexcept = 0;
};
