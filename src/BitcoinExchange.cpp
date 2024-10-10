/* Copyright 2024 <mbernard>************************************************  */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:19:44 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/09 21:34:44 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

#include "../includes/Colors.hpp"
#include "../includes/FileSrc.hpp"

const std::string BitcoinExchange::_dataFile = "data.csv";
BitcoinExchange::BitcoinExchange(void) { return; }

BitcoinExchange::BitcoinExchange(const std::string inputFile)
    : _inputFile(inputFile) {
  return;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
    : _inputFile(src._inputFile) {
  *this = src;
  return;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src) {
  if (this != &src) {
    this->_inputFile = src._inputFile;
  }
  return (*this);
}

BitcoinExchange::~BitcoinExchange() { return; }

void BitcoinExchange::dataLineValidation(const std::string &line, char sep) {
  std::istringstream iss(line);
  int year, month, day = 0;
  float value;
  char dash;
  char separator;
  char unwantedChar;

  if (!(iss >> year >> dash) || dash != '-')
    throw InvalidDataLine();
  if (!(iss >> month >> dash >> day) || dash != '-')
    throw InvalidDataLine();

  if (!(iss >> separator) || separator != sep)
    throw InvalidDataLine();

  if (!(iss >> value))
    throw InvalidDataLine();

  if (value < 0)
    throw notAPositiveNumber();
  if (value > 1000)
    throw numberHigherThan1000();

  if (iss >> unwantedChar)
    throw InvalidDataLine();

  if (this->_calendar.dateIsWrong(day, month, year))
    throw InvalidDate();
}

static bool containsLetters(std::string line) {
  unsigned int i = 0;

  while (line[i] != '\0') {
    if (std::isalpha(line[i])) {
      return (true);
    }
    ++i;
  }
  return (false);
}

void BitcoinExchange::fillMap(std::stringstream *dataFile) {
  std::string line;

  while (std::getline(*dataFile, line)) {
    std::istringstream iss(line);
    std::string date;
    float value;
    if (line.empty() || line == "\n" || containsLetters(line))
      continue;
    std::getline(iss, date, ',');
    iss >> value;
    _datas[date] = value;
  }
}

void BitcoinExchange::printBitcoinValue(std::string line,
                                        std::map<std::string, float> map) {
  std::istringstream iss(line);
  float value;
  char dash;
  std::string date;

  getline(iss, date, ' ');
  iss >> dash >> value;

  if (this->_calendar.dateToInt(date) <
      this->_calendar.dateToInt(map.begin()->first)) {
    std::cerr << RED << "Error : date inferior to every database's dates : ";
    std::cerr << date << RESET << std::endl;
    return;
  }
  if (map.find(date) == map.end()) {
    std::string newDate = this->_calendar.findClosestDate(date, map);
    std::cout << date << " => " << value << " = ";
    std::cout << value * map[newDate] << std::endl;
    return;
  }
  std::cout << date << " => " << value << " = ";
  std::cout << value * map[date] << std::endl;
}

void BitcoinExchange::processLine(const std::string line, bool *isFirstLine) {
    if (line.empty() || line == "\n")
      return;
    if (isFirstLine) {
      *isFirstLine = false;
      if (containsLetters(line))
        return;
    }
    try {
      dataLineValidation(line, '|');
      printBitcoinValue(line, this->_datas);
    } catch (InvalidDate &e) {
      std::string firstPart;
      std::istringstream iss(line);
      std::getline(iss, firstPart, '|');
      std::cerr << RED "Error: " << e.what() << firstPart << RESET << std::endl;
    } catch (InvalidDataLine &e) {
      std::cerr << RED "Error: " << e.what() << line << RESET << std::endl;
    } catch (std::exception &e) {
      std::cerr << RED "Error: " << e.what() << RESET << std::endl;
    }
}

void BitcoinExchange::searchBitcoinValue(void) {
  FileSrc            file;
  std::stringstream *dataFile = NULL;
  std::stringstream *inFile = NULL;
  std::string        line;
  bool               isFirstLine = true;

  try {
    inFile = file.convertFileToStream(this->_inputFile);
    dataFile = file.convertFileToStream(this->_dataFile);
  } catch (std::exception &e) {
    if (inFile != NULL) delete inFile;
    std::cerr << RED "Error: " << e.what() << RESET << std::endl;
    return;
  }
  this->fillMap(dataFile);
  while (std::getline(*inFile, line)) {
    this->processLine(line, &isFirstLine);
  }
  delete dataFile;
  delete inFile;
  return;
}

const char* BitcoinExchange::InvalidDataLine::what() const throw() {
       return ("Bad input => ");
}

const char* BitcoinExchange::InvalidDate::what() const throw() {
       return ("Invalid date => ");
}

const char* BitcoinExchange::notAPositiveNumber::what() const throw() {
       return ("Not a positive number.");
}

const char* BitcoinExchange::numberHigherThan1000::what() const throw() {
        return ("too large a number.");
}
