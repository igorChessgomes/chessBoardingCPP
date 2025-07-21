#include <chess/square.hpp>

#include <chess/piece.hpp>


Square::Square(const Position& position, Piece* const piece) noexcept
	: _position(position), _piece(piece)
{}


const Position& Square::position() const noexcept { return _position; }
Piece* Square::piece() const noexcept { return _piece; }

void Square::setPosition(const Position& position) noexcept { _position = position; }
void Square::setPiece(Piece* const piece) noexcept
{
	_piece = piece;

	if (_piece)
		_piece->setSquare(this);
}


bool Square::isWhiteSquare(const Position& position) noexcept
{
	return (position.row + position.col) % 2 == 0;
}


bool Square::isBlackSquare(const Position& position) noexcept
{
	return !isWhiteSquare(position);
}
