#include <terminal/renderer.hpp>

#include <sstream>

#include <chess/board.hpp>


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

	const std::string squareColor = getSquareColorForPosition(position);
	const std::string pieceColor = getPieceColorForPosition(position);

	std::stringstream stream;

	stream << squareColor << pieceColor;

	stream << (!square.piece() ? " " : "*") << " ";

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


std::string BoardRenderer::getPieceColorForPosition(const Position& position) const noexcept
{
	if (Square::isWhiteSquare(position))
		return _colorPalette.whitePiece;
	else
		return _colorPalette.blackPiece;
}
