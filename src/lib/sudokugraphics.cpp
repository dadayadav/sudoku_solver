#include<iostream>
#include<cairo/cairo.h>
#include<gtk/gtk.h>

struct globule
{
  cairo_surface_t *image;  
};

const char* getString(int num)
{
	char const* intToChar;
	switch(num)
 	{
 		case 1: intToChar = "1";
 		break;
 		case 2: intToChar = "2";
 		break;
 		case 3: intToChar = "3";
 		break;
 		case 4: intToChar = "4";
 		break;
 		case 5: intToChar = "5";
 		break;
 		case 6: intToChar = "6";
 		break;
 		case 7: intToChar = "7";
 		break;
 		case 8: intToChar = "8";
 		break;
 		case 9: intToChar = "9";
 		break;
 		default: intToChar = "";
 		break;
 	}
 	return intToChar;
}

void drawMark(int num, int row, int col, double red, struct globule glob) 
{ 
  cairo_t *ic;
  ic = cairo_create(glob.image);
  cairo_set_font_size(ic, 25);
  
  cairo_set_source_rgb(ic, red , 0.0 , 0.0);
  cairo_move_to(ic, 56*col+20, 56*row+40);
  cairo_show_text(ic, getString(num));
  cairo_stroke(ic); 
}

void fillDefault(int grid[][9], double red, struct globule glob)
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(grid[i][j]) drawMark(grid[i][j], i, j, red, glob); 
		}
	}
}
