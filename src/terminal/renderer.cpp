#include <terminal/renderer.hpp>

#include <sstream>

#include <chess/board.hpp>
#include <chess/piece.hpp>


BoardRenderer::BoardRenderer(const Board& board, const ColorPalette& colorPalette)
	: _board(board), _colorPalette(colorPalette)
{}


std::string BoardRenderer::render() const noexcept
{
	std::stringstream stream;

	for (const std::vector<Square>& row : _board.getSquares())
	{
		for (const Square& square : row)
			stream << renderSquare(square);

		stream << std::endl;
	}

	return stream.str();
}


std::string BoardRenderer::renderSquare(const Square& square) const noexcept
{
	const Position position = square.position();
	Piece* piece = square.piece();

	const std::string squareColor = getSquareColorForPosition(position);
	const std::string pieceColor = piece ? getPieceColorForSide(piece->side()) : "";

	std::stringstream stream;

	stream << squareColor << pieceColor;

	stream << (!piece ? ' ' : piece->getPieceChar()) << " ";

	stream << ColorPalette::reset;

	return stream.str();
}


std::string BoardRenderer::getSquareColorForPosition(const Position& position) const noexcept
{
	if (Square::isWhiteSquare(position))
		return _colorPalette.whiteSquare;
	else
		return _colorPalette.blackSquare;
}


std::string BoardRenderer::getPieceColorForSide(const Side side) const noexcept
{
	if (side == Side::White)
		return _colorPalette.whitePiece;
	else
		return _colorPalette.blackPiece;
}
