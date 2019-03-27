#include <iostream>
#include <sstream>
#include "message_parser.h"

/**Problem description
 * https://code.google.com/codejam/contest/dashboard?c=351101#s=p2
 */

// Run/executable              cat
// Run/Command Line Arguments ../T9/C-small-practice.in | ./t9 >
// ../T9/C-small-practice.out

int main(int argc, char const *argv[]) {
  std::string count;
  std::getline(std::cin, count);
  int messagesCount = std::stoi(count);

  for (int i = 1; i <= messagesCount; i++) {
    std::string message;
    std::getline(std::cin, message);
    std::cout << "Case #" << i << ": " << parseMessage(message) << std::endl;
  }

  return 0;
}
