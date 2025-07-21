#pragma once

#include <vector>

#include <chess/square.hpp>


using SquareMatrix = std::vector<std::vector<Square>>;


class Board
{
private:
	SquareMatrix _squares;


public:
	Board() noexcept;


	const SquareMatrix& getSquares() const noexcept;

	void setSquares(const SquareMatrix& squares) noexcept;


private:
	static SquareMatrix generateDefaultSquareMatrix() noexcept;
};
