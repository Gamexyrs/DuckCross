#define __WCODE_SCISSORS__     0x38CCD1B9L
#define __WCODE_PISTOL__       0x5B15B69AL

class Char_M::Weapon {
  friend class Char_M::Enemy;
  friend class UiView_Manager;
  friend class Resource_Manager;
  friend class ChickBoss_Manager;

protected:
  std::vector<sf::Image>   __i{2};
  std::vector<sf::Texture> __t{2};
             size_t __img_code{0};
  
  sf::Clock __attkClock{};

  sf::VertexArray __attkLine{sf::Lines, 2};
  
  func initData(const std::string&) -> void;
  
  func attCast(void) -> int;
  func critCheck(void) -> bool;
  func maths_attkLine(float) -> void;
  
_data_public:
  class Scissors;
  class Pistol;

  inline static std::unique_ptr<Weapon> __v{};
  sf::Sprite __s{};
  
  inline static long __weapon_code{-1};
  inline static bool __is_remote{false};
  
  inline static float __cd{1.0f};            // 攻击间隙
  inline static sf::Vector2i __attack{1, 1}; // 基础攻击范围
  inline static bool __signal_call_att{false};
  inline static bool __signal_crit{false};
  
  // Long-range Data
  inline static std::vector<std::pair
    <sf::VertexArray, sf::Vector2f>> __bullet{};
  inline static std::pair
    <sf::VertexArray, sf::Vector2f>* __attk_bullet{nullptr};
  
_func_public:
  virtual func act(void) -> void;
  virtual func attValid(Char_M::Enemy*, bool = false) -> void {}
  virtual func attCheck(void) -> void {}
  virtual func setTexture(void) -> void {}
  
           Weapon(void) = default;
  virtual ~Weapon(void) = default;
};

class Char_M::Weapon::Pistol : public Char_M::Weapon {
_func_public:
  virtual func act(void) -> void;
  virtual func attValid(Char_M::Enemy*, bool __isBoss = false) -> void;
  virtual func attCheck(void) -> void;
  virtual func setTexture(void) -> void;
  
           Pistol(void);
  virtual ~Pistol(void) = default;
};

[[nodiscard]] static inline constexpr func mathsKLCoord
  (const sf::Vector2f& pos_0, const sf::Vector2f& pos_1, float _x) -> float {
  return (pos_0.y * (_x - pos_1.x) - pos_1.y * (_x - pos_0.x)) / (pos_0.x - pos_1.x);
}

class Char_M::Weapon::Scissors : public Char_M::Weapon {
_func_public:
  virtual func act(void) -> void;
  virtual func attValid(Char_M::Enemy*, bool __isBoss = false) -> void;
  virtual func attCheck(void) -> void;
  virtual func setTexture(void) -> void;
  
           Scissors(void);
  virtual ~Scissors(void) = default;
};
