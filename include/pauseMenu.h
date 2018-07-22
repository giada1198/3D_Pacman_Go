#ifndef PAUSEMENU_IS_INCLUDED
#define PAUSEMENU_IS_INCLUDED

class PauseMenu 
{
	private:
		int highlight_x, highlight_y, ymax, ymin;
	public:
		PauseMenu();
		int ReadInput(int input);
		void Draw();
		void HighlightDraw();
};
#endif
