#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa
{
  char cpf[12];
  char nome[100];
} Pessoa;

typedef struct veiculo
{
  char placa[8];
  char modelo[100];
  char cpf[12];
  char ano[5];
} Veiculo;

int pessoasTamanho;
int veiculosTamanho;

Pessoa *pessoas;
Veiculo *veiculos;

void inserePessoa(Pessoa pessoa)
{
  pessoasTamanho++;
  pessoas = realloc(pessoas, sizeof(Pessoa) * pessoasTamanho);
  pessoas[pessoasTamanho - 1] = pessoa;
}

void insereVeiculo(Veiculo veiculo)
{
  veiculosTamanho++;
  veiculos = realloc(veiculos, sizeof(Veiculo) * veiculosTamanho);
  veiculos[veiculosTamanho - 1] = veiculo;
}

void cadastraPessoa()
{
  system("clear");

  Pessoa pessoa;
  int pessoaExiste = 0;
  char continuar;

  printf("Digite o CPF da pessoa: ");
  scanf(" %[^\n]", pessoa.cpf);

  for (int indice = 0; indice < pessoasTamanho; indice++)
  {
    if (strcmp(pessoas[indice].cpf, pessoa.cpf) == 0)
    {
      pessoaExiste = 1;
    }
  }

  if (pessoaExiste)
  {
    system("clear");
    puts("PESSOA JÁ EXISTENTE! APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    scanf("%c", &continuar);
    return;
  }

  system("clear");
  printf("Digite o nome da pessoa: ");
  scanf(" %[^\n]", pessoa.nome);

  inserePessoa(pessoa);
}

void cadastraCarro()
{
  system("clear");

  Veiculo veiculo;
  int pessoaExiste = 0;
  int veiculoExiste = 0;
  char continuar;

  if (pessoasTamanho == 0)
  {
    puts("NENHUMA PESSOA CADASTRADA! APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    scanf("%c", &continuar);
    return;
  }

  printf("Digite o CPF do proprietário: ");
  scanf(" %[^\n]", veiculo.cpf);

  for (int indice = 0; indice < pessoasTamanho; indice++)
  {
    if (strcmp(pessoas[indice].cpf, veiculo.cpf) == 0)
    {
      pessoaExiste = 1;
    }
  }

  if (!pessoaExiste)
  {
    system("clear");
    puts("PESSOA NÃO EXISTENTE! APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    scanf("%c", &continuar);
    return;
  }

  system("clear");
  printf("Digite a placa do veiculo: ");
  scanf(" %[^\n]", veiculo.placa);

  for (int indice = 0; indice < veiculosTamanho; indice++)
  {
    if (strcmp(veiculos[indice].placa, veiculo.placa) == 0)
    {
      veiculoExiste = 1;
    }
  }

  if (veiculoExiste)
  {
    system("clear");
    puts("VEICULO JÁ EXISTENTE! APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    scanf("%c", &continuar);
    return;
  }

  system("clear");
  printf("Digite o modelo do veiculo: ");
  scanf(" %[^\n]", veiculo.modelo);

  system("clear");
  printf("Digite o ano do veiculo: ");
  scanf(" %[^\n]", veiculo.ano);

  insereVeiculo(veiculo);
}

void imprime()
{
  system("clear");
  char continuar;

  for (int indice = 0; indice < pessoasTamanho; indice++)
  {
    printf("DADOS DA PESSOA\n\n");

    printf("Nome: %s\n", pessoas[indice].nome);
    printf("CPF: %s\n\n", pessoas[indice].cpf);

    printf("VEICULOS DA PESSOA\n\n");

    for (int veiculoIndice = 0; veiculoIndice < veiculosTamanho; veiculoIndice++)
    {
      if (strcmp(veiculos[veiculoIndice].cpf, pessoas[indice].cpf) == 0)
      {
        printf("Placa: %s\n", veiculos[veiculoIndice].placa);
        printf("Modelo: %s\n", veiculos[veiculoIndice].modelo);
        printf("Ano: %s\n\n", veiculos[veiculoIndice].ano);
      }
    }

    puts("===============================================================");
  }

  puts("APERTE ENTER PARA VOLTAR AO MENU");
  getchar();
  scanf("%c", &continuar);
}

void init()
{
  veiculos = malloc(sizeof(Pessoa));
  pessoas = malloc(sizeof(Pessoa));
}

void salvaArquivos()
{
  FILE *arquivoPessoas;
  FILE *arquivoVeiculos;

  int podeSalvar = 0;
  int quantidadePessoas = 0;

  arquivoPessoas = fopen("pessoas.txt", "w");
  arquivoVeiculos = fopen("veiculos.txt", "w");

  for (int indice = 0; indice < pessoasTamanho; indice++)
  {

    for (int indiceVeiculo = 0; indiceVeiculo < veiculosTamanho; indiceVeiculo++)
    {
      if (strcmp(pessoas[indice].cpf, veiculos[indiceVeiculo].cpf) == 0)
      {
        quantidadePessoas++;
      }
    }
  }

  fprintf(arquivoPessoas, "%d\n", quantidadePessoas);
  for (int indice = 0; indice < pessoasTamanho; indice++)
  {
    podeSalvar = 0;

    for (int indiceVeiculo = 0; indiceVeiculo < veiculosTamanho; indiceVeiculo++)
    {
      if (strcmp(pessoas[indice].cpf, veiculos[indiceVeiculo].cpf) == 0)
      {
        podeSalvar = 1;
      }
    }

    if (podeSalvar)
    {
      fprintf(arquivoPessoas, "%s\n", pessoas[indice].cpf);
      fprintf(arquivoPessoas, "%s\n", pessoas[indice].nome);
    }
    else
    {
      quantidadePessoas--;
    }
  }

  fprintf(arquivoVeiculos, "%d\n", veiculosTamanho);
  for (int indice = 0; indice < veiculosTamanho; indice++)
  {
    fprintf(arquivoVeiculos, "%s\n", veiculos[indice].cpf);
    fprintf(arquivoVeiculos, "%s\n", veiculos[indice].ano);
    fprintf(arquivoVeiculos, "%s\n", veiculos[indice].modelo);
    fprintf(arquivoVeiculos, "%s\n", veiculos[indice].placa);
  }

  fclose(arquivoPessoas);
  fclose(arquivoVeiculos);
}

void carregaArquivos()
{
  char *linha;
  int numeroPessoas, numeroVeiculos;

  FILE *arquivoPessoas;
  FILE *arquivoVeiculos;

  arquivoPessoas = fopen("pessoas.txt", "r");
  arquivoVeiculos = fopen("veiculos.txt", "r");

  if (arquivoPessoas != NULL)
  {
    fscanf(arquivoPessoas, "%d", &numeroPessoas);
    for (int indice = 0; indice < numeroPessoas; indice++)
    {
      Pessoa pessoa;

      fscanf(arquivoPessoas, " %[^\n]", pessoa.cpf);
      fscanf(arquivoPessoas, " %[^\n]", pessoa.nome);

      inserePessoa(pessoa);
    }
    fclose(arquivoPessoas);
  }

  if (arquivoVeiculos != NULL)
  {
    fscanf(arquivoVeiculos, "%d", &numeroVeiculos);
    for (int indice = 0; indice < numeroVeiculos; indice++)
    {
      Veiculo veiculo;

      fscanf(arquivoVeiculos, " %[^\n]", veiculo.cpf);
      fscanf(arquivoVeiculos, " %[^\n]", veiculo.ano);
      fscanf(arquivoVeiculos, " %[^\n]", veiculo.modelo);
      fscanf(arquivoVeiculos, " %[^\n]", veiculo.placa);

      insereVeiculo(veiculo);
    }
    fclose(arquivoVeiculos);
  }
}

int menu()
{
  system("clear");
  int opcao;
  char continuar;

  puts("MENU DE OPÇÕES");
  puts("1 - CADASTRAR PESSOA");
  puts("2 - CADASTRAR CARRO");
  puts("3 - IMPRIMIR");
  puts("0 - SAIR");

  scanf(" %d", &opcao);

  switch (opcao)
  {
  case 1:
    cadastraPessoa();
    break;
  case 2:
    cadastraCarro();
    break;
  case 3:
    imprime();
    break;
  case 0:
    salvaArquivos();
    return 0;

  default:
    system("clear");
    puts("OPÇÃO INVÁLIDA! APERTE ENTER PARA VOLTAR AO MENU.");
    getchar();
    scanf("%c", &continuar);
    menu();
  }

  menu();
}

int main()
{
  init();
  carregaArquivos();
  menu();

  return 0;
}