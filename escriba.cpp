#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include "Num_parser.h"

class Mult_Func: public Fl_Window{
public:
  Mult_Func(int x, int y, int w, int h, const char* nome = 0)
    :Fl_Window(x, y, w, h, nome){}
  ~Mult_Func(){}
  Fl_Input* entrada = new Fl_Input(80, 10, 320, 25, "Equações: ");
  Fl_Button* adicionar = new Fl_Button(410, 10, 70, 25, "Adicionar");
  Fl_Output* saida = new Fl_Output(10, 45, 470, 150);
  Fl_Button* desenhar = new Fl_Button(230, 210, 70, 25, "Desenhar");
};

Mult_Func funcs(500, 250, 500, 250);

void adicionar_cb();
void desenhar_cb();

int main(){
  funcs.show();
  funcs.end();
  Fl::run();
}
