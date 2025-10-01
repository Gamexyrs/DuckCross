typedef class AttackDisplay_Manager {
_data_public:
  inline static std::vector<std::unique_ptr<sf::TextDiv>> __text{};
  
_func_public:
  static func call(sf::String, std::optional<sf::Vector2f> = std::nullopt, sf::Color = {}) -> void;
  static func draw(void) -> void;

} AttackDisplay_M;
