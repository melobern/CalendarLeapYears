/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileSrc.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:15:50 by mbernard          #+#    #+#             */
/*   Updated: 2024/08/13 09:10:09 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FileSrc.hpp"

FileSrc::FileSrc(void) {
    return;
}

FileSrc::~FileSrc() {
    return;
}

bool FileSrc::open_in(const std::string name) {
        this->file_src.open(name.c_str(), std::ios::in);
        if (!this->file_src.is_open())
            return (0);
        return (1);
}

std::stringstream* FileSrc::convertFileToStream(const std::string filename) {
    if (!this->open_in(filename))
        throw std::runtime_error(std::strerror(errno));

    std::stringstream *stream = new std::stringstream();

    *stream << this->file_src.rdbuf();
    this->file_src.close();
    if (stream->str().empty()) {
        delete stream;
        throw std::runtime_error("File is empty");
    }
    return (stream);
}
