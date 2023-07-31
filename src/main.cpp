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
	char *zErrMsg = 0;
	int rc;
	const char *sql;

	/* Open database */
	rc = sqlite3_open("todo.db", &db);

	if (rc) {
		std::cerr << "Can't open database\n";
		return 0;
	} else { 
		std::cout << "Database opened sucefully\n"; 
	}

	/* Make SQL statement */
	sql = "CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY, task TEXT, completed INTEGER);";

	/* Execute the statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
    	std::cerr << "Table creation failed: " << &zErrMsg << '\n';
	    sqlite3_free(zErrMsg);
	} else {
		std::cout << "Statement executed successfully\n";
	}

//	execute_db_statement("INSERT INTO todo (task, completed) VALUES ('Buy groceries', 0);", rc, db);

	execute_db_statement("SELECT * FROM todo;", rc, db);

	sqlite3_close(db);
	return 0;

}
