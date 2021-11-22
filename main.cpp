#include <iostream>
#include <fstream> // para ler e escrever arquivo
#include <string.h>
#include <stdlib.h> //Limpar tela - usando: system("CLS");
#include <stdio.h>
#include "Review.h"
#include <fstream>
#include <ctime>
using namespace std;



void leituraArquivoCompleto(string caminho)
{

    ifstream arquivo;
    arquivo.open(caminho+"tiktok_app_reviews.csv");
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

Review *leituraLinha(string linha){//funcao que lê uma linha e salva como review
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

void leituraCsvEscritaBinario(string caminho){ //le o arquivo .csv linha por linha,salva as linhas em um objeto review e salva no arquivo binario
    string nome = caminho+"tiktok_app_reviews.csv";
    ifstream arquivoEntrada;
    string linha;
    fstream arq_bin(caminho+"tiktok_app_reviews.bin", ios::out | ios::binary);
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

Review acessaRegistro(ifstream &arq, int n){ //funcao que acessa o i-esimo registro de um arquivo
    Review review;
    if(arq.is_open()){
        arq.seekg(n*sizeof(Review), ios_base::beg);
        arq.read((char *) &review,sizeof(Review));
        return review;
    }
    else{
        return review;
    }

}


Review returnVetReviews(ifstream &arq, int qtd){ //funcao que acessa n registros aleatorios(quantidade passada por parametro)

    Review *vetReviews = new Review[qtd];

    if(!arq.is_open()){
        cout << "Arquivo não aberto durante o retorno do vetor" << endl;
        return *vetReviews;
    }

    srand(time(0));//mudar os numeros sorteados
    int randN;

    if(qtd > nmRegistrosReviews(arq)){cout << "Requisição maior do que os já salvos" << endl; return *vetReviews;}

    try{

        for(int i = 0; i < qtd ;i++){
            randN = rand()%nmRegistrosReviews(arq);//soteia de 0 ao numero de Reviews - 1
            vetReviews[i] = acessaRegistro(arq, randN);
        }

    }catch(const exception& e){

        cout << "Erro ao ler n-quantidade de Reviews do arquivo";
        cout << e.what() << endl;

    }

    return *vetReviews;

}


void testeImportacao(ifstream &arq, string caminho){
    int opcao;
    int qtd;
    cout<<"Digite como deseja ler os dados do arquivo: "<<endl<<"1 para ler do console"<<endl<<"2 para salvar em um arquivo de texto"<<endl;
    cin>>opcao;
    if(opcao == 1){
        qtd = 10;
    }
    else if(opcao == 2){
        qtd = 100;
    }
    Review *reviews = new Review[qtd];
    *reviews = returnVetReviews(arq, qtd);
    if(opcao == 1){
        for(int i = 0; i<qtd; i++){
            reviews[i].printReview();
        }
    }
    else if(opcao == 2){
        fstream arq_texto;
        arq_texto.open(caminho+"tiktok_app_reviews.txt", ios::out);
        for(int i = 0; i<qtd; i++){
            escreveArquivoTxt(reviews[i], arq_texto);
        }
    }
    delete [] reviews;

}

int main(int argc, char *argv[ ])
{
    string caminho;
    if(argv[1]){
        caminho = argv[1];
    }
    else{
        caminho = "./";
    }
    int qtd;
    leituraCsvEscritaBinario(caminho);
    
    
    return 0;
}
