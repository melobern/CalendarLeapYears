/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:25:30 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/09 21:40:12 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX00_INCLUDES_BITCOINEXCHANGE_HPP_
#define EX00_INCLUDES_BITCOINEXCHANGE_HPP_
# include <iostream>
# include <string>
# include <map>
# include "Calendar.hpp"

class BitcoinExchange {
 private:
  std::map<std::string, float> _datas;
  static const std::string     _dataFile;
  std::string                  _inputFile;
  Calendar                     _calendar;

  BitcoinExchange(void);
  BitcoinExchange &operator=(const BitcoinExchange &src);
  BitcoinExchange(const BitcoinExchange &src);
  void fillMap(std::stringstream *dataFile);
  void dataLineValidation(const std::string &line, char sep);
  void printBitcoinValue(std::string line, std::map<std::string, float> map);
  void processLine(const std::string line, bool *isFirstLine);
  class InvalidDataLine : public std::exception {
   public:
    virtual const char *what() const throw();
  };
  class InvalidDate : public std::exception {
   public:
    virtual const char *what() const throw();
  };
  class notAPositiveNumber : public std::exception {
   public:
    virtual const char *what() const throw();
  };
  class numberHigherThan1000 : public std::exception {
   public:
    virtual const char *what() const throw();
  };

 public:
  explicit BitcoinExchange(const std::string inputFile);
  ~BitcoinExchange(void);
  void searchBitcoinValue(void);
};

#endif  //  EX00_INCLUDES_BITCOINEXCHANGE_HPP_
