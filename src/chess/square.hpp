#pragma once

#include <chess/position.hpp>


class Piece;


class Square
{
private:
	Position _position;
	Piece* _piece;


public:
	Square(const Position& position, Piece* piece) noexcept;


	const Position& position() const noexcept;
	Piece* piece() const noexcept;

	void setPosition(const Position& position) noexcept;
	void setPiece(Piece* piece) noexcept;


	static bool isWhiteSquare(const Position& position) noexcept;
	static bool isBlackSquare(const Position& position) noexcept;
};
