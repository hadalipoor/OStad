// DateTimeElement.h

#ifndef DateTimeElement_h
#define DateTimeElement_h

#include "TextElement.h"
#include "../../AppContext.h"

class DateTimeElement : public TextElement
{
private:
    AppContext* appContext;
public:
    DateTimeElement(AppContext* appContext);
    DateTimeElement(AppContext* appContext, String id, String format, uint8_t size, int16_t x_Position, int16_t y_Position, uint8_t order, Rotation rot);

    void RefreshText();

    String format;
};

DateTimeElement::DateTimeElement(AppContext* appContext) : TextElement(), appContext(appContext)
{

}

DateTimeElement::DateTimeElement(AppContext* appContext, String id, String format, uint8_t size, int16_t x_Position, int16_t y_Position, uint8_t order, Rotation rot) :
    TextElement(id, "", size, x_Position, y_Position, order, rot), appContext(appContext)
{
    this->format = format;
    RefreshText();
    CalculateWidthAndHeight();
}

void DateTimeElement::RefreshText()
{
    Text = appContext->systemContext->getClock()->now().toDateTimeString();
    CalculateWidthAndHeight();
}

#endif // DateTimeElement_h
