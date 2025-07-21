#pragma once

#include <string>

#include <terminal/color_palette.hpp>


class Board;
class Square;

struct Position;


class BoardRenderer
{
private:
	const Board& _board;
	ColorPalette _colorPalette;


public:
	explicit BoardRenderer(const Board& board, const ColorPalette& colorPalette);


	std::string render() const noexcept;


private:
	std::string renderSquare(const Square& square) const noexcept;

	std::string getSquareColorForPosition(const Position& position) const noexcept;
	std::string getPieceColorForPosition(const Position& position) const noexcept;
};
