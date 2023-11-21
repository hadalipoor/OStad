#ifndef IINKJETPRINTER
#define IINKJETPRINTER

class IInkjetPrinter {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
};

#endif // IINKJETPRINTER
