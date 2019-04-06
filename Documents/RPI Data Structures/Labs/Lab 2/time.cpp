#include <iostream>
#include "time.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
    cout << "Hour: " << hour << endl;
    cout << "Minute: " << minute << endl;
    cout << "Second: " << second << endl;
}

Time::Time (int hour_input, int minute_input, int second_input)
{
    hour = hour_input;
    minute = minute_input;
    second = second_input;

}

int Time::get_hour() const
{
    return hour;
}

int Time::get_minute() const
{
    return minute;
}

int Time::get_second() const
{
    return second;
}

void Time::set_hour(int h)
{
    hour = h;
}

void Time::set_minute(int m)
{
    minute = m;
}

void Time::set_second(int s)
{
    second = s;
}

void Time::PrintAmPM()
{
    string print_hour;
    string print_minute;
    string print_second;
    string end;
    if (hour == 0)
    {
        print_hour = to_string(12);
        end = " AM";
    }
    else if (hour > 12)
    {
        if (hour - 12 < 10){
            print_hour = "0" + to_string(hour-12);
            end = " PM";
        }
        else {
            print_hour = to_string(hour - 12);
            end = " PM";
        }
    }
    else if (hour ==12)
    {
        print_hour = to_string(hour);
        end = " PM";
    }
    else
    {
        if (hour < 10) {
            print_hour = "0" + to_string(hour);
            end = " AM";
        }
        else{
            print_hour = to_string(hour);
            end = " AM";
        }
    }
    if (minute < 10)
    {
        print_minute = "0" + to_string(minute);
    }
    else
    {
        print_minute = to_string(minute);
    }
    if (second < 10)
    {
        print_second = "0" + to_string(second);
    }
    else
    {
        print_second = to_string(second);
    }
    cout << print_hour << ":" << print_minute << ":" << print_second << end << endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
    if (t1.get_hour() < t2.get_hour())
    {
        return true;
    }

    else if (t1.get_hour() == t2.get_hour() && t1.get_minute() < t2.get_minute())
    {
        return true;
    }

    else if (t1.get_hour() == t2.get_hour() && t1.get_minute() == t2.get_minute() && t1.get_second() < t2.get_second())
    {
        return true;
    }
    else
    {
        return false;
    }
}