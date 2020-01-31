#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long int ePrimo(long long int p)
{
    int i;
    long long int j;
    
    //Calcula a raiz quadrada para p
    j = sqrt(p);

    for(i = 2; i <= j; i++)
    {
        //Retorna 0 caso não seja um número primo
        if(p % i == 0)
        {
            return 0;
        }
    }
    //Retorna 1 quando é um número primo
    return 1;
}
long long int mdc( long long int x, long long int y)
{
    long long int resultado;
    if (y == 0)
    {
        return x;
    }
    else
    {
        resultado = mdc(y , x % y);
        return resultado;
    }
}
long long int inversoMod(long long int a, long long int b)
{
    long long int quociente[100000], valor[100000], i = 0, x = 0, k, resto, d = 0, phi;
    phi = a;

    while(b != 0)
    {
        quociente[i] = a/b;
        i++;
        resto = a % b;
        a = b;
        b = resto;
    }
    valor[0] = 1;
    for (k = i - 2; k >= 0; k--)
    {
        if(x == 0)
        {
            valor[x + 1] = quociente[k] * valor[x];
            x++;
        }
        else
        {
            valor[x + 1] = (quociente[k] * valor[x]) + valor[x -1];
            x++;
        }
    }
    if (x % 2 == 0)
    {
        d = valor[x];
        return d;
    }
    else
    {
        d = -valor[x];
        while(1)
        {
            d = d + phi;
            if (d >= 0)
            {
                 break;
            }
        }
        return d;
    }
}
long long int criararquivo(long long int n, long long int e, long long int p, long long int q, long long int d)
{
    FILE *chave;
    chave = fopen("chave.txt", "w");
    fprintf(chave,"As chaves publicas sao: %lld e %lld\n As chaves privadas sao: %lld, %lld e %lld\n", n, e, p, q, d);
    fclose(chave); // txt com as chaves publicas 
    printf("\n Suas chaves foram salvas em um arquivo de texto.\n");
}



int main()
{
    long long int p, q, n, e, d, phi;
    int opcao, voltar;
    
    menu:
    system("clear");
    printf("\n\n Criptografia RSA");
    printf("\n\n 1 - Gerar chave publica");
    printf("\n\n 2 - Criptografar");
    printf("\n\n 3 - Descriptografar");
    printf("\n\n 4 - Sair");
    printf("\n\n Informe a opcao desejada: ");
    scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            opcaop1:
            printf("\n Insira o Primo 1: ");
            scanf("%lld", &p);

            if(ePrimo(p) != 1)
            {
            printf("\n\n Você digitou um numero nao primo");
            goto opcaop1;
            }

            opcaop2:
            printf("\n Insira o Primo 2: ");
            scanf("%lld", &q);

            if(ePrimo(q) != 1)
            {
            printf("\n\n Você digitou um numero nao primo");
            goto opcaop2;
            }
            
            //Calcula o n
            n = p * q;
            //Calcula o totiente de n
            phi = (p - 1)*(q - 1);

            printf("\n Insira o expente E (Lembre-se que 1 < E < phi(n): ");

            while(1)
            {
                scanf("%lld", &e);
                if (e <= 1 || e >= phi)
                {
                    printf("\n\n Invalido! O valor de E tem que estar entre 1 e %lld, digite um novo E: ", phi);  
                }
                else if (mdc(phi, e) != 1)
                {
                    printf("\n\n Invalido! O valor de E tem que ser co-primo de Phi(n), digite um novo E: ");
                }
                else if (mdc(phi, e) == 1)
                {
                    printf("\n Valor valido!\n");
                    break;
                }
            }

            d = inversoMod(phi, e);

            criararquivo(n, e, p, q, d);
            printf("\n As chaves publicas sao: %lld e %lld.\n", n, e);
            printf("\n As chaves privadas sao: %lld, %lld e %lld", p, q, d);
            printf("\n Processo finalizado.\n");

            printf("\n Deseja voltar ao menu inicial?\n");
            printf("\n 1 - Sim\n");
            printf("\n 2 - Nao\n");
            printf("\n Informe a opcao desejada: ");
            scanf("%d", &voltar);
            if (voltar == 1)
            {
                goto menu;
            }
            else
            {
                printf("\n Processo finalizado.\n");
            }

            
        case 2:
            system("clear");
            /*Criptografar();*/
            
        case 3:
            system("clear");
            /*Descriptografar();*/
            
        case 4:
            printf("\nFinalizando...\n\n");
            system("pause");
            exit(0);
            break;
        default:
            printf("Opcao invalida! Por favor, tente novamente...");
        }
    
    return 0;
}