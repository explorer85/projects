#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include <iostream>
#include <map>

std::map<char /*letter*/, char /*digit*/> t9map{
    {'a', '2'}, {'b', '2'}, {'c', '2'}, {'d', '3'}, {'e', '3'}, {'f', '3'},
    {'g', '4'}, {'h', '4'}, {'i', '4'}, {'j', '5'}, {'k', '5'}, {'l', '5'},
    {'m', '6'}, {'n', '6'}, {'o', '6'}, {'p', '7'}, {'q', '7'}, {'r', '7'},
    {'s', '7'}, {'t', '8'}, {'u', '8'}, {'v', '8'}, {'w', '9'}, {'x', '9'},
    {'y', '9'}, {'z', '9'}, {' ', '0'},
};

std::string parseMessage(const std::string &message) {
  std::string output;
  for (const auto &letter : message) {
    //по позиции буквы на текущей кнопке определяем колво повторений символа
    char digit = t9map[letter];
    output.push_back(digit);
  }
  std::cout << output;
  return output;
}

#endif  // MESSAGE_PARSER_H
