#include <iostream>
#include <fstream> // para ler e escrever arquivo
#include <string.h>
#include <stdlib.h> //Limpar tela - usando: system("CLS");
#include <stdio.h>
#include "Review.h"
#include <fstream>
#include<bits/stdc++.h>
using namespace std;



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

int nmRegistrosReviews(ifstream &arq){

    if(arq.is_open()){

        arq.seekg(0, ios_base::end);
        int tam = int(arq.tellg()/sizeof(Review));
        return tam;

    }else{

        cout << "Erro no retorno da quantidades de elementos salvos" << endl;
        return -1;

    }

}

Review *leituraLinha(string linha){
    Review *review = new Review();

    string temp; // temporario
    int campo = 0;
    bool ignorarVirgula = false;

    for (int i=0; i < linha.size(); i++){

        // SOMENTE ID
        if(campo == 0){
            for(int i=0; i < REVIEW_ID_SIZE; i++){
                temp += linha[i];
            }
            review->setId(temp);
            temp = "";
            campo++;
            i = REVIEW_ID_SIZE; // i = 89, que em todos reviews será a posição da virgula, mas será ignorada logo em seguida pois o for aumenta em +1
        }

        else{
            // SOMENTE CAMPO 1 = TEXT
            if (campo == 1){

                if(linha[i] == '"'){
                    temp += linha[i];

                    if (!ignorarVirgula){
                        ignorarVirgula = true;
                    }

                    if(linha[i+1] == ',' && isdigit(linha[i+2])){ // pois pode haver um text do tipo alguma coisa ",,alguma coisa
                        review->setText(temp);
                        campo++;
                        temp = "";
                    }
                }

                else{
                    if(!ignorarVirgula && linha[i] == ','){
                        review->setText(temp);
                        campo++;
                        temp = "";
                    }
                    else{
                        temp += linha[i];
                    }
                }

            } // FIM DA PARTE DO CAMPO 1 = TEXT


            // UPVOTES,  APPVERSION E POSTED DATE
            else{
               if(linha[i] != ','){
                    temp += linha[i];
                }
                if (linha[i] == ',' || i+1 == linha.size()){
                    if (temp != "" || temp == "" && linha[i-1] == ','){
                        if (campo == 2){
                            review->setUpVotes(temp);
                        }
                        if (campo == 3){
                            review->setAppVersion(temp);
                        }
                        if (campo == 4){
                            review->setPostedDate(temp);
                        }
                        campo++;
                        temp = "";
                    }
                }
            } // FIM DO PRIMEIRO ELSE DENTRO DO ELSE PRINCIPAL
        } // FIM ELSE PRINCIPAL
    } // FIM DO LACO DOREVIEW
    return review;
} // FIM DA FUNCAO

void escreveArquivoBinario(Review review, fstream &arq_binario)
{

    if(arq_binario.is_open())
    {
        arq_binario.write(reinterpret_cast<char*>(&review), sizeof(Review));
        //cout<<"Gravando no arquivo binário"<<endl;
    }
    else{
        cout<<"O arquivo não está aberto"<<endl;
    }
}

/*void escreveArquivoBinarioString(string linha, fstream &arq_binario)
{
    if(arq_binario.is_open()){
        arq_binario.write(reinterpret_cast<char*>(&linha), sizeof(string));
    }
    else{
        cout<<"O arquivo não está aberto"<<endl;
    }
}*/

/*void escreveArquivoTxtString(string linha, fstream &arq_texto){
    if(arq_texto.is_open()){
        arq_texto.write(reinterpret_cast<char*>(&linha), sizeof(string));
    }
    else{
        cout<<"O arquivo não está aberto"<<endl;
    }
}*/
void escreveArquivoTxt(Review review, fstream &arq_texto)
{

    if(arq_texto.is_open())
    {
        arq_texto.write(reinterpret_cast<char*>(&review), sizeof(Review));
        //cout<<"Gravando no arquivo texto"<<endl;
    }
    else{
        cout<<"O arquivo não está aberto"<<endl;
    }
}

void leituraCsvEscritaBinario(string caminho){
    string nome = caminho+"tiktok_app_reviews.csv";
    ifstream arquivoEntrada;
    string linha;
    fstream arq_bin("tiktok_app_reviews.bin", ios::out | ios::binary);
    arquivoEntrada.open(nome, ios::in);
    Review *review;
    if(arquivoEntrada){
        getline(arquivoEntrada, linha);
        while(!arquivoEntrada.eof()){
            getline(arquivoEntrada, linha);
            review = leituraLinha(linha);
            if(arq_bin){
                escreveArquivoBinario(*review, arq_bin);
            }
            //review->printReview();
            delete review;
        }
    }
    else{
        return;
    }
    arquivoEntrada.close();
    arq_bin.close();
}

int main(int argc, char *argv[ ])
{
    string caminhoCsv;
    if(argv[1]){
        caminhoCsv = argv[1];
    }
    else{
        caminhoCsv = "";
    }
    return 0;
}
