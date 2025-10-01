typedef class UiView_Manager {
_data_public:
  sf::MsgDiv          __msg{40, {0.4, 0.4}};
  sf::InputMessageDiv __ipt{40, {0.4, 0.4}};
  
  sf::PushBtn __back{}; // quickBuilt
  
  // Camera
  std::queue<sf::Vector2f> __cameraMovePath{};
  bool __cameraOnceUnlock{false};
  
  // View
  sf::Clock __flashClock;
  sf::Div  __viewpos;
  sf::View __view;
  
  // Bubble
  std::queue<std::pair<sf::String, sf::Color>>
              __bubble_msg_queue{};
  sf::Clock   __bubble_msg_clock{};
  sf::Div     __bubble_msg_blinker{};
  sf::TextDiv __bubble_msg{};
  bool __bubble_locked{false};
  
_func_public:
  func update(void) -> void;
  func reset(void) -> void;
  func draw(void) -> void;
  
  func flashScreen(const sf::Color& __flashColor = sf::Color::White, float __flashTime = 0.1f) -> void;
  
  func bubble(const sf::String& = "", const sf::Color& = sf::ColorEx::LightBlue, bool __repeatable = false) -> void;
  func bubble_is_lock(void) -> bool;
  func bubble_lock(void) -> void;
  func bubble_unlock(void) -> void;
  
  func fix_darkMode (void) -> void;
  
  UiView_Manager(void);
 ~UiView_Manager(void) = default;
} UiView_M;

static std::unique_ptr<UiView_M> ui_m;
