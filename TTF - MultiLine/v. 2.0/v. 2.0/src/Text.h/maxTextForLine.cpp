#include "../../lib/Text.h"

std::size_t Text::maxTextForLine(std::string textLine, int text_limit)
{
    /* This function returns the maximum text that can stay on one line, giving as input a limit beyond which we should wrap the text. */
    int w = 0;
    std::string maxTextForLine;

        for(std::size_t i = 0; w <= text_limit; i++)
        {
            maxTextForLine.append(textLine, i, 1);
            TTF_SizeText(gFont, maxTextForLine.c_str(), &w, NULL);
        }

    return maxTextForLine.length();
}
