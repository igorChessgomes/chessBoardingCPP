#include <terminal/color_palette.hpp>


std::string ColorPalette::reset = "\x1b[0m";


ColorPalette ColorPalette::defaultTheme() noexcept
{
	return ColorPalette {
		.whiteSquare = "\x1b[48;5;253m",
		.blackSquare = "\x1b[48;5;35m",
		.whitePiece = "\x1b[38;5;25m",
		.blackPiece = "\x1b[38;5;245m"
	};
}
