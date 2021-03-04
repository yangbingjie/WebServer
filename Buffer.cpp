#include "Buffer.h"
Buffer::Buffer(){}
Buffer::~Buffer(){}
const char* Buffer::c_str(){
    return _buffer.c_str();
}
string Buffer::value() const{
    return string(_buffer);
}
int Buffer::size(){
    return _buffer.size();
}
void Buffer::substr(int len){
    _buffer = _buffer.substr(len, _buffer.size());
}
void Buffer::append(const string& str){
    _buffer.append(str);
}
bool Buffer::empty(){
    return _buffer.empty();
}
