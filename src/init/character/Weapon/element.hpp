class Char_M::Element {
public:
  enum Type { None = 0, Fire, Ice, Water, /*Wind,*/ Poison };
  
  enum InteractType {
    Melt,        // Fire -> Ice    2x
    Evaporation, // Fire -> Water  1.5x
    Freeze,      // Ice  -> Water  1.5x
    
  };
  
_data_public:
  
  
_func_public:
  inline static func attCast(const Type&, const Type&) -> float;
  
};
