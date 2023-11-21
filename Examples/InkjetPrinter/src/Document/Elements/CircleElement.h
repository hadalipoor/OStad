#ifndef CircleElement_h
#define CircleElement_h

#include "Element.h"

class CircleElement : public Element
{
private:
    
public:
    CircleElement();
    CircleElement(String id, int16_t x_Position, int16_t y_Position, int16_t radius, uint8_t size, uint8_t order);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();
    void CalculateWidthAndHeight();
    void CalculateWidthAndHeight(int16_t radius);
    int8_t Radius;
};

CircleElement::CircleElement() : Element()
{
}

CircleElement::CircleElement(String id, int16_t x_Position, int16_t y_Position, int16_t radius, uint8_t size, uint8_t order): Element(id,x_Position,y_Position, size, order, Rotation::ROTATE_0)
{
    Radius = radius;
    CalculateWidthAndHeight();
}
void CircleElement::CalculateWidthAndHeight()
{
    Height = Radius * 2;
    Width = Height;
}

void CircleElement::CalculateWidthAndHeight(int16_t radius)
{
    Height = radius * 2;
    Width = Height;
}

void CircleElement::GetLineArray(int line, bool (&lineArray)[300])
{
    GFXcanvas16SerialDemo demo8(1,Height);
    demo8.fillScreen(0x00);
    
    demo8.drawCircle(Radius - line , yPosition, Radius, 65535);
    
    for (size_t j = 0; j < Height; j++)
    {
        int16_t pixel_index = -1 * (j - Height + 1);

        if(demo8.getPixel(pixel_index,0)> 0)
        {
            lineArray[j] = true;
        }
        else
        {
            lineArray[j] = false;
        }
    }
}

void CircleElement::Print()
{
for (size_t i = 0; i < Width; i++)
    {
        bool lineArray[300];
        GetLineArray(i,lineArray);
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
