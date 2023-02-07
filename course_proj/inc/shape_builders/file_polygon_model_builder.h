#ifndef _FILE_POLYGON_MODEL_BUILDER_H_
#define _FILE_POLYGON_MODEL_BUILDER_H_

#include "file_shape_builder.h"

class FilePolygonModelBuilder : public FileShapeBuilder
{
    public:
        FilePolygonModelBuilder(const char *filename);
        virtual ~FilePolygonModelBuilder(void) override;
        virtual std::shared_ptr<Shape> build(void) override;
};

class CommonFilePolygonModelBuilderException: public CommonFileShapeBuilderException
{
    public:
        CommonFilePolygonModelBuilderException(void) = default;
        CommonFilePolygonModelBuilderException(const char *filename, const size_t line,
                                        const char *function,
                                        const char *message = "General file poygon model builder exception")
            : CommonFileShapeBuilderException(filename, line, function, message) {};
        ~CommonFilePolygonModelBuilderException(void) = default;
};

class WrongFilePolygonModelBuilderException: public CommonFilePolygonModelBuilderException
{
    public:
        WrongFilePolygonModelBuilderException(void) = default;
        WrongFilePolygonModelBuilderException(const char *filename, const size_t line,
                                    const char *function,
                                    const char *message = "File has wrong structure")
            : CommonFilePolygonModelBuilderException(filename, line, function, message) {};
        ~WrongFilePolygonModelBuilderException(void) = default;
};

#endif

