#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Num_parser.h"
using namespace std;

namespace{
  int escala = 20; //pixels
  double limite_superior = 0;
  double limite_inferior = 0;
  int centrox = 502, centroy = 255;
  int ck1 = 0, ck2 = 0, ck3 = 0;
};

string muda_var(string eq, char var, double valor){
  //find the variables and change them for numbers in the string
  //CENTRO EM (X, Y) = (502, 255)
  string res = eq;
  for(int clk = 0; clk < res.size(); clk++){
    if(res[clk]==var){
      if(valor>=0) res = res.substr(0, clk) + to_string(valor) + res.substr(clk+1, res.size()-1);
      else res = res.substr(0, clk) + "-" + to_string(abs(valor)) + res.substr(clk+1, res.size()-1);
    }
  }
  return res;
}

class Janela: public Fl_Double_Window{
public:
  Janela(int x, int y, const char* nome): Fl_Double_Window(200, 100, x, y, nome){}
  ~Janela(){}
  Fl_Round_Button* check1 = new Fl_Round_Button (20, 510, 100, 30, "Cartesiano");
  Fl_Round_Button* check2 = new Fl_Round_Button(350, 510, 100, 30, "Polar");
  Fl_Round_Button* check3 = new Fl_Round_Button(680, 510, 100, 30, "Paramétrico");
  Fl_Input* parametro1 = new Fl_Input(210, 515, 60, 20, "Parâmetro: ");
  Fl_Input* parametro2 = new Fl_Input(510, 515, 60, 20, "Parâmetro: ");
  Fl_Input* parametro3 = new Fl_Input(880, 515, 60, 20, "Parâmetro: ");
  Fl_Input* equacao1 = new Fl_Input(90, 540, 250, 25, "Equação: ");
  Fl_Input* equacao2 = new Fl_Input(420, 540, 250, 25, "Equação: ");
  Fl_Input* equacao3 = new Fl_Input(760, 540, 250, 25, "Equação 1:");
  Fl_Input* equacao4 = new Fl_Input(760, 570, 250, 25, "Equação 2:");
  Fl_Counter* inferior = new Fl_Counter(200, 570, 120, 20, "Limite inferior");
  Fl_Counter* superior = new Fl_Counter(340, 570, 120, 20, "Limite superior");

  class Grafico;
  friend Grafico;
  class Grafico: public Fl_Widget{
    int check1 = 0, check2 = 0, check3 = 0;
    string parametro1 = "", parametro2 = "", parametro3 = "";
    string equacao1 = "", equacao2 = "", equacao3 = "", equacao4 = "";
    double inferior = 0.0, superior = 0.0;
    int centro_x = 0, centro_y = 0;
  public:
    Grafico(const Janela& jan):
      Fl_Widget(10, 30, jan.w()-20, jan.h()-200, 0), centro_x(int(w())/2), centro_y(int(h())/2){}
    ~Grafico(){}
    Fl_Button* gerar = new Fl_Button(490, 615, 110, 25, "&Gerar gráfico");
    void passa_valores(const Janela& jan);
    void eixo_x(int pos1, int x_pos, int y_pos);
    void eixo_y(int pos2, int x_pos, int y_pos);
    void computa_cart();
    void computa_polar();
    void computa_param();
    void desenha_func();

    friend void grafico_cb();
    void draw();
  protected:
    int handle(int e);
  };
  friend void muda1();
  friend void muda2();
  friend void muda3();
};
Janela janela(1025, 650, "Avaliador de Funções");
Janela::Grafico graf(janela);

void muda1(){
  if(janela.check1->value()==1){
    janela.parametro1->color(FL_WHITE);
    janela.parametro1->readonly(0);
    janela.equacao1->color(FL_WHITE);
    janela.equacao1->readonly(0);      janela.check2->value(0);
    janela.parametro2->color(FL_GRAY); janela.parametro2->value(0);
    janela.equacao2->color(FL_GRAY);   janela.equacao2->value(0);
    janela.parametro2->readonly(1);
    janela.equacao2->readonly(1);      janela.check3->value(0);
    janela.parametro3->color(FL_GRAY); janela.parametro3->value(0);
    janela.equacao3->color(FL_GRAY);   janela.equacao3->value(0);
    janela.equacao4->color(FL_GRAY);   janela.equacao4->value(0);
    janela.parametro3->readonly(1);
    janela.equacao3->readonly(1);
    janela.equacao4->readonly(1);
    janela.redraw();
    ck1 = 1; ck2 = 0; ck3 = 0;
  }
}
void muda2(){
  if(janela.check2->value()==1){
    janela.parametro2->color(FL_WHITE);
    janela.parametro2->readonly(0);
    janela.equacao2->color(FL_WHITE);
    janela.equacao2->readonly(0);       janela.check1->value(0);
    janela.parametro1->color(FL_GRAY);  janela.parametro1->value(0);
    janela.equacao1->color(FL_GRAY);    janela.equacao1->value(0);
    janela.parametro1->readonly(1);
    janela.equacao1->readonly(1);       janela.check3->value(0);
    janela.parametro3->color(FL_GRAY);  janela.parametro3->value(0);
    janela.equacao3->color(FL_GRAY);
    janela.equacao4->color(FL_GRAY);
    janela.parametro3->readonly(1);
    janela.equacao3->readonly(1);       janela.equacao3->value(0);
    janela.equacao4->readonly(1);       janela.equacao4->value(0);
    janela.redraw();
    ck1 = 0; ck2 = 1; ck3 = 0;
  }
}
void muda3(){
  if(janela.check3->value()==1){
    janela.parametro3->color(FL_WHITE);
    janela.parametro3->readonly(0);
    janela.equacao3->color(FL_WHITE);
    janela.equacao4->color(FL_WHITE);
    janela.equacao3->readonly(0);
    janela.equacao4->readonly(0);        janela.check1->value(0);
    janela.parametro1->color(FL_GRAY);
    janela.equacao1->color(FL_GRAY);
    janela.parametro1->readonly(1);      janela.parametro1->value(0);
    janela.equacao1->readonly(1);        janela.equacao1->value(0);
    janela.check2->value(0);
    janela.parametro2->color(FL_GRAY);
    janela.equacao2->color(FL_GRAY);     janela.equacao2->value(0);
    janela.parametro2->readonly(1);     janela.parametro2->value(0);
    janela.equacao2->readonly(1);
    janela.redraw();
    ck1 = 0; ck2 = 0; ck3 = 1;
  }
}
void Janela::Grafico::passa_valores(const Janela& jan){
  check1 = jan.check1->value(); check2 = jan.check2->value(); check3 = jan.check3->value();
  parametro1 = string(jan.parametro1->value()); parametro2 = string(jan.parametro2->value()); parametro3 = string(jan.parametro3->value());
  equacao1 = jan.equacao1->value(); equacao2 = jan.equacao2->value(); equacao3 = jan.equacao3->value(); equacao4 = jan.equacao4->value();
  inferior = jan.inferior->value(); superior = jan.superior->value();
  if(check1==1) computa_cart();
  else if(check2==1) computa_polar();
  else if(check3==1) computa_param();
}
void Janela::Grafico::draw(){
  fl_color(FL_WHITE);
  fl_rectf(x(), y(), w(), h());
  limite_superior = max(inferior, superior);
  limite_inferior = min(inferior, superior);
  eixo_x(10, centroy, w()+10);
  eixo_y(30, centrox, h());

  fl_color(FL_BLUE);

  desenha_func();
}
void Janela::Grafico::eixo_x(int pos1, int x_pos, int y_pos){
  fl_color(FL_BLACK);
  fl_line(pos1, x_pos, y_pos, x_pos); //eixo
  fl_line(pos1, x_pos, pos1+5, x_pos+5);
  fl_line(pos1, x_pos, pos1+5, x_pos-5);
  fl_line(y_pos, x_pos, y_pos-5, x_pos-5);
  fl_line(y_pos, x_pos, y_pos-5, x_pos+5);

  for(int clk = centrox; clk <= y_pos; clk+=escala)
    fl_line(clk, x_pos-3, clk, x_pos+3);
  for(int clk = centrox; clk >= 10; clk-=escala)
    fl_line(clk, x_pos-3, clk, x_pos+3);
}
void Janela::Grafico::eixo_y(int pos2, int x_pos, int y_pos){
  fl_color(FL_BLACK);
  fl_line(x_pos, pos2, x_pos, y_pos + pos2);
  fl_line(x_pos, pos2, x_pos-5, pos2+5);
  fl_line(x_pos, pos2, x_pos+5, pos2+5);
  fl_line(x_pos, pos2+y_pos, x_pos-5, y_pos-5+pos2);
  fl_line(x_pos, pos2+y_pos, x_pos+5, y_pos-5+pos2);

  for(int clk = centroy; clk <= x_pos-10; clk+=escala)
    fl_line(x_pos-3, clk, x_pos+3, clk);
  for(int clk = centroy; clk >= 30; clk-=escala)
    fl_line(x_pos-3, clk, x_pos+3, clk);
}

void Janela::Grafico::computa_cart(){  //NOVO CÓDIGO
  ofstream ofs("coordenadas.txt");
  Num_parser nu;
  string nova_entrada = equacao1;

  double x_anterior = inferior;
  double y_anterior = nu.num_parse(muda_var(nova_entrada, parametro1[0], inferior));
  for(double clk = inferior; clk <= superior; clk+=0.05){
    string saida = muda_var(nova_entrada, parametro1[0], clk);
    double x_atual = clk;
    double y_atual = nu.num_parse(saida);
    ofs << x_anterior << " " << y_anterior << " " << x_atual << " " << y_atual << endl;
    y_anterior = y_atual;
    x_anterior = x_atual;
  }
  ofs.close();
}
void Janela::Grafico::computa_polar(){  //NOVO CÓDIGO
  ofstream ofs("coordenadas.txt");
  Num_parser nu;
  string nova_entrada = equacao2;

  double x_anterior = nu.num_parse(muda_var(nova_entrada, parametro2[0], limite_inferior))*cos(limite_inferior);
  double y_anterior = nu.num_parse(muda_var(nova_entrada, parametro2[0], limite_inferior))*sin(limite_inferior);
  for(double clk = limite_inferior; clk <= limite_superior; clk+=0.05){
    string saida = muda_var(nova_entrada, parametro2[0], clk);
    double raio = (nu.num_parse(muda_var(nova_entrada, parametro2[0], clk)));
    double x_atual = raio*cos(clk);
    double y_atual = raio*sin(clk);
    ofs << x_anterior << " " << y_anterior << " " << x_atual << " " << y_atual << endl;
    y_anterior = y_atual;
    x_anterior = x_atual;
  }
  ofs.close();
}
void Janela::Grafico::computa_param(){  //NOVO CÓDIGO
  ofstream ofs("coordenadas.txt");
  Num_parser nu_x;
  Num_parser nu_y;
  string entrada_x = equacao3;
  string entrada_y = equacao4;

  double x_anterior = nu_x.num_parse(muda_var(entrada_x, parametro3[0], limite_inferior));
  double y_anterior = nu_y.num_parse(muda_var(entrada_y, parametro3[0], limite_inferior));
  for(double clk = limite_inferior; clk <= limite_superior; clk+=0.05){
    string saida_x = muda_var(entrada_x, parametro3[0], clk);
    string saida_y = muda_var(entrada_y, parametro3[0], clk);
    double x_atual = nu_x.num_parse(saida_x);
    double y_atual = nu_y.num_parse(saida_y);
    ofs << x_anterior << " " << y_anterior << " " << x_atual << " " << y_atual << endl;
    y_anterior = y_atual;
    x_anterior = x_atual;
  }
  ofs.close();
}

void Janela::Grafico::desenha_func(){
  ifstream ifs("coordenadas.txt");
  string extrator = "";

  while(!ifs.eof()){
    double array[4];
    int count_array = 0;
    string saida = "";
    getline(ifs, saida);
    istringstream ss(saida);
    while(ss>>extrator){
      array[count_array] = stod(extrator);
      count_array++;
    }
    fl_line(centrox + escala*array[0],
            centroy - escala*array[1],
            centrox + escala*array[2],
            centroy - escala*array[3]);
  }
}

void grafico_cb(){
  graf.passa_valores(janela);
  graf.check1 = ck1;
  graf.check2 = ck2;
  graf.check3 = ck3;
  if(graf.check1==graf.check2==graf.check3==0) fl_choice("Um modo de equação \n deve ser escolhido", "OK", 0, 0);
  else{
    if(graf.superior==graf.inferior)
      fl_choice("Os limites da equação devem ser diferentes", "OK", 0, 0);
    else{
      if(graf.check1==1 or graf.check2==1 or graf.check3==1){
        graf.redraw();
      }
    }
  }
}
int Janela::Grafico::handle(int e){
  int event = Fl_Widget::handle(e);
  int x_inicial = 0, y_inicial = 0;
  int x = 0, y = 0;
  switch(e){
    case FL_MOUSEWHEEL:{
      if(escala>1) escala-=12*Fl::event_dy();
      graf.redraw();
      }
    case FL_PUSH:{
      x_inicial = Fl::event_x();
      y_inicial = Fl::event_y();
      return(1);
    }
    case FL_RELEASE:{
      return(1);
    }
    case FL_DRAG:{
      if(Fl::event_x()!=x_inicial){
        if(Fl::event_x()>centrox)
          centrox += 5;
        else if((Fl::event_x()<centrox))
          centrox -= 5;
        }
      if(Fl::event_y()!=y_inicial){
        if(Fl::event_y()>centroy)
          centroy += 5;
        else if(Fl::event_y()<centroy)
          centroy -= 5;
        }
        graf.redraw();
        return(1);
      }
    }
  }


int main(){
  Janela::Grafico graf(janela);
  janela.check1->callback((Fl_Callback*)muda1);
  janela.check2->callback((Fl_Callback*)muda2);
  janela.check3->callback((Fl_Callback*)muda3);
  graf.gerar->callback((Fl_Callback*)grafico_cb);
  janela.end();
  janela.show();
  Fl::run();
}
