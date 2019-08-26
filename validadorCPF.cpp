#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

void validadorCPF();

long long int cpfNumeros[11], digito1, digito2;
char cpf[11];
int i;

void receberCpf()
{

    //recebe CPF como char, converte pra int e salva na int cpfNumero
    cout << "Digite o CPF\n";
    for (i = 0; i < 11; i++)
    {
        //adiciona a formatação enquanto digita
        if (i - 1 == 2)
        {
            cout << ".";
        }
        if (i - 1 == 5)
        {
            cout << ".";
        }
        if (i - 1 == 8)
        {
            cout << "-";
        }
        cpf[i] = getche();
        // func atoi faz converção de int pra string
        cpfNumeros[i] = atoi(cpf);
        //limpa o buffer pra evitar lixo de memória
        cpf[i] = ' ';
    }
    validadorCPF();
    system("pause");
}

void validadorCPF()
{
    system("CLS");  
    long long int aux, aux1;
    long long int soma = 0;
    // soma segundo matematica do
    for (int i = 0; i < 9; i++)
    {
        soma += cpfNumeros[i] * (10 - i);
    }
    soma %= 11;

    if (soma < 2)
    {

        digito1 = 0;
    }
    else
    {
        digito1 = 11 - soma;
    }

    soma = 0;

    for (int i = 0; i < 10; i++)
    {
        soma += cpfNumeros[i] * (11 - i);
    }

    soma %= 11;
    if (soma < 2)
    {
        digito2 = 0;
    }
    else
    {
        digito2 = 11 - soma;
    }
    //mostrar cpf com pontuação
    for (i = 0; i < 11; i++)
    {

        if (i - 1 == 2)
        {
            cout << ".";
        }
        if (i - 1 == 5)
        {
            cout << ".";
        }
        if (i - 1 == 8)
        {
            cout << "-";
        }
        cout << cpfNumeros[i];
    }
    cout << "\nPrimeiro Digito: " << digito1;
    cout << "\nSegundo Digito: " << digito2;
    cout << "\n";

    if (digito1 == cpfNumeros[9] && digito2 == cpfNumeros[10])
    {
        cout << "CPF Valido.";
    }
    else
    {
        cout << "CPF Invalido.";
    }
}

main()
{
    receberCpf();
    validadorCPF();

}
