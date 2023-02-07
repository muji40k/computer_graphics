#ifndef _FILE_SHAPE_BUILDER_H_
#define _FILE_SHAPE_BUILDER_H_

#include "shape_builder.h"
#include <fstream>

class FileShapeBuilder : public BaseShapeBuilder
{
    public:
        FileShapeBuilder(const char *filename);
        virtual ~FileShapeBuilder(void) = 0;
        virtual std::shared_ptr<Shape> build(void) = 0;

    protected:
        std::ifstream file;
};

class CommonFileShapeBuilderException: public CommonShapeBuilderException
{
    public:
        CommonFileShapeBuilderException(void) = default;
        CommonFileShapeBuilderException(const char *filename, const size_t line,
                                        const char *function,
                                        const char *message = "General file shape builder exception")
            : CommonShapeBuilderException(filename, line, function, message) {};
        ~CommonFileShapeBuilderException(void) = default;
};

class NoFileShapeBuilderException: public CommonFileShapeBuilderException
{
    public:
        NoFileShapeBuilderException(void) = default;
        NoFileShapeBuilderException(const char *filename, const size_t line,
                                    const char *function,
                                    const char *message = "No given file for builder")
            : CommonFileShapeBuilderException(filename, line, function, message) {};
        ~NoFileShapeBuilderException(void) = default;
};

#endif

