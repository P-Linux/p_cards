// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "flcards.h"

void Quitter_CB(Fl_Widget*,void*) {
  if (fl_ask("Do you want to quit the application Yes/No") )
  	exit(0);
}

Fl_Menu_Item menu_[] = {
 {"Actions", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Synchronize", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Quit", 0,  (Fl_Callback*)Quitter_CB, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Information", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Paquets diponibles", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Paquets install\303\251s", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"About", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

void Selectionner_CB(Fl_Widget *W, void *v)
{
	 fl_alert("callback receive!");
}
int main(int argc, char **argv) {
	Fl_Double_Window  win(900, 900);
	Fl_Input* Recherche = new Fl_Input(MARGIN+80, MARGIN, 499, 24, "Search:");
	Recherche->labelfont(2);
	Fl_Menu_Bar* BarMenu = new Fl_Menu_Bar(0, 0, 900, 20);
	BarMenu->menu(menu_);
	new Fl_Text_Display(MARGIN, 600, win.w()-MARGIN*2, 300-MARGIN, "Info about the selected package:");
	new Fl_Button(760, 820, 100, 40, "INSTALL");	
	Tableau list(MARGIN, MARGIN+40, win.w()-MARGIN*2, win.h()-400);
	list.selection_color(FL_YELLOW);
	list.col_header(1);
	list.col_resize(1);
	list.when(FL_WHEN_RELEASE);
	list.load_command(CMD);
	list.row_height_all(18);
	list.tooltip("Click on the header of the column to sort it");
	list.color(FL_WHITE);
	list.callback(Selectionner_CB,0);
	win.show(argc, argv);
	win.end();
	win.resizable(list);
	list.resize_window();
  	return Fl::run();
}
