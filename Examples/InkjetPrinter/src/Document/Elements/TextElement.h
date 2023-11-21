#ifndef TextElement_h
#define TextElement_h

#include "Element.h"
#include <Fonts/FreeMono24pt7b.h>

class TextElement : public Element
{
private:
    
public:
    TextElement();
    TextElement(String id, String text, uint8_t size, int16_t x_Position, int16_t y_Position, uint8_t order, Rotation rot);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();
    void CalculateWidthAndHeight();
    void CalculateWidthAndHeight(String text, uint8_t size);
    String Text;
};

TextElement::TextElement() : Element()
{

}
TextElement::TextElement(String id, String text, uint8_t size, int16_t x_Position, int16_t y_Position, uint8_t order, Rotation rot): Element(id, x_Position, y_Position, size, order, rot)
{
    Text = text;
    CalculateWidthAndHeight(text, size);
}

void TextElement::CalculateWidthAndHeight()
{
    int16_t distance = 7 * Size;
    if (rotation == Rotation::ROTATE_0 || rotation == Rotation::ROTATE_180)
    {
        Width = Text.length() * distance;
        Height = (Size * 7);
    }
    else // Rotation::ROTATE_90 or Rotation::ROTATE_270
    {
        Width = (Size * 7);
        Height = Text.length() * distance;
    }
    //svs [Width, Height]
}

void TextElement::CalculateWidthAndHeight(String text, uint8_t size)
{
    int16_t distance = 7 * size;
    if (rotation == Rotation::ROTATE_0 || rotation == Rotation::ROTATE_180)
    {
        Width = text.length() * distance;
        Height = (size * 7);
    }
    else // Rotation::ROTATE_90 or Rotation::ROTATE_270
    {
        Width = (size * 7);
        Height = text.length() * distance;
    }
    //svs [Width, Height]
}


void TextElement::GetLineArray(int line, bool (&lineArray)[300])
{
    int16_t character_distance = 7 * Size;
    GFXcanvas16SerialDemo demo8(1, character_distance);
    
    demo8.fillScreen(0x00);
    // Map custom Rotation enum to setRotation values using if-else statements
    for (size_t i = 0; i < Text.length(); i++)
    {
        char currentChar = Text.substring(i, i + 1).charAt(0);
        //sbvs [i,line,(i * character_distance) - line,currentChar]
        demo8.drawChar((i * character_distance) - line, 0, currentChar, 65535, 0, Size);
        // if (rotation == ROTATE_0 || rotation == ROTATE_180) {
        // } else if (rotation == ROTATE_90 || rotation == ROTATE_270) {
        //     demo8.drawChar(0 ,(i * character_distance) - line, Text.substring(i, i + 1).charAt(0), 65535, 0, Size);
        // }            
    }
    demo8.setFont(&FreeMono24pt7b);
    
    if (rotation == ROTATE_0) {
        demo8.setRotation(3);
    } else if (rotation == ROTATE_90) {
        demo8.setRotation(0);
    } else if (rotation == ROTATE_180) {
        demo8.setRotation(1);
    } else if (rotation == ROTATE_270) {
        demo8.setRotation(2);
    }

    for (size_t j = 0; j < Height; j++)
    {
        int16_t pixel_index = -1 * (j - Height + 1);
        if(demo8.getPixel(pixel_index, 0) > 100)
        {
            lineArray[j] = true;
        }
        else
        {
            lineArray[j] = false;
        }
    }
}

void TextElement::Print()
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

#endif
