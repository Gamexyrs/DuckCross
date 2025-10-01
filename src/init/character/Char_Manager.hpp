typedef class Char_Manager {
public:
  class Duck;
  class Weapon;
  class Enemy;
  class Explode;
  class Value;
  class Skill;
  class Element;
  
  inline static struct {
    struct {
      size_t __chick;
      size_t __bombChick;
      size_t __shellPig;
    }enemyNum;
    
    struct {
      size_t
        __ordi,
        __spec,
        __boss;
      
    }killedNum;
    func resetKilledNum(void) -> void {killedNum = {0, 0, 0};};
    
  }data{{0, 0, 0}, {0, 0, 0}};
  
  inline static std::vector<
    std::pair<sf::Vector2f, sf::Drawable*>> __drawList{};
    
  // 计算升级至下一个等级时需要的经验数(向下取整)
  static func mathsLevelExp(unsigned nextLevel) -> unsigned;
  
  static func drawList(void) -> void;
  
} Char_M;

#include "./Weapon/.hpp"
#include "./Weapon/element.hpp"
#include "./Duck.hpp"
#include "./Explode.hpp"
#include "./Enemy/.hpp"
#include "./Value.hpp"
#include "./Skill.hpp"
