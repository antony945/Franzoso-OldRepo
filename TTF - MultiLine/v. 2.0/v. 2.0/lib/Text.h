class Text
{
	public:
		//Initializes variables
		Text();

		//Deallocates memory
		~Text();

		//Return the max length of line of text, given a limit
		std::size_t maxTextForLine(int text_limit);

		Uint32 getMaxWidth(std::string textureText);

		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		void free();

		void render(int x, int y);

	private:
	    //The actual hardware texture
		SDL_Texture* tTexture;

		//Image dimensions
		int tWidth;
		int tHeight;

		//Length of each line (until comes an '\n')
		std::size_t lengthLine;

		//Text of each line (until comes an '\n')
		std::string textLine;
};
