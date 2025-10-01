#include <iostream>
#include <sstream>

auto main(void) -> int {
  std::string s{};
  std::cin >> s;

  std::stringstream ss{""}; int d_code{}; std::string a_code{};
  
  ss << std::hex << s;
  ss >> d_code; ss.clear();
  
  ss << std::hex << static_cast<int>(static_cast<float>(d_code) * 123.0f / 456.0f * 789.0f / 100.0f);
  ss >> a_code;
  
  std::transform(a_code.begin(), a_code.end(), a_code.begin(), ::toupper);
  
  a_code = "[analysed by " + s + "]: " + a_code;
  
  std::cout << std::endl << a_code;
  
  return EXIT_SUCCESS;
}
