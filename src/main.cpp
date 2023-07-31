#include <iostream>
#include <string>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	for (int i = 0; i < argc; i++) {
        	std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << '\n';
    	}
    	std::cout << "-------------------\n";

	return 0;

}

void execute_db_statement(const char *statement, int rc, sqlite3 *db) {

	char *errMsg = 0;

	/* Execute the statement */
	rc = sqlite3_exec(db, statement, callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
    	std::cerr << "Statement execution failed: " << &errMsg << '\n';
		sqlite3_free(errMsg);
	} else {
		std::cout << "Statement executed successfully\n";
	}

}

int main () {
	
	sqlite3 *db;

	/* Open database */
	int rc = sqlite3_open("todo.db", &db);

	/* Check if the table exists. If not create it */
	execute_db_statement("CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY, task TEXT, completed INTEGER);", rc, db);

//	execute_db_statement("INSERT INTO todo (task, completed) VALUES ('Buy groceries', 0);", rc, db);

	execute_db_statement("SELECT * FROM todo;", rc, db);

	sqlite3_close(db);
	return 0;

}
