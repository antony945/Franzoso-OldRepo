struct lineLength{
    int maxLengthLine = 0;
    std::size_t lengthLine = 0;

};

struct lineText{
    std::string maxTextLine;
    std::size_t lengthTextLine;
};

struct lineFinder{
    std::string newLine = "\n";
    std::size_t exFinder = 0;
    std::size_t newLineFinder = 0;
    bool stopFinder = false;
};
