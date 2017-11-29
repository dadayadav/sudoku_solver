#include <cairo/cairo.h>
#include <gtk/gtk.h>
#include <iostream>
#include "probables.h"
#include "sudokubasicoperations.h"
#include "sudokusolvingalgos.h"
#include "sudokugraphics.h"

static void do_drawing(cairo_t*);

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

int main(int argc, char *argv[])
{
	long row[9], infoGrid[81], infoGridRow[81], infoGridCol[81];
	int grid[9][9], grid2[9][9];
	struct probables* tail[9][9];
	setNull(tail);
	
	std::cout<<"Enter the values of the Sudoku:"<<std::endl;
	std::cout<<"(Enter 0 when blank)"<<std::endl;
	int i;
	for(i=0;i<9;i++)
	{
	  std::cin >> row[i];										//row[] contains 9 9-digit-long integers which are rows of sudoku
	}
	readInput(row, grid, grid2);
	probableCandidate(tail, grid);
	
	//Finding solution starts
	int counter=0;
	while(checkIfDone(grid)&&counter<1000)
	{
		createInfoGrid(infoGrid, tail, grid);
		createInfoGridRow(infoGridRow, tail, grid);
		createInfoGridColumn(infoGridCol, tail, grid);
		uniqueCandidate(infoGrid, infoGridRow, infoGridCol, tail, grid);
		soleCandidate(tail, grid);
		bcrInteraction(infoGrid, tail, grid);
		nakedPair(infoGrid, tail);
		counter++;
	}
	printGrid(grid);
	//Finding solution ends
	
	//Graphics programming started
	GtkWidget *window;
	GtkWidget *darea; 
    
	glob.image = cairo_image_surface_create_from_png("../res/sudoku.png");

	fillDefault(grid, 0.9, glob);
	fillDefault(grid2, 0.0, glob);

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
	//Graphics programming ends
  
	return 0;
}
