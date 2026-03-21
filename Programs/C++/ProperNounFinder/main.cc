#include <iostream>
#include <fstream>

int main() {
  std::string myText;
  std::ifstream text("../../../TextOrderings/OfficialText/2.txt");

  while (getline (text, myText)) {
    std::cout << myText;
  }
  text.close();

  return 0;
}