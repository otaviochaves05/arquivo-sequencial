#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void gravarFibo(int n);
void verificarParImpar();
void verificarPrimo();
void verificarValores();
double a,b,c,numero;
FILE *arquivoPrincipal, *arquivoImpar, *arquivoPar, *arquivoPrimo, *arquivoTeste, *arquivoResultadoTeste;
int main()
{
    int op;
    setlocale(LC_ALL,"portuguese");
    printf("Escolha a opção que você deseja: \n");
    printf("1 - Gravar em um arquivo, no formato txt, os 64 primeiros valores da serie Fibonacci \n");
    printf("2 - ler o arquivo gerado anteriormente e armazenar os valores pares em um arquivo e os impares em outro arquivo utilize o formato txt \n");
    printf("3 - ler o arquivo inicialmente gerado e armazenar apenas os primos em um arquivo, no formato txt \n");
    printf("4 - leia um arquivo contendo um conjunto de valores (flag -1) e verifique para cada valor se ele se encontra ou não no arquivo gravado com a serie. Caso não exista deverá mostrar o valor anterior e o posterior a esse valor. Exemplo: caso seja lido o valor 8 – deverá ser mostrada a informação o valor 8 está no arquivo na posição 6, caso o valor lido seja o 15 – deverá ser mostrada a informação o valor 15 não está no arquivo, valores mais próximos: 13 e 21. Grave esses resultados em um arquivo no formato txt.\n");
    scanf("%i",&op);
    switch (op)
    {
    case 1:
        gravarFibo(64);
        break;
    case 2:
        gravarFibo(64);
        verificarParImpar();
        break;
    case 3:
        gravarFibo(64);
        verificarPrimo();
        break;
    case 4:
        gravarFibo(64);
        verificarValores();
        break;

    }
    return 0;
}

void gravarFibo(int n)
{
    //arquivo = fopen("fibonacci.txt","w");
    if ((arquivoPrincipal = fopen("fibonacci.txt", "w"))== NULL)
    {
        printf("Erro arquivo fibonacci.txt!\n");
    }

    a=b=1;
    fprintf(arquivoPrincipal, "%.0lf\n",a);
    fprintf(arquivoPrincipal, "%.0lf\n",b);
    for (int i=3; i<=n ; i++)
    {
        c=a+b;
        fprintf(arquivoPrincipal,"%.0lf\n",c);
        a=b;
        b=c;
    }
    fclose(arquivoPrincipal);
}

void verificarParImpar()
{
    arquivoPrincipal = fopen("fibonacci.txt","r");
    if (arquivoPrincipal== NULL)
    {
        printf("Erro arquivo fibonacci.txt!\n");
    }
    arquivoImpar = fopen("impares.txt","w");
    arquivoPar = fopen("pares.txt","w");
    if (arquivoImpar == NULL || arquivoPar == NULL)
    {
        printf("Erro Pares e Impares!\n");
    }
    for (int i=0; i<= 63; i++)
    {
        fscanf(arquivoPrincipal,"%lf",&numero);
        if (fmod(numero,2) == 0)
        {
            fprintf(arquivoPar,"%.0lf\n",numero);
        }
        else
        {
            fprintf(arquivoImpar,"%.0lf\n",numero);
        }
    }
    fclose(arquivoPrincipal);
    fclose(arquivoPar);
    fclose(arquivoImpar);
}

void verificarPrimo()
{
    if ((arquivoPrincipal = fopen("fibonacci.txt", "r")) == NULL)
    {
        printf("Erro arquivo fibonacci.txt!\n");
    }

    if ((arquivoPrimo = fopen("primos.txt", "w")) == NULL)
    {
        printf("Erro arquivo primos.txt!\n");
    }
    while (fscanf(arquivoPrincipal, "%lf", &numero) != EOF)
    {
        int divisores = 0;
        for (int i = 2; i <= sqrt(numero); i++)
        {
            if (fmod(numero, i) == 0)
            {
                divisores++;
            }
        }
        if (divisores == 0 && numero > 1)
        {
            fprintf(arquivoPrimo, "%.0lf\n", numero);
        }
    }
    fclose(arquivoPrincipal);
    fclose(arquivoPrimo);
}

void verificarValores()
{
    if ((arquivoTeste = fopen("teste.txt", "w")) == NULL)
    {
        printf("Erro arquivo teste.txt!\n");
        exit(1);
    }

    printf("Insira os valores a serem testados (digite -1 para terminar):\n");
    while (1)
    {
        scanf("%lf", &numero);
        if (numero == -1)
        {
            break;
        }
        fprintf(arquivoTeste, "%.0lf\n", numero);
    }
    fclose(arquivoTeste);

    // Abrir o arquivo teste.txt para leitura
    if ((arquivoTeste = fopen("teste.txt", "r")) == NULL)
    {
        printf("Erro arquivo teste.txt!\n");
        exit(1);
    }

    // Abrir o arquivo fibonacci.txt para leitura
    if ((arquivoPrincipal = fopen("fibonacci.txt", "r")) == NULL)
    {
        printf("Erro arquivo fibonacci.txt!\n");
        fclose(arquivoTeste);
        exit(1);
    }

    // Ler os valores da série de Fibonacci para um array
    double fibonacci[64];
    for (int i = 0; i < 64; i++)
    {
        fscanf(arquivoPrincipal, "%lf", &fibonacci[i]);
    }
    fclose(arquivoPrincipal);

    // Abrir o arquivo resultado-do-teste.txt para escrita
    if ((arquivoResultadoTeste = fopen("resultado-do-teste.txt", "w")) == NULL)
    {
        printf("Erro arquivo resultado-do-teste.txt!\n");
        fclose(arquivoTeste);
        exit(1);
    }

    // Ler valores do arquivo teste.txt e verificar contra a série de Fibonacci
    while (fscanf(arquivoTeste, "%lf", &numero) != EOF)
    {
        int encontrado = 0;
        for (int i = 0; i < 64; i++)
        {
            if (numero == fibonacci[i])
            {
                fprintf(arquivoResultadoTeste, "O valor %.0lf está no arquivo na posição %d.\n", numero, i + 1);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
        {
            double anterior = -1, posterior = -1;
            for (int i = 0; i < 64; i++)
            {
                if (fibonacci[i] < numero)
                {
                    anterior = fibonacci[i];
                }
                if (fibonacci[i] > numero && posterior == -1)
                {
                    posterior = fibonacci[i];
                }
                if (anterior != -1 && posterior != -1)
                {
                    break;
                }
            }
            fprintf(arquivoResultadoTeste, "O valor %.0lf não está no arquivo, valores mais próximos: %.0lf e %.0lf.\n", numero, anterior, posterior);
        }
    }

    fclose(arquivoTeste);
    fclose(arquivoResultadoTeste);

}



