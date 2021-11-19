#include <iostream>
#include <fstream> // para ler e escrever arquivo
#include <string.h>
#include <stdlib.h> //Limpar tela - usando: system("CLS");
#include <stdio.h>
#include <fstream>
using namespace std;
#include <stdio.h>
#include<bits/stdc++.h>


void leituraArquivoCompleto()
{

    ifstream arquivo("tiktok_app_reviews.csv");
    string linha;
    if(arquivo.is_open()) // se o arquivo está aberto
    {
        while(!arquivo.eof()) //enquanto arquivo não termina
        {
            getline(arquivo, linha);// le os dados do arquivo
            cout<<linha<<endl;

        }
    }

    arquivo.close(); // fecha o arquivo
}


int main(int argc, char *argv[ ])
{
    return 0;
}