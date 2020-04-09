#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>  //TESTE
#define DEBUG(X) std::cout << #X << std::endl;  //TESTE

namespace{
  std::string valores = "";
  std::string entrada = "", tipo = "", parametro = "";
  std::string equacao1 = "", equacao2 = "";
  std::string limites = "";
  std::string cor = "";
};

class Mult_Func: public Fl_Window{
public:
  Mult_Func(int x, int y, int w, int h, const char* nome = 0)
    :Fl_Window(x, y, w, h, nome){}
  ~Mult_Func(){}
  Fl_Input* entrada = new Fl_Input(80, 10, 320, 25, "Equações: ");
  Fl_Button* adicionar = new Fl_Button(410, 10, 70, 25, "Adicionar");
  Fl_Button* desenhar = new Fl_Button(230, 85, 70, 25, "Desenhar");
  Fl_Text_Display* saida = new Fl_Text_Display(10, 45, 470, 30);
  friend void adicionar_cb();
};

Mult_Func funcs(500, 250, 500, 120);

void parser_dados();
std::string parser_limite();
void adicionar_cb();
void desenhar_cb();
void escreve_dados();

//##############################################################################
int main(){
  remove("multiplas_funcoes.txt");

  funcs.adicionar->callback((Fl_Callback*)adicionar_cb);
  funcs.desenhar->callback((Fl_Callback*)desenhar_cb);
  funcs.show();
  funcs.end();
  Fl::run();
}
//##############################################################################

void adicionar_cb(){
  //valores = valores + "\n" + std::string(funcs.entrada->value());
  valores = std::string(funcs.entrada->value());
  funcs.entrada->value(0);
  Fl_Text_Buffer* buff = new Fl_Text_Buffer(100);
  buff->text(valores.c_str());
  funcs.saida->buffer(buff);
}

void parser_dados(){
  std::string* arr[] = {&tipo, &parametro, &equacao1, &equacao2, &limites, &cor}; //tamanho = 6
  std::string arr_provisorio[6];
  int contador = 0;
  std::istringstream teste(valores);
  std::string leitura;

  while(std::getline(teste, leitura)){
    std::cout << leitura << std::endl;
    if(leitura.size()==0) continue;
    else{
      for(int clk = 0; clk < leitura.size(); clk++){
        if(leitura[clk]==';' and contador!=6) {contador++;}
        else if(leitura[clk]==';' and contador==6) {break;}
        else if(leitura[clk]==' ') {continue;}
        else{
          arr_provisorio[contador].push_back(leitura[clk]);
        }
      }
    }
    if(arr_provisorio[0]=="param"){
      for(int clk = 0; clk < 6; clk++)
        *arr[clk] = arr_provisorio[clk];
    }
    else if(arr_provisorio[0]=="cart" or arr_provisorio[0]=="polar"){
      *arr[0] = arr_provisorio[0];
      *arr[1] = arr_provisorio[1];
      *arr[2] = arr_provisorio[2];
      *arr[4] = arr_provisorio[3];
      *arr[5] = arr_provisorio[4];
    }
    for(int clk = 0; clk < 6;  clk++)
      arr_provisorio[clk] = "";
    escreve_dados();
    contador = 0;
  }
}

std::string parser_limite(std::string eval){
  std::string limite1 = "", limite2 = "";
  std::string array[] = {limite1, limite2};
  int contador = 0;
  for(int clk = 0; clk < eval.size(); clk++){
    if(eval[clk]==',' and contador!=2) contador++;
    else if(eval[clk]==',' and contador==2) break;
    else if(eval[clk]==' ') continue;
    else if (isdigit(eval[clk]) or eval[clk]=='.'){
      array[contador].push_back(eval[clk]);
    }
  }
  std::string saida = array[0] + " " + array[1];
  return saida;
}

void escreve_dados(){
  std::ofstream ofs("multiplas_funcoes.txt", std::ios::out|std::ios::app);
  ofs << cor << "\n";
  ofs << tipo << "\n";
  ofs << parametro << "\n";
  ofs << equacao1 << "\n";
  ofs << equacao2 << "\n";
  ofs << parser_limite(limites) << "\n";
  ofs.close();
}

void desenhar_cb(){
  parser_dados();
  std::string escriba = std::string(get_current_dir_name()) + "/escriba.out";
  system(escriba.c_str());
  exit(0);
}
