inline func Char_M::mathsLevelExp(unsigned nextLevel) -> unsigned {
  if(nextLevel <= 10) return static_cast<unsigned>(0.85f * nextLevel * nextLevel + 5);
                 else return static_cast<unsigned>(1.20f * nextLevel + 80);
} // f(x) = [0.85x^2 + 5] (x <= 10),  [1.2x + 80] (x > 10)

inline func Char_M::drawList(void) -> void {
  std::sort(__drawList.begin(),
            __drawList.end(), [](const std::pair<sf::Vector2f, sf::Drawable*>& fir,
                                 const std::pair<sf::Vector2f, sf::Drawable*>& sec) -> bool {
    return fir.first.y < sec.first.y;
  });
  for(auto& i : Char_M::__drawList) {
    sf::Renderable::draw(*i.second);
  } Char_M::__drawList.clear();
}

#include "./Duck.cpp"
#include "./Explode.cpp"
#include "./Weapon/.cpp"
#include "./Weapon/element.cpp"
#include "./Enemy/.cpp"
#include "./Value.cpp"
#include "./Skill.cpp"
