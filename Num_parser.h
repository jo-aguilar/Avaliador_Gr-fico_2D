#ifndef NUM_PARSER_H
#define NUM_PARSER_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <math.h>
using namespace std;

class Num_parser
{
	public:
		double num_parse(string entrada);
		class Token{
			//Tokens para criacao de objetos para resolucao numerica
				double valor;
				char tipo;
				string func;
			public:
				Token():valor(0), tipo(' '), func(" "){}
				Token(double val, char tip):valor(val), tipo(tip), func(""){}
				Token(char tip):valor(0), tipo(tip), func(""){}
				Token(string ffunc):valor(0), tipo(' '), func(ffunc){}
				~Token(){}
				char retorna_tipo(){return tipo;}
				double retorna_valor(){return valor;}
				string retorna_func(){return func;}
		};

	protected:
		bool frac_par(double entrada);
		void erro(const string entrada);
		string pega_str();
		string tira_espaco(string entrada);
		void mostra_token(vector<Token>tok);
		vector<Token>gera_tok(string entrada);
		string gera_string(vector<Token>entrada);
		vector<Token>res_trig(vector<Token>ent);
		vector<Token>res_inv_trig(vector<Token>ent);
		vector<Token>res_log(vector<Token>ent);
		vector<Token>res_pot(vector<Token>ent);
		vector<Token>res_raiz(vector<Token>ent);
		vector<Token>res_mult(vector<Token>ent);
		vector<Token>res_mult_cont(vector<Token>ent);
		vector<Token>res_div(vector<Token>ent);
		vector<Token>res_bas(vector<Token>ent);
		vector<Token>res_sinal(vector<Token>ent, char sin1, char sin2);
		vector<Token>retorna_falsa_saida();
		vector<Token>res_eq_maior(vector<Token> &entrada);
		vector<Token> res_eq(string entrada, int tam2);
		double ret_res(string ent);
};

#endif
