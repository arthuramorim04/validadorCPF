#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

void validadorCPF();

long long cpfNumeros[11], digito1, digito2;
char cpf[11];
int i;

void receberCpf()
{

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
        //cada vez que passa no loop ele vai completando a numerção do cpf
        cpfNumeros[i] = atoi(cpf);
        cpf[i] = ' ';
    }
    validadorCPF();
    system("pause");
}

void validadorCPF()
{
    system("CLS");
    long long aux, aux1;
    long long soma = 0;
    // soma = ((cpfNumeros[0]*10)+(cpfNumeros[1]*9)+(cpfNumeros[2]*8)+(cpfNumeros[3]*7)+(cpfNumeros[4]*6)+(cpfNumeros[5]*5)+(cpfNumeros[6]*4)+(cpfNumeros[7]*3)+(cpfNumeros[8]*2));
    //resolver divisão pra validação
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

    for (i = 0; i < 11; i++)
    {
        cout << cpfNumeros[i];
        if (i - 1 == 4)
        {
            cout << ".";
        }
        if (i - 1 == 8)
        {
            cout << ".";
        }
        if (i - 1 == 9)
        {
            cout << "-";
        }
    }
    cout << "\nPrimeiro Digito: " << digito1;
    cout << "\nSegundo Digito: " << digito2;
    cout << "\n";
}

main()
{

    receberCpf();
}
