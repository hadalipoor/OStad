#ifndef Element_h
#define Element_h

#include "../Tools/GFXcanvasSerialDemo.h"

enum ElementType{
    Text,
    Barcode,
    Rectangle,
    Line,
    Circle,
};

enum Rotation {
    ROTATE_0,
    ROTATE_90,
    ROTATE_180,
    ROTATE_270,
};

class Element
{
private:

public:
    Element();
    Element(String id, int16_t x_Position, int16_t y_Position, uint8_t size, uint8_t order, Rotation rotation_);

    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();

    String Id;
    int16_t Width;
    int16_t Height;
    int16_t xPosition;
    int16_t yPosition;
    uint8_t Order;
    uint8_t Size;
    Rotation rotation;
};

Element::Element()
{
}

Element::Element(String id, int16_t x_Position, int16_t y_Position, uint8_t size, uint8_t order, Rotation rotation_)
{
    Id = id;
    xPosition = x_Position;
    yPosition = y_Position;
    Size = size;
    Order = order;
    rotation = rotation_;
}

void Element::GetLineArray(int line, bool (&lineArray)[300])
{
    GFXcanvas16SerialDemo demo8(1, Height);
    demo8.fillScreen(0x00);
    demo8.drawRect(xPosition - line, yPosition, Width, Height, 65535);

    // Map custom Rotation enum to setRotation values using if-else statements
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

        if (demo8.getPixel(pixel_index, 0) > 100)
        {
            lineArray[j] = true;
        }
        else
        {
            lineArray[j] = false;
        }
    }
}


void Element::Print()
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
