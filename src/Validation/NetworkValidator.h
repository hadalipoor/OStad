#ifndef NETWORKVALIDATOR_H
#define NETWORKVALIDATOR_H

class NetworkValidator
{
private:
    
public:
    NetworkValidator();
    ~NetworkValidator();
    bool isValidIP(String ip);
};

NetworkValidator::NetworkValidator()
{

}

NetworkValidator::~NetworkValidator()
{
}

bool NetworkValidator::isValidIP(String ip)
{
    int numDots = 0;
    int numDigits = 0;
    int acc = 0;  // accumulator for the current segment

    // Check each character in the string
    for (int i = 0; i < ip.length(); i++) {
    char c = ip.charAt(i);
    if (c == '.') {
        numDots++;
        if (numDigits == 0 || numDigits > 3) return false;  // wrong number of digits
        if (acc > 255) return false;  // segment exceeds the maximum of 255
        numDigits = 0;  // reset for the next byte
        acc = 0;
    } else if (c >= '0' && c <= '9') {  // update accumulator with digit
        numDigits++;
        acc = acc * 10 + (c - '0');
        if (acc > 255) return false;  // segment exceeds the maximum of 255
        if (numDigits > 3) return false;  // too many digits
    } else {
        return false;  // invalid character
    }
    }

    // Check the last segment
    if (numDots != 3 || numDigits == 0 || numDigits > 3) return false;
    if (acc > 255) return false;

    return true;
}

#endif //NETWORKVALIDATOR_H