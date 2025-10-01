typedef class XTerminal {
protected:
  func handle(const std::string&) -> void;
  
  std::vector<std::string> __key_stream{};
  
_func_public:
  func puts(void) -> void;
  
  XTerminal(void);
 ~XTerminal(void) = default;
} XTerminal;
