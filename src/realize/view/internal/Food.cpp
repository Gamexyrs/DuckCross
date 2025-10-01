#define __FOOD_PROGRESS__                  \
  (!Char_M::Value::__food) ? -1 : \
   (Char_M::Value::__food / 100)

inline func PlayView_M::Food_init(void) -> void {
  this->fd.__t.loadFromFile("./src/res/img/sgv/food.png");
  this->fd.__t.setSmooth(sys::__smoothTex);
  
  this->fd.__pic.setSize({60, 60});
  this->fd.__pic.setOutlineThickness(0);
  this->fd.__pic.getBase().setTexture(&this->fd.__t);
  this->fd.__pic.setBuilder(this->bl.__prog, sf::Vector2f{0, 5}, sf::Vector2b{false, true});
  
  this->fd.__prog.setSize(sf::Vector2f{this->bl.__prog.getSize().x - this->fd.__pic.getSize().x - 5, this->bl.__prog.getSize().y * 0.2f});
  this->fd.__prog.setFillColor(sf::ColorEx::Orange | 70);
  this->fd.__prog.getInside().setFillColor(sf::ColorEx::Orange);
  this->fd.__prog.setBuilder(this->bl.__prog, sf::Vector2f{this->fd.__pic.getSize().x + 5, this->fd.__pic.getSize().y / 2 - 5}, sf::Vector2b{false, true});
  this->fd.__prog.setOutlineThickness(2);
  
  if(sys_acti::__actype == sys_acti::ActivityType::Play)
       this->fd.__prog.setProgress(__FOOD_PROGRESS__);
  else this->fd.__prog.setProgress(1);
}

inline func PlayView_M::Food_act(void) -> void {
  if(Char_M::Duck::__v->noBlood()) {
    this->fd.__prog.setProgress(-1);
  } else if(sys::__cheat___allow_duck_unlimited_blood__) {
    this->fd.__prog.setProgress(1);
  } else {
    this->fd.__prog.setProgress(__FOOD_PROGRESS__);
  }
}

#undef __FOOD_PROGRESS__
