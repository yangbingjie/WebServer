#ifndef _BUFFER_H_
#define _BUFFER_H_
#include <string>
using namespace std;
class Buffer{
public:
    Buffer();
    ~Buffer();
    const char* c_str();
    string value() const;
    int size();
    void retrieve(int len);
    string retrieveAndReturn(int len);
    void append(const string& str);
    bool empty();
private:
    string _buffer;
};
#endif // _BUFFER_H_