#include "probables.h"
#include "sudokubasicoperations.h"
#include "sudokusolvingalgos.h"

#include <cairo/cairo.h>
#include <gtk/gtk.h>
#include <iostream>

struct {
  cairo_surface_t *image;  
} glob;


static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
  cairo_set_source_surface(cr, glob.image, 0, 0);
  cairo_paint(cr);    
}

static const char* getString(int num)
{
	char const* str;
	switch(num)
 	{
 		case 1: str = "1";
 		break;
 		case 2: str = "2";
 		break;
 		case 3: str = "3";
 		break;
 		case 4: str = "4";
 		break;
 		case 5: str = "5";
 		break;
 		case 6: str = "6";
 		break;
 		case 7: str = "7";
 		break;
 		case 8: str = "8";
 		break;
 		case 9: str = "9";
 		break;
 		default: str = "";
 		break;
 	}
 	return str;
}

static void draw_mark(int num, int row, int col, double red) 
{ 
  cairo_t *ic;
  ic = cairo_create(glob.image);
  cairo_set_font_size(ic, 25);
  
  cairo_set_source_rgb(ic, red , 0.0 , 0.0);
  cairo_move_to(ic, 56*col+20, 56*row+40);
  cairo_show_text(ic, getString(num));
  cairo_stroke(ic); 
}

static void fillDefault(int grid[][9], double red)
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(grid[i][j]) draw_mark(grid[i][j], i, j, red); 
		}
	}
}

int main(int argc, char *argv[])
{
	long int row[9], infoGrid[81], infoGridRow[81], infoGridCol[81];
	int grid[9][9], grid2[9][9];
	struct probables* tail[9][9];
	setNull(tail);
	
	std::cout<<"Enter the values of the Sudoku:"<<std::endl;
	std::cout<<"(Enter 0 when blank)"<<std::endl;
	int i;
	for(i=0;i<9;i++)
	{
	  std::cin >> row[i];
	}
	readInput(row, grid, grid2);
	//printGrid(grid);
	probableCandidate(tail, grid);
	int counter=0;
	while(checkIfDone(grid)&&counter<1000)
	{
		createInfoGrid(infoGrid, tail, grid);
		createInfoGridRow(infoGridRow, tail, grid);
		createInfoGridColumn(infoGridCol, tail, grid);
		//printInfoGrid(infoGrid);
		//printInfoGrid(infoGridRow);
		//printInfoGrid(infoGridCol);
		//printProbables(tail, grid);
		uniqueCandidate(infoGrid, infoGridRow, infoGridCol, tail, grid);
		soleCandidate(tail, grid);
		bcrInteraction(infoGrid, tail, grid);
		nakedPair(infoGrid, tail);
		counter++;
	}
	printGrid(grid);
	
	//-----------------------------------------------GRAPHICS AHEAD---------------------------------------------------------------//
	GtkWidget *window;
	GtkWidget *darea; 
    
	glob.image = cairo_image_surface_create_from_png("../res/sudoku.png");

	fillDefault(grid, 0.9);
	fillDefault(grid2, 0.0);

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (window), darea);

	g_signal_connect(G_OBJECT(darea), "draw", 
		G_CALLBACK(on_draw_event), NULL); 
	g_signal_connect(window, "destroy",
		G_CALLBACK (gtk_main_quit), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 504, 504); 
	gtk_window_set_title(GTK_WINDOW(window), "Sudoku");

	gtk_widget_show_all(window);

	gtk_main();

	cairo_surface_destroy(glob.image);
  
	return 0;
}
