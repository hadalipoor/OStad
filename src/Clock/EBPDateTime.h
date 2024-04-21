#ifndef EBPDATETIME_H
#define EBPDATETIME_H

#include <RTClib.h>
#include "JalaliDateTime.h"

class EBPDateTime : public DateTime {
public:
    EBPDateTime();
    EBPDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
    EBPDateTime(DateTime dt);
    EBPDateTime(String datestring);

    bool isNull(); 
    bool isDateTimeStringValid(String strDateTime); 
    void fromString(String strDateTime);
    String toDateTimeString();
    String toDateString();
    String toTimeString();
    TimeSpan getTimeSpan(EBPDateTime _dateTime); 
    bool isInSameDate(EBPDateTime _dateTime);
    bool isInSameDateTime(EBPDateTime _dateTime);
    bool isBetweenTwoDate(EBPDateTime _startTime, EBPDateTime _endTime);
    bool isBetweenTwoDateTime(EBPDateTime _startTime, EBPDateTime _endTime);
    JalaliDateTime getJalaliDateTime();
    void fromJalaliDateTime(JalaliDateTime jalaliDateTime);
    void fromJalaliDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
    void addToDateTime(int add_year, int add_month, int add_day, int add_hour, int add_minute, int add_second);
    static const EBPDateTime nullDateTime();
};

EBPDateTime::EBPDateTime() : DateTime(2000, 1, 1, 0, 0, 0) {}

EBPDateTime::EBPDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
    : DateTime(year, month, day, hour, min, sec) {}

EBPDateTime::EBPDateTime(DateTime dt) : DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second()) 
{
    
}

EBPDateTime::EBPDateTime(String datestring) 
{
    fromString(datestring);
}

bool EBPDateTime::isNull() {
    return (year() == 2000 && month() == 1 && day() == 1 && hour() == 0 && minute() == 0 && second() == 0);
}

bool EBPDateTime::isDateTimeStringValid(String strDateTime) {
    // Check string length to match "YY/MM/DD - HH:MM:SS" format
    if (strDateTime.length() != 17) return false;

    // Validate date separators
    if (strDateTime.charAt(2) != '/' || strDateTime.charAt(5) != '/' || strDateTime.charAt(8) != ' ' || strDateTime.charAt(11) != ':' || strDateTime.charAt(14) != ':')
        return false;

    // Validate year, month and day
    int _year = strDateTime.substring(0, 2).toInt();
    int _month = strDateTime.substring(3, 5).toInt();
    int _day = strDateTime.substring(6, 8).toInt();
    if (_year < 1300 || _year > 2000) return false;
    if (_month < 1 || _month > 12) return false;
    if (_day < 1 || _day > 31) return false;

    // Validate hour, minute and second
    int _hour = strDateTime.substring(10, 12).toInt();
    int _minute = strDateTime.substring(13, 15).toInt();
    int _second = strDateTime.substring(16, 18).toInt();
    if (_hour < 0 || _hour > 23) return false;
    if (_minute < 0 || _minute > 59) return false;
    if (_second < 0 || _second > 59) return false;

    // If all checks passed, the string is valid
    return true;
}

void EBPDateTime::fromString(String strDateTime) {
    // Extract and convert year, month, and day from the string
    int year = strDateTime.substring(0, 4).toInt();
    int month = strDateTime.substring(5, 7).toInt();
    int day = strDateTime.substring(8, 10).toInt();

    // Extract and convert hour, minute, and second from the string
    int hour = strDateTime.substring(11, 13).toInt();
    int minute = strDateTime.substring(14, 16).toInt();
    int second = strDateTime.substring(17, 19).toInt();

    // Assign the newly created DateTime object to this
    *this = EBPDateTime(year, month, day, hour, minute, second);
}

String EBPDateTime::toDateTimeString() {
    String strDateAndTime = String(year()) + "/" +
        (month() < 10 ? "0" : "") + String(month()) + "/" +
        (day() < 10 ? "0" : "") + String(day()) + " - " +
        (hour() < 10 ? "0" : "") + String(hour()) + ":" +
        (minute() < 10 ? "0" : "") + String(minute()) + ":" +
        (second() < 10 ? "0" : "") + String(second());
    return strDateAndTime;
}

String EBPDateTime::toDateString() {
    char buf[11];
    sprintf(buf, "%04d/%02d/%02d", year(), month(), day());
    return String(buf);
}

String EBPDateTime::toTimeString() {
    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", hour(), minute(), second());
    return String(buf);
}

TimeSpan EBPDateTime::getTimeSpan(EBPDateTime _dateTime) {
    return TimeSpan(DateTime::unixtime() - _dateTime.unixtime());
}

bool EBPDateTime::isInSameDate(EBPDateTime _dateTime) {
    return (year() == _dateTime.year() && month() == _dateTime.month() && day() == _dateTime.day());
}

bool EBPDateTime::isInSameDateTime(EBPDateTime _dateTime) {
    return (year() == _dateTime.year() && month() == _dateTime.month() && day() == _dateTime.day() && hour() == _dateTime.hour() && minute() == _dateTime.minute() && second() == _dateTime.second());
}

bool EBPDateTime::isBetweenTwoDate(EBPDateTime _startTime, EBPDateTime _endTime) {
    // Convert start, end, and current times to a format that only includes the date for comparison
    DateTime startDate(_startTime.year(), _startTime.month(), _startTime.day());
    DateTime endDate(_endTime.year(), _endTime.month(), _endTime.day());
    DateTime currentDate(year(), month(), day());

    // Check if current date is between start and end dates
    return (currentDate >= startDate && currentDate <= endDate);
}

bool EBPDateTime::isBetweenTwoDateTime(EBPDateTime _startTime, EBPDateTime _endTime) {
    // Use the unixtime method to get the time in seconds since Unix epoch
    time_t startUnix = _startTime.unixtime();
    time_t endUnix = _endTime.unixtime();
    time_t currentUnix = this->unixtime();

    // Check if current datetime is between start and end datetime
    return (currentUnix >= startUnix && currentUnix <= endUnix);
}

JalaliDateTime EBPDateTime::getJalaliDateTime() {
    JalaliDateTime jd;
    jd.ConvertToJalali(*this);
    return jd;
}

void EBPDateTime::fromJalaliDateTime(JalaliDateTime jalaliDateTime) {
    DateTime dt = jalaliDateTime.ConvertToGregorian();
    *this = EBPDateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
}

void EBPDateTime::fromJalaliDateTime(int year, int month, int day, int hour, int minute, int second) {
    JalaliDateTime jd(year, month, day, hour, minute, second);
    fromJalaliDateTime(jd);
}

void EBPDateTime::addToDateTime(int add_year, int add_month, int add_day, int add_hour, int add_minute, int add_second)
{
    int new_second = second() + add_second;
    int new_minute = minute() + add_minute + new_second / 60;
    new_second %= 60;
    
    int new_hour = hour() + add_hour + new_minute / 60;
    new_minute %= 60;

    int new_day = day() + add_day + new_hour / 24;
    new_hour %= 24;

    int new_month = month() + add_month;
    int new_year = year() + add_year;
    
    while (new_day > 30) {  // assuming all months have 30 days
        new_day -= 30;
        new_month++;
    }

    while (new_month > 12) {
        new_month -= 12;
        new_year++;
    }

    *this = EBPDateTime(new_year, new_month, new_day, new_hour, new_minute, new_second);
}

const EBPDateTime EBPDateTime::nullDateTime()
{
    return EBPDateTime(2000, 1, 1, 0, 0, 0);
}
#endif // EBPDATETIME_H
