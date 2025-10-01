class Char_M::Explode {
protected:
  sf::Clock   __clock{};
  sf::TextDiv __shape{};
  bool __skillMode{false};

  inline static std::unique_ptr<Explode> __active_poison{};
  inline static std::vector<Explode> __active{};
  
_func_public:
  static func make(const sf::Vector2f& ctPos = {}, float radius = 100, bool skillMode = false, Char_M::Enemy* __protected = nullptr) -> void;
  static func make_boss(const sf::Vector2f& ctPos = {}) -> void;
  static func make_poison(void) -> void;
  
  static func reset(void) -> void;
  static func act(void) -> void;

};
