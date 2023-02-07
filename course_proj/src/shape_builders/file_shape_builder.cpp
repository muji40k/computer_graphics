#include "file_shape_builder.h"
#include <iostream>

FileShapeBuilder::FileShapeBuilder(const char *filename)
{
    try
    {
        this->file.open(filename, std::ifstream::in);
    }
    catch (std::ios_base::failure &e)
    {
        throw CALL_EX(NoFileShapeBuilderException);
    }
}

FileShapeBuilder::~FileShapeBuilder(void)
{
    this->file.close();
}

