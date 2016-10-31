#include <string>

class date_t
{
public:
    date_t()
    {
        day = 0;
        month = 0;
        year = 0;
    }
    unsigned char day;
    unsigned char month;
    unsigned int  year;
    bool QSTR_TO_DATE_T(std::string time);
    ~date_t(){};
};

bool date_t::QSTR_TO_DATE_T(std::string time_s)
{
    day = (time_s[0]-'0')*10+time_s[1]-'0';
    month = (time_s[3]-'0')*10+time_s[4]-'0';
    year = (time_s[6]-'0')*1000+(time_s[7]-'0')*100+(time_s[8]-'0')*10+(time_s[9]-'0');
    return ((day <= 31) && (day > 0) && (month <=12) && (month > 0) && (year >= 2015));
}
