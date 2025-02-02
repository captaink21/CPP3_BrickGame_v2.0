#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>

int main() {
  while (1) {
    std::cout << "==================================" << std::endl;
    std::cout << "I wanna have some game with you! " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "1- Tetris" << std::endl;
    std::cout << "2- Snake" << std::endl;
    std::cout << "3- Exit" << std::endl;

    int choice = 0;

    while (1) {
      std::cout << "Choice: ";
      std::cin >> choice;

      if (std::cin.fail()) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
          std::cin.clear();
        };
        std::cout << "Choose another option" << std::endl;

      } else {
        break;
      }
    }

    switch (choice) {
      case 1:
        std::cout << "You choice is tetris" << std::endl;
        system("./s21_tetris");
        break;
      case 2:
        std::cout << "You choice is snake" << std::endl;
        system("./s21_snake");
        break;
      case 3:
        std::cout << "Good bye" << std::endl;
        return 0;
      default:

        break;
    }
  }

  return 0;
}
