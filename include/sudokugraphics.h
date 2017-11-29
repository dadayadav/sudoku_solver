#ifndef SUDOKUGRAPHICS_H
#define SUDOKUGRAPHICS_H
	struct globule
	{
	  cairo_surface_t *image;  
	} glob;

	const char* getString(int num);
	void drawMark(int num, int row, int col, double red, struct globule glob);
	void fillDefault(int grid[][9], double red, struct globule glob);
#endif
