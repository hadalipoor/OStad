#ifndef JALALIDATETIME_H
#define JALALIDATETIME_H

#include <RTClib.h>

class JalaliDateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    long* gregorian_to_jalali(long gy, long gm, long gd, long out[]);
    long *jalali_to_gregorian(long jy, long jm, long jd, long out[]);
    bool _isNull;

public:
    // Existing constructors and conversion methods.

    // New methods:
    JalaliDateTime();  // sets to the Jalali date corresponding to 2000/1/1 12:00:00
    JalaliDateTime(DateTime gregorian_dateTime);  // sets to the Jalali date corresponding to 2000/1/1 12:00:00
    JalaliDateTime(int year, int month, int day, int hour, int minute, int second);
    JalaliDateTime(int year, int month, int day);
    bool isNull();  // check if the date is the Jalali date corresponding to 2000/1/1 12:00:00
    bool isDateTimeStringValid(String strDateTime);  // Check if string is in format YY/MM/DD - HH:MM:SS
    void fromString(String strDateTime);  // Fill JalaliDateTime from string in format YY/MM/DD - HH:MM:SS
    String toDateTimeString();  // return JalaliDateTime in string in format YY/MM/DD - HH:MM:SS 
    String toDateString();  // return JalaliDateTime in string in format YY/MM/DD
    String toTimeString();  // return JalaliDateTime in string in format HH:MM:SS
    TimeSpan getTimeSpan(JalaliDateTime _dateTime);  // Return time span between current time and passed time in _dateTime
    bool isInSameDate(JalaliDateTime _dateTime);  // Return true if _dateTime and current JalaliDateTime are in the same date.
    bool isInSameDateTime(JalaliDateTime _dateTime);  // Return true if _dateTime and current JalaliDateTime are exactly the same.
    void ConvertToJalali(DateTime dateTime);
    DateTime ConvertToGregorian();
};

JalaliDateTime::JalaliDateTime(): JalaliDateTime(DateTime(2000, 1, 1, 0, 0, 0))
{
    
}

JalaliDateTime::JalaliDateTime(DateTime dateTime): _isNull(true)
{
    ConvertToJalali(dateTime);
}

JalaliDateTime::JalaliDateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second), _isNull(false) 
{

}

JalaliDateTime::JalaliDateTime(int year, int month, int day)
    : year(year), month(month), day(day), hour(0), minute(0), second(0), _isNull(false)
{

}

bool JalaliDateTime::isNull()
{
    return _isNull;
}

bool JalaliDateTime::isDateTimeStringValid(String strDateTime) {
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

void JalaliDateTime::fromString(String strDateTime) {
    // Extract and convert year, month, and day from the string
    year = strDateTime.substring(0, 2).toInt();
    month = strDateTime.substring(3, 5).toInt();
    day = strDateTime.substring(6, 8).toInt();

    // Extract and convert hour, minute, and second from the string
    hour = strDateTime.substring(10, 12).toInt();
    minute = strDateTime.substring(13, 15).toInt();
    second = strDateTime.substring(16, 18).toInt();
}

String JalaliDateTime::toDateTimeString() {
    String strDateTime = "";

    // Formatted YY/MM/DD - HH:MM:SS
    strDateTime += String(year) + "/" + String(month) + "/" + String(day);
    strDateTime += " - ";
    strDateTime += String(hour) + ":" + String(minute) + ":" + String(second);

    return strDateTime;
}

String JalaliDateTime::toDateString() {
    String strDate = "";

    // Formatted YY/MM/DD
    strDate += String(year) + "/" + String(month) + "/" + String(day);

    return strDate;
}

String JalaliDateTime::toTimeString() {
    String strTime = "";

    // Formatted HH:MM:SS
    strTime += String(hour) + ":" + String(minute) + ":" + String(second);

    return strTime;
}

TimeSpan JalaliDateTime::getTimeSpan(JalaliDateTime _dateTime) {
    // First, convert both Jalali dates to Gregorian DateTime
    DateTime thisDateTime = ConvertToGregorian();
    DateTime otherDateTime = _dateTime.ConvertToGregorian();

    // Calculate difference in seconds between the two DateTime objects
    long timeSpanSeconds = thisDateTime.unixtime() - otherDateTime.unixtime();

    // Create TimeSpan object from difference and return
    TimeSpan timeSpan(timeSpanSeconds);
    return timeSpan;
}

bool JalaliDateTime::isInSameDate(JalaliDateTime _dateTime) {
    // Returns true if year, month, and day are the same
    return (year == _dateTime.year && month == _dateTime.month && day == _dateTime.day);
}

bool JalaliDateTime::isInSameDateTime(JalaliDateTime _dateTime) {
    // Returns true if year, month, day, hour, minute, and second are the same
    return (year == _dateTime.year && month == _dateTime.month && day == _dateTime.day &&
            hour == _dateTime.hour && minute == _dateTime.minute && second == _dateTime.second);
}

void JalaliDateTime::ConvertToJalali(DateTime dateTime) {
    long out[3];
    gregorian_to_jalali(dateTime.year(), dateTime.month(), dateTime.day(), out);
    year = out[0];
    month = out[1];
    day = out[2];
    hour = dateTime.hour();
    minute = dateTime.minute();
    second = dateTime.second();
}

DateTime JalaliDateTime::ConvertToGregorian() {
    long out[3];
    jalali_to_gregorian(year, month, day, out);
    return DateTime(out[0], out[1], out[2], hour, minute, second);
}

long *JalaliDateTime::gregorian_to_jalali(long gy, long gm, long gd, long out[]) {
    long days;
    {
        long gy2 = (gm > 2) ? (gy + 1) : gy;
        long g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        days = 355666 + (365 * gy) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + gd + g_d_m[gm - 1];
    }
    long jy = -1595 + (33 * ((int)(days / 12053)));
    days %= 12053;
    jy += 4 * ((int)(days / 1461));
    days %= 1461;
    if (days > 365) {
        jy += (int)((days - 1) / 365);
        days = (days - 1) % 365;
    }
    out[0] = jy;
    if (days < 186) {
        out[1]/*jm*/ = 1 + (int)(days / 31);
        out[2]/*jd*/ = 1 + (days % 31);
    } else {
        out[1]/*jm*/ = 7 + (int)((days - 186) / 30);
        out[2]/*jd*/ = 1 + ((days - 186) % 30);
    }
    return out;
}

long *JalaliDateTime::jalali_to_gregorian(long jy, long jm, long jd, long out[]) {
    jy += 1595;
    long days = -355668 + (365 * jy) + (((int)(jy / 33)) * 8) + ((int)(((jy % 33) + 3) / 4)) + jd + ((jm < 7) ? (jm - 1) * 31 : ((jm - 7) * 30) + 186);
    long gy = 400 * ((int)(days / 146097));
    days %= 146097;
    if (days > 36524) {
        gy += 100 * ((int)(--days / 36524));
        days %= 36524;
        if (days >= 365) days++;
    }
    gy += 4 * ((int)(days / 1461));
    days %= 1461;
    if (days > 365) {
        gy += (int)((days - 1) / 365);
        days = (days - 1) % 365;
    }
    long gd = days + 1;
    long gm;
    {
        long sal_a[13] = {0, 31, ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (gm = 0; gm < 13 && gd > sal_a[gm]; gm++) gd -= sal_a[gm];
    }
    out[0] = gy;
    out[1] = gm;
    out[2] = gd;
    return out;
}

#endif  // JALALIDATETIME_H
