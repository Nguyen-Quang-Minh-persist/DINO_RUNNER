#include "check_touch.h"


// Check touch of two rectangles
bool check_touch_two_rect(SDL_Rect& a, SDL_Rect& b)
{
    return (a.x < b.x + b.w &&
            b.x < a.x + a.w &&
            a.y < b.y + b.h &&
            b.y < a.y + a.h);
}


