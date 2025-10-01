class Char_M::Duck {
  friend func mathsPoints(void) -> unsigned long;
  friend func mathsDetail(void) -> sf::String;
  friend class Map_Manager;
  friend class UiView_Manager;
  friend class PlayView_Manager;
  friend class Resource_Manager;
  friend class ChickBoss_Manager;
  friend class Archive_Manager;
  friend class Char_M::Skill;
  friend class Char_M::Enemy;
  friend class Char_M::Weapon;
  friend class Char_M::Explode;
  
protected:
  std::vector<sf::Image>   __i{6};
  std::vector<sf::Texture> __t{6};
  
  sf::Clock    __last {}; // last time to get attacked;
  sf::Vector2f __repel{};
  
  Char_M::Element::Type __element{Char_M::Element::None};
  
  // 贴图
  sf::Sprite    __s{};
  sf::FloatRect __realRect{};
         size_t __img_code{3};
  sf::Clock __img_clock{};
  
  // - Debugable DATA
  sf::Div __trackBox{};
  
_data_public:
  inline static std::unique_ptr<Duck> __v{};
  
_func_public:
          func noBlood(void) -> bool;
  virtual func act(void) -> void;
  
           Duck(void);
  virtual ~Duck(void) = default;
};
