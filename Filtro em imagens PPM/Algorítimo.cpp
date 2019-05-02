#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

int const DMAX=512;
int const SMAX=512;
struct Img
{
    char id[3];
    int vm;
    int c;
    int l;
    int r[DMAX][DMAX];
    int g[DMAX][DMAX];
    int b[DMAX][DMAX];
};
void abre_img(char nome[], Img& img);
void remove_ruido_mediana(Img img_in, Img& img_out);
void corta_rgb(Img img_in, Img& img_out, int li, int ci, int larg, int alt);
void reflete_horizontal_b_c(Img img_in, Img& img_out);
void reflete_horizontal_c_b(Img img_in, Img& img_out);
void reflete_vertical_d_e(Img img_in, Img& img_out);
void reflete_vertical_e_d(Img img_in, Img& img_out);
void converte_para_cinza(Img img_in, Img& img_out);
void binariza(Img img_in, Img& img_out, int limiar);
void salva_img(char nome[], Img img_out);

using namespace std;
int main()
{
    bool inicia=true;
    while(inicia==true)
    {
        int li,ci,larg,alt;
        char nome[DMAX],complemento[DMAX],abrir_funcao[DMAX];
        Img img,img_out;
        cout<<"Digite um numero correspondente ao processamento que queira realizar:\n\n";
        cout<<"[1] Cortar imagem\n"<<"[2] Remover ruido\n"<<"[3] Refletir imagem verticalmente\n"<<"[4] Refletir imagem horizontalmente\n"<<"[5] Conversao para niveis de cinza\n"<<"[6] Binarizacao de imagem (por canal) \n"<<"[7] Sair \n";
        cin.getline(abrir_funcao,DMAX);
        while((abrir_funcao[0]!='1' && abrir_funcao[0]!='2' && abrir_funcao[0]!='3' && abrir_funcao[0]!='4' && abrir_funcao[0]!='5' && abrir_funcao[0]!='6' && abrir_funcao[0]!='7')|| abrir_funcao[1]!='\0')
        {
            system("cls");
            cout<<"Comandos disponiveis -> '1' ,'2' ,'3', '4', '5', '6', '7'\n\n";
            cout<<"[1] Cortar imagem\n"<<"[2] Remover ruido\n"<<"[3] Refletir imagem verticalmente\n"<<"[4] Refletir imagem horizontalmente\n"<<"[5] Conversao para niveis de cinza\n"<<"[6] Binarizacao de imagem (por canal \n"<<"[7] Sair \n";
            cin.getline(abrir_funcao,DMAX);
        }
        system("cls");
        if(abrir_funcao[0]=='7')
        {
            inicia=false;
            break;
        }
        cout<<"Digite o nome do arquivo a ser aberto: \n";
        cin.getline(nome,DMAX);
        abre_img(nome,img);
        //chamar funcao de cortar imagem
        if(abrir_funcao[0]=='1')
        {
            cout<<"Informe a linha (de 0 a "<<img.l-1<<")"<<endl;
            cin>>li;
            while(li<0 || li>img.l-1)
            {

                cout<<"digite uma opcao de linha correta (de 0 a "<<img.l-1<<")"<<endl;
                cin>>li;
            }
            cout<<"Informe a coluna (de 0 a "<<img.c-1<<")"<<endl;
            cin>>ci;
            while(ci<0 || ci>img.c-1)
            {
                ;
                cout<<"digite uma opcao de coluna correta (de 0 a "<<img.c-1<<")"<<endl;;
                cin>>ci;
            }
            cout<<"Informe a largura (tamanho maximo de "<<img.c-ci<<")"<<endl;
            cin>>larg;
            while(larg<1 || larg>img.c-ci)
            {

                cout<<"digite uma largura correta (tamanho maximo de "<<img.c-ci<<")"<<endl;
                cin>>larg;
            }
            cout<<"Informe a altura (tamanho maximo de "<<img.l-li<<")"<<endl;
            cin>>alt;
            while(alt<1 || alt>img.l-li)
            {

                cout<<"digite uma altura correta (tamanho maximo de "<<img.l-li<<")"<<endl;
                cin>>alt;
            }
            corta_rgb(img,img_out,li,ci,larg,alt);
            char cortado[]="_cortado.ppm";
            //nomeando o arquivo de saida
            for(int i=0,j=0; cortado[j]!='\0'; i++)
            {
                if(nome[i]=='.')
                {
                    for(  ; cortado[j]!='\0'; j++,i++)
                    {
                        nome[i]=cortado[j];
                    }
                    nome[i]=='\0';
                }
            }
            salva_img(nome,img_out);
            cin.ignore();
        }
        // chamar funcao de remover ruido com mediana
        if(abrir_funcao[0]=='2')
        {
            remove_ruido_mediana(img,img_out);
            char sem_ruido[]="_sem_ruido.ppm";
            for(int i=0,j=0; sem_ruido[j]!='\0'; i++)
            {
                if(nome[i]=='.')
                {
                    for(  ; sem_ruido[j]!='\0'; j++,i++)
                    {
                        nome[i]=sem_ruido[j];
                    }
                    nome[i]=='\0';
                }
            }
            salva_img(nome,img_out);
        }
        // chamar funcao de refletir verticalmente
        if(abrir_funcao[0]=='3')
        {
            char ref_vert[SMAX];
            cout<<"Digite qual tipo de reflexao\n\n";
            cout<<"[1] Da esquerda para direita \n"<<"[2] Da direita para esquerda\n";
            cin.getline(ref_vert,SMAX);
            while((ref_vert[0]!='1' && ref_vert[0]!='2') || ref_vert[1]!='\0')
            {
                 cout<<"Comandos disponiveis -> '1' e '2' \n\n";
                 cin.getline(ref_vert,SMAX);
            }
            if(ref_vert[0]=='1')
            {
                reflete_vertical_e_d(img,img_out);
                char refletida_e_d[]="_refletida_e_d.ppm";
                for(int i=0,j=0; refletida_e_d[j]!='\0'; i++)
                {
                    if(nome[i]=='.')
                    {
                        for(  ; refletida_e_d[j]!='\0'; j++,i++)
                        {
                            nome[i]=refletida_e_d[j];
                        }
                        nome[i]=='\0';
                    }
                }
                salva_img(nome,img_out);
            }
            else
            {
                reflete_vertical_d_e(img,img_out);
                char refletida_d_e[]="_refletida_d_e.ppm";
                for(int i=0,j=0; refletida_d_e[j]!='\0'; i++)
                {
                    if(nome[i]=='.')
                    {
                        for(  ; refletida_d_e[j]!='\0'; j++,i++)
                        {
                            nome[i]=refletida_d_e[j];
                        }
                        nome[i]=='\0';
                    }
                }
                salva_img(nome,img_out);
            }

        }
        // chamar funcao de refletir horizontalmente
        if(abrir_funcao[0]=='4')
        {
            char ref_horiz[SMAX];
            cout<<"Digite qual tipo de reflexao\n\n";
            cout<<"[1] De cima para baixo \n"<<"[2] De baixo para cima\n";
            cin.getline(ref_horiz,SMAX);
            while((ref_horiz[0]!='1' && ref_horiz[0]!='2') || ref_horiz[1]!='\0')
            {
                 cout<<"Comandos disponiveis -> '1' e '2' \n\n";
                 cin.getline(ref_horiz,SMAX);
            }
            if(ref_horiz[0]=='1')
            {
                reflete_horizontal_c_b(img,img_out);
                char refletida_c_b[]="_refletida_c_b.ppm";
                for(int i=0,j=0; refletida_c_b[j]!='\0'; i++)
                {
                    if(nome[i]=='.')
                    {
                        for(  ; refletida_c_b[j]!='\0'; j++,i++)
                        {
                            nome[i]=refletida_c_b[j];
                        }
                        nome[i]=='\0';
                    }
                }
                salva_img(nome,img_out);
            }
            else
            {
                reflete_horizontal_b_c(img,img_out);
                char refletida_b_c[]="_refletida_b_c.ppm";
                for(int i=0,j=0; refletida_b_c[j]!='\0'; i++)
                {
                    if(nome[i]=='.')
                    {
                        for(  ; refletida_b_c[j]!='\0'; j++,i++)
                        {
                            nome[i]=refletida_b_c[j];
                        }
                        nome[i]=='\0';
                    }
                }
                salva_img(nome,img_out);
            }
        }
        if(abrir_funcao[0]=='5')
        {
            converte_para_cinza(img,img_out);
            char cinzento[]="_cinzento.ppm";
            for(int i=0,j=0; cinzento[j]!='\0'; i++)
            {
                if(nome[i]=='.')
                {
                    for(  ; cinzento[j]!='\0'; j++,i++)
                    {
                        nome[i]=cinzento[j];
                    }
                    nome[i]=='\0';
                }
            }
            salva_img(nome,img_out);
        }
        if(abrir_funcao[0]=='6')
        {
            int limiar;
            cout<<"Digite uma limiar entre 0 e 255\n\n";
            cin>>limiar;
            while(limiar <0 && limiar >255){
                cout<<"Digite uma limiar entre 0 e 255\n\n";
                cin>>limiar;
            }
            binariza(img,img_out,limiar);
            char binarizado[]="_binarizado.ppm";
            for(int i=0,j=0; binarizado[j]!='\0'; i++)
            {
                if(nome[i]=='.')
                {
                    for(  ; binarizado[j]!='\0'; j++,i++)
                    {
                        nome[i]=binarizado[j];
                    }
                    nome[i]=='\0';
                }
            }
            salva_img(nome,img_out);
        }
        system("pause");
        system("cls");
        char continuar[SMAX];
        cout<<"Deseja continuar no programa?\n\n"<<"[1] Sim \n"<<"[2] nao \n";
        cin.getline(continuar,SMAX);
        while((continuar[0]!='1' && continuar[0]!='2') || continuar[1]!='\0')
        {
            system("cls");
            cout<<"Comandos disponiveis -> '1' e '2' \n\n";
            cout<<"Deseja continuar no programa?\n\n"<<"[1] Sim \n"<<"[2] nao \n";
            cin.getline(continuar,SMAX);
        }
        if (continuar[0]=='2')
        {
            inicia=false;
        }
        system("cls");
    }
    return 0;
}
void abre_img(char nome[], Img& img)
{
    fstream arq;
    char ext[]=".ppm";
    if((nome[strlen(nome)-1] != 'm') && (nome[strlen(nome)-2] != 'p') && (nome[strlen(nome)-3] != 'p') && (nome[strlen(nome)-4] != '.'))
    {
        arq.open(strcat(nome,ext));
    }
    else
    {
        arq.open(nome);

    }
    if(arq.is_open()==false)
    {
        cout<<"O Arquivo com o nome informado nao foi encontrado no formato '.ppm'! \n";
        exit(0);
    }
    arq.getline(img.id,3);
    if(img.id[0]!='P' || img.id[1]!='3' || img.id[2]!='\0')
    {
        cout<<"Erro ao ler arquivo! \n";
        exit(0);
    }
    arq>>img.c;
    arq>>img.l;
    arq>>img.vm;
    if(img.vm<128 || img.vm>255||img.c<1 || img.c>512||img.l<1 || img.l>512)
    {
        cout<<"Imagem nao suportada! \n";
        exit(0);
    }
    for(int i=0; i<img.l; i++)
    {
        for(int j=0; j<img.c; j++)
        {
            arq>>img.r[i][j];
            arq>>img.g[i][j];
            arq>>img.b[i][j];
        }
    }
    arq.close();

}
void corta_rgb(Img img_in, Img& img_out, int li, int ci, int larg, int alt)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = larg;
    img_out.l = alt;
    img_out.vm = img_in.vm;
    for(int i=0,p=li; i<alt; i++,p++)
    {
        for(int j=0,q=ci; j<larg; j++,q++)
        {
            img_out.r[i][j]=img_in.r[p][q];
            img_out.g[i][j]=img_in.g[p][q];
            img_out.b[i][j]=img_in.b[p][q];
        }
    }
}
void remove_ruido_mediana(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;

    int vr[9],vg[9],vb[9];
    for(int i=0; i<img_in.l; i++)
    {
        for(int j=0; j<img_in.c; j++)
        {
            //aplicando a mediana

            for(int p=0,k=0; p<3; p++)
            {
                for(int q=0; q<3; q++)
                {

                    if((i+p-1<0) || (j+q-1<0) || (i+p-1==img_in.l) || (j+q-1==img_in.c))
                    {
                        vr[k]=0;
                        vg[k]=0;
                        vb[k]=0;
                    }
                    else
                    {
                        vr[k]=img_in.r[i + p - 1][j + q - 1];
                        vg[k]=img_in.g[i + p - 1][j + q - 1];
                        vb[k]=img_in.b[i + p - 1][j + q - 1];
                    }
                    k++;
                }
            }
            //ordenar vetor
            for(int w=0; w<9; w++)
            {
                for(int z=0,aux; z<8; z++)
                {
                    if(vr[z+1]<vr[z])
                    {
                        aux=vr[z+1];
                        vr[z+1]=vr[z];
                        vr[z]=aux;
                    }
                    if(vg[z+1]<vg[z])
                    {
                        aux=vg[z+1];
                        vg[z+1]=vg[z];
                        vg[z]=aux;
                    }
                    if(vb[z+1]<vb[z])
                    {
                        aux=vb[z+1];
                        vb[z+1]=vb[z];
                        vb[z]=aux;
                    }
                }
            }
            img_out.r[i][j]=vr[4];
            img_out.g[i][j]=vg[4];
            img_out.b[i][j]=vb[4];
        }
    }
}
void reflete_vertical_e_d(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    int z;
    if (img_in.c%2==0)
    {
        z=1;
    }
    else
    {
       z=0;
    }
    for(int i=0; i<img_in.l; i++)
    {
        for(int j=0,k=(img_in.c/2)-z; j<img_in.c; j++)
        {
            if(j<img_in.c/2)
            {
                img_out.r[i][j]=img_in.r[i][j];
                img_out.g[i][j]=img_in.g[i][j];
                img_out.b[i][j]=img_in.b[i][j];
            }
            else
            {
                img_out.r[i][j]=img_in.r[i][k];
                img_out.g[i][j]=img_in.g[i][k];
                img_out.b[i][j]=img_in.b[i][k];
                k--;
            }
        }
    }
}
void reflete_vertical_d_e(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    int z;
    if (img_in.c%2==0)
    {
        z=0;
    }
    else
    {
        z=1;
    }
    for(int i=0; i<img_in.l; i++)
    {
        for(int j=0,k=(img_in.c)-1; j<img_in.c; j++)
        {
            if(j<img_in.c/2)
            {
                img_out.r[i][j]=img_in.r[i][k];
                img_out.g[i][j]=img_in.g[i][k];
                img_out.b[i][j]=img_in.b[i][k];
                k--;
            }
            else
            {

                img_out.r[i][j]=img_in.r[i][j];
                img_out.g[i][j]=img_in.g[i][j];
                img_out.b[i][j]=img_in.b[i][j];
            }
        }
    }
}
void reflete_horizontal_c_b(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    int i,j,z,k;
    if((img_in.l/2)%2==0)
    {
        z=1;
    }
    else
    {
         z=0;
    }
    for(i=0; i<img_in.l/2; i++)
    {
        for(int j=0; j<img_in.c; j++)
        {

            img_out.r[i][j]=img_in.r[i][j];
            img_out.g[i][j]=img_in.g[i][j];
            img_out.b[i][j]=img_in.b[i][j];
        }
    }
    for(k=(img_in.l/2)-z; i<img_in.l; i++,k--)
    {
        for(j=0; j<img_in.c; j++)
        {
            img_out.r[i][j]=img_in.r[k][j];
            img_out.g[i][j]=img_in.g[k][j];
            img_out.b[i][j]=img_in.b[k][j];
        }
    }
}
void reflete_horizontal_b_c(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    int i,j,z,k;
    if((img_in.l/2)%2==0)
    {
        z=0;
    }
    else
    {
         z=1;
    }
    for(i=0,k=(img_in.l)-1; i<(img_in.l/2)+z; i++,k--)
    {
        for(j=0; j<img_in.c; j++)
        {
            img_out.r[i][j]=img_in.r[k][j];
            img_out.g[i][j]=img_in.g[k][j];
            img_out.b[i][j]=img_in.b[k][j];
        }
    }
    for(; i<img_in.l; i++)
    {
        for(j=0; j<img_in.c; j++)
        {

            img_out.r[i][j]=img_in.r[i][j];
            img_out.g[i][j]=img_in.g[i][j];
            img_out.b[i][j]=img_in.b[i][j];
        }
    }
}
void converte_para_cinza(Img img_in, Img& img_out)
{
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    for(int i=0; i<img_out.l; i++)
    {
        for(int j=0,media; j<img_out.c; j++)
        {
            media=(img_in.r[i][j]+img_in.g[i][j]+img_in.b[i][j])/3;
            img_out.r[i][j]=media;
            img_out.g[i][j]=media;
            img_out.b[i][j]=media;
        }
    }

}
void binariza(Img img_in, Img& img_out, int limiar){
    img_out.id[0]='P';
    img_out.id[1]='3';
    img_out.id[2]='\0';
    img_out.c = img_in.c;
    img_out.l = img_in.l;
    img_out.vm = img_in.vm;
    for(int i=0; i<img_out.l; i++)
    {
        for(int j=0,media; j<img_out.c; j++)
        {
            media=(img_in.r[i][j]+img_in.g[i][j]+img_in.b[i][j])/3;
            if(media < limiar){
                img_out.r[i][j]=0;
                img_out.g[i][j]=0;
                img_out.b[i][j]=0;

            }
            else{
                img_out.r[i][j]=255;
                img_out.g[i][j]=255;
                img_out.b[i][j]=255;

            }

        }
    }
}
void salva_img(char nome[], Img img)
{
    ofstream arq_criado;
    arq_criado.open(nome);
    if(arq_criado.is_open()==true)
    {
        system("cls");
        cout<<"Arquivo criado com sulcesso! \n";
    }
    arq_criado<<img.id<<endl<<img.c<<" "<<img.l<<endl<<img.vm<<endl;

    for(int i=0; i<img.l; i++)
    {
        for(int j=0; j<img.c; j++)
        {
            arq_criado<<img.r[i][j]<<" "<< img.g[i][j]<<" "<<img.b[i][j]<<" ";
        }
        arq_criado<<endl;

    }
    arq_criado.close();

}
