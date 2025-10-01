/* system_ item serve */
namespace sis {
  enum class Item : int {
        Chick_token,
    BombChick_token,
    ShellPig_token,
    
    Drumstick,
    ChickWing,
    Shell,
    PigFeet,
    
    Coin,
    
    Unknown = -1,
  };

#ifdef __SFUI_OBJECT__
  static std::unordered_map<sis::Item, std::pair<sf::String, sf::String>> ItemName {
    {sis::Item::    Chick_token,         {L"咬鸭鸡的信物", "chick_token"}},
    {sis::Item::BombChick_token,         {L"炸弹鸡的信物", "bombChick_token"}},
    {sis::Item::ShellPig_token,          {L"甲壳猪的信物", "shellPig_token"}},
    
    {sis::Item::Drumstick,               {L"鸡腿",   "drumstick"}},
    {sis::Item::ChickWing,               {L"鸡翅膀", "chickWing"}},
    {sis::Item::Shell,                   {L"甲壳", "shell"}},
    {sis::Item::PigFeet,                 {L"猪蹄", "pigFeet"}},
    
    {sis::Item::Coin,                    {L"金币", "coin"}},
    
    {sis::Item::Unknown,                 {L"未知物品", "unknown"}},
  };
#endif
  static std::unordered_map<std::string, sis::Item> ItemName_Callback {
    {    "Chick_token",            sis::Item::    Chick_token},
    {"bombChick_token",            sis::Item::BombChick_token},
    {"shellPig_token",            sis::Item::ShellPig_token},
    
    {"drumstick",                 sis::Item::Drumstick},
    {"chickWing",                 sis::Item::ChickWing},
    {"shell",                     sis::Item::Shell},
    {"pigFeet",                   sis::Item::PigFeet},
    
    {"coin",                      sis::Item::Coin},
    
    {"unknown",                   sis::Item::Unknown},
  };
  
  using item_t = std::unordered_map<sis::Item, size_t>::iterator;
}
