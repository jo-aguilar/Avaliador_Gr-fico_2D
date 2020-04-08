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
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Output.H>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
using namespace std;
#define DEBUG(X) cout << #X << endl;

void exit_handle1(){
  ofstream ofs("coordenadas.txt", ios_base::out|ios_base::trunc);
  ofs.close();
}

namespace{
  int escala = 20; //pixels
  double limite_superior = 0;
  double limite_inferior = 0;
  int centrox = 502, centroy = 255;
  int ck1 = 0, ck2 = 0, ck3 = 0;
  string diretorio = string(get_current_dir_name());
};

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

void fechar_cb();
void mult_f_cb();
void muda1();
void muda2();
void muda3();
void grafico_cb();

Fl_Menu_Item menu[] = {
  {"Janela", 0, 0, 0, FL_SUBMENU},
    {"Múltiplas Equações", 0, (Fl_Callback*)mult_f_cb, 0},
    {"&Fechar", FL_CTRL + 'f', (Fl_Callback*)fechar_cb, 0},
    {0},
  {0}
};

Janela janela(1025, 650, "Hipatia - Avaliador Gráfico de Funções");
  Janela::Grafico graf(janela);
    Fl_Menu_Bar* barra = new Fl_Menu_Bar(2, 1, 1025, 20);

//#####################################################################
int main(){
  atexit(exit_handle1);
  barra->copy(menu);
  Janela::Grafico graf(janela);
  janela.check1->callback((Fl_Callback*)muda1);
  janela.check2->callback((Fl_Callback*)muda2);
  janela.check3->callback((Fl_Callback*)muda3);
  graf.gerar->callback((Fl_Callback*)grafico_cb);
  janela.resizable(janela);
  janela.end();
  janela.show();
  return(Fl::run());
}
//#####################################################################

//############################  FUNÇÕES PARA MÚLTIPLAS EQUAÇÕES ###################################
void fechar_cb(){exit(0);}

void mult_f_cb(){  //verificar se funciona
  string endereco = diretorio + "/geomatra";
  system(endereco.c_str());
  graf.desenha_func();
  graf.redraw();
  janela.redraw();
  Fl::run();
}

//####################################  FUNÇÕES GERAIS ############################################
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
}   //FUNCIONA POR DEFINIÇÃO
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
}   //FUNCIONA POR DEFINIÇÃO
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
}   //FUNCIONA POR DEFINIÇÃO
void grafico_cb(){
  /* Assegura-se de que todos os dados fundamentais foram coletados da janela principal do programa
  e as passa para o objeto da janela de desenho, avaliando o modo como as funções serão desenhadas,
  suas variáveis e seus limites, e então faz a chamada para o desenho da função*/
  graf.passa_valores(janela);
  string arquivo = diretorio + "/escriba.out";
  system(arquivo.c_str());
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
void Janela::Grafico::passa_valores(const Janela& jan){
  /* Passa os valores tanto para as variáveis gerais dentro do próprio arquivo, tanto quanto para
  o arquivo funcoes.txt, que detém as variáveis, limites e tipo da função a ser desenhada, para que
  seus valores sejam avaliados pelo módulo escriba.out e transformados em valores contínuos de uma
  função, para ser, então, desenhada*/
 check1 = jan.check1->value(); check2 = jan.check2->value(); check3 = jan.check3->value();
 parametro1 = string(jan.parametro1->value()); parametro2 = string(jan.parametro2->value()); parametro3 = string(jan.parametro3->value());
 equacao1 = jan.equacao1->value(); equacao2 = jan.equacao2->value(); equacao3 = jan.equacao3->value(); equacao4 = jan.equacao4->value();
 inferior = jan.inferior->value(); superior = jan.superior->value();
  ofstream ofs("funcao.txt");
  ofs << (int)jan.check1->value() << endl << (int)jan.check2->value() << endl << (int)jan.check3->value() << endl
   << string(jan.parametro1->value()) << endl << string(jan.parametro2->value()) << endl << string(jan.parametro3->value()) << endl
   << jan.equacao1->value() << endl << jan.equacao2->value() << endl << jan.equacao3->value() << endl << jan.equacao4->value() << endl
   << jan.inferior->value() << endl << jan.superior->value() << endl;
  ofs.close();
}
void Janela::Grafico::draw(){
  /* Desenha o objeto gráfico, e, posteriormente, quando os dados são inseridos no arquivo coordenadas.txt
  o objeto gráfico é redesenhado com os valores coniderados no arquivo, criando e mostrando a curva de
  acordo com os dados fornecidos pelo usuário*/
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
} //FUNCIONA POR DEFINIÇÃO
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
void Janela::Grafico::desenha_func(){
  /* Funciona desenhando o gráfico de acordo com os dados contidos dentro do arquivo coordenadas.txt */
  ifstream ifs("coordenadas.txt");
  string extrator = "";

  while(!ifs.eof()){
    double array[4];
    int count_array = 0;
    string saida = "";
    getline(ifs, saida);
    istringstream ss(saida);

    if(saida=="preto") {fl_color(FL_BLACK);}
    else if(saida=="vermelho") {fl_color(FL_RED);}
    else if(saida=="verde") {fl_color(FL_GREEN);}
    else if(saida=="magenta") {fl_color(FL_MAGENTA);}
    else if(saida=="azul") {fl_color(FL_BLUE);}

    while(ss>>extrator){
        array[count_array++] = stod(extrator);
      }
      fl_line(centrox + escala*array[0],
        centroy - escala*array[1],
        centrox + escala*array[2],
        centroy - escala*array[3]);
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
