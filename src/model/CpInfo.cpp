#include "CpInfo.h"
#include <cstring>
#include <vector>
#include <stdio.h>

uint16_t CpInfo::get_name_index() {
    return (this->info[0] << 8) + this->info[1];
}

uint16_t CpInfo::get_descriptor_index() {
    return (this->info[2] << 8) + this->info[3];
}

uint16_t CpInfo::get_class_index() {
    return this->get_name_index();
}

uint16_t CpInfo::get_name_and_type_index() {
    return this->get_descriptor_index();
}

uint16_t CpInfo::get_string_index() {
    return this->get_name_index();
}

uint32_t CpInfo::get_bytes() {
    return (this->info[0] << 24) + (this->info[1] << 16) + (this->info[2] << 8) + this->info[3];
}

uint32_t CpInfo::get_high_bytes() {
    return this->get_bytes();
}

uint32_t CpInfo::get_low_bytes() {
    return (this->info[4] << 24) + (this->info[5] << 16) + (this->info[6] << 8) + this->info[7];
}

uint16_t CpInfo::get_lenght() {
    return this->get_name_index();
}

std::vector<char> CpInfo::get_bytes_utf8() {
    std::vector<char> value(this->info.begin() + 2, this->info.end());
    return value;
}