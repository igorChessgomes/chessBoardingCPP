#pragma once

#include <vector>

#include <chess/square.hpp>


using SquareMatrix = std::vector<std::vector<Square>>;


enum class Side;


class Board
{
private:
	SquareMatrix _squares;


public:
	Board() noexcept;


	const SquareMatrix& squares() const noexcept;

	void setSquares(const SquareMatrix& squares) noexcept;


private:
	static SquareMatrix generateDefaultSquareMatrix(bool setupPieces = true) noexcept;

	static void setDefaultPieceSetup(SquareMatrix& squares) noexcept;
	static void setDefaultFirstRowPieceSetup(std::vector<Square>& row, Side side) noexcept;
	static void setDefaultSecondRowPawnSequence(std::vector<Square>& row, Side side) noexcept;
};
