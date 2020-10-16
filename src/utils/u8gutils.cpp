#include "u8gutils.h"

void clearScreen(DISPLAY_CLASS &u8g)
{
    u8g.firstPage();
    do
    {
    } while (u8g.nextPage());
}

void drawStrLeft(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y)
{
    u8g.drawStr(DISPLAY_MINX, y, str);
}

void drawStrRight(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y)
{
    u8g_uint_t strWidth = u8g.getStrWidth(str);
    u8g_uint_t x = DISPLAY_MINX + (DISPLAY_WIDTH - strWidth);

    u8g.drawStr(x, y, str);
}

void drawStrCentered(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y)
{
    u8g_uint_t strWidth = u8g.getStrWidth(str);
    u8g_uint_t x = DISPLAY_MINX + ((DISPLAY_WIDTH - strWidth) / 2);

    u8g.drawStr(x, y, str);
}
