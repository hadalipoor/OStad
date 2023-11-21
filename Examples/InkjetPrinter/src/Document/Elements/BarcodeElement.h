#ifndef BarcodeElement_h
#define BarcodeElement_h

#include "../Tools/code128.h"
#include "Element.h"
#include "TextElement.h"


class BarcodeElement : public Element
{
private:
    size_t barcode_length;
    char *barcode_data;
public:
    BarcodeElement();
    BarcodeElement(String id, String value, uint8_t size, int16_t height, int16_t x_Position, int16_t y_Position, bool showText, uint8_t textSize, uint8_t order, Rotation rotation);
    
    virtual void GetLineArray(int line, bool (&lineArray)[300]);
    virtual void Print();
    void setValue(String _value);
    
    void FillBarcodeData();
    char Value[40];
    bool ShowText;
    uint8_t TextSize;
};

BarcodeElement::BarcodeElement() : Element()
{
}

BarcodeElement::BarcodeElement(String id, String value, uint8_t size, int16_t height, int16_t x_Position, int16_t y_Position, bool showText, uint8_t textSize, uint8_t order, Rotation rotation): Element(id,x_Position,y_Position, size, order, rotation)
{
    Width = 1;
    Height = height;
    value.toCharArray(Value,sizeof(value));
    ShowText = showText;
    TextSize = textSize;
    FillBarcodeData();
}

void BarcodeElement::setValue(String value)
{
    value.toCharArray(Value,sizeof(value));
}

void BarcodeElement::GetLineArray(int line, bool (&lineArray)[300]) 
{
    bool res = false;
    if(barcode_data[line / Size])
    {
        res = true;
    }
    for (size_t j = 0; j < 300; j++)
    {
        lineArray[j] = res;
    }
    if (ShowText)
    {
        TextElement textElement = TextElement("barcode_text",Value, TextSize, 0, 0, 0, Rotation::ROTATE_0);
        textElement.xPosition = (Width - textElement.Width) / 2;
        textElement.yPosition = Height - textElement.Height;

        if(line >= textElement.xPosition && line <= textElement.xPosition + textElement.Width)
        {
            bool textLineArray[300];
            textElement.GetLineArray(line - textElement.xPosition , textLineArray);
            for (size_t i = 0; i < textElement.Height; i++)
            {
                lineArray[i + textElement.yPosition] = textLineArray[i];
            }            
        }
    }
      
}

void BarcodeElement::FillBarcodeData()
{
    // const char *str = text.c_str();
    barcode_length = code128_estimate_len(Value);
    barcode_data = (char *) malloc(barcode_length);

    barcode_length = code128_encode_gs1(Value, barcode_data, barcode_length);
    Width = barcode_length * Size;
}

void BarcodeElement::Print() 
{
    for (size_t i = 0; i < Width; i++)
    {
        bool lineArray[300];
        GetLineArray(i,lineArray);
        for (size_t j = 0; j < Height; j++)
        {
            Serial.print(lineArray[j]);
        }
        Serial.println("");
    }
    
}


#endif