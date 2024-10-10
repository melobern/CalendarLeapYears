/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileSrc.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:17:15 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/09 21:57:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX00_INCLUDES_FILESRC_HPP_
#define EX00_INCLUDES_FILESRC_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

class FileSrc {
 public:
  FileSrc(void);
  ~FileSrc();
  std::stringstream*           convertFileToStream(const std::string filename);
 private:
  std::ifstream file_src;
  bool open_in(const std::string name);
};
#endif  // EX00_INCLUDES_FILESRC_HPP_
