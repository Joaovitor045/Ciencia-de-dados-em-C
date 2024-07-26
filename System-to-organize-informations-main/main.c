/************************************************************************************
  Aluno: João Vitor Alves Viana
  Matrícula: 22006122

  Declaro que eu sou o autor deste trablho e que o código não foi copiado de outra 
  pessoa nem repassado para alguém. Estou ciente de que poderei sofrer penalizações na 
  avaliação em caso de detecção de plágio.
*************************************************************************************/
  

// Inclusão de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Comandos para dar funcionalidade ao menu
#define CONSULTAR_MINIUSINA 1
#define CONSULTAR_CONSUMIDOR 2
#define LISTAR_MINIUSINA 3
#define LISTAR_MINIUSINA_CAPACIDADE_DECRESCENTE 4
#define LISTAR_RA_QUANTIDADE_MINIUSINA_DESCRESCENTE 5
#define LISTAR_RA_NUMERO_CONTRATO_CRESCENTE 6
#define LISTAR_RA_CAPACIDADE_DECRESCENTE 7
#define LISTAR_RA_CAPACIDADE_DISPONIVEL_DECRESCENTE 8
#define SAIR 9


// Comandos para dar tamanho aos dados
#define MAX_CNPJ 19
#define MAX_NOME 1000
#define MAX_CPF 14
#define MAX_TODOS 100
#define MAX_CONTRATOS 100
#define MAX_MINIUSINAS 100
#define MAX_CONSUMIDORES 100
#define MAX_RAS 100



// Struct para definir uma miniusina
struct miniusina {
    char cnpj[MAX_CNPJ];
    char nome[MAX_NOME];
    float capacidade_total;
    int ra;
    char status_usina[100];
};


// Struct para definir um consumidor
struct consumidor {
char cnpjcpf[MAX_CNPJ];
char nome[MAX_NOME];
int ra;
};


// Struct para definir uma RA
struct ra {
    int id_ra;
    char nome_ra[MAX_NOME];
    int qtd_miniusinas;
    float capacidade_total;
};

// Struct para definir um contrato
struct Contrato {
    char id_contrato[MAX_TODOS];
    char id_consumidor[MAX_TODOS];
    char cnpj_miniusina[MAX_TODOS];
    char data_inicio_contrato[MAX_TODOS];
    char energia_contratada[MAX_TODOS];
};

// Struct para definir uma miniusina
struct Miniusina {
    char cnpj_miniusina[MAX_TODOS];
    char nome_miniusina[MAX_TODOS];
    char capacidade_total[MAX_TODOS];
    char id_ra[MAX_TODOS];
    char status_usina[MAX_TODOS];
};

// Struct para definir um consumidor
struct Consumidor {
    char id_consumidor[MAX_TODOS];
    char nome[MAX_TODOS];
    char id_ra[MAX_TODOS];
};

// Struct para definir uma RA em uma função diferente
struct RA {
    char id_ra[MAX_TODOS];
    char nome_ra[MAX_TODOS];
    int num_contratos;
};

// Struct para definir uma miniusina
struct Miniusina2 {
    char cnpj_miniusina[20];
    char nome_miniusina[100];
    float capacidade_total;
    int id_ra;
    char status_usina[20];
};

// Struct para definir um contrato
struct Contrato2 {
    int id_contrato;
    char id_consumidor[20];
    char cnpj_miniusina[20];
    char data_inicio_contrato[20];
    float energia_contratada;
};

// Struct para definir uma RA 
struct RA2 {
    int id_ra;
    char nome_ra[50];
};




// Função para validar um CNPJ no formato (123.456.789/0001-12)
int validarCNPJ(const char* cnpj) {
    int i;
    int tamanho = strlen(cnpj);

// Verificar se o CNPJ possui 14 dígitos e caracteres especiais
    if (tamanho != 14 && tamanho != 18)
        return 0;

    for (i = 0; i < tamanho; i++) {
// Verificar se cada caractere é um dígito numérico ou um caractere especial permitido
        if ((cnpj[i] < '0' || cnpj[i] > '9') && cnpj[i] != '.' && cnpj[i] != '/' && cnpj[i] != '-')
            return 0;
    }

    return 1;
}


// Função para validar um CPF no formarto (123.456.789-12)
int validarCPF(const char* cpf) {
    int i;
    int tamanho = strlen(cpf);

// Verificar se o CPF possui 11 dígitos (sem contar os caracteres especiais)
    if (tamanho != 11)
        return 0;

    for (i = 0; i < tamanho; i++) {
// Verificar se cada caractere é um dígito numérico ou um caractere especial válido
        if ((cpf[i] < '0' || cpf[i] > '9') && cpf[i] != '.' && cpf[i] != '-')
            return 0;
    }

    return 1;
}


// Função de comparação utilizada para ordenar as miniusinas por capacidade
int comparar_capacidade_miniusina(const void *a, const void *b) {
    const struct miniusina *miniusina_a = (const struct miniusina *)a;
    const struct miniusina *miniusina_b = (const struct miniusina *)b;

// Ordenar em ordem decrescente
    if (miniusina_a->capacidade_total > miniusina_b->capacidade_total)
        return -1;
    else if (miniusina_a->capacidade_total < miniusina_b->capacidade_total)
        return 1;
    else
        return 0;
}

// Função de comparação utilizada para ordenar as RAs por quantidade de miniusinas
int comparar_RA_info(const void *a, const void *b) {
    const struct ra *info_a = (const struct ra *)a;
    const struct ra *info_b = (const struct ra *)b;
  
// Ordenar em ordem decrescente
    if (info_a->qtd_miniusinas < info_b->qtd_miniusinas)
        return 1;
    else if (info_a->qtd_miniusinas > info_b->qtd_miniusinas)
        return -1;
    else
        return 0;
}

// Função para ordenar as RAs por capacidade total
int comparar_capacidade_ra(const void *a, const void *b) {
    const struct ra *ra1 = (const struct ra *)a;
    const struct ra *ra2 = (const struct ra *)b;

  // Ordenar em ordem decrescente
    if (ra1->capacidade_total < ra2->capacidade_total) {
        return 1;
    } else if (ra1->capacidade_total > ra2->capacidade_total) {
        return -1;
    }
    return 0;
}


// Função para ordenar as RAs por quantidade de contratos
int comparar_ra_contrato(const void* a, const void* b) {

// Ordenar em ordem crescente
    struct RA* ra1 = (struct RA*)a;
    struct RA* ra2 = (struct RA*)b;
    return ra1->num_contratos - ra2->num_contratos;
}



// Função para mostrar o menu de opções na tela
void menu() {
    printf("O que deseja executar?\n");
    printf("(1) Consultar miniusina cadastrada\n");
    printf("(2) Consultar consumidor cadastrado\n");
    printf("(3) Listar miniusinas cadastradas\n");
    printf("(4) Listar miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
    printf("(5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
    printf("(6) Listar as RAs por ordem crescente de número de contratos\n");
    printf("(7) Listar as RAs por ordem decrescente de capacidade de geração\n");
    printf("(8) Listar as RAs por ordem decrescente de percentual de energia disponível\n");
    printf("(9) Sair do programa\n");
}


// Função para limpar o buffer e possibilitar a leitura do nome
void limpar_buffer(){

char ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
  }


// Função para pausar o programa e só voltar quando for pressionado alguma tecla
void pause(){
  printf("\n");
  printf ("Pressione qualquer tecla para continuar...");
  getc(stdin);
  }


// Função para limpar a tela
void limpar_tela(){

  #if defined(linux) || defined(unix) || defined(APPLE)
         system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
         system("cls");
  #endif
}


// Função(1) para consultar miniusina cadastrada pelo CNPJ
void consultar_miniusina() {
  
// Declaração de variáveis
    FILE *arquivo_miniusinas;
    struct miniusina miniusina_cadastrada;
    char cnpj_consulta[MAX_CNPJ];
    int encontrei_miniusina = 0;
    char primeira_linha[1000];

// Coletar CNPJ a ser consultado
    printf("Insira o CNPJ a ser consultado no formato (00.000.000/0000-00): ");
    scanf(" %[^\n]", cnpj_consulta);
  
// Validar CNPJ
  int cnpjValido = validarCNPJ(cnpj_consulta);
    if (!cnpjValido) {
        printf("CNPJ inválido: %s\n", cnpj_consulta);
        return;
    }
  
// Abrir arquivo
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
  
// Verificar se arquivo foi aberto e pular a primeira linha
    if (arquivo_miniusinas != NULL) {
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
      
// Leitura de dados dentro do arquivo
        while (!feof(arquivo_miniusinas)) {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^;\n]\n",
       miniusina_cadastrada.cnpj,
       miniusina_cadastrada.nome,
       &miniusina_cadastrada.capacidade_total,
       &miniusina_cadastrada.ra,
       &miniusina_cadastrada.status_usina);
          
// Comparação do CNPJ digitado com o do arquivo para mostrar os dados da miniusina consultada
            if (strcmp(cnpj_consulta, miniusina_cadastrada.cnpj) == 0) {
                printf("CNPJ: %s\n", miniusina_cadastrada.cnpj);
                printf("Nome: %s\n", miniusina_cadastrada.nome);
                printf("Capacidade: %.1f\n", miniusina_cadastrada.capacidade_total);
                printf("RA: %d\n", miniusina_cadastrada.ra);
                printf("Status: %s\n", miniusina_cadastrada.status_usina);
                encontrei_miniusina = 1;
                break;
            }
        }
      
// Verificar se a miniusina foi encontrada
        if (encontrei_miniusina == 0) {
            printf("Não foi possível encontrar a miniusina com o CNPJ: %s.\n", cnpj_consulta);
        }
      
// Fechar o arquivo
        fclose(arquivo_miniusinas);
    } else {
        printf("Não foi possível abrir o arquivo.\n");
    }
}


// Função(2) para consultar consumidor cadastrado 
void consultar_consumidor() {
  
// Declaração de variáveis    
  FILE *arquivo_consumidores;
    struct consumidor consumidor_cadastrado;
    char cnpjcpf_consulta[MAX_CNPJ];
    int encontrei_consumidor = 0;
    char primeira_linha[1000];
  
// Coletar CNPJ/CPF a ser consultado
    printf("Insira o CNPJ/CPF a ser consultado no formato (000.000.000-00) caso seja CPF ou (000.000.000/0000-00) caso seja CNPJ: ");
    scanf(" %[^\n]", cnpjcpf_consulta);

// Verificar se é um CNPJ válido
    if (validarCNPJ(cnpjcpf_consulta)) {
      
// Se for um CNPJ válido, realizar a consulta do consumidor por CNPJ
// Abrir o arquivo
        arquivo_consumidores = fopen("consumidores.csv", "r");
      
// Verificar se arquivo foi aberto e pular a primeira linha
        if (arquivo_consumidores != NULL) {
            fscanf(arquivo_consumidores, "%[^\n]\n", primeira_linha);
          
// Coletar os dados de dentro do arquivo
            while (!feof(arquivo_consumidores)) {
                fscanf(arquivo_consumidores, "%[^;];%[^;];%d\n",
                    consumidor_cadastrado.cnpjcpf,
                    consumidor_cadastrado.nome,
                    &consumidor_cadastrado.ra);
              
// Verificar se existe um CNPJ/CPF cadastrado e mostrar os dados referentes ao consumidor cadastrado
                if (strcmp(cnpjcpf_consulta, consumidor_cadastrado.cnpjcpf) == 0) {
                    printf("CNPJ/CPF: %s\n", consumidor_cadastrado.cnpjcpf);
                    printf("Nome: %s\n", consumidor_cadastrado.nome);
                    printf("RA: %d\n", consumidor_cadastrado.ra);
                    encontrei_consumidor = 1;
                    break;
                }
            }
          
// Verificar se o consumidor foi encontrado
            if (encontrei_consumidor == 0) {
                printf("Não foi possível encontrar o consumidor com o CNPJ/CPF: %s.\n", cnpjcpf_consulta);
            }
          
// fechar o arquivo
            fclose(arquivo_consumidores);
        } else {
            printf("Não foi possível abrir o arquivo.\n");
        }
    } else {
      
// Se não é um CNPJ válido, verificar se é um CPF válido
        if (validarCPF(cnpjcpf_consulta)) {
          
// Se for um CPF válido, realizar a consulta do consumidor por CPF
            
            printf("CPF válido: %s\n", cnpjcpf_consulta);
        } else {
            printf("CNPJ/CPF inválido: %s\n", cnpjcpf_consulta);
        }
    }
}


// Função(3) para listar as miniusinas
void listar_miniusina(){
  
// Declarações de variáveis   
  FILE *arquivo_miniusinas;
    struct miniusina miniusina_cadastrada;
    int encontrei_miniusina = 0;
    char primeira_linha[1000];
  
// Abrir arquivo
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
  
// Verificar se o arquivo foi aberto e plar primeira linha
    if (arquivo_miniusinas != NULL) {
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
      
// Ler as miniusinas do arquivo
        while (!feof(arquivo_miniusinas)) {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^;\n]\n",
                   miniusina_cadastrada.cnpj,
                   miniusina_cadastrada.nome,
                   &miniusina_cadastrada.capacidade_total,
                   &miniusina_cadastrada.ra,
                   &miniusina_cadastrada.status_usina);
          
// Mostrar todas as miniunsinas cadastradas
            printf("CNPJ: %s\n", miniusina_cadastrada.cnpj);
            printf("Nome: %s\n", miniusina_cadastrada.nome);
            printf("Capacidade: %.1f\n", miniusina_cadastrada.capacidade_total);
            printf("RA: %d\n", miniusina_cadastrada.ra);
            printf("Status: %s\n", miniusina_cadastrada.status_usina);
            printf("\n");
        }
      
// Fechar aqrquivo
        fclose(arquivo_miniusinas);
    } else {
        printf("Não foi possível abrir o arquivo.\n");
    }
}


// Função(4) para listar as miniusinas por capacidade e de forma decrescente
void listar_miniusina_capacidade_decrescente() {
  
// Declaração de variáveis
    FILE *arquivo_miniusinas;
    struct miniusina miniusina_cadastrada;
    int encontrei_miniusina = 0;
    char primeira_linha[1000];
    struct miniusina miniusinas[200];  
    int num_miniusinas = 0;
  
// Abrir o arquivo
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
  
// Verificar se o arquivo foi aberto e pular primeira linha
    if (arquivo_miniusinas != NULL) {
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
      
// Ler as informações do arquivo das miniusinas
        while (!feof(arquivo_miniusinas)) {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^;\n]\n",
                   miniusinas[num_miniusinas].cnpj,
                   miniusinas[num_miniusinas].nome,
                   &miniusinas[num_miniusinas].capacidade_total,
                   &miniusinas[num_miniusinas].ra,
                   miniusinas[num_miniusinas].status_usina);
            num_miniusinas++;
        }
      
// Fechar o arquivo
        fclose(arquivo_miniusinas);
      
// Ordenar as miniusinas em ordem decrescente
        qsort(miniusinas, num_miniusinas, sizeof(struct miniusina), comparar_capacidade_miniusina);
      
// Colocar as informações coletadas na tela em ordem decrescente
        for (int i = 0; i < num_miniusinas; i++) {
            printf("CNPJ: %s\n", miniusinas[i].cnpj);
            printf("Nome: %s\n", miniusinas[i].nome);
            printf("Capacidade: %.1f\n", miniusinas[i].capacidade_total);
            printf("RA: %d\n", miniusinas[i].ra);
            printf("Status: %s\n", miniusinas[i].status_usina);
            printf("\n");
        }
    } else {
        printf("Não foi possível abrir o arquivo.\n");
    }
}


// Função(5) para listar as RAs por quantidade de miniusina e em ordem decrescente
void listar_ra_quantidade_miniusina_decrescente() {
  
// Declarar variáveis
    FILE *arquivo_miniusinas;
    FILE *arquivo_ra;
    struct ra RA_infos[100];
    int num_RAs = 0;
    int id_ra = 0;
    char primeira_linha[1000];
  
// Abrir os arquivos
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ra = fopen("ra.csv", "r");
  
// Verificar os arquivos foram abertos 
    if (arquivo_miniusinas != NULL || arquivo_ra != NULL) {
        fscanf(arquivo_ra, "%[^\n]\n", primeira_linha);
      
// Ler os dados do arquivo de RAs
        while (fscanf(arquivo_ra, "%d;%[^\n]", &RA_infos[num_RAs].id_ra, RA_infos[num_RAs].nome_ra) == 2) {
            RA_infos[num_RAs].qtd_miniusinas = 0;
            num_RAs++;
        }

        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
      
// Ler os dados do arquivo das miniusinas e comparar o id_ra 
        while (fscanf(arquivo_miniusinas, "%*[^;];%*[^;];%*[^;];%d;", &id_ra) == 1) {
            for (int i = 0; i < num_RAs; i++) {
                if (RA_infos[i].id_ra == id_ra) {
                    RA_infos[i].qtd_miniusinas++;
                    break;
                }
            }
        }
// Fechar os arquivos
        fclose(arquivo_miniusinas);
        fclose(arquivo_ra);
      
// Ordenar as RAs
        qsort(RA_infos, num_RAs, sizeof(struct ra), comparar_RA_info);
      
// Colocar na tela as RAs já ordenadas
        printf("RAs por quantidade de miniusinas (ordem decrescente):\n\n");
        for (int i = 0; i < num_RAs; i++) {
            printf("Quantidade de miniusinas: %d\n", RA_infos[i].qtd_miniusinas);
            printf("ID-RA: %d\n", RA_infos[i].id_ra);
            printf("Nome: %s\n", RA_infos[i].nome_ra);
            printf("\n");
        }
    } else {
        printf("Não foi possível abrir o arquivo.\n");
    }
}


// Função(6) para listar as RAs pelo número de contratos (em ordem crescente)
void listar_ra_numero_contrato_crescente() {
  
// Declaração de variáveis
    FILE* arquivo_contratos;
    FILE* arquivo_miniusinas;
    FILE* arquivo_consumidores;
    FILE* arquivo_ra;
    struct Consumidor consumidores[MAX_CONSUMIDORES];
    int num_consumidores = 0;
    struct Miniusina miniusinas[MAX_MINIUSINAS];
    int num_miniusinas = 0;
    struct Contrato contratos[MAX_CONTRATOS];
    int num_contratos = 0;
    char line[MAX_TODOS];
    struct RA ras[MAX_RAS];
    int num_ras = 0;
    int contratos_por_miniusina[MAX_MINIUSINAS] = {0};
  
// Abrir os arquivos
  arquivo_contratos = fopen("contratos.csv", "r");
  arquivo_miniusinas = fopen("miniusinas.csv", "r");
  arquivo_consumidores = fopen("consumidores.csv", "r");
  arquivo_ra = fopen("ra.csv", "r");

// Verificar se os arquivos foram abertos e pular as primeiras linhas
    if (arquivo_contratos != NULL || arquivo_miniusinas != NULL || arquivo_consumidores!= NULL || arquivo_ra != NULL) {
      fscanf(arquivo_ra, "%*[^\n]\n");
      fscanf(arquivo_contratos, "%*[^\n]\n");
      fscanf(arquivo_miniusinas, "%*[^\n]\n");
      fscanf(arquivo_consumidores, "%*[^\n]\n");

// Ler os dados dos contratos
        while (fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%s\n",
          contratos[num_contratos].id_contrato,
          contratos[num_contratos].id_consumidor,
          contratos[num_contratos].cnpj_miniusina,
          contratos[num_contratos].data_inicio_contrato,
          contratos[num_contratos].energia_contratada) == 5 && num_contratos < MAX_CONTRATOS) {
        num_contratos++;
    }
      
// Ler os dados das miniusinas
    while (fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%s\n", 
          miniusinas[num_miniusinas].cnpj_miniusina,
          miniusinas[num_miniusinas].nome_miniusina,
          miniusinas[num_miniusinas].capacidade_total,
          miniusinas[num_miniusinas].id_ra,
          miniusinas[num_miniusinas].status_usina) == 5 && num_miniusinas < MAX_MINIUSINAS) {
        num_miniusinas++;
    }
      
// Ler os dados dos consumidores
    while (fscanf(arquivo_consumidores, "%s\n",
          consumidores[num_consumidores].id_ra) == 1 && num_consumidores < MAX_CONSUMIDORES) {
        num_consumidores++;
    }
      
// Ler os dados das RAs
    while (fscanf(arquivo_ra, "%[^;];%[^\n]\n",
          ras[num_ras].id_ra, 
          ras[num_ras].nome_ra) == 2 && num_ras < MAX_RAS) {
          ras[num_ras].num_contratos = 0;
        num_ras++;
    }

// Contar quantos contratos cada miniusina possui
    for (int i = 0; i < num_contratos; i++) {
        for (int j = 0; j < num_miniusinas; j++) {
          if (strcmp(contratos[i].cnpj_miniusina, miniusinas[j].cnpj_miniusina) == 0) {
                contratos_por_miniusina[j]++;
                break;
            }
        }
    }

// Relacionar a quantidade de contratos por RA
    for (int i = 0; i < num_miniusinas; i++) {
        for (int j = 0; j < num_ras; j++) {
            if (strcmp(miniusinas[i].id_ra, ras[j].id_ra) == 0) {
                ras[j].num_contratos += contratos_por_miniusina[i];
                break;
            }
        }
    }

// Ordenar os RAs por número de contratos em ordem crescente
    qsort(ras, num_ras, sizeof(struct RA), comparar_ra_contrato);

// Imprimir o número de contratos por RA em ordem crescente
    for (int i = 0; i < num_ras; i++) {
        printf("ID_RA: %s\nNome RA: %s\nContratos: %d\n\n", ras[i].id_ra, ras[i].nome_ra, ras[i].num_contratos);
    }

// Fechar os arquivos
    fclose(arquivo_ra);
    fclose(arquivo_contratos);
    fclose(arquivo_miniusinas);
    fclose(arquivo_consumidores);
}else {
        printf("Não foi possível abrir o arquivo.\n");
    }
}


// Função(7) para listar as RAs por capacidade e em ordem crescente
void listar_ra_capacidade_decrescente() {
  
// Declaração de variáveis
    FILE *arquivo_miniusinas;
    FILE *arquivo_ra;
    struct ra RA_infos[300];
    int num_RAs = 0;
    char primeira_linha[1000];
  
// Abrir os arquivos
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ra = fopen("ra.csv", "r");
  
// Verificar se foi aberto os dois arquivos e pular primeira linha
    if (arquivo_miniusinas != NULL && arquivo_ra != NULL) {
        fscanf(arquivo_ra, "%[^\n]\n", primeira_linha);
      
// Ler informações do arquivo ra
        while (fscanf(arquivo_ra, "%d;%[^\n]", 
          &RA_infos[num_RAs].id_ra, 
          RA_infos[num_RAs].nome_ra) == 2) {
          RA_infos[num_RAs].capacidade_total = 0;
            num_RAs++;
        }
      
// Descartar a primeira linha
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
      
// Ler as informações do arquivo miniusinas
        while (fscanf(arquivo_miniusinas, "%*[^;];%*[^;];%f;%d;%*[^;\n]\n", 
          &RA_infos[num_RAs].capacidade_total, 
          &RA_infos[num_RAs].id_ra) == 2) {
            num_RAs++;
        }
      
// Fechar os arquivos
        fclose(arquivo_miniusinas);
        fclose(arquivo_ra);

// Somar a capacidade total para IDs repetidos
        for (int i = 0; i < num_RAs; i++) {
            for (int j = i + 1; j < num_RAs; j++) {
                if (RA_infos[i].id_ra == RA_infos[j].id_ra) {
                    RA_infos[i].capacidade_total += RA_infos[j].capacidade_total;
                    RA_infos[j].capacidade_total = 0;
                }
            }
        }

// Ordenar as RAs
        qsort(RA_infos, num_RAs, sizeof(struct ra), comparar_capacidade_ra);
      
// Mostrar na tela todas as RAs já ordenadas
        printf("RAs por capacidade total (ordem decrescente):\n\n");
        for (int i = 0; i < num_RAs; i++) {
            if (RA_infos[i].capacidade_total > 0) {
                printf("RA ID: %d\n", RA_infos[i].id_ra);
                printf("RA Nome: %s\n", RA_infos[i].nome_ra);
                printf("Capacidade Total: %.1f\n", RA_infos[i].capacidade_total);
                printf("\n");
            }
        }
    } else {
        printf("Não foi possível abrir os arquivos.\n");
    }
}


// Função(8) para listar as RAs por capacidade disponivel (em ordem decrescente)
void listar_ra_capacidade_disponivel_decrescente() {

// Declaração de variáveis
    struct Miniusina2 miniusinas[100];
    struct Contrato2 contratos[100];
    struct RA2 ras[100];
    int num_miniusinas = 0, num_contratos = 0, num_ras = 0;
    char primeira_linha[1000];
    FILE* arquivo_contratos = fopen("contratos.csv", "r");
    FILE* arquivo_ra = fopen("ra.csv", "r");
    FILE* arquivo_miniusinas = fopen("miniusinas.csv", "r");

// Verificar se os arquivos foram abertos e pular a primeira linha
    if (arquivo_miniusinas != NULL || arquivo_ra != NULL || arquivo_contratos != NULL) {
    fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
    fscanf(arquivo_contratos, "%[^\n]\n", primeira_linha);
    fscanf(arquivo_ra, "%[^\n]\n", primeira_linha);

// Ler os dados das miniusinas
    while (fgets(primeira_linha, sizeof(primeira_linha), arquivo_miniusinas) != NULL) {
        sscanf(primeira_linha, "%[^;];%[^;];%f;%d;%[^;]", 
          miniusinas[num_miniusinas].cnpj_miniusina,
          miniusinas[num_miniusinas].nome_miniusina, 
          &miniusinas[num_miniusinas].capacidade_total,
          &miniusinas[num_miniusinas].id_ra, 
          miniusinas[num_miniusinas].status_usina);
        num_miniusinas++;
    }
  
// Ler os dados dos contratos    
    while (fgets(primeira_linha, sizeof(primeira_linha), arquivo_contratos) != NULL) {
        sscanf(primeira_linha, "%d;%[^;];%[^;];%[^;];%f", 
          &contratos[num_contratos].id_contrato,
          contratos[num_contratos].id_consumidor, 
          contratos[num_contratos].cnpj_miniusina,
          contratos[num_contratos].data_inicio_contrato, 
          &contratos[num_contratos].energia_contratada);
        num_contratos++;
    }
    
// Ler os dados das RAs 
    while (fgets(primeira_linha, sizeof(primeira_linha), arquivo_ra) != NULL) {
        sscanf(primeira_linha, "%d;%[^;]", 
          &ras[num_ras].id_ra,
          ras[num_ras].nome_ra);
        num_ras++;
    }

// Fechar os arquivos
    fclose(arquivo_miniusinas);
    fclose(arquivo_ra);
    fclose(arquivo_contratos);
  
// Calcular a capacidade disponível em cada RA
    float capacidade_total_ra[100] = {0};
    float capacidade_contratada_ra[100] = {0};
    for (int i = 0; i < num_miniusinas; i++) {
        capacidade_total_ra[miniusinas[i].id_ra] += miniusinas[i].capacidade_total;
    }

// Relacionar a quantidade contratada com a capacidade total das miniusinas
    for (int i = 0; i < num_contratos; i++) {
        for (int j = 0; j < num_miniusinas; j++) {
            if (strcmp(contratos[i].cnpj_miniusina, miniusinas[j].cnpj_miniusina) == 0) {
                capacidade_contratada_ra[miniusinas[j].id_ra] += contratos[i].energia_contratada;
                break;
            }
        }
    }

// Calcular a capacidade disponível em cada RA após considerar os contratos
    float capacidade_disponivel_ra[100] = {0};
    for (int i = 0; i < num_ras; i++) {
        int id_ra = ras[i].id_ra;
        capacidade_disponivel_ra[id_ra] = capacidade_total_ra[id_ra] - capacidade_contratada_ra[id_ra];
    }

// Ordenar as RAs por capacidade disponível 
    for (int i = 0; i < num_ras - 1; i++) {
        for (int j = i + 1; j < num_ras; j++) {
            if (capacidade_disponivel_ra[ras[i].id_ra] < capacidade_disponivel_ra[ras[j].id_ra]) {
                struct RA2 temp = ras[i];
                ras[i] = ras[j];
                ras[j] = temp;
            }
        }
    }

// Definir RAs com o percentual disponível em cada uma
    float total_capacidade_disponivel = 0;
    for (int i = 0; i < num_ras; i++) {
        total_capacidade_disponivel += capacidade_disponivel_ra[ras[i].id_ra];
    }
      
// Mostrar as RAs na tela
    for (int i = 0; i < num_ras; i++) {
        float percentual_disponivel = (capacidade_disponivel_ra[ras[i].id_ra] / capacidade_total_ra[ras[i].id_ra]) * 100;
        printf("ID RA: %d\n", ras[i].id_ra);
        printf("Nome RA: %s", ras[i].nome_ra);
        printf("Percentual Disponível: %.2f%%\n", percentual_disponivel);
        printf("\n");
    }
}else {
        printf("Não foi possível abrir os arquivos.\n");
    }
}

// Função principal para dar funcionalidade ao menu de opções
int main() {
    int opcao;
    
  do{
    menu();
    scanf("%d",&opcao);
    
    
    switch (opcao){

      case CONSULTAR_MINIUSINA:
      consultar_miniusina();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case CONSULTAR_CONSUMIDOR:
      consultar_consumidor();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_MINIUSINA:
      listar_miniusina();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_MINIUSINA_CAPACIDADE_DECRESCENTE:
      listar_miniusina_capacidade_decrescente();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_RA_QUANTIDADE_MINIUSINA_DESCRESCENTE:
      listar_ra_quantidade_miniusina_decrescente();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_RA_NUMERO_CONTRATO_CRESCENTE:
      listar_ra_numero_contrato_crescente();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_RA_CAPACIDADE_DECRESCENTE:
      listar_ra_capacidade_decrescente();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case LISTAR_RA_CAPACIDADE_DISPONIVEL_DECRESCENTE:
      listar_ra_capacidade_disponivel_decrescente();
      limpar_buffer();
      pause();
      limpar_tela();
      break;

      case SAIR:
      printf("Encerrando o sistema...\n\n");
      break;

      

      default:
      printf("Opção inválida\n");

    }
    }
    while(opcao != SAIR);
  return 1;
}