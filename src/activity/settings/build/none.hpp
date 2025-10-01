#define __ANY__ [](sf::PushButton& v) -> void

const static std::unordered_map<int, void(*)(sf::PushButton&)> __SETTINGS_TYPE_BUILD_NONE__ {
  {500, // 账号
    __ANY__{
      v.setSize({v.getSize().x, v.getSize().y});
      v.setTextString("ID: " + sys::__device_id);
      v.setTextColor(sf::ColorEx::Orange);
      v.setTextAlign(sf::Align::C);
      v.setTextDeviat({0, -5.0f});
      v.setFont(res::__font_en);
    },
  },
  
  // {702, // 修改数据
    // __ANY__{
      // v.setSize({v.getSize().x, v.getSize().y * 2});
      // v.setTextAlign(sf::Align::C);
    // },
  // },
};

#undef __ANY__
