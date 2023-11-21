#ifndef PrintDocument_h
#define PrintDocument_h

#include <vector>
#include "Elements\TextElement.h"
#include "Elements\CounterElement.h"
#include "Elements\DateTimeElement.h"
#include "Elements\BarcodeElement.h"
#include "Elements\LineElement.h"
#include "Elements\RectangleElement.h"
#include "Elements\CircleElement.h"
#include "Elements\ImageElement.h"
#include <ArduinoJson.h>
#include "../AppContext.h"

class PrintDocument
{
private:
    bool _linePixels[300];
    std::vector<TextElement> _textEelements;
    std::vector<CounterElement> _counterEelements;
    std::vector<DateTimeElement> _dateTimeElements;
    std::vector<BarcodeElement> _barcodeEelements;
    std::vector<LineElement> _lineEelements;
    std::vector<RectangleElement> _rectangleEelements;
    std::vector<CircleElement> _circleEelements;
    std::vector<ImageElement> _imageEelements;
    void calculateWidth();
    String getBufferFromImage(String id, String fileName);
    String _fileName;
    std::vector<String> _stackDatas;
    AppContext* appContext;
    
    
public:
    PrintDocument(AppContext* appContext, String fileName);
    void LoadFromFile();
    void ChangeData(String data);
    void AddChangeDataToStack(String data);
    void NextData();
    void AddTextElement(TextElement textEelement);
    void AddCounterElement(CounterElement counterEelement);
    void UpdatePrintData();
    void AddDateTimeElement(DateTimeElement dateTimeElement);
    void AddBarcodeElement(BarcodeElement barcodeEelement);
    void AddLineElement(LineElement lineEelement);
    void AddImageElement(ImageElement imageEelement);
    void AddCircleElement(CircleElement circleEelement);
    void AddRectangleElement(RectangleElement element);
    std::vector<TextElement> getTextElements();
    void getLinePixel(int line, bool (&linePixels)[300]);
    void PrintOnSerial(int pixelWidth);
    String GetImageBuffer();
    void ClearElements();
    

    bool RepeatDocument = false;
    int PrintCount = 0;
    int DelayBeforPrint = 0;
    int Quantity = 1;
    int QuantityDelay = 0;
    String LastPrintDate = "";

    int Width = 100;
    bool Printed = false;
};

PrintDocument::PrintDocument(AppContext* appContext, String fileName): appContext(appContext)
{
    ClearElements();
    Printed = false;
    _fileName = fileName;
}

void PrintDocument::ClearElements()
{
    _textEelements = std::vector<TextElement>();
    _counterEelements = std::vector<CounterElement>();
    _dateTimeElements = std::vector<DateTimeElement>();
    _barcodeEelements = std::vector<BarcodeElement>();
    _lineEelements = std::vector<LineElement>();
    _rectangleEelements = std::vector<RectangleElement>();
    _circleEelements = std::vector<CircleElement>();
    _imageEelements = std::vector<ImageElement>();
    _stackDatas = std::vector<String>();
}

void PrintDocument::AddRectangleElement(RectangleElement element)
{
    _rectangleEelements.push_back(element);
}
void PrintDocument::AddTextElement(TextElement element)
{
    _textEelements.push_back(element);
}

void PrintDocument::AddCounterElement(CounterElement element)
{
    _counterEelements.push_back(element);
}

void PrintDocument::AddDateTimeElement(DateTimeElement element)
{
    _dateTimeElements.push_back(element);
}

void PrintDocument::AddBarcodeElement(BarcodeElement element)
{
    _barcodeEelements.push_back(element);
}

void PrintDocument::AddLineElement(LineElement lineEelement)
{
    _lineEelements.push_back(lineEelement);
}

void PrintDocument::AddImageElement(ImageElement imageEelement)
{
    _imageEelements.push_back(imageEelement);
}

void PrintDocument::AddCircleElement(CircleElement circleEelement)
{
    _circleEelements.push_back(circleEelement);
}

std::vector<TextElement> PrintDocument::getTextElements()
{
    return _textEelements;
}

void PrintDocument::getLinePixel(int line, bool (&linePixels)[300])
{
    for (size_t k = 0; k < 300; k++)
    {
        linePixels[k] = false;
    }
    int16_t min_order = 255;
    int16_t max_order = 0;

    //Check for min and max order in
    for (size_t i = 0; i < _rectangleEelements.size(); i++)
    {
        uint8_t order = _rectangleEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _lineEelements.size(); i++)
    {
        uint8_t order = _lineEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _barcodeEelements.size(); i++)
    {
        uint8_t order = _barcodeEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _textEelements.size(); i++)
    {
        uint8_t order = _textEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _counterEelements.size(); i++)
    {
        uint8_t order = _counterEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _dateTimeElements.size(); i++)
    {
        uint8_t order = _dateTimeElements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _circleEelements.size(); i++)
    {
        uint8_t order = _circleEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    for (size_t i = 0; i < _imageEelements.size(); i++)
    {
        uint8_t order = _imageEelements.at(i).Order;
        if(order > max_order)
        {
            max_order = order;
        }
        if(order < min_order)
        {
            min_order = order;
        }
    }
    
    for (size_t order = min_order; order <= max_order; order++)
    {
        //fill Rectangle
        for (size_t li = 0; li < _rectangleEelements.size(); li++)
        {
            RectangleElement _element = _rectangleEelements.at(li);
            
            
            if(_element.Order == order)
            {
                if (_element.xPosition <= line && _element.xPosition + _element.Width >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line-_element.xPosition,elementLinearray);
                    for (size_t lj = 0; lj < _element.Height; lj++)
                    {
                        if(elementLinearray[lj])
                        {
                            linePixels[lj+_element.yPosition] = elementLinearray[lj];
                        }
                    }            
                }
                li = _rectangleEelements.size();
                continue;
            }        
        }    

        //fill Lines
        for (size_t i = 0; i < _lineEelements.size(); i++)
        {
            LineElement _element = _lineEelements.at(i);
            if(_element.Order == order)
            {
                if (_element.xPosition <= line && _element.xPosition + _element.Width >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line-_element.xPosition,elementLinearray);
                    for (size_t lj = 0; lj < _element.Height; lj++)
                    {
                        if(elementLinearray[lj])
                        {
                            // Serial.printf("id = %s ; order = %d at line = %d\n",_lineEelements.at(i).Id, order, line);
                            linePixels[lj+_element.yPosition] = elementLinearray[lj];
                        }
                    }            
                }
                i = _lineEelements.size();
                continue;
            }
        }    

        //fill Circles
        for (size_t i = 0; i < _circleEelements.size(); i++)
        {
            CircleElement _element = _circleEelements.at(i);
            if(_element.Order == order)
            {
                if (_element.xPosition - _element.Radius <= line && _element.xPosition + _element.Radius >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line - _element.xPosition,elementLinearray);
                    for (size_t lj = 0; lj < _element.Height; lj++)
                    {
                        if(elementLinearray[lj])
                        {
                            linePixels[lj+_element.yPosition] = elementLinearray[lj];
                        }
                    }            
                }
                i = _lineEelements.size();
                continue;
            }
        }    

        //Fill Barcodes
        for (size_t bi = 0; bi < _barcodeEelements.size(); bi++)
        {
            BarcodeElement _belement = _barcodeEelements.at(bi);
            if(_belement.Order == order)
            {
                if (_belement.xPosition <= line && _belement.xPosition + _belement.Width >= line)
                {
                    bool elementLinearray[300];
                    _belement.GetLineArray(line-_belement.xPosition,elementLinearray);
                    for (size_t bj = 0; bj < _belement.Height; bj++)
                    {
                        if(elementLinearray[bj])
                        {
                            linePixels[bj+_belement.yPosition] = elementLinearray[bj];
                        }
                    }            
                }
                bi = _barcodeEelements.size();
                continue;
            }
        }

        //Fill Images
        for (size_t ii = 0; ii < _imageEelements.size(); ii++)
        {
            ImageElement _ielement = _imageEelements.at(ii);
            if(_ielement.Order == order)
            {
                if (_ielement.xPosition <= line && _ielement.xPosition + _ielement.Width > line)
                {
                    bool elementLinearray[300];
                    _ielement.GetLineArray(line - _ielement.xPosition , elementLinearray);
                    for (size_t ij = 0; ij < _ielement.Height; ij++)
                    {
                        if(elementLinearray[ij])
                        {
                            linePixels[ij+_ielement.yPosition] = elementLinearray[ij];
                        }
                    }            
                }
                ii = _barcodeEelements.size();
                continue;
            }
        }

        //fill Counter
        for (size_t ci = 0; ci < _counterEelements.size(); ci++)
        {
            CounterElement _element = _counterEelements.at(ci);
            if(_element.Order == order)
            {
                if (_element.xPosition <= line && _element.xPosition + _element.Width >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line-_element.xPosition,elementLinearray);
                    for (size_t cj = 0; cj < _element.Height; cj++)
                    {
                        if(elementLinearray[cj])
                        {
                            linePixels[cj+_element.yPosition] = elementLinearray[cj];
                        }
                    }            
                }
                ci = _counterEelements.size();
                continue;
            }
        }

        //fill DateTime
        for (size_t ci = 0; ci < _dateTimeElements.size(); ci++)
        {
            DateTimeElement _element = _dateTimeElements.at(ci);
            if(_element.Order == order)
            {
                if (_element.xPosition <= line && _element.xPosition + _element.Width >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line-_element.xPosition,elementLinearray);
                    for (size_t cj = 0; cj < _element.Height; cj++)
                    {
                        if(elementLinearray[cj])
                        {
                            linePixels[cj+_element.yPosition] = elementLinearray[cj];
                        }
                    }            
                }
                ci = _dateTimeElements.size();
                continue;
            }
        }

        //fill Texts
        for (size_t ti = 0; ti < _textEelements.size(); ti++)
        {
            TextElement _element = _textEelements.at(ti);
            if(_element.Order == order)
            {
                if (_element.xPosition <= line && _element.xPosition + _element.Width >= line)
                {
                    bool elementLinearray[300];
                    _element.GetLineArray(line-_element.xPosition,elementLinearray);
                    for (size_t tj = 0; tj < _element.Height; tj++)
                    {
                        if(elementLinearray[tj])
                        {
                            // _element.Print();
                            linePixels[tj+_element.yPosition] = elementLinearray[tj];
                        }
                    }            
                }    
                ti = _textEelements.size();
                continue;
            }    
        }    


    }

}

void PrintDocument::PrintOnSerial(int pixelWidth)
{
    for (size_t i = 0; i < pixelWidth; i++)
    {
        bool lineArray[300];
        getLinePixel(i,lineArray);
        for (size_t j = 0; j < 300; j++)
        {
            if (lineArray[j])
            {
                Serial.print("♦");                
            }else{
                Serial.print(" ");
            }
            
        }
        Serial.println("");
    }
    
}

void PrintDocument::NextData()
{
    if(_stackDatas.size() > 0)
    {
        ChangeData(_stackDatas.at(0));
        
        if(_stackDatas.size() > 0)
        {
            for (size_t i = 0; i < _stackDatas.size()-1; i++)
            {
                _stackDatas.at(i) = _stackDatas.at(i+1);
            }
            _stackDatas.pop_back();
            Printed = false;
        }
        else
        {
            Printed = true;
        }
    }
    else
    {
        LoadFromFile();
        Printed = true;
    }
}

void PrintDocument::AddChangeDataToStack(String data)
{
    _stackDatas.push_back(data);
    Printed = false;
}

void PrintDocument::ChangeData(String data)
{
    LoadFromFile();
    StaticJsonDocument<4096> doc;
    DeserializationError error = deserializeJson(doc, data);
        
    JsonArray array = doc["elements"].as<JsonArray>();
    for(JsonVariant v : array) {
        String _key = "rotation";
        Rotation rotation;
        if (v.containsKey(_key))
        {
            String rotation = v[_key].as<String>();
            if (rotation == "ROTATE_0") {
                rotation = ROTATE_0;    
            } else if (rotation == "ROTATE_90") {
                rotation = ROTATE_90;    
            } else if (rotation == "ROTATE_180") {
                rotation = ROTATE_180;
            } else if (rotation == "ROTATE_270") {
                rotation = ROTATE_270;
            }                        
        }
        if (v["type"].as<String>() == "Text")
        {
            for (size_t i = 0; i < _textEelements.size(); i++)
            {
                if (String(_textEelements.at(i).Id) == String(v["id"].as<String>()))
                {
                    _key = "text";
                    if (v.containsKey(_key))
                    {
                        //svs [_textEelements.at(i).Id, v["id"].as<String>(), v[_key].as<String>()]
                        _textEelements.at(i).Text = v[_key].as<String>();
                    }
                    _key = "size";
                    if (v.containsKey(_key))
                    {
                        _textEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _textEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _textEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _textEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _textEelements.at(i).rotation = rotation;
                    }
                    _textEelements.at(i).CalculateWidthAndHeight();
                }
            }
        }
        else if(v["type"].as<String>() == "CounterText")
        {
            for (size_t i = 0; i < _counterEelements.size(); i++)
            {
                if (String(_counterEelements.at(i).Id) == String(v["id"].as<String>()))
                {
                    String _key = "text";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).Text = v[_key].as<String>();
                    }
                    _key = "size";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "start_value";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).StartValue = v[_key].as<int>();
                    }
                    _key = "end_value";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).EndValue = v[_key].as<int>();
                    }
                    _key = "pulse_value";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).PulseValue = v[_key].as<int>();
                    }
                    _key = "step_value";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).StepValue = v[_key].as<int>();
                    }
                    _key = "current_value";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).CurrentValue = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _counterEelements.at(i).rotation = rotation;
                    }

                    _counterEelements.at(i).CalculateWidthAndHeight();
                }
            }
        }
        else if(v["type"].as<String>() == "DateTimeText")
        {
            for (size_t i = 0; i < _dateTimeElements.size(); i++)
            {
                if (String(_dateTimeElements.at(i).Id) == String(v["id"].as<String>()))
                {
                    String _key = "format";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).format = v[_key].as<String>();
                    }
                    _key = "size";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _dateTimeElements.at(i).rotation = rotation;
                    }
                    _dateTimeElements.at(i).CalculateWidthAndHeight();
                }
            }
        }
        else if (v["type"].as<String>() == "Barcode")
        {
            for (size_t i = 0; i < _barcodeEelements.size(); i++)
            {
                if (_barcodeEelements.at(i).Id == v["id"].as<String>());
                {
                    String _key = "text";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).setValue(v[_key].as<String>());
                    }
                    _key = "size";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "height";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).Height = v[_key].as<int>();
                    }
                    _key = "show_text";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).ShowText = v[_key].as<bool>();
                    }
                    _key = "text_size";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).TextSize = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _barcodeEelements.at(i).rotation = rotation;
                    }

                    _barcodeEelements.at(i).FillBarcodeData();
                }
            }
        }
        else if (v["type"].as<String>() == "Line")
        {
            for (size_t i = 0; i < _lineEelements.size(); i++)
            {
                if (_lineEelements.at(i).Id == v["id"].as<String>());
                {
                    String _key = "size";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "end_x_position";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).EndXPosition = v[_key].as<int>();
                    }
                    _key = "end_y_position";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).EndYPosition = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _lineEelements.at(i).rotation = rotation;
                    }

                    _lineEelements.at(i).CalculateWidthAndHeight();
                }
            }
        }
        else if (v["type"].as<String>() == "Circle")
        {
            for (size_t i = 0; i < _circleEelements.size(); i++)
            {
                if (_circleEelements.at(i).Id == v["id"].as<String>());
                {
                    String _key = "size";
                    if (v.containsKey(_key))
                    {
                        _circleEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "radius";
                    if (v.containsKey(_key))
                    {
                        _circleEelements.at(i).Radius = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _circleEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _circleEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _circleEelements.at(i).Order = v[_key].as<int>();
                    }
                    _circleEelements.at(i).CalculateWidthAndHeight();
                }
            }        
        }
        else if (v["type"].as<String>() == "Rectangle")
        {
            for (size_t i = 0; i < _rectangleEelements.size(); i++)
            {
                if (_rectangleEelements.at(i).Id == v["id"].as<String>());
                {
                    String _key = "size";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).Size = v[_key].as<int>();
                    }
                    _key = "width";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).Width = v[_key].as<int>();
                    }
                    _key = "height";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).Height = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _rectangleEelements.at(i).rotation = rotation;
                    }

                }
            }        
        }
        else if (v["type"].as<String>() == "Image")
        {
            for (size_t i = 0; i < _imageEelements.size(); i++)
            {
                if (_imageEelements.at(i).Id == v["id"].as<String>());
                {
                    String _key = "width";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).Width = v[_key].as<int>();
                    }
                    _key = "height";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).Height = v[_key].as<int>();
                    }
                    _key = "xPos";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).xPosition = v[_key].as<int>();
                    }
                    _key = "yPos";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).yPosition = v[_key].as<int>();
                    }
                    _key = "order";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).Order = v[_key].as<int>();
                    }
                    _key = "rotation";
                    if (v.containsKey(_key))
                    {
                        _imageEelements.at(i).rotation = rotation;
                    }

                }
            }        
        }
    }
    calculateWidth();
}

void PrintDocument::LoadFromFile()
{
    StaticJsonDocument<4096> doc;
    
    IEBPFile* file = appContext->systemContext->getLittleFS()->open(_fileName, "r");
    DeserializationError error = deserializeJson(doc, file->readString());
    String key = "repeat_document";
    if(doc.containsKey(key))
    {
        RepeatDocument = doc[key].as<bool>();
    }

    key = "print_count";
    if(doc.containsKey(key))
    {
        PrintCount = doc[key].as<int>();
    }

    key = "last_print_date";
    if(doc.containsKey(key))
    {
        LastPrintDate = doc[key].as<String>();
    }

    key = "delay_before_print";
    if(doc.containsKey(key))
    {
        DelayBeforPrint = doc[key].as<int>();
    }

    key = "quantity";
    if(doc.containsKey(key))
    {
        Quantity = doc[key].as<int>();
    }

    key = "quantity_delay";
    if(doc.containsKey(key))
    {
        QuantityDelay = doc[key].as<int>();
    }

    ClearElements();
    JsonArray array = doc["elements"].as<JsonArray>();
    for(JsonVariant v : array) {
        Rotation rotation;
        String _key = "rotation";
        if (v.containsKey(_key))
        {
            String rotationStr = v[_key].as<String>();
            if (rotationStr == "ROTATE_0") {
                rotation = ROTATE_0;    
            } else if (rotationStr == "ROTATE_90") {
                rotation = ROTATE_90;    
            } else if (rotationStr == "ROTATE_180") {
                rotation = ROTATE_180;
            } else if (rotationStr == "ROTATE_270") {
                rotation = ROTATE_270;
            }                        
        }

        // Map custom Rotation enum to setRotation values using if-else statements
        if (rotation == ROTATE_0) {
            //svs ["ROTATE_0"]   
        } else if (rotation == ROTATE_90) {
            //svs ["ROTATE_90"]   

        } else if (rotation == ROTATE_180) {
            //svs ["ROTATE_180"]   

        } else if (rotation == ROTATE_270) {
            //svs ["ROTATE_270"]   

        }

        if (v["type"].as<String>() == "Text")
        {
            AddTextElement(TextElement(v["id"].as<String>(), v["text"].as<String>(),v["size"].as<int>(),v["xPos"].as<int>(),v["yPos"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "CounterText")
        {
            AddCounterElement(CounterElement(v["id"].as<String>(), v["size"].as<int>(),v["xPos"].as<int>(),v["yPos"].as<int>(),
            v["start_value"].as<int>(), v["end_value"].as<int>(), v["pulse_value"].as<int>(), v["step_value"].as<int>(), v["current_value"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "DateTimeText")
        {
            AddDateTimeElement(DateTimeElement(appContext, v["id"].as<String>(), v["format"].as<String>(),v["size"].as<int>(),v["xPos"].as<int>(),v["yPos"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "Barcode")
        {
            AddBarcodeElement(BarcodeElement(v["id"].as<String>(), v["text"].as<String>(),v["size"].as<int>(),v["height"].as<int>(),
                                v["xPos"].as<int>(),v["yPos"].as<int>(),v["show_text"].as<bool>(),v["text_size"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "Line")
        {
            AddLineElement(LineElement(v["id"].as<String>(), v["xPos"].as<int>(), v["yPos"].as<int>(), v["end_x_position"].as<int>(), v["end_y_position"].as<int>(), v["size"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "Circle")
        {
            AddCircleElement(CircleElement(v["id"].as<String>(), v["xPos"].as<int>(), v["yPos"].as<int>(), v["radius"].as<int>(), v["size"].as<int>(), v["order"].as<int>()));
        }
        else if (v["type"].as<String>() == "Rectangle")
        {
            AddRectangleElement(RectangleElement(v["id"].as<String>(), v["xPos"].as<int>(), v["yPos"].as<int>(), v["width"].as<int>(), v["height"].as<int>(), v["size"].as<int>(), v["order"].as<int>(), rotation));
        }
        else if (v["type"].as<String>() == "Image")
        {
            String buffer = getBufferFromImage(v["id"].as<String>(), _fileName); 
            AddImageElement(ImageElement(v["id"].as<String>(),buffer,v["xPos"].as<int>(),v["yPos"].as<int>(),v["width"].as<int>(),v["height"].as<int>(),v["order"].as<int>(), rotation));
        }
    }

    file->close();
    calculateWidth();
}

String PrintDocument::GetImageBuffer()
{
    String buffer = "";
    for (size_t i = 0; i < Width; i++)
    {
        char currentLine[60];
        for (size_t index = 0; index < 60; index++)
        {
            currentLine[index] = '0';
        }
        bool lineArray[300];
        getLinePixel(i, lineArray);

        for (size_t j = 0; j < 300; j++)
        {
            ImageElement().setPixelAtLine(j ,lineArray[j], currentLine);
        }
        for (size_t k = 0; k < 60; k++)
        {
            buffer += currentLine[k];
        }
    }
    return buffer;
}

void PrintDocument::calculateWidth()
{
    //Check for min and max order in
    for (size_t i = 0; i < _rectangleEelements.size(); i++)
    {
        if(_rectangleEelements.at(i).xPosition + _rectangleEelements.at(i).Width > Width)
        {
            Width = _rectangleEelements.at(i).xPosition + _rectangleEelements.at(i).Width;
        }
    }
    for (size_t i = 0; i < _lineEelements.size(); i++)
    {
        if(_lineEelements.at(i).xPosition + _lineEelements.at(i).Width > Width)
        {
            Width = _lineEelements.at(i).xPosition + _lineEelements.at(i).Width;
        }
    }
    for (size_t i = 0; i < _barcodeEelements.size(); i++)
    {
        if(_barcodeEelements.at(i).xPosition + _barcodeEelements.at(i).Width > Width)
        {
            Width = _barcodeEelements.at(i).xPosition + _barcodeEelements.at(i).Width;
        }
    }
    for (size_t i = 0; i < _textEelements.size(); i++)
    {
        if(_textEelements.at(i).xPosition + _textEelements.at(i).Width > Width)
        {
            Width = _textEelements.at(i).xPosition + _textEelements.at(i).Width;
        }
    }
    for (size_t i = 0; i < _counterEelements.size(); i++)
    {
        if(_counterEelements.at(i).xPosition + _counterEelements.at(i).Width > Width)
        {
            Width = _counterEelements.at(i).xPosition + _counterEelements.at(i).Width;
        }        
    }
    for (size_t i = 0; i < _dateTimeElements.size(); i++)
    {
        if(_dateTimeElements.at(i).xPosition + _dateTimeElements.at(i).Width > Width)
        {
            Width = _dateTimeElements.at(i).xPosition + _dateTimeElements.at(i).Width;
        }        
    }    
    for (size_t i = 0; i < _circleEelements.size(); i++)
    {
        if(_circleEelements.at(i).xPosition + _circleEelements.at(i).Radius > Width)
        {
            Width = _circleEelements.at(i).xPosition + _circleEelements.at(i).Radius;
        }
    }
    for (size_t i = 0; i < _imageEelements.size(); i++)
    {
        if(_imageEelements.at(i).xPosition + _imageEelements.at(i).Width > Width)
        {
            Width = _imageEelements.at(i).xPosition + _imageEelements.at(i).Width;
        }
    }
}

String PrintDocument::getBufferFromImage(String id, String fileName)
{
     
    IEBPFile* file = appContext->systemContext->getLittleFS()->open(fileName, "r");
    String _fileContent = file->readString();
    String fileContent = _fileContent;
    
    file->close();
    for (size_t i = 0; i < fileContent.length() - id.length() - 10; i++)
    {
        if (fileContent.substring(i,i+id.length()) == id)
        {
            String buffer_title = "buffer";
            for (size_t j = i+2; j < fileContent.length() - buffer_title.length(); j++)
            {
                if (fileContent.substring(j,j+buffer_title.length()) == buffer_title)
                {
                    for (size_t k = j + 8; k < fileContent.length()-2; k++)
                    {
                        if (fileContent.substring(k,k+1) == "\"")
                        {
                            for (size_t l = k +1; l < fileContent.length()-1; l++)
                            {
                                if (fileContent.substring(l,l+1) == "\"")
                                {
                                    return fileContent.substring(k+1, l);
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    return "";
}

void PrintDocument::UpdatePrintData()
{
    StaticJsonDocument<4096> doc;

    PrintCount = PrintCount + 1;

    // Open file for reading
    IEBPFile* file = appContext->systemContext->getLittleFS()->open(_fileName, "r");
    if (!file) {
        // Handle file open error
        return;
    }

    DeserializationError error = deserializeJson(doc, file->readString());
    file->close();

    if (error) {
        // Handle deserialization error
        return;
    }

    // Update QuantityCounter
    doc["print_count"] = PrintCount;

    // Update current_value for all CounterText elements
    JsonArray elements = doc["elements"].as<JsonArray>();
    for (JsonVariant element : elements) {
        if (element["type"].as<String>() == "CounterText") {
            for (size_t ci = 0; ci < _counterEelements.size(); ci++)
            {
                CounterElement _element = _counterEelements.at(ci);
                if(_element.Id == element["id"].as<String>())
                {
                    _element.Increment();
                    element["current_value"] = _element.CurrentValue;
                }                
            }
        }
    }

    // Update last_print_date and update_date
    // String currentDateTime = getCurrentDateTime(); // You should implement this function to get the current date and time in the same format as in the JSON document
    // doc["last_print_date"] = currentDateTime;
    // doc["update_date"] = currentDateTime;

    // Open file for writing and save updated JSON data back to the file
    file = appContext->systemContext->getLittleFS()->open(_fileName, "w");
    if (!file) {
        // Handle file open error
        return;
    }

    serializeJson(doc, file);
    file->close();

    for (size_t ci = 0; ci < _dateTimeElements.size(); ci++)
    {
        DateTimeElement _element = _dateTimeElements.at(ci);
        _element.RefreshText();
    }
}

#endif