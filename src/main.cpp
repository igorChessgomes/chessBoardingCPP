#include <chess/board.hpp>
#include <terminal/renderer.hpp>

#include <iostream>


int main()
{
    Board board;
    BoardRenderer renderer(board, ColorPalette::defaultTheme());

    std::cout << renderer.render() << std::endl;

    return 0;
}
