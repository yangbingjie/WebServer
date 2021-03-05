#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_
#include <string>
using namespace std;
class Timestamp{
public:
    Timestamp(double micro_seconds = 0.0);
    ~Timestamp();
    bool valid() const;
    string to_string() const;
    static Timestamp now();
    static Timestamp nowAfter(double seconds);
    static double nowMicroseconds();
    int get_timestamp() const;
    bool operator==(const Timestamp& timestamp) const;
    bool operator<(const Timestamp& timestamp) const;
    static const int _MICROSECOND_PRE_SECOND = 1000 * 1000;
private:
    int64_t _micro_seconds;
};
#endif // _TIMESTAMP_H_