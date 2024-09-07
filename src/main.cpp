#include <iostream>
#include <string>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	for (int i = 0; i < argc; i++) {
        	std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << '\n';
	}
    	std::cout << "--------\n";

	return 0;

}

void execute_db_statement(const char *statement, int rc, sqlite3 *db) {

	char *errMsg = 0;

	/* Execute the statement and get callback */
	rc = sqlite3_exec(db, statement, callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
    	std::cerr << "Statement execution failed: " << &errMsg << '\n';
		sqlite3_free(errMsg);
	} else {
		std::cout << "Statement '" << statement << "' executed successfully\n-------------------------------\n";
	}

}

int main () {
	
	sqlite3 *db;

	/* Open database */
	int rc = sqlite3_open("todo.db", &db);

	/* Check if the table exists. If not create it */
	execute_db_statement("CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY, task TEXT, completed INTEGER);", rc, db);

	/* Insert a task and that if its completed to the "todo" table */
	/* execute_db_statement("INSERT INTO todo (task, completed) VALUES ('Clean windows', 1);", rc, db); */

	/* See everything in the "todo" table */
	execute_db_statement("SELECT * FROM todo;", rc, db);

	/* Get the number of rows in the "todo" table */
	/* execute_db_statement("SELECT COUNT(*) FROM todo;", rc, db); */

	/* Get some info about the "todo" table */
	execute_db_statement("PRAGMA table_info(todo);", rc, db);

	/* See every table in the db */
	/* execute_db_statement("SELECT name FROM sqlite_master WHERE type='table';", rc, db); */

	/* Change the "completed" state in a row in the "todo" table by id */
	execute_db_statement("UPDATE todo SET completed = 1 WHERE id = 1;", rc, db);

	sqlite3_close(db);
	return 0;

}
