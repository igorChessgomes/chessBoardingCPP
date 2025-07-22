#include <chess/board.hpp>

#include <chess/pieces/rook.hpp>
#include <chess/pieces/knight.hpp>
#include <chess/pieces/bishop.hpp>
#include <chess/pieces/queen.hpp>
#include <chess/pieces/king.hpp>
#include <chess/pieces/pawn.hpp>


Board::Board() noexcept
{
	_squares = generateDefaultSquareMatrix();
}


const SquareMatrix& Board::squares() const noexcept { return _squares; }


void Board::setSquares(const SquareMatrix& squares) noexcept { _squares = squares; }


SquareMatrix Board::generateDefaultSquareMatrix(const bool setupPieces) noexcept
{
	SquareMatrix matrix(8);

	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int o = 0; o < 8; o++)
			matrix[i].push_back(Square({i, o}, nullptr));

	if (setupPieces)
		setDefaultPieceSetup(matrix);

	return matrix;
}


void Board::setDefaultPieceSetup(SquareMatrix& squares) noexcept
{
	setDefaultFirstRowPieceSetup(squares[0], Side::White);
	setDefaultSecondRowPawnSequence(squares[1], Side::White);


	setDefaultSecondRowPawnSequence(squares[6], Side::Black);
	setDefaultFirstRowPieceSetup(squares[7], Side::Black);
}


void Board::setDefaultFirstRowPieceSetup(std::vector<Square>& row, const Side side) noexcept
{
	new Rook(&row[0], side);
	new Knight(&row[1], side);
	new Bishop(&row[2], side);
	new King(&row[3], side);

	new Queen(&row[4], side);
	new Bishop(&row[5], side);
	new Knight(&row[6], side);
	new Rook(&row[7], side);
}


void Board::setDefaultSecondRowPawnSequence(std::vector<Square>& row, Side side) noexcept
{
	for (size_t i = 0; i < 8; i++)
		new Pawn(&row[i], side);
}
