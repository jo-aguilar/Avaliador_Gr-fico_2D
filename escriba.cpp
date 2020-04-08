#include <fstream>
#include <string>
#include <sstream>
#include "Num_parser.h"
#include <iostream>
using namespace std;
#define DEBUG(X) cout << #X << endl;

namespace{
  int ck1 = -1, ck2 = -1, ck3 = -1;
  string parametro1 = "", parametro2 = "", parametro3 = "";
  string equacao1 = "", equacao2 = "", equacao3 = "", equacao4 = "";
  double inferior = 0, superior = 0;
  string arr[8] = {"", "", "", "", "", "", "", ""};
  bool func_flag = false;
  bool mult_flag = false;
};

void le_doc(const char* nome);
void le_multi_doc(const char* nome);
void passa_valores();
string muda_var(string eq, char var, double valor);
void computa_cart(const char* nome);
void computa_polar(const char* nome);
void computa_param(const char* nome);


//###################################################
int main(){
  DEBUG(chegou em main);
  ifstream ifs("multiplas_funcoes.txt"); //verifica a existência do arquivo
  if(ifs.fail()){
    DEBUG(chegou em funcao_txt);
    func_flag = true;
    mult_flag = false;
    le_doc("funcao.txt");             //variaveis.txt é criado por hipatia para desenhar o gráfico com as vars
    passa_valores();                                     //caso não exista o documento "variaveis_multiplas.txt",
    if(ck1==1) computa_cart("coordenadas.txt");          //abre-se a leitura do documento "variaveis.txt"
    else if(ck2==1) computa_polar("coordenadas.txt");    //para sua leitura e computação normal de dados
    else if(ck3==1) computa_param("coordenadas.txt");
  } else{ //MODO DE LEITURA MÚLTIPLA
    DEBUG(chegou em !funcao_txt);
    func_flag = false;
    mult_flag = true;
    ifs.close();  //vai ser reaberto dentro da função
    le_multi_doc("multiplas_funcoes.txt");          //criado com os parametros fornecidos pelo geomatra
  }
  remove("funcao.txt");
  remove("multiplas_funcoes.txt");
}
//###################################################

void le_multi_doc(const char* nome){ //MODO DE LEITURA MÚLTIPLA

  DEBUG(chegou em le_mult_doc);
  ifstream ifs(nome);
  ofstream ofs("coordenadas.txt", ios_base::out|ios_base::app);
  //ofstream ofs("coordenadas.txt", ios_base::out|ios_base::app); //
  string entrada = "";
  int contador = 0;
  while(!ifs.eof()){
    getline(ifs, entrada);
    if(entrada=="preto" or entrada=="verde" or entrada=="azul" or entrada=="vermelho" or entrada=="magenta"){
      ofs << entrada << endl;
      if(contador>0) passa_valores();
      contador = 0;
    }
    else if(entrada=="cart") {arr[0]="1"; arr[1]="0"; arr[2]="0"; contador = 3;}
    else if(entrada=="polar") {arr[0]="0"; arr[1]="1"; arr[2]="0"; contador = 3;}
    else if(entrada=="param") {arr[0]="0"; arr[1]="0"; arr[2]="1"; contador = 3;}
    else{arr[contador++] = entrada;}
  }
  passa_valores();
  if(ck1==1) computa_cart("coordenadas.txt");
  else if(ck2==1) computa_polar("coordenadas.txt");
  else if(ck3==1) computa_param("coordenadas.txt");
  ofs.close();
  ifs.close();
}

void le_doc(const char* nome){
  DEBUG(chegou em le_doc);
  ifstream ifs(nome); //variaveis.txt
  string entrada = "";
  int contador = 0;
  while(!ifs.eof()){
    getline(ifs, entrada);
    if(entrada.size()>0)
      arr[contador++] = entrada;
  }
  ifs.close();
}

void passa_valores(){
  DEBUG(chegou em passa_valores);
  ck1 = stoi(arr[0]);
  ck2 = stoi(arr[1]);
  ck3 = stoi(arr[2]);
  if(ck1==1) parametro1 = arr[3][0];
  else if(ck2==1) parametro2 = arr[3][0];
  else if(ck3==1) parametro3 = arr[3][0];

  if(ck1==1) equacao1 = arr[4];
  else if(ck2==1) equacao2 = arr[4];
  else if(ck3==1){
    equacao3 = arr[4];
    equacao4 = arr[5];
  }

  int contador = 6;
  istringstream is(arr[6]);
  string pass = "";
  while(is>>pass){ arr[contador++] = pass;}

  if(func_flag==true){ //funcionamento para funções regulares
    if(ck1==1 or ck2==1){
      inferior = stod(arr[5]);
      superior = stod(arr[6]);
    }
    else if(ck3==1){
      inferior = stod(arr[6]);
      superior = stod(arr[7]);
    }
  }
  if(mult_flag==true){  //funcionamento para funções múltiplas
    inferior = stod(arr[6]);
    superior = stod(arr[7]);
  }
}

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

void computa_cart(const char* nome){
  DEBUG(chegou em computa_cart);
  fstream ofs;
  if(func_flag==true) ofs.open(nome, ios::out);
  if(mult_flag==true) ofs.open(nome, ios::out|ios::app);

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

void computa_polar(const char* nome){
  DEBUG(chegou em computa_polar);
  fstream ofs;
  if(func_flag==true) ofs.open(nome, ios::out);
  if(mult_flag==true) ofs.open(nome, ios::out|ios::app);

  Num_parser nu;
  string nova_entrada = equacao2;
  double x_anterior = nu.num_parse(muda_var(nova_entrada, parametro2[0], inferior))*cos(inferior);
  double y_anterior = nu.num_parse(muda_var(nova_entrada, parametro2[0], inferior))*sin(inferior);
  for(double clk = inferior; clk <= superior; clk+=0.05){
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
void computa_param(const char* nome){
  DEBUG(chegou em computa_param);
  fstream ofs;
  if(func_flag==true) ofs.open(nome, ios::out);
  if(mult_flag==true) ofs.open(nome, ios::out|ios::app);

  Num_parser nu_x;
  Num_parser nu_y;
  string entrada_x = equacao3;
  string entrada_y = equacao4;
  double x_anterior = nu_x.num_parse(muda_var(entrada_x, parametro3[0], inferior));
  double y_anterior = nu_y.num_parse(muda_var(entrada_y, parametro3[0], inferior));
  for(double clk = inferior; clk <= superior; clk+=0.05){
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
