#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include <iostream>
#include <unordered_map>

const std::unordered_map<char /*letter*/,
                         std::pair<char /*digit*/, short /*btnpos*/>>
    t9map{
        {'a', {'2', 1}}, {'b', {'2', 2}}, {'c', {'2', 3}}, {'d', {'3', 1}},
        {'e', {'3', 2}}, {'f', {'3', 3}}, {'g', {'4', 1}}, {'h', {'4', 2}},
        {'i', {'4', 3}}, {'j', {'5', 1}}, {'k', {'5', 2}}, {'l', {'5', 3}},
        {'m', {'6', 1}}, {'n', {'6', 2}}, {'o', {'6', 3}}, {'p', {'7', 1}},
        {'q', {'7', 2}}, {'r', {'7', 3}}, {'s', {'7', 4}}, {'t', {'8', 1}},
        {'u', {'8', 2}}, {'v', {'8', 3}}, {'w', {'9', 1}}, {'x', {'9', 2}},
        {'y', {'9', 3}}, {'z', {'9', 4}}, {' ', {'0', 1}},
    };

/**
 * @brief Converts text to T9
 * @param message the input text message
 * @return input text presented in T9
 */
std::string parseMessage(const std::string &message) {
  std::string output;
  char digit;
  for (const auto &letter : message) {
    // if the digital code of the previous character is equal to the current
    // space added
    if (t9map.count(letter) != 0) {  // checking that character is out of range
      if (digit == t9map.at(letter).first) {
        output.push_back(' ');
      }
      // find the number and repeat its number of times equal to its position on
      // the button
      digit = t9map.at(letter).first;
      for (int i = 0; i < t9map.at(letter).second; i++) output.push_back(digit);
    }
  }
  return output;
}

#endif  // MESSAGE_PARSER_H
