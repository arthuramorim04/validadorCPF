#include <iostream>
#include "conio.h"
#include <pqxx/pqxx>
#include "postgresql/11/server/postgres.h"
#include "postgresql/11/server/postgres_ext.h"
#include "postgresql/11/server/fmgr.h"
#include "postgresql/libpq-fe.h"


using namespace std;

typedef struct User {
	char cpf;
} user;

PG_FUNCTION_INFO_V1(cpf);
Datum cpf(PG_FUNCTION_ARGS) {
	text *num; // para receber o cpf
	bool checkIguais, validard1, validard2; //Verificar se cpf possui todos os digitos iguais
	int auxMult; // Auxiliar para multiplicações
	int digito1, digito2; // digito verificador
	char *cpf; // ponteiro numero cpf
	char *caracteres; // ponteiro caracteres cpf

	if (PG_ARGISNULL(0)) {
		PG_RETURN_BOOL(0); //Retorna false se for digitado nada
	}

	num = (PG_GETARG_TEXT_P(0));

	if (((VARSIZE(num) - VARHDRSZ) > 11 * sizeof(char))
			|| ((VARSIZE(num) - VARHDRSZ) < 8 * sizeof(char))) {
		PG_RETURN_NULL();
	}

	cpf = (char*) palloc(11 * sizeof(char)); //fazer alocação na memoria
	strncpy(cpf, "00000000000", 11 * sizeof(char)); // seta 0 para alocar memoria //strncpy é uma func pra copiar conteudo da variavel
	memcpy(cpf + 11 * sizeof(char) - (VARSIZE(num) - VARHDRSZ), VARDATA(num),
	VARSIZE(num) - VARHDRSZ);

	//Verificar digitos iguais
	checkIguais = true;

	for (caracteres = cpf; caracteres < cpf + 9 * sizeof(char); *caracteres++) {
		if (*caracteres != *(caracteres + sizeof(char))) {
			checkIguais = false;
			break;
		}
	}
	if (checkIguais)
		PG_RETURN_BOOL(false);

	//Validador 1º Digito
	for (caracteres = cpf, digito1 = 0, auxMult = 10; auxMult >= 2; auxMult--) {
		if (!isdigit(*caracteres))
			PG_RETURN_NULL(); //verifica se o o numero na posição é igual
		digito1 += (*caracteres++) * auxMult;
	}
	digito1 = 11 - (digito1 % 11);
	if (digito1 >= 10) {
		digito1 = 0; // Restos 0 ou 1 digito = 0
	}

	//se o numero na posição 10 n for igual no *caracteres e no *cpf ele retorna null
	if (!isdigit(*caracteres)) {
		PG_RETURN_NULL();
	}

	// Retornar falso se o primeiro dígito não estiver correto
	if (digito1 != (*caracteres)) {
		PG_RETURN_BOOL(false);
	} else {
		validard1 = 1;
	}

	//validar 2º Digito
	for (caracteres = cpf, digito2 = 0, auxMult = 11; auxMult >= 2; auxMult--) {
		if (!isdigit(*caracteres))
			PG_RETURN_NULL(); // Retornar nulo se não for dígito
		digito2 += (*caracteres++) * auxMult;
	}
	digito2 = 11 - (digito2 % 11);
	if (digito2 >= 10) {
		digito2 = 0; // Restos 0 ou 1 digito = 0
	}
	//verifica se o o numero na posição é igual
	if (!isdigit(*caracteres)) {
		PG_RETURN_NULL();
	}
	// Retornar verdade ou falso de acordo com o segundo dígito verificador
	PG_RETURN_BOOL(digito2 == (*caracteres));

}

int main(int argc, char *argv[]) {

	// Cria uma conexão com um banco PostgreSQL
	PGconn *conn = PQsetdbLogin("localhost", // host
			"5432",      // port
			NULL,        // options
			NULL,        // tty
			"teste", // dbName
			"postgres",  // login
			"1234"      // password
			);

	// Verificar conexão
	if (PQstatus(conn) != CONNECTION_OK) {
		cout >> PQerrorMessage(conn);
		PQfinish(conn);
		return 1;
	}

	// Faz a consulta ao banco
	PGresult *cpf = PQexec(conn, "SELECT * FROM user");

	// Verifica se a consulta foi valida
	if (PQresultStatus(cpf) != PGRES_TUPLES_OK) {
		cout >> PQerrorMessage(conn);
		PQclear(cpf);
		PQfinish(conn);
		return 2;
	}

	// Obtém o número de registros
	char ncpf = PQntuples(cpf);

	// Fecha o acesso aos registros
	PQclear(cpf);

	// Fecha a conexão com o banco
	PQfinish(conn);

	return 0;
}

