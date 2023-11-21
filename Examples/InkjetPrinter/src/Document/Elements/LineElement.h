#ifndef LineElement_h
#define LineElement_h

#include "Element.h"

class LineElement : public Element
{
private:
    
public:
    LineElement();
    LineElement(String id, int16_t x_Position, int16_t y_Position, int16_t endXPosition, int16_t endYPosition, uint8_t size, uint order, Rotation rot);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();
    void CalculateWidthAndHeight();

    int16_t EndXPosition;
    int16_t EndYPosition;
};

LineElement::LineElement() : Element()
{

}

LineElement::LineElement(String id, int16_t x_Position, int16_t y_Position, int16_t endXPosition, int16_t endYPosition, uint8_t size, uint order, Rotation rot) : Element(id, x_Position, y_Position, size, order, rot)
{
    EndXPosition = endXPosition;
    EndYPosition = endYPosition;
    CalculateWidthAndHeight();
}

void LineElement::CalculateWidthAndHeight()
{
    if (rotation == ROTATE_0 || rotation == ROTATE_180) {
        Width = abs(xPosition - EndXPosition);
        Height = abs(yPosition - EndYPosition);
    } else if (rotation == ROTATE_90 || rotation == ROTATE_270) {
        Width = abs(yPosition - EndYPosition);
        Height = abs(xPosition - EndXPosition);
    }
}

void LineElement::GetLineArray(int line, bool (&lineArray)[300])
{
    GFXcanvas16SerialDemo demo8(1, Height);
    demo8.fillScreen(0x00);

    if (rotation == ROTATE_0) {
        demo8.drawLine(-line, yPosition, EndXPosition - xPosition - line, EndYPosition, 65535);
    } else if (rotation == ROTATE_90) {
        demo8.drawLine(yPosition, line, EndYPosition, EndXPosition - xPosition - line, 65535);
    } else if (rotation == ROTATE_180) {
        demo8.drawLine(Width - line, Height - yPosition, EndXPosition - xPosition - (Width - line), EndYPosition - yPosition, 65535);
    } else if (rotation == ROTATE_270) {
        demo8.drawLine(Height - yPosition, Width - line, EndYPosition - yPosition, EndXPosition - xPosition - (Width - line), 65535);
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

void LineElement::Print()
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
