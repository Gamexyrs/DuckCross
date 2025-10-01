typedef class Resource_Manager {
_data_public:
  inline static bool __regular_font_load_fault{false};

  inline static sf::Font
    __font,
    __font_en,
    __font_ac;
  
  inline static std::unique_ptr<sf::SoundBuffer>
    __soundbf_levelup{},
    __soundbf_kill{},
    __soundbf_scissors{},
    __soundbf_pistol{};
  
  struct ui {
    inline static std::vector<sf::Image> __i_step{2};
    inline static std::vector<sf::Image> __i_back{2};
    
                inline static std::unique_ptr<sf::Texture>  __settings{};
                inline static std::unique_ptr<sf::Texture>  __pause{};
                inline static std::unique_ptr<sf::Texture>  __switch{};
                inline static std::unique_ptr<sf::Texture>  __accept{};
                inline static std::unique_ptr<sf::Texture>  __refuse{};
    inline static std::vector<std::unique_ptr<sf::Texture>> __step{2};
    inline static std::vector<std::unique_ptr<sf::Texture>> __back{2};
  };
  
  struct enemy {
    inline static std::vector<std::vector<sf::Image>>
      __i_chick{2}; // common & attack
    inline static std::vector<std::vector<std::unique_ptr<sf::Texture>>>
      __t_chick{2}; // common & attack
    
    inline static std::unique_ptr<sf::Texture> __t_chickEgg{};
    
    inline static std::vector<std::vector<sf::Image>>
      __i_bombChick{2}; // common & attack
    inline static std::vector<std::vector<std::unique_ptr<sf::Texture>>>
      __t_bombChick{2}; // common & attack
      
    inline static std::vector<std::vector<sf::Image>>
      __i_shellPig{2}; // common & attack
    inline static std::vector<std::vector<std::unique_ptr<sf::Texture>>>
      __t_shellPig{2}; // common & attack
    
    
  };
  
  inline static std::unique_ptr<sf::Texture> __tex_tree{};
  
  // ctrl
  inline static std::unique_ptr<sf::Texture> __tex_ctrl_attk{}, __tex_ctrl_obsr{};
  
  // item
  inline static std::unordered_map<sis::Item, std::unique_ptr<sf::Texture>> __tex_item{};

  static func update(void) -> void;
  static func load(void) -> void;
  
} res;
