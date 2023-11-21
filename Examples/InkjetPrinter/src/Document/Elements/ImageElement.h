#ifndef ImageElement_h
#define ImageElement_h

#include "Element.h"
#include <math.h>

class ImageElement : public Element
{
private:
    
public:
    ImageElement();
    ImageElement(String id, String buffer, int16_t x_Position, int16_t y_Position, int16_t width, int16_t height, uint8_t order, Rotation rotation);
    void getBinaryFromBase36(char _hex, bool (& binaryArray) [5]);
    bool getPixelAtLine(uint16_t position, char line[60]);
    void setPixelAtLine(uint16_t position, bool black, char (& line) [60]);
    void getBase36FromBinary(bool binaryArray[5], char &output);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();

    String Buffer;
};

ImageElement::ImageElement() : Element()
{

}

ImageElement::ImageElement(String id, String buffer, int16_t x_Position, int16_t y_Position, int16_t width, int16_t height, uint8_t order, Rotation rotation): Element(id,x_Position,y_Position, 1, order, rotation)
{
    Width = width;
    Height = height;
    Buffer = buffer;
    Serial.printf("Buffer = %s\n",Buffer);
}
void ImageElement::GetLineArray(int line, bool (&lineArray)[300]) 
{
    int sep_count = Height / 5 ;
    if(float(sep_count) < (float(Height) / 5.0))
    {
        sep_count += 1;
    }

    String lineString = Buffer.substring(line*sep_count, (line*sep_count)+sep_count);
    char line_buffer[sep_count];
    lineString.toCharArray(line_buffer, sizeof(line_buffer));
    // Rotate the image according to the rotation value
    // if (rotation == ROTATE_0 || rotation == ROTATE_180) {
    //     for (size_t i = 0; i < 300; i++) {
    //         lineArray[i] = getPixelAtLine(i, line_buffer);
    //     }
    // } else if (rotation == ROTATE_90 || rotation == ROTATE_270) {
    //     for (size_t i = 0; i < 300; i++) {
    //         lineArray[i] = getPixelAtLine(Height - 1 - i, line_buffer);
    //     }
    // }

    // if (rotation == ROTATE_180 || rotation == ROTATE_270) {
    //     std::reverse(lineArray, lineArray + 300);
    // }
    for (size_t i = 0; i < 300; i++)
    {
        lineArray[i] = getPixelAtLine(i, line_buffer);
    }    
}

void ImageElement::Print() 
{
    for (size_t i = 0; i < Width; i++)
    {
        bool lineArray[300];
        GetLineArray(i, lineArray);
        for (size_t j = 0; j < Height; j++)
        {
            Serial.print(lineArray[j]);
        }
        Serial.println("");
    }
    
}

void ImageElement::getBinaryFromBase36(char _hex, bool (& binaryArray) [5])
{
    uint8_t ascii = _hex;
    uint8_t base36Decimal = 0;
    if (ascii > 47 || ascii < 80)
    {
        base36Decimal = ascii - 48;
    }else
    {
        base36Decimal = 0;
    }
    
    for(uint8_t index=0; index<5; index++)
    {
        binaryArray[index] = base36Decimal % 2;
        base36Decimal = base36Decimal / 2;
    }
}

bool ImageElement::getPixelAtLine(uint16_t position, char line[60])
{
    uint8_t charPosition = position / 5;
    uint8_t pixelPositionAtHex = position % 5;
    bool binaryArray[5];
    getBinaryFromBase36(line[charPosition], binaryArray);
            
    return binaryArray[pixelPositionAtHex];
}

void ImageElement::setPixelAtLine(uint16_t position, bool black, char (& line) [60])
{
    uint8_t charPosition = position / 5;
    uint8_t pixelPositionAtHex = position % 5;

    bool binaryArray[5];
    for (size_t i = 0; i < 5; i++)
    {
        if(i == pixelPositionAtHex)
        {
            binaryArray[i] = black;
        }
        else
        {
            binaryArray[i] = getPixelAtLine((charPosition * 5) + i, line);
        }
    }
    char tempChar;

    getBase36FromBinary(binaryArray, tempChar);
    line[charPosition] = tempChar;
}

void ImageElement::getBase36FromBinary(bool binaryArray[5], char &output)
{
    uint8_t value = binaryArray[0] + (binaryArray[1] * 2) + (binaryArray[2] * 4) + (binaryArray[3] * 8) + (binaryArray[4] * 16);
    output = '0';
    if (value < 32 && value >=0)
    {
        output = (value + 48);
    }else
    {
        output = '0';
    }
}

#endif
