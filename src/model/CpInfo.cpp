#include "CpInfo.h"
#include <cstring>
#include <vector>
#include <stdio.h>

uint16_t CpInfo::get_name_index() {
    return (this->info[0] << 8) + this->info[1];
}

uint16_t CpInfo::get_ref_index() {
    return (this->info[1]<<8) | this->info[2];
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

int CpInfo::get_int() {
    return this->get_bytes();
}

long long CpInfo::get_long() {
    return ((long long)this->get_high_bytes() << 32) + this->get_low_bytes();
}

float CpInfo::get_float() {
    uint32_t temp = this->get_bytes();
    float f;
    memcpy(&f, &temp, sizeof(float));
    return f;
}

double CpInfo::get_double() {
    uint64_t temp = this->get_long();
    double d;
    memcpy(&d, &temp, sizeof(double));
    return d;
}

std::vector<char> CpInfo::get_bytes_utf8() {
    std::vector<char> value(this->info.begin() + 2, this->info.end());
    return value;
}