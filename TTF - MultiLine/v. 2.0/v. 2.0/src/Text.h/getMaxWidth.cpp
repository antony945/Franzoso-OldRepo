#include "../../lib/Text.h"

Uint32 Text::getMaxWidth(std::string textureText)
{
    std::string maxTextLine;
    int maxLengthLine = 0;

    std::size_t lengthLine = 0;
    std::string textLine;

    std::size_t exFinder = 0;
    std::size_t newLineFinder = 0;

    std::string newLine("\n");
    std::string space(" ");

    bool stopFinder = false;

    int w_line = 0;

    for(std::size_t i = 0; !stopFinder; i+=lengthLine+1)
    {
        do
        {
            if(w_line <= SCREEN_WIDTH)
            {
                if(newLineFinder == 0)
                    exFinder = newLineFinder;
                else
                    exFinder = newLineFinder + 1;
            }

            newLineFinder = textureText.find(newLine, i);

            stopFinder = (newLineFinder == std::string::npos);
            if (stopFinder)
            {
                if(i == 0)
                {
                    newLineFinder = 0;
                    lengthLine = textureText.length();
                }
                else
                {
                    newLineFinder = textureText.length();
                    lengthLine = newLineFinder - exFinder;
                }
            }
            else
            {
                    lengthLine = newLineFinder - exFinder; //LUNGHEZZA LINEA DI TESTO
                    if (lengthLine > maxLengthLine)
                    {
                        maxLengthLine = lengthLine;
                    }
            }

            /** TESTO LINEA **/
            textLine.assign(textureText, i, lengthLine);
            TTF_SizeText(gFont, textLine.c_str(), &w_line, NULL);

            if(textLine.length() > maxTextLine.length())
            {
                maxTextLine = textLine;
            }

            if(w_line > SCREEN_WIDTH)
            {
                std::size_t pos_last_space_allowed = textLine.find_last_of(space.c_str(), maxTextForLine(textLine, SCREEN_WIDTH)) + exFinder;
                textureText.replace(pos_last_space_allowed, 1, newLine);

                maxTextLine.clear();
            }

        }while(w_line > SCREEN_WIDTH);
    }

    TTF_SizeText(gFont, maxTextLine.c_str(), &maxLengthLine, NULL); //MASSIMA LUNGHEZZA DI UNA LINEA IN PIXEL

    return maxLengthLine;
}
