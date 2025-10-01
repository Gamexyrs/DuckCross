#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define __DARK_COLOR_TEXT__ sf::Color{209, 209, 209}
#define __DARK_COLOR_CLR__  sf::Color{17, 17, 17}
#define __DARK_COLOR_COL__  sf::Color{25, 25, 25}
#define __DARK_COLOR_MSG__  sf::Color{44, 44, 44}

#define _app_(fn) _app_##fn

#include "./src/main.cpp"

func main(int argc, char** argv) -> int {
  [[maybe_unused]] static int    _argc_{argc};
  [[maybe_unused]] static char** _argv_{argv};
  
  return _app_(main)();
}

#undef _app_