#ifndef _LINE_ALGORITHMS_H_
#define _LINE_ALGORITHMS_H_

#include <cstdlib>

#define ERROR_DEGENERATE_LINE 100

#define CONTINUE_DRAW 0
#define FINISHED_DRAW 1

#define POINT_AMOUNT 2

template <typename T>
using point_t = T[POINT_AMOUNT];

// DDA
typedef struct
{
    point_t<double> point;
    int length;
    double dx;
    double dy;
} dda_line_handle_t;

int dda_line_handle_init(dda_line_handle_t &handle,
                         const point_t<int> start, 
                         const point_t<int> end);
int dda_line_handle_step(dda_line_handle_t &handle);
void dda_line_handle_get(dda_line_handle_t &handle, point_t<int> &point);

// Bresenham
typedef struct
{
    point_t<int> point;
    int length;
    bool swap;
    double tangent;
    double error;
    int sx;
    int sy;
} BRHM_line_handle_t;

int BRHM_line_handle_init(BRHM_line_handle_t &handle,
                          const point_t<int> start, 
                          const point_t<int> end);
int BRHM_line_handle_step(BRHM_line_handle_t &handle);
void BRHM_line_handle_get(BRHM_line_handle_t &handle, point_t<int> &point);

// Bresenham integer
typedef struct
{
    point_t<int> point;
    int length;
    bool swap;
    int dx;
    int dy;
    int error;
    int sx;
    int sy;
} BRHMI_line_handle_t;

int BRHMI_line_handle_init(BRHMI_line_handle_t &handle,
                           const point_t<int> start, 
                           const point_t<int> end);
int BRHMI_line_handle_step(BRHMI_line_handle_t &handle);
void BRHMI_line_handle_get(BRHMI_line_handle_t &handle, point_t<int> &point);

// Bresenham smoothing
typedef struct
{
    point_t<int> point;
    int length;
    bool swap;
    double tangent;
    double error;
    double error_limit;
    int sx;
    int sy;
} BRHMA_line_handle_t;

typedef struct
{
    point_t<int> dot;
    double alpha;
} BRHMA_result_t;

int BRHMA_line_handle_init(BRHMA_line_handle_t &handle,
                           const point_t<int> start, 
                           const point_t<int> end);
int BRHMA_line_handle_step(BRHMA_line_handle_t &handle);
void BRHMA_line_handle_get(BRHMA_line_handle_t &handle, BRHMA_result_t &point);


// Wu
typedef enum
{
    VERTICAL,
    HORIZONTAL,
    SMOOTH,
    STEAP
} tangent_type_WU_t;

typedef struct
{
    point_t<double> point;
    int length;
    double dx;
    double dy;
    tangent_type_WU_t tangent;
} WU_line_handle_t;

typedef struct
{
    size_t amount;
    point_t<int> start;
    double alpha_start;
    point_t<int> end;
    double alpha_end;
} WU_result_t;

int WU_line_handle_init(WU_line_handle_t &handle,
                        const point_t<int> start, 
                        const point_t<int> end);
int WU_line_handle_step(WU_line_handle_t &handle);
void WU_line_handle_get(WU_line_handle_t &handle, WU_result_t &point);

#endif

