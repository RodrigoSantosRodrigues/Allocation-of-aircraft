#include<iostream>
#include<stdio.h>
#include <sstream>

#include <ilcplex/ilocplex.h>


typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumVarMatrix> IloNumVar3Matrix;
typedef IloArray<IloNumVar3Matrix> IloNumVar4Matrix;

using namespace std;

int main(int argc, char *argv[])
{
	/*
	// F -> conjunto de Fazendas
    // C -> conjunto de Culturas
    int F, C;
	
	// Dados de entrada dependentes dos conjuntos
    char** NomeFazenda; // por fazenda
    float* Area; // por fazenda
    float* Agua; // por fazenda

    char** NomeCultura; // por cultura
    float* AMax; // por cultura
    float* ConsAgua; // por cultura
    float* Lucro; // por cultura
	*/
	
	
	
	
	
	// Declarando conjuntos de entrada
    // A -> Quantidade de aviões
    // V -> Quantidade de voos
	// D -> Quantidade de dias
	// T -> Quantidade de trechos
	// O -> Quantidade de aeroportos
	int A, V, D, T, O;
	
	// Dados de entrada dependentes de 1 conjunto
	// Por aviões (a)
	int*   KA;        // Capacidade de passageiros do avião do tipo a
	float* CA;        // Consumo do avião a
	float* VA;        // Velocidade do avião a
	int*   QA;	      // Quantidade de aviões do tipo a
	
	// Por voos (v)
	float* DisTv;	  // Distância do voo v
	int*   DV;        // Demanda do voo v
	
	// Por trechos (t)
	float* DisTt;	  // Distância do trecho t
	
	// Por dias (d)
	int*   VDd;		  // Quantidades de voo no dia d
	
	// Dados de entrada dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	int**  DTvo;        // Variável binária que informa se o voo v tem origem no aeroporto o
	int**  OT;        // Variável binária que informa se o voo v tem destino no aeroporto o
	
	// Por voos (v) e dias (d)
	int**  VDvd;      // Variável binária que informa se o voo v pertence ao dia d
	
	// Por trechos (t) e dias (d)
	int**  DTtd;	  // Demanda por voos do trecho t no dia d



    // Leitura do Arquivo
    FILE* fp;
    fp = fopen(argv[1],"r");

    if( fp == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);    
    }
    
    // Leitura dos conjuntos
    fscanf(fp, "%d", &F);
    fscanf(fp, "%d", &C); 

    // Definindo os dados de entrada de acordo com o tamanho dos conjuntos lidos
    // Por fazenda
    NomeFazenda = new char*[F];
    for(int f = 0; f < F; f++)
    {
        NomeFazenda[f] = new char[51];
    }

    Area = new float[F];
    Agua = new float[F];

    //Por Cultura
    NomeCultura = new char*[C];
    for(int c = 0; c < C; c++)
    {
        NomeCultura[c] = new char[51];
    }

    AMax = new float[C];
    ConsAgua = new float[C];
    Lucro = new float[C];



    // Após a declaração dos tamanhos dos dados de entrada, realizando a leitura
    // Por Fazenda
    for(int f = 0; f < F; f++)
    {
        fscanf(fp, "%s", NomeFazenda[f]);
        fscanf(fp, "%f", &Area[f]);
        fscanf(fp, "%f", &Agua[f]);
    }

    // Por Cultura

    for(int c = 0; c < C; c++)
    {
        fscanf(fp, "%s", NomeCultura[c]);
        fscanf(fp, "%f", &AMax[c]);
        fscanf(fp, "%f", &ConsAgua[c]);
        fscanf(fp, "%f", &Lucro[c]);
    }  


    // Impressão para Verificação dos dados
    printf("F: %d\n", F);
    printf("C: %d\n", C);

    printf("Fazendas: \n");
    printf("Nome \t Area \t Agua\n");
    for(int f = 0; f < F; f++)
    {
        printf("%s \t %.2f \t %.2f \n", NomeFazenda[f], Area[f], Agua[f]);
    }

    // Por Cultura
    printf("Culturas: \n");
    printf("Nome \t AreaMax \t ConsAgua \t Lucro\n");

    for(int c = 0; c < C; c++)
    {
        printf("%s \t %.2f \t %.2f \t %.2f \n", NomeCultura[c], AMax[c], ConsAgua[c], Lucro[c]);
    }  




    // DECLARANDO O AMBIENTE E O MODELO MATEMATICO
    IloEnv env;
	IloModel modelo;
    // iniciando o modelo
    modelo = IloModel(env);
    

    // parametros para declaração de variáveis: ambiente, tamanho, valor min, valor max, tipo (ILOINT, ILOFLOAT, ILOBOOL)

    // DECLARAÇÃO DE VARIÁVEIS DE UMA DIMENSÃO  
    // declarando a variavel y  
    /*IloNumVarArray y(env, F, 0, IloInfinity, ILOFLOAT);
    // adicionar as variaveis ao modelo
    for(int f = 0; f < F; f++)
    {
        modelo.add(y[f]);
    }*/

    // DECLARAÇÃO DE VARIÁVEIS DE DUAS DIMENSÕES
    // declaração de x
    // para variáveis com mais de uma dimensão, os parâmetros são: ambiente, tamanho
    IloNumVarMatrix x(env, F);
    for(int f= 0 ; f < F; f++)
    {
        x[f] = IloNumVarArray(env, C, 0, IloInfinity, ILOFLOAT);
    }

    // adicionando x ao modelo
    for(int f= 0; f < F; f++)
    {
        for(int c = 0 ; c < C; c++)
        {
            stringstream var;
            var << "x[" << NomeFazenda[f] << "][" << NomeCultura[c]<< "]";
            x[f][c].setName(var.str().c_str());
            modelo.add(x[f][c]);
        }
    }

    // DECLARAÇÃO DA FUNÇÃO OBJETIVO

    IloExpr fo(env);
    
    //somatorio de F
    for(int f=0; f < F; f++)
    {
        for(int c = 0; c < C; c++)
        {
            fo += Lucro[c]*x[f][c];            
        }
    }

      
    //IloMinimize e IloMaximize
    modelo.add(IloMaximize(env, fo));

    
    // DECLARAÇÃO DAS RESTRIÇÕES DO PROBLEMA

    // declarando a restrição
    // parametros: ambiente, valor min, expressão, valor maximo

    // restrição relativa à area da fazenda
    // para todo F
    for(int f = 0 ; f < F ; f++)
    {
        IloExpr soma(env);
        // somatorio em C
        for(int c = 0 ; c < C; c++)
        {
            soma += x[f][c];
        }
        // declara a restrição
        IloRange rest_areaFaz(env, -IloInfinity, soma, Area[f]);
        // definindo nome para a restrição
        stringstream rest;
        rest << "AreaFaz[" << NomeFazenda[f] << "]:";
        rest_areaFaz.setName(rest.str().c_str());
        // adicionar a restrição ao modelo
        modelo.add(rest_areaFaz); 
    }

    // restrição de disponibilidade de água nas fazendas
    // para todo F
    for(int f = 0 ; f < F; f++)
    {
        IloExpr soma(env);
        // somatório de C
        for(int c = 0 ; c < C; c++)
        {
           soma+= ConsAgua[c]*x[f][c]; 
        } 
        // declarar a restrição
        IloRange rest_consAgua(env, -IloInfinity, soma, Agua[f]);
        // nome das restrições
        stringstream rest;
        rest << "consAgua[" << NomeFazenda[f] << "]:";
        rest_consAgua.setName(rest.str().c_str());
        // adicionar a restrição ao modelo
        modelo.add(rest_consAgua);
    }

    // restrição área Maxima Plantada
    // para todo C
    for(int c = 0 ; c < C; c++)
    {
        IloExpr soma(env);
        // somatorio de F
        for(int f = 0 ; f < F; f++)
        {
            soma+=x[f][c];
        }

        // declarar a restrição
        IloRange rest_areaMax(env, -IloInfinity, soma, AMax[c]);
        // adicionar a restrição ao modelo
        modelo.add(rest_areaMax);
    }
    
    // restrição de proporcionalidade
    // para cada F
    for(int f = 0 ; f < F; f++)
    {
        // para todo F
        for(int g = 0; g < F; g++)
        {
            if(f != g)
            {
                IloExpr soma1(env);
                IloExpr soma2(env);
                
                // somatorio C
                for(int c = 0; c < C; c++)
                {
                    soma1+= x[f][c];
                }
                soma1 = soma1 / Area[f];

                // somatorio C
                for(int c = 0 ; c < C; c++)
                {
                    soma2 += x[g][c];
                }
                soma2 = soma2 / Area[g];

                // definindo a restrição
                IloRange restProporcao(env, 0, soma1-soma2, 0);
                // adicionando a restrição ao modelo
                modelo.add(restProporcao);
            } 
        }
    }


 
    // Carregando o módulo do Cplex
    IloCplex cplex(modelo);
    // exportando o lp
    cplex.exportModel("fazenda.lp");
    // Executando o modelo
    cplex.solve();
    
    // PEGAR OS VALORES DAS VARIÁVEIS 
    //cplex.getValue(NOME_VAR)    

    for(int f = 0; f < F; f++)
    {
        printf("*****\n");
        printf("%s\n", NomeFazenda[f]);
        for(int c = 0 ; c < C; c++)
        {
            double valor = cplex.getValue(x[f][c]);
            printf("%s: %f \n", NomeCultura[c], valor);
        }

    }


    return 0;
}












