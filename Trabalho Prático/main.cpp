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
		fscanf(fp, "%d", &KA[a]);
		fscanf(fp, "%f", &CA[a]);
		fscanf(fp, "%f", &VA[a]);
	}
	
	// Por voos (v)
	for(int v=0; v<V; v++){
		fscanf(fp, "%f", &DisTv[v]);
		fscanf(fp, "%d", &DV[v]);
	}
	
	// Por trechos (t)
	for(int t=0; t<T; t++){
		fscanf(fp, "%f", &DisTt[t]);
	}
	
	// Por dias (d)
	for(int d=0; d<D; d++){
		fscanf(fp, "%d", &VDd[d]);
	}
	
	// Realizando a leitura dos dados dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			fscanf(fp, "%d", &DTvo[v][o]);
		}
    }
	
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			fscanf(fp, "%d", &OT[v][o]);
		}
    }
	
	// Por voos (v) e dias (d)
	for(int v=0; v<V; v++){
		for(int d=0; d<D; d++){
			fscanf(fp, "%d", &VDvd[v][d]);
		}
    }
	
	// Por trechos (t) e dias (d)
	for(int t=0; t<T; t++){
		for(int d=0; d<D; d++){
			fscanf(fp, "%d", &DTtd[t][d]);
		}
    }
	
	
	
	
	// Impressão para verificação dos dados
	printf("A: %d\n",A);
    printf("V: %d\n",V);
	printf("D: %d\n",D);
	printf("T: %d\n",T);
	printf("O: %d\n",O);
	
	// Impressão dos dados dependentes de 1 conjunto
	printf("\nAvioes: \n\n");
    printf("Aviao \t Capacidade \t Consumo \t Velocidade\n\n");
    for(int a=0; a<A; a++){
        printf("Aviao %d \t %d \t %.2f \t %.2f\n", a, KA[a], CA[a], VA[a]);
    }
	
	printf("\nVoos: \n\n");
    printf("Voo \t Distancia \t Demanda\n\n");
    for(int v=0; v<V; v++){
        printf("Voo %d \t %.2f \t %d \n", v, DisTv[v], DV[v]);
    }
	
	printf("\nTrechos: \n\n");
	printf("Trecho \t Distancia\n\n");
	for(int t=0; t<T; t++){
		printf("Trecho %d \t %.2f \n", t, DisTt[t]);
	}
	
	printf("\nDias: \n\n");
	printf("Dia \t Quant. de voos \n\n");
	for(int d=0; d<D; d++){
		printf("Dia %d \t %d \n", d, VDd[d]);
	}
	
	// Impressão dos dados dependentes de 2 conjuntos
	// Por voos (v) e aeroportos (o)
	printf("\n\nVoo V tem origem no aeroporto O? (1 caso sim, 0 caso nao)\n\n");
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			printf("Voo %d/Aeroporto %d: %d \t", v, o, DTvo[v][o]);
		}
		printf("\n");
    }
	
	printf("\n\nVoo V tem destino no aeroporto O? (1 caso sim, 0 caso nao)\n\n");
	for(int v=0; v<V; v++){
		for(int o=0; o<O; o++){
			printf("Voo %d/Aeroporto %d: %d \t", v, o, OT[v][o]);
		}
		printf("\n");
    }
	
	// Por voos (v) e dias (d)
	printf("\n\nVoo V pertence ao dia D? (1 caso sim, 0 caso nao)\n\n");
	for(int v=0; v<V; v++){
		for(int d=0; d<D; d++){
			printf("Voo %d/Dia %d: %d \t", v, d, VDvd[v][d]);
		}
		printf("\n");
    }
	
	// Por trechos (t) e dias (d)
	printf("\n\nDemanda por voos do Trecho X no dia Y\n\n");
	for(int t=0; t<T; t++){
		for(int d=0; d<D; d++){
			printf("Trecho %d/Dia %d: %d \t", t, d, DTtd[t][d]);
		}
		printf("\n");
    }
	
	
	
	
	// Declarando o ambiente e o modelo matemático
    IloEnv env;
	IloModel modelo;
    // Iniciando o modelo
    modelo = IloModel(env);
    
	
	
	
    // Declaração da variável de decisão x
    IloNumVarMatrix x(env, A);
	for(int a=0; a<A; a++){
        x[a] = IloNumVarArray(env, V, 0, 1, ILOINT);
    }
	// Adicionando x ao modelo
    for(int a=0; a<A; a++){
        for(int v=0; v<V; v++){
            stringstream var;
            var << "x[Aviao"<<a<<"][Voo"<<v<<"]";
            x[a][v].setName(var.str().c_str());
            modelo.add(x[a][v]);
        }
    }
	
	// Declaração da variável de decisão y
	IloNumVar3Matrix y(env, A);
	for(int a=0; a<A; a++){
        	y[a] = IloNumVarMatrix(env, O);
		for(int o = 0; o<O; o++){
			y[a][o] = IloNumVarArray(env, D, 0, 1, ILOINT);
		
			for(int d = 0; d<D; d++){
				stringstream var;
				var << "y[Aviao"<<a<<"][Aeroporto"<<o<<"][Dia"<<d<<"]";
				y[a][o][d].setName(var.str().c_str());
				modelo.add(y[a][o][d]);
			}
		}
	}
	
	
	
	
	
	// Declaração da função objetivo
	IloExpr fo(env);
    // Somatório de A 
	for(int a=0; a<A; a++){
        // Somatório de V
		for(int v=0; v<V; v++){
            fo = fo + x[a][v] * DisTv[v] * CA[a];
        }
    }
	//Adiciona ao modelo a função objetivo de minimização
    modelo.add(IloMinimize(env, fo));

    
	
	
	// Declaração das restrições do problema

    // Restrição 2 - Garante que cada voo seja atendido somente por 1 avião
	// Para todo V
	for(int v=0; v<V; v++){
		IloExpr soma(env);
		
		// Somatório de A
		for(int a=0; a<A; a++){
			soma = soma + x[a][v];
		}
		
		// Declara a restrição
		IloRange rest_2(env, 1, soma, 1);
		
		// Define o nome da restrição
		stringstream rest;
        rest << "Restricao 2[Voo"<<v<<"]:";
        rest_2.setName(rest.str().c_str());
		
		// Adicionando a restrição ao modelo
        modelo.add(rest_2);
    }
	
	// Restrição 3 - Garante que o limite de horas operadas por cada aeronave seja respeitado
	// Para todo A
	for(int a=0; a<A; a++){
		// Para todo D
		for(int d=0; d<D; d++){
			IloExpr soma(env);
			
			// Somatório de V
			for(int v=0; v<V; v++){
				soma = soma + x[a][v] * DisTv[v] * VDvd[v][d];
			}
			
			// Declara a restrição
			IloRange rest_3(env, 0, soma, 24*VA[a]);
		
			// Define o nome da restrição
			stringstream rest;
			rest << "Restricao 3[Aviao"<<a<<"][Dia"<<d<<"]:";
			rest_3.setName(rest.str().c_str());
		
			// Adicionando a restrição ao modelo
			modelo.add(rest_3);
		}
	}
	
	// Restrição 4 - Cada avião a cada dia deve iniciar suas operações de uma única origem
	// Para todo A
	for(int a=0; a<A; a++){
		// Para todo D
		for(int d=0; d<D; d++){
			IloExpr soma(env);
			
			// Somatório de O
			for(int o=0; o<O; o++){
				soma = soma + y[a][o][d];
			}
			
			// Declara a restrição
			IloRange rest_4(env, 1, soma, 1);
			
			// Define o nome da restrição
			stringstream rest;
			rest << "Restricao 4[Aviao"<<a<<"][Dia"<<d<<"]:";
			rest_4.setName(rest.str().c_str());
		
			// Adicionando a restrição ao modelo
			modelo.add(rest_4);
		}
	}

/*
	// Restrição 5 - Certifica que a quantidade de decolagens deve ser igual a quantidade de pousos
	// Para todo A
	for(int a=0; a<A; a++){
		// Para todo D
		for(int d=0; d<D; d++){
			// Para todo O
			for(int o=0; o<O; o++){
				IloExpr rest_5(env);
				IloExpr soma(env);
				
				// Somatório de V
				for(int v=0; v<V; v++){
					rest_5 = rest_5 + x[a][v] * DTvo[v][o] * VDvd[v][d];
				}
				rest_5 = rest_5 + y[a][o][d];
				
				// Somatório de V
				for(int v=0; v<V; v++){
					if((d+1) < D){
						soma = soma + x[a][v] * OT[v][o] + y[a][o][d+1];
					}
					if((d+1) >= D){
						soma = soma + x[a][v] * OT[v][o];
					}
				}
				
				modelo.add(rest_5 == soma);
			}
		}
	}
*/
	// Restrição 6 - Só podem ser alocados aviões que cumprem a demanda do voo
	// Para todo V
	for(int v=0; v<V; v++){
		IloExpr soma(env);
		
		// Somatório de A
		for(int a=0; a<A; a++){
			soma = soma + x[a][v] * KA[a];
		}
		
		// Declara a restrição
		IloRange rest_6(env, DV[v], soma, IloInfinity);
		
		// Define o nome da restrição
		stringstream rest;
		rest << "Restricao 6[Voo"<<v<<"]:";
		rest_6.setName(rest.str().c_str());
		
		// Adicionando a restrição ao modelo
		modelo.add(rest_6);
	}
	
	// Restrição 7 - x[a][v] pertence a {0,1}
	// Para todo A
	for(int a=0; a<A; a++){
		// Para todo V
		for(int v=0; v<V; v++){
			IloExpr variavel(env);
			variavel = x[a][v];
			
			// Declara a restrição
			IloRange rest_7(env, 0, variavel, 1);
			
			// Define o nome da restrição
			stringstream rest;
			rest << "Restricao 7[Aviao"<<a<<"][Voo"<<v<<"]:";
			rest_7.setName(rest.str().c_str());
			
			// Adicionando a restrição ao modelo
			modelo.add(rest_7);
		}
	}
	
	// Restrição 8 - y[a][o][d] pertence a {0,1}
	// Para todo A
	for(int a=0; a<A; a++){
		// Para todo O
		for(int o=0; o<O; o++){
			// Para todo D
			for(int d=0; d<D; d++){
				IloExpr variavel(env);
				variavel = y[a][o][d];
			
				// Declara a restrição
				IloRange rest_8(env, 0, variavel, 1);
			
				// Define o nome da restrição
				stringstream rest;
				rest << "Restricao 8[Aviao"<<a<<"][Aero"<<o<<"][Dia"<<d<<"]:";
				rest_8.setName(rest.str().c_str());
			
				// Adicionando a restrição ao modelo
				modelo.add(rest_8);
			}
		}
	}
	
	
	
	
	// Carregando o módulo do Cplex
    IloCplex cplex(modelo);
    // Exportando o lp
    cplex.exportModel("aeronave1.lp");
    // Executando o modelo
    cplex.solve();
    
	
	
	int valor = 0;
    // Imprimindo os valores das variáveis de decisão
	// Variável x[a][v]
    printf("\n\nVARIAVEIS DE DECISAO\n\n");
	for(int a=0; a<A; a++){
		for(int v=0; v<V; v++){
			valor = cplex.getValue(x[a][v]);
			if(valor == 1){
				printf("x[aviao%d][voo%d] = %d\n", a, v, valor);
			}
		}
	}
	
	// Variável y[a][o][d]
	printf("\n\n");
	for(int a=0; a<A; a++){
		for(int o=0; o<O; o++){
			for(int d=0; d<D; d++){
				valor = cplex.getValue(y[a][o][d]);
				if(valor == 1){
					printf("y[aviao%d][aeroporto%d][dia%d] = %d\n", a, o, d, valor);
				}
			}
		}
	}
	
	printf("\n\nFUNCAO OBJETIVO\n");
	double teste = cplex.getObjValue();
	printf("FO = %.2f\n", teste);
	
	return 0;
}
