#pragma once

#include <string>


struct ColorPalette
{
	static std::string reset;


	std::string whiteSquare;
	std::string blackSquare;
	std::string whitePiece;
	std::string blackPiece;


	static ColorPalette defaultTheme() noexcept;
};
