#include<iostream>
#include<stdio.h>
#include<sstream>
#include<ilcplex/ilocplex.h>

typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumVarMatrix> IloNumVar3Matrix;
typedef IloArray<IloNumVar3Matrix> IloNumVar4Matrix;

using namespace std;

int main(int argc, char *argv[]){
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
	int**  DTvo;      // Variável binária que informa se o voo v tem origem no aeroporto o
	int**  OT;        // Variável binária que informa se o voo v tem destino no aeroporto o
	
	// Por voos (v) e dias (d)
	int**  VDvd;      // Variável binária que informa se o voo v pertence ao dia d
	
	// Por trechos (t) e dias (d)
	int**  DTtd;	  // Demanda por voos do trecho t no dia d

	
	// Leitura do Arquivo
    FILE* fp;
    fp = fopen(argv[1],"r");

    if(fp == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);    
    }
    
    
	// Leitura dos conjuntos A, V, D, T e O
    fscanf(fp, "%d", &A);
    fscanf(fp, "%d", &V);
	fscanf(fp, "%d", &D);
	fscanf(fp, "%d", &T);
	fscanf(fp, "%d", &O);
	
	
	// Definindo os dados de entrada dependentes de 1 conjunto
	// Por aviões (a)
	KA = new int[A];
	CA = new float[A];
	VA = new float[A];
	QA = new int[A];
	
	// Por voos (v)
	DisTv = new float[V];
	DV = new int[V];
	
	// Por trechos (t)
	DisTt = new float[T];
	
	// Por dias (d)
	VDd = new int[D];

	// Definindo os dados de entrada dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	DTvo = new int*[V];
	for(int v=0; v<V; v++){
        DTvo[v] = new int[O];
    }
	
	OT = new int*[V];
	for(int v=0; v<V; v++){
        OT[v] = new int[O];
    }
	
	// Por voos (v) e dias (d)
	VDvd = new int*[V];
	for(int v=0; v<V; v++){
        VDvd[v] = new int[D];
    }
	
	// Por trechos (t) e dias (d)
	DTtd = new int*[T];
	for(int t=0; t<T; t++){
        DTtd[t] = new int[D];
    }
	
	
	// Realizando a leitura dos dados dependentes de 1 conjunto
	// Por aviões (a)
	for(int a=0; a<A; a++){
		fscanf(fp, "%d", KA[a]);
		fscanf(fp, "%f", CA[a]);
		fscanf(fp, "%f", VA[a]);
		fscanf(fp, "%d", QA[a]);
	}
	
	// Por voos (v)
	for(int v=0; v<V; v++){
		fscanf(fp, "%f", DisTv[v]);
		fscanf(fp, "%d", DV[v]);
	}
	
	// Por trechos (t)
	for(int t=0; t<T; t++){
		fscanf(fp, "%f", DisTt[t]);
	}
	
	// Por dias (d)
	for(int d=0; d<D; d++){
		fscanf(fp, "%d", VDd[d]);
	}
	
	// Realizando a leitura dos dados dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			fscanf(fp, "%d", DTvo[v][o]);
		}
    }
	
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			fscanf(fp, "%d", OT[v][o]);
		}
    }
	
	// Por voos (v) e dias (d)
	for(int v=0; v<V; v++){
		for(int d=0; d<D; d++){
			fscanf(fp, "%d", VDvd[v][d]);
		}
    }
	
	// Por trechos (t) e dias (d)
	for(int t=0; t<T; t++){
		for(int d=0; d<D; d++){
			fscanf(fp, "%d", DTtd[t][d]);
		}
    }
	
	// Impressão para verificação dos dados
	printf("A: %d\n",A);
    printf("V: %d\n",V);
	printf("D: %d\n",D);
	printf("T: %d\n",T);
	printf("O: %d\n",O);
	
	// Impressão dos dados dependentes de 1 conjunto
	printf("Avioes: \n");
    printf("Aviao \t Capacidade \t Consumo \t Velocidade \t Quantidade\n");
    for(int a=0; a<A; a++){
        printf("Aviao%d \t %d \t %.2f \t %.2f \t %d \n", A, KA[a], CA[a], VA[a], QA[a]);
    }
	
	printf("Voos: \n");
    printf("Voo \t Distancia \t Demanda\n");
    for(int v=0; v<V; v++){
        printf("Voo%d \t %.2f \t %d \n", V, DisTv[v], DV[v]);
    }
	
	printf("Trechos: \n");
	printf("Trecho \t Distancia\n");
	for(int t=0; t<T; t++){
		printf("Trecho%d \t %.2f \n", T, DisTt[t]);
	}
	
	printf("Dias: \n");
	printf("Dia \t Quant. de voos \n");
	for(int d=0; d<D; d++){
		printf("Dia%d \t %d \n", D, VDd[d]);
	}
	
	// Impressão dos dados dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	printf("\nVoo V tem origem no aeroporto O? (1 caso sim, 0 caso nao)\n");
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			printf("Voo%d/Aeroporto%d: %d \t", V, O, DTvo[v][o]);
		}
		printf("\n");
    }
	
	printf("\n\nVoo V tem destino no aeroporto O? (1 caso sim, 0 caso nao)\n");
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			printf("Voo%d/Aeroporto%d: %d \t", V, O, OT[v][o]);
		}
		printf("\n");
    }
	
	// Por voos (v) e dias (d)
	printf("\n\nVoo V pertence ao dia D? (1 caso sim, 0 caso nao)\n");
	for(int v=0; v<V; v++){
		for(int d=0; d<D; d++){
			printf("Voo%d/Dia%d: %d \t", V, D, VDvd[v][d]);
		}
		printf("\n");
    }
	
	// Por trechos (t) e dias (d)
	printf("\n\nDemanda por voos do Trecho X no dia Y\n");
	for(int t=0; t<T; t++){
		for(int d=0; d<D; d++){
			printf("Trecho%d/Dia%d: %d \t", T, D, DTtd[t][d]);
		}
		printf("\n");
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