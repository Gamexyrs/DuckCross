class Char_M::Enemy::CreatePool {
  friend class Resource_Manager;

protected:
  inline static std::vector<std::unique_ptr<Enemy>> __pool{};
  inline static             std::unique_ptr<Enemy>  __buf{};
  
  inline static struct {
    size_t     __chick{};
    size_t __bombChick{};
    size_t __shellPig{};
  }content{0, 0, 0};
  
_func_public:
  static func clear(void) -> void;
  static func valid(long) -> bool;

  static func move_from_active(void) -> void;
  static func move(void) -> std::unique_ptr<Enemy>;
  static func move(std::unique_ptr<Enemy>&) -> void;
};
