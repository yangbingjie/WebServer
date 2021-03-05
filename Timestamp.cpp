#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS
#include <sys/time.h>
#include <stdio.h>
#include "Timestamp.h"
#include <iostream>
Timestamp::Timestamp(double micro_seconds):_micro_seconds(micro_seconds){

}
Timestamp::~Timestamp(){}
bool Timestamp::valid() const {return _micro_seconds > 0;}
string Timestamp::Timestamp::to_string() const{
    int64_t seconds = _micro_seconds / _MICROSECOND_PRE_SECOND;
    int64_t microseconds = _micro_seconds % _MICROSECOND_PRE_SECOND;
    char buffer[32];
    snprintf(buffer, sizeof(buffer) - 1,"%" PRId64 ".%06" PRId64, seconds, microseconds);
    return buffer;
}
Timestamp Timestamp::now(){
    return Timestamp(Timestamp::nowMicroseconds());
}
double Timestamp::nowMicroseconds(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return seconds * _MICROSECOND_PRE_SECOND + tv.tv_usec;
}
Timestamp Timestamp:: nowAfter(double seconds){
    return Timestamp(Timestamp::nowMicroseconds() + seconds * _MICROSECOND_PRE_SECOND);
}
int Timestamp::get_timestamp() const{return _micro_seconds;}
bool Timestamp::operator==(const Timestamp& timestamp) const{
    return this->get_timestamp() == timestamp.get_timestamp();
}
bool Timestamp::operator<(const Timestamp& timestamp) const{
    return this->get_timestamp() < timestamp.get_timestamp();
}