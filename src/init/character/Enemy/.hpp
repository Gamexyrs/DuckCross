#define __ECODE_CHICK__     0x49E90297L
#define __ECODE_CHICKEGG__  0x49E90298L
#define __ECODE_BOMBCHICK__ 0x3AA22C9BL
#define __ECODE_SHELLPIG__  0xD2F9AA5L

typedef enum class BombState : short {
  None = 0,
  Kindling,
  Exploded,
  Defuse,
  
  Unknown = -1,
}BombState;

class Char_M::Enemy {
  friend class UiView_Manager;
  friend class Archive_Manager;
  friend class Resource_Manager;
  friend class ChickBoss_Manager;
  friend class CreatePool;
  friend class Explode;
  friend class Weapon;
  friend class Skill;

protected:
          func moveToDuck(void) -> void;
  virtual func setTexture(void) -> void;
  virtual func adaptRect (void) -> void;
  virtual func checkDrop (void) -> void;
          func pushList  (void) -> void;
          func initData  (const std::string&) -> void;
          func initPos   (void) -> void;
  virtual func del(void) -> void;
  
  // 运动
  sf::Vector2f __move{}, // 移动
             __exmove{}; // 逃逸
  Enemy* __hinderWith{nullptr}; // 碰撞对象
  float  __speed_f{1};          // 速度因子
  
  // 贴图
  size_t __img_code{3}; // 贴图代号
  sf::Clock __img_c{};  // 贴图时钟
  sf::Sprite    __s{};  // 贴图实体
  sf::FloatRect __realRect{}; // 碰撞箱
  
  // 属性
  bool __attking{false}; // 正在攻击
  int  __attack{0};      // 攻击力
  int  __cast_blood{0},  // 当前生命值
       __cnst_blood{0};  // 初始生命值
  int  __cast_exp{0},    // 可获取经验值
       __cnst_exp{0};    // 最大经验值
  sf::Clock __attkc{},   // 攻击间隔
            __ghost{},   // 穿透时间
            __out_of_screen_clock{};
  // sf::Time __to_fission{};
  
  Char_M::Element::Type __element{Char_M::Element::None};
  
  // - Base DATA
  long __enemy_code{__ECODE_CHICK__};
  
  inline static bool __signal_call_del{false};
  
  // sf::Timer __fission_clock{}; // 分裂
  // bool __fissionable{false}; // 可分裂
  bool __nodrop{false}; // 无掉落物
  
  bool __movable{true}; // 可移动
  
  bool __inview{true},
       __inzone{true};
  
  // - Bombable DATA
  unsigned  __kindlingTick{0};
  BombState __bombState{BombState::None};

  // - Dedugable DATA
  sf::Div         __trackBox{};
  sf::VertexArray __trackLine{sf::Lines, 2};
  
_data_public:
  class Chick;
  class BombChick;
  class ShellPig;
  class ChickEgg;
  
  class Alloter;
  class Allocator;
  class CreatePool;
  
_func_public:
  virtual func hurt(int _bl, sf::Vector2f _toward = {}, bool by_explode = false, bool count_acc = true) -> void;
  virtual func act(void) -> void {}
  
           Enemy(void) = default;
  virtual ~Enemy(void) = default;
};

#include "./internal/CreatePool.hpp"
#include "./internal/Allocator.hpp"
#include "./internal/Alloter.hpp"

#include "./boss/ChickBoss_Manager.hpp"

class Char_M::Enemy::BombChick : public Char_M::Enemy {
protected:
  virtual func setTexture(void) -> void;
  virtual func adaptRect (void) -> void;
  virtual func checkDrop (void) -> void;
  virtual func del(void) -> void;

_data_public:

_func_public:
  virtual func act(void) -> void;
  
           BombChick(void);
  virtual ~BombChick(void) = default;
};

class Char_M::Enemy::ShellPig : public Char_M::Enemy {
protected:
  virtual func adaptRect (void) -> void;
  virtual func checkDrop (void) -> void;
  virtual func del(void) -> void;

_data_public:

_func_public:
  virtual func act(void) -> void;
  
           ShellPig(void);
  virtual ~ShellPig(void) = default;
};

class Char_M::Enemy::Chick : public Char_M::Enemy {
protected:
  virtual func adaptRect(void) -> void;
  virtual func checkDrop(void) -> void;
  virtual func del(void) -> void;

_data_public:

_func_public:
  virtual func act(void) -> void;
  
           Chick(void);
  virtual ~Chick(void) = default;
};

class Char_M::Enemy::ChickEgg : public Char_M::Enemy {
protected:
  virtual func adaptRect(void) -> void;
  virtual func del(void) -> void;

  sf::Timer __hatch_clock{sf::Time::Zero, true};

_data_public:

_func_public:
  virtual func act(void) -> void;
  
           ChickEgg(void);
  virtual ~ChickEgg(void) = default;
};
