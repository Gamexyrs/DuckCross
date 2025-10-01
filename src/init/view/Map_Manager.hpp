#define __MAX_MAP_RECT__ sf::FloatRect{-35000, -35000, 70000, 70000}

typedef class Map_Manager {
private:
  sf::Div __map_boundary{};
  
  std::vector<sf::Sprite> __s_tree;
  
  std::pair<std::vector<sf::VertexArray>,
            std::vector<sf::VertexArray>> __grid{};
  
  sf::Timer __outMapTimer{};
  
  func dichotomy(bool) -> size_t;
  
_data_public:
  inline static std::vector<sf::FloatRect>        __obstacle{};
  inline static std::vector<sf::FloatRect> __active_obstacle{};
  
_func_public:
  
  // 寻找活跃(在视窗内)的障碍物
  static func findActiveObstacle(void) -> void;
  // 计算指定方向被阻挡时的最佳前进路线
  static func mathsObsPath(const sf::Align& _side, const sf::Vector2f& _forw) -> sf::Vector2f;
  // 计算阻挡方向
  static func mathsObsSide(const sf::FloatRect& _this) -> sf::Align;

  func inMap(void) -> bool;
  func draw(void) -> void;

  Map_Manager(void);
 ~Map_Manager(void) = default;
} Map_M;
