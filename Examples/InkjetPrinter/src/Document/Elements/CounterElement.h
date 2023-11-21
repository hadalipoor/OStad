#ifndef COUNTERELEMENT_H
#define COUNTERELEMENT_H

#include "TextElement.h"

class CounterElement : public TextElement
{
private:

public:
    CounterElement();
    CounterElement(String id, uint8_t size, int16_t x_Position, int16_t y_Position,
        int16_t start_value, int16_t end_value, int16_t pulse_value, int16_t step_value, int16_t current_value, uint8_t order, Rotation rot);

    void GetLineArray(int line, bool (&lineArray)[300]) override;

    int16_t StartValue;
    int16_t EndValue;
    int16_t PulseValue;
    int16_t StepValue;
    int16_t CurrentValue;
    void Increment();
    void Decrement();
    void Reset();

};

CounterElement::CounterElement() : TextElement()
{

}

CounterElement::CounterElement(String id, uint8_t size, int16_t x_Position, int16_t y_Position,
    int16_t start_value, int16_t end_value, int16_t pulse_value, int16_t step_value, int16_t current_value, uint8_t order, Rotation rot) :
    TextElement(id, "", size, x_Position, y_Position, order, rot)
{
    StartValue = start_value;
    EndValue = end_value;
    PulseValue = pulse_value;
    StepValue = step_value;
    CurrentValue = current_value;
    Text = String(CurrentValue);
    CalculateWidthAndHeight();
}


void CounterElement::Increment()
{
    CurrentValue += StepValue;
    if (CurrentValue > EndValue)
    {
        CurrentValue = EndValue;
    }
    Text = String(CurrentValue);
    CalculateWidthAndHeight();
}

void CounterElement::Decrement()
{
    CurrentValue -= StepValue;
    if (CurrentValue < StartValue)
    {
        CurrentValue = StartValue;
    }
    Text = String(CurrentValue);
    CalculateWidthAndHeight();
}

void CounterElement::Reset()
{
    CurrentValue = StartValue;
    Text = String(CurrentValue);
    CalculateWidthAndHeight();
}

void CounterElement::GetLineArray(int line, bool (&lineArray)[300])
{
    TextElement::GetLineArray(line, lineArray);
}

#endif // COUNTERELEMENT_H