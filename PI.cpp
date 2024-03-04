#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{ //typedef define o nome da struct como um "tipo"
	int id, dia, mes, ano;
	char nome[50], CPF[15], tel[15], cel[15];
	char cidade[50], rua[100], complemento[50], bairro[25], CEP[10], UF[10], num[10];
} Cliente;

//função para cadastrar 
cadastrarcliente(FILE*arquivo, Cliente cliente){
	fprintf(arquivo, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, 
	cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, 
	cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, 
	cliente.complemento, cliente.bairro);
}

// Função para obter o último ID cadastrado no arquivo
int obterUltimoID(FILE *arquivo, Cliente cliente) {
    int ultimoID = 0;

    rewind(arquivo); // Retorna ao início do arquivo

while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, 
cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, 
cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
		if (cliente.id > ultimoID) {
            ultimoID = cliente.id;
        }
    }

    return ultimoID;
}

//função de consulta utilizando o ID do cliente
consultaID(FILE *arquivo, int id){
	Cliente cliente;
	int encontrado = 0;
	
	rewind(arquivo);
	
	while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
       // fgetc(arquivo);
		if (cliente.id == id) {
            printf("Cliente encontrado!\n\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nData de Nascimento: %d/%d/%d\nTelefone: %s\nCelular: %s\nCEP: %s\nUF: %s\nCidade: %s\nRua: %s\nNumero: %s\nComplemento: %s\nBairro: %s\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
      		encontrado = 1;
	    }
    }
    
    if(!encontrado){
    	printf("Cliente nao encontrado!\n");
	}
}

//função de consulta utilizando o CPF do cliente
consultaCPF(FILE *arquivo, char cpf[15]){
	Cliente cliente;
	int encontrado = 0;
	
	rewind(arquivo);
	while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
       //fgetc(arquivo);
		if (strcmp(cliente.CPF, cpf) ==  0) {
            printf("Cliente encontrado!\n\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nData de Nascimento: %d/%d/%d\nTelefone: %s\nCelular: %s\nCEP: %s\nUF: %s\nCidade: %s\nRua: %s\nNumero: %s\nComplemento: %s\nBairro: %s\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
      		encontrado = 1;
      		break;
	    }
    }
    
    if(!encontrado){
    	printf("Cliente nao encontrado!\n");
	}
	return encontrado;
}

//função de edição utilizando o CPF do cliente	
editarCPF(FILE *arquivo, char cpf[15]){
	FILE *tempfile = fopen("temp.txt", "w");
	Cliente cliente;
	int edit, encontrado = 0;
	
	rewind(arquivo);
	
	while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
		if (strcmp(cliente.CPF, cpf) !=  0) {
			fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
		}
		else{
			fflush(stdin);
			encontrado = 1;
			printf("\nQual info do cliente deseja editar?\n1 - Nome\n2 - CPF\n3 - Data de Nascimento\n4 - Contato\n5 - Endereco\n");
			scanf("%d", &edit);
			switch(edit){
				case 1:
					fflush(stdin);
					printf("\nEntre com o novo nome: ");
					fgets(cliente.nome, sizeof(cliente.nome), stdin);
					cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
					
					while(strlen(cliente.nome) == 0){
					fflush(stdin);
					printf("Entre com o novo nome: ");
					fgets(cliente.nome, sizeof(cliente.nome), stdin);
					cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
					}
					fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					break;
				
				case 2:
					fflush(stdin);
					printf("\nEntre com o novo CPF (11 Digitos): ");
					fgets(cliente.CPF, sizeof(cliente.CPF), stdin);
					cliente.CPF[strcspn(cliente.CPF, "\n")] = '\0';
					
					while(strlen(cliente.CPF) != 11){
					fflush(stdin);
					printf("Entre com o novo CPF (11 Digitos): ");
					fgets(cliente.CPF, sizeof(cliente.CPF), stdin);
					cliente.CPF[strcspn(cliente.CPF, "\n")] = '\0';
					}
					fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					break;
				
				case 3:
					fflush(stdin);
					printf("\nData de nascimento (Formato DD/MM/AAAA): ");
					scanf("%d/%d/%d", &cliente.dia, &cliente.mes, &cliente.ano);
					while(cliente.dia <= 0 || cliente.dia >= 32 || cliente.mes <= 0 || cliente.mes >= 13 || cliente.ano == 0){ 
						printf("\nEntre com uma data valida!\n");
						fflush(stdin);
						printf("Data de nascimento (Formato DD/MM/AAAA): ");
						scanf("%d%d%d", &cliente.dia, &cliente.mes, &cliente.ano);
					}
					fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					break;
					
				case 4:
					fflush(stdin);
					printf("\nTelefone (DDD + Num): ");
					fgets(cliente.tel, sizeof(cliente.tel), stdin);
					cliente.tel[strcspn(cliente.tel, "\n")] = '\0';
					if(strlen(cliente.tel) == 0 || strlen(cliente.tel) != 10){
						strcpy(cliente.tel, " ");
						cliente.tel[strcspn(cliente.tel, "\n")] = '\0';
					}
					
					fflush(stdin);
					printf("Celular (DDD + Num): ");
					fgets(cliente.cel, sizeof(cliente.cel), stdin);
					cliente.cel[strcspn(cliente.cel, "\n")] = '\0';
					while(strlen(cliente.cel) != 10 && strlen(cliente.cel) != 11){
						fflush(stdin);
						printf("Celular (DDD + Num): ");
						fgets(cliente.cel, sizeof(cliente.cel), stdin);
						cliente.cel[strcspn(cliente.cel, "\n")] = '\0';
					}
					fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					break;
				
				case 5:
					fflush(stdin);
					
					printf("\nCEP (8 Digitos): ");
					fgets(cliente.CEP, sizeof(cliente.CEP), stdin);
					cliente.CEP[strcspn(cliente.CEP, "\n")] = '\0';
					
					while(strlen(cliente.CEP) != 8){
					fflush(stdin);
					printf("CEP (8 Digitos): ");
					fgets(cliente.CEP, sizeof(cliente.CEP), stdin);
					cliente.CEP[strcspn(cliente.CEP, "\n")] = '\0';
					}
					
					printf("UF: ");
					fgets(cliente.UF, sizeof(cliente.UF), stdin);
					cliente.UF[strcspn(cliente.UF, "\n")] = '\0';
					fflush(stdin);
					
					while(strlen(cliente.UF) != 2){
					fflush(stdin);
					printf("UF: ");
					fgets(cliente.UF, sizeof(cliente.UF), stdin);
					cliente.UF[strcspn(cliente.UF, "\n")] = '\0';
					}
					
					printf("Cidade: ");
					fgets(cliente.cidade, sizeof(cliente.cidade), stdin);
					cliente.cidade[strcspn(cliente.cidade, "\n")] = '\0';
					
					while(strlen(cliente.cidade) == 0){
					fflush(stdin);
					printf("Cidade: ");
					fgets(cliente.cidade, sizeof(cliente.cidade), stdin);
					cliente.cidade[strcspn(cliente.cidade, "\n")] = '\0';
					}
					
					printf("Rua: ");
					fgets(cliente.rua, sizeof(cliente.rua), stdin);
					cliente.rua[strcspn(cliente.rua, "\n")] = '\0';
					
					while(strlen(cliente.rua) == 0){
					fflush(stdin);
					printf("Rua: ");
					fgets(cliente.rua, sizeof(cliente.rua), stdin);
					cliente.rua[strcspn(cliente.rua, "\n")] = '\0';
					}
					
					printf("Numero: ");
					fgets(cliente.num, sizeof(cliente.num), stdin);
					cliente.num[strcspn(cliente.num, "\n")] = '\0';
					fflush(stdin);
					
					while(strlen(cliente.num) == 0){
					fflush(stdin);
					printf("Numero: ");
					fgets(cliente.num, sizeof(cliente.num), stdin);
					cliente.num[strcspn(cliente.num, "\n")] = '\0';
					}
					
					printf("Complemento (deixar em branco se nao houver): ");
					fgets(cliente.complemento, sizeof(cliente.complemento), stdin);
					cliente.complemento[strcspn(cliente.complemento, "\n")] = '\0';
					if(strlen(cliente.complemento) == 0){
						strcpy(cliente.complemento, " ");
						cliente.complemento[strcspn(cliente.complemento, "\n")] = '\0';
					}
						
					printf("Bairro: ");
					fgets(cliente.bairro, sizeof(cliente.bairro), stdin);
					cliente.bairro[strcspn(cliente.bairro, "\n")] = '\0';
					
					while(strlen(cliente.bairro) == 0){
					fflush(stdin);
					printf("Bairro: ");
					fgets(cliente.bairro, sizeof(cliente.bairro), stdin);
					cliente.bairro[strcspn(cliente.bairro, "\n")] = '\0';
					}
					
					fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					break;
				}
			}
		}
		
		fclose(arquivo);
		fclose(tempfile);
		
		remove("Cadastros.txt");
		rename("temp.txt", "Cadastros.txt");
		
		fopen("Cadastros.txt", "a+");
		
		if(encontrado){
			printf("\nCliente editado com sucesso!\n");
		}
	}

//função para exclusão de cadastro utilizando o CPF do cliente
excluircad(FILE *arquivo, char cpf[15]){
	FILE *tempfile = fopen("temp.txt", "w");
	Cliente cliente;
	int encontrado = 0;
	
	rewind(arquivo);
	
	while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
		if (strcmp(cliente.CPF, cpf) !=  0) {
			fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
		}
		else{
			encontrado = 1;
			
			strcpy(cliente.nome, "Cliente excluido"); 
			strcpy(cliente.CPF, " ");
			cliente.dia = 0;
			cliente.mes = 0;
			cliente.ano = 0;
			strcpy(cliente.CEP, " ");
			strcpy(cliente.UF, " ");
			strcpy(cliente.cidade, " ");
			strcpy(cliente.rua, " ");
			strcpy(cliente.num, " ");
			strcpy(cliente.tel, " ");
			strcpy(cliente.cel, " ");
			strcpy(cliente.complemento, " ");
			strcpy(cliente.bairro, " ");
			
			fprintf(tempfile, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
					
			}
		}
		fclose(arquivo);
		fclose(tempfile);
		
		remove("Cadastros.txt");
		rename("temp.txt", "Cadastros.txt");
		
		fopen("Cadastros.txt", "a+");
		
		if(encontrado){
			printf("Cliente excluido com sucesso!\n");
		}
	}
	
//função para exclusão de cadastro utilizando o CPF do cliente
gerarelatorio(FILE *arquivo){
	FILE *relatorio = fopen("Relatorio Clientes.csv", "w");
	Cliente cliente;
	
	rewind(arquivo);
	
	fprintf(relatorio, "ID;Nome Completo;CPF;Data de Nascimento;Telefone;Celular;CEP;UF;Cidade;Rua;Numero;Complemento;Bairro;\n");
	while(fscanf(arquivo, "%d;%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n];\n", &cliente.id, cliente.nome, cliente.CPF, &cliente.dia, &cliente.mes, &cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro) != EOF){
			fprintf(relatorio, "%d;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente.id, cliente.nome, cliente.CPF, cliente.dia, cliente.mes, cliente.ano, cliente.tel, cliente.cel, cliente.CEP, cliente.UF, cliente.cidade, cliente.rua, cliente.num, cliente.complemento, cliente.bairro);
		}
		fclose(relatorio);
	}



int main(){
	
	FILE*arquivo; //Ponteiro do arquivo.
	
	arquivo = fopen("Cadastros.txt", "a+"); //Função usada para abrir o arquivo. "a+" indica q o arquivo com o nome "Cadastros.txt" será procurado.
										   //Caso encontrado, o arquivo será aberto, caso contrário, será criado um com este nome.
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo. Encerrando o Programa.");
		exit(0);
	}
	else{
		printf("Arquivo aberto com sucesso!\n");
		system("pause");
		system("CLS");
	}
	
	int consulta, id, op = -1;
	char cpf[15], nstring[50], dec;
	Cliente novoCliente;
		
	while(op != 0){
	
	//Logo da empresa. EVERGARDEN.
	printf("    .-''-. ,---.  ,---.  .-''-. .-------.     .-_'''-.     ____   .-------.    ______        .-''-. ,---.   .--. \n");
	printf("  .'_ _   \\|   /  |   |.'_ _   \\|  _ _   \\   '_( )_   \\  .'  __ `.|  _ _   \\  |    _ `''.  .'_ _   \\|    \\  |  | \n");
	printf(" / ( ` )   |  |   |  ./ ( ` )   | ( ' )  |  |(_ o _)|  '/   '  \\  | ( ' )  |  | _ | ) _  \\/ ( ` )   |  ,  \\ |  | \n");
	printf(". (_ o _)  |  | _ |  . (_ o _)  |(_ o _) /  . (_,_)/___||___|  /  |(_ o _) /  |( ''_'  ) . (_ o _)  |  |\\_ \\|  | \n");
	printf("|  (_,_)___|  _( )_  |  (_,_)___| (_,_).' __|  |  .-----.  _.-`   | (_,_).' __| . (_) `. |  (_,_)___|  _( )_\\  | \n");
	printf("'  \\   .---\\ (_ o._) '  \\   .---|  |\\ \\  |  '  \\  '-   ..'   _    |  |\\ \\  |  |(_    ._) '  \\   .---| (_ o _)  | \n");
	printf(" \\  `-'    /\\ (_,_) / \\  `-'    |  | \\ `'   /\\  `-'`   ||  _( )_  |  | \\ `'   |  (_.\\.' / \\  `-'    |  (_,_)\\  | \n");
	printf("  \\       /  \\     /   \\       /|  |  \\    /  \\        /\\ (_ o _) |  |  \\    /|       .'   \\       /|  |    |  | \n");
	printf("   `'-..-'    `---`     `'-..-' ''-'   `'-'    `'-...-'  '.(_,_).'''-'   `'-' '-----'`      `'-..-' '--'    '--' \n\n");
	    

	
	printf("Entre com o numero de acordo com a operacao desejada: \n");
	printf("1 - Cadastrar\n2 - Consultar\n3 - Editar\n4 - Excluir\n0 - Sair\n");
	scanf("%d", &op);
	fflush(stdin);
	
	system("CLS");
	
	switch(op){
		case 1: //Pede e grava todos os dados do cliente e chama a função de cadastro, passando todas variaveis para a mesma e gravando tudo em arquivo.
			novoCliente.id = obterUltimoID(arquivo, novoCliente) + 1; // Incrementa o ID automaticamente
            printf("Novo ID gerado: %d\n", novoCliente.id);
			
			printf("Nome: ");
			fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin); //Insere uma linha inteira ao arquivo, mas há quebra de linha automatica após inserir valor.
			novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0'; //Remove a quebra de linha do fgets.
			while(strlen(novoCliente.nome) == 0){ //Verifica se o input é = 0 
					fflush(stdin);
					printf("Nome: ");
					fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
					novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';
					}
			
			printf("CPF (11 Digitos): ");
			fgets(novoCliente.CPF, sizeof(novoCliente.CPF), stdin);
			novoCliente.CPF[strcspn(novoCliente.CPF, "\n")] = '\0';
			while(strlen(novoCliente.CPF) != 11){
					fflush(stdin);
					printf("CPF (11 Digitos): ");
					fgets(novoCliente.CPF, sizeof(novoCliente.CPF), stdin);
					novoCliente.CPF[strcspn(novoCliente.CPF, "\n")] = '\0';
					}
				
			fflush(stdin);
			printf("Data de nascimento (Formato DD/MM/AAAA): ");
			scanf("%d/%d/%d", &novoCliente.dia, &novoCliente.mes, &novoCliente.ano);
			while(novoCliente.dia <= 0 || novoCliente.dia >= 32 || novoCliente.mes <= 0 || novoCliente.mes >= 13 || novoCliente.ano == 0){ //Verifica se o input é = 0 
					printf("\nEntre com uma data valida!\n");
					printf("Data de nascimento (Formato DD/MM/AAAA): ");
					scanf("%d%d%d", &novoCliente.dia, &novoCliente.mes, &novoCliente.ano);
					fflush(stdin);
					}
			
			fflush(stdin);
			printf("Telefone (DDD + Num): ");
			fgets(novoCliente.tel, sizeof(novoCliente.tel), stdin);
			novoCliente.tel[strcspn(novoCliente.tel, "\n")] = '\0';
			if(strlen(novoCliente.tel) == 0){
				strcpy(novoCliente.tel, " ");
				novoCliente.tel[strcspn(novoCliente.tel, "\n")] = '\0';
			}
			
			fflush(stdin);
			printf("Celular (DDD + Num): ");
			fgets(novoCliente.cel, sizeof(novoCliente.cel), stdin);
			novoCliente.cel[strcspn(novoCliente.cel, "\n")] = '\0';
			while(strlen(novoCliente.cel) != 10 && strlen(novoCliente.cel) != 11){
					fflush(stdin);
					printf("Celular (DDD + Num): ");
					fgets(novoCliente.cel, sizeof(novoCliente.cel), stdin);
					novoCliente.cel[strcspn(novoCliente.cel, "\n")] = '\0';
					}
			
			fflush(stdin);
			printf("CEP (8 Digitos): ");
			fgets(novoCliente.CEP, sizeof(novoCliente.CEP), stdin);
			novoCliente.CEP[strcspn(novoCliente.CEP, "\n")] = '\0';
			while(strlen(novoCliente.CEP) != 8){
					fflush(stdin);
					printf("CEP (8 Digitos): ");
					fgets(novoCliente.CEP, sizeof(novoCliente.CEP), stdin);
					novoCliente.CEP[strcspn(novoCliente.CEP, "\n")] = '\0';
					}
					
			printf("UF: ");
			fgets(novoCliente.UF, sizeof(novoCliente.UF), stdin);
			novoCliente.UF[strcspn(novoCliente.UF, "\n")] = '\0';
			while(strlen(novoCliente.UF) != 2){
					fflush(stdin);
					printf("UF: ");
					fgets(novoCliente.UF, sizeof(novoCliente.UF), stdin);
					novoCliente.UF[strcspn(novoCliente.UF, "\n")] = '\0';
					}
			
			printf("Cidade: ");
			fgets(novoCliente.cidade, sizeof(novoCliente.cidade), stdin);
			novoCliente.cidade[strcspn(novoCliente.cidade, "\n")] = '\0';
			while(strlen(novoCliente.cidade) == 0){
					fflush(stdin);
					printf("Cidade: ");
					fgets(novoCliente.cidade, sizeof(novoCliente.cidade), stdin);
					novoCliente.cidade[strcspn(novoCliente.cidade, "\n")] = '\0';
					}
			
			printf("Rua: ");
			fgets(novoCliente.rua, sizeof(novoCliente.rua), stdin);
			novoCliente.rua[strcspn(novoCliente.rua, "\n")] = '\0';
			while(strlen(novoCliente.rua) == 0){
					fflush(stdin);
					printf("Rua: ");
					fgets(novoCliente.rua, sizeof(novoCliente.rua), stdin);
					novoCliente.rua[strcspn(novoCliente.rua, "\n")] = '\0';
					}
			
			printf("Numero: ");
			fgets(novoCliente.num, sizeof(novoCliente.num), stdin);
			novoCliente.num[strcspn(novoCliente.num, "\n")] = '\0';
			while(strlen(novoCliente.num) == 0){
					fflush(stdin);
					printf("Numero: ");
					fgets(novoCliente.num, sizeof(novoCliente.num), stdin);
					novoCliente.num[strcspn(novoCliente.num, "\n")] = '\0';
					}
			fflush(stdin);
			
			printf("Complemento (deixar em branco se nao houver): ");
			fgets(novoCliente.complemento, sizeof(novoCliente.complemento), stdin);
			novoCliente.complemento[strcspn(novoCliente.complemento, "\n")] = '\0';
			if(strlen(novoCliente.complemento) == 0){
				strcpy(novoCliente.complemento, " ");
				novoCliente.complemento[strcspn(novoCliente.complemento, "\n")] = '\0';
			}
				
			printf("Bairro: ");
			fgets(novoCliente.bairro, sizeof(novoCliente.bairro), stdin);
			novoCliente.bairro[strcspn(novoCliente.bairro, "\n")] = '\0';
			while(strlen(novoCliente.bairro) == 0){
					fflush(stdin);
					printf("Bairro: ");
					fgets(novoCliente.bairro, sizeof(novoCliente.bairro), stdin);
					novoCliente.bairro[strcspn(novoCliente.bairro, "\n")] = '\0';
					}
			
			cadastrarcliente(arquivo, novoCliente);
			
			gerarelatorio(arquivo);
			printf("\nCliente cadastrado com sucesso!\n");
			system("pause");
			system("CLS");
			break;
		
		case 2: //Chama a função de consulta, dando opção de consultar por ID ou CPF do cliente.
			printf("De qual forma deseja consultar?\n1 - ID\n2 - CPF\n0 - Voltar\n");
			scanf("%d", &consulta);
			system("CLS");
			
			switch (consulta){
				
				case 1:
					printf("Informe o ID do cliente: ");
					scanf("%d", &id);
					system("CLS");
					consultaID(arquivo, id);
					system("pause");
					system("CLS");
				break;

				case 2:
					printf("Informe o CPF do cliente: ");
					scanf("%s", &cpf);
					consultaCPF(arquivo, cpf);
					system("pause");
					system("CLS");
					break;
				
				case 0:
					break;
				
				default:
					printf("Entre com uma opcao valida!\n");
					system("pause");
					system("CLS");
					break;
		}
		break;
		
		case 3: //Chama a função de editar dados do cliente, e as opções de edição. A busca do cliente só é possível por meio de CPF.
				printf("Informe o CPF do cliente: ");
				scanf("%s", &cpf);
				consultaCPF(arquivo, cpf);
				editarCPF(arquivo, cpf);
				
				gerarelatorio(arquivo);
				system("pause");
				system("CLS");
				break;
				
		case 4: //Chama a função de exclusão de cliente. A busca do cliente só é possível por meio de CPF.
			printf("Informe o CPF do cliente a ser excluido: ");
				scanf("%s", &cpf);
				
				fflush(stdin);
				
				if(consultaCPF(arquivo, cpf) == 1){
					printf("\nDeseja excluir o cliente? (s/n): ");
					dec = getchar();
										
					if(dec == 's'){
					excluircad(arquivo, cpf);
					gerarelatorio(arquivo);
					}
				}
				
				system("pause");
				system("CLS");
				break;

		case 0:
			printf("Encerrando o programa.\n");
			system("pause");
			fclose(arquivo);
			return 0;
			break;
			
		default:
			printf("Entre com uma operacao valida!\n");
			system("pause");
			system("CLS");
			fflush(stdin);
			break;
		}
	}
}
