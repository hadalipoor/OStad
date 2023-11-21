#ifndef INKJETPRINTER_H
#define INKJETPRINTER_H

#include "IInkjetPrinter.h"
#include "../AppContext.h"
#include "../Config/DefaultInkjetPrinterConfigs.h"

class InkjetPrinter : public IInkjetPrinter {
private:
    AppContext* context;

public:
    InkjetPrinter(AppContext* context);
    
    void initialize() override;
    void update() override;
};

InkjetPrinter::InkjetPrinter(AppContext* context)
    : context(context) {}

void InkjetPrinter::initialize() {

}

void InkjetPrinter::update() {

}

#endif //INKJETPRINTER_H
