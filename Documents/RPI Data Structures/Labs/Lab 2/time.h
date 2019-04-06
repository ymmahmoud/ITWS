#ifndef Header_h
#define lab2_time_h

class Time {
public:
    Time();
    Time(int hour, int minute, int second);
    
    //Accessors
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    
    //Modifiers
    void set_hour (int hour_input); //takes a single integer argument and changes the appropriate member variable
    void set_minute (int minute_input);
    void set_second (int second_input);
    void PrintAmPM ();  //prints time in terms of am or pm
    
private:
    int hour;
    int minute;
    int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);


#endif /* Header_h */