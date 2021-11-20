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


void leituraCsvEscritaBinario(){
    ifstream arquivoEntrada;
    string linha;
    arquivoEntrada.open("tiktok_app_reviews.csv", ios::in);
    Review *review;
    if(arquivoEntrada){
        getline(arquivoEntrada, linha);
        while(!arquivoEntrada.eof()){
            getline(arquivoEntrada, linha);
            review = leituraLinha(linha);
            review->printReview();
            delete review;
        }
    }
    else{
        return;
    }
    arquivoEntrada.close();

}

int main(int argc, char *argv[ ])
{
    return 0;
}
