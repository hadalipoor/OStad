#ifndef RectangleElement_h
#define RectangleElement_h

#include "Element.h"

class RectangleElement : public Element
{
private:
    
public:
    RectangleElement();
    RectangleElement(String id, int16_t x_Position, int16_t y_Position, int16_t width, int16_t height, uint8_t size, uint8_t order, Rotation rot);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();

};

RectangleElement::RectangleElement() : Element()
{
}

RectangleElement::RectangleElement(String id, int16_t x_Position, int16_t y_Position, int16_t width, int16_t height, uint8_t size, uint8_t order, Rotation rot): Element(id, x_Position, y_Position, size, order, rot)
{
    Width = width;
    Height = height;
}

void RectangleElement::GetLineArray(int line, bool (&lineArray)[300])
{
    GFXcanvas16SerialDemo demo8(1, Height);
    demo8.fillScreen(0x00);

    if (rotation == ROTATE_0 || rotation == ROTATE_180) {
        demo8.drawRect(-line, yPosition, Width, Height - 1, 65535);
    } else if (rotation == ROTATE_90 || rotation == ROTATE_270) {
        demo8.drawRect(yPosition, -line, Height - 1, Width, 65535);
    }
    
    demo8.setRotation(3);
    
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

void RectangleElement::Print()
{
    for (size_t i = 0; i < Width; i++)
    {
        bool lineArray[300];
        GetLineArray(i, lineArray);
        for (size_t j = 0; j < Height; j++)
        {
            if(lineArray[j])
            {
                Serial.print("♦");
            }
            else
            {
                Serial.print(" ");
            }
        }
        Serial.println("");
    }
}

#endif
