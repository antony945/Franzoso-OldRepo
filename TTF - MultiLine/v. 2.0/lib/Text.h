class Text
{
	public:
		//Initializes variables
		Text();

		//Deallocates memory
		~Text();

		//Return the max length of line of text, given a limit
		std::size_t maxTextForLine(std::string textLine, int text_limit);

		//Loads image at specified path
		Uint32 getMaxWidth(std::string textureText);

		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

		//Deallocates texture
		void free();

		void render(int x, int y);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* tTexture;

		//Image dimensions
		int tWidth;
		int tHeight;
};
