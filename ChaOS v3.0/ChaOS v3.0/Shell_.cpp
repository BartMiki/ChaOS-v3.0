// Shell_.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include "Headers\Process.h"
#include "Headers\ProcessesManager.h"
#include "Headers\Interpreter.h"
#include "Headers\MemoryManager.h"
#include "Headers\ChaOS_filesystem.h"
//#include "Headers\ConditionVariable.h"

using namespace std;

PCB* ActiveProcess;

ChaOS_filesystem *fs;
//ConditionVariable *cv;
ProcessesManager *pm;
Interpreter *i;
MemoryManager *mm;
//SMS *S;


class main_loop {
private:
	vector<string> command;
	string line;
	void choose_function();
	void initialize();
	void prepare_string();
	void help();
	PCB* ActiveProcess;

public:
	main_loop();
	void run();
};



void main_loop::initialize() {
	//uruchmienie logo

	cout << "________/\\\\\\\\\\\\\\\\\\__/\\\\\\______________________________/\\\\\\\\\__________/\\\\\\\\\\\\\\\\\\\\\\___        " << endl
		 << " _____/\\\\\\////////__\\/\\\\\\____________________________/\\\\\\///\\\\\\______/\\\\\\/////////\\\\\\_       " << endl
		 << "  ___/\\\\\\/___________\\/\\\\\\__________________________/\\\\\\/__\\///\\\\\\___\\//\\\\\\______\\///__      " << endl
		 << "   __/\\\\\\_____________\\/\\\\\\__________/\\\\\\\\\\\\\\\\\\_____/\\\\\\______\\//\\\\\\___\\////\\\\\\_________     " << endl
		 << "    _\\/\\\\\\_____________\\/\\\\\\\\\\\\\\\\\\\\__\\////////\\\\\\___\\/\\\\\\_______\\/\\\\\\______\\////\\\\\\______    " << endl
		 << "     _\\//\\\\\\____________\\/\\\\\\/////\\\\\\___/\\\\\\\\\\\\\\\\\\\\__\\//\\\\\\______/\\\\\\__________\\////\\\\\\___   "<<endl
		 << "      __\\///\\\\\\__________\\/\\\\\\___\\/\\\\\\__/\\\\\\/___\\\\\\___\\///\\\\\\__/\\\\\\_____/\\\\\\______\\//\\\\\\__  "<<endl
		 << "       ____\\////\\\\\\\\\\\\\\\\\\_\\/\\\\\\___\\/\\\\\\_\\//\\\\__\\\\\\/\\\\____\\///\\\\\\\\\\/_____\\///\\\\\\\\\\\\\\\\\\\\\\/___ "<<endl
		 << "        _______\\/////////__\\///____\\///___\\////////\\//_______\\/////_________\\///////////_____" << endl;

	//uruchamiam tutaj moduły innych osób

	pm = new ProcessesManager();
	i = new Interpreter();
	mm = new MemoryManager();
	fs = new ChaOS_filesystem();
	//cv = new ConditionVariable();
	//s = SMS();

	//procesor, planista, ram, interpreter, system plików, ?????
}


void main_loop::prepare_string() {
	command.clear();
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int pom = 0;
	while (((pos = line.find(delimiter)) != string::npos + 1) && pom<3) {
		token = line.substr(0, pos);
		command.push_back(token);
		line.erase(0, pos + delimiter.length());
		pom++;
	}
}

void main_loop::run() {
	initialize();
	while (true) {
		try {
		cout << "> ";
		getline(cin, line);
			if (line == "close")break;
			else {
				prepare_string();
				choose_function();
			}
		}
		catch (...) {
			cout << "Bledna nazwa rozkazu. \nWpisz \"help\" zeby zobaczyc liste rozkazow\n";
		}
	}
}

main_loop::main_loop() {

}



void main_loop::choose_function() {
	if (command[0] == "help") {
		help();
	}
	else if (command[0] == "xD") {
		cout << "           /$$$$$$$ " << endl
			<< "          | $$__  $$" << endl
			<< " /$$   /$$| $$  \\ $$" << endl
			<< "|  $$ /$$/| $$  | $$" << endl
			<< " \\  $$$$/ | $$  | $$" << endl
			<< "  >$$  $$ | $$  | $$" << endl
			<< " /$$/\\  $$| $$$$$$$/" << endl
			<< "|__/  \\__/|_______/ " << endl;

	}
	else if (command[0] == "") {
		
	}
	else {
		throw 1;
	}


}


void main_loop::help() {
	fstream file;
	std::string line;
	file.open("help.txt");
	while (!file.eof()) {
		getline(file, line);
		cout << line <<endl;
	}
	file.close();
}


int main() {
	main_loop m;
	m.run();
	return EXIT_SUCCESS;
}




