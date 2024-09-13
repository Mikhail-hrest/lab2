#include "MYREGEX.h"

/*
void REgex::start(){
	std::cout<< "==============================START================================";
	std::cout<< "#                    ENTER NUM TO RUN METHO                       #";
	std::cout<< "#  1) Compile DFA from RE                                         #";
	std::cout<< "#  2) Find all substrung from a string                            #";
	std::cout<< "#  3) Restore RE from DFA via K-path                              #";
	std::cout<< "#  4) difference between languages ​​defined by RE                  #";
	std::cout<< "#  5) intersection of languages ​​defined by RE                     #";
	std::cout<< "#  6-...) Close program                                           #";
	std::cout<< "===================================================================";
	int num;
	std::cin >> num;
	while(num < 6 && std::cin.good() && !std::cin.eof()){
		switch(num){
			case 1:
				compile();
				break;
			case 2:
				findall();
				break;
			case 3:
				std::cout << "	<regular expession> \n";
				std::cout << dfa.get_regex() << std::endl;
				break;
			case 4:
				dfa = make_difference();
				dfa.show();
				break;
			case 5:
				dfa = make_intersection();
				dfa.show();
				break;
			default:
				break;
		}
		std::cin >> num;
	}
	std::cout << "                     PROGRAM IS CLOSING                           ";
}

void REgex::compile(){
	std::string a;
	std::cout << "Enter the string -> ";
	std::cin >> a;
	Synt_Tree re(a);
	NFA nfa(re);
	dfa = DFA(nfa);
	dfa.show();
	std::cout<<"    if you want to see Synt. Tree enter 1\n"
		<< "    else if you want to see NFA enter 2\n"
		<< "    else entet any num";
	int num;
	std::cin >> num;
	while(num < 3 && std::cin.good() && !std::cin.eof()){
		switch(num){
			case 1:
				re.show();
				break;
			case 2:
				nfa.show();
				break;
			default:
				break;
		}
		std::cin >> num;
	}
}


void REgex::findall(){
	if (dfa.states_dfa.size() == 0){
		std::cout << "No RE was compiled. Try to compile some RE first.\n";
		return;
	}
	std::string str;
	std::cout << "Enter the string -> ";
	std::cin >> str;
	if(std::cin.eof()){
		std::cout << "close program. you enter eof\n";
		return;
	}
	std::vector<std::string> substr;
	std::string sub = "", sub1 = "";
	State_dfa* current = dfa.get_START();

	for(int i = 0; i < str.size(); ++i){
		bool flag = false;
		for(auto tr : current->traces){
			if(tr->let == str[i]){
				sub+=str[i];
				flag = true;
				current = tr->out;
				break;
			}
		}
		if(current->is_final){
			sub1 = sub;
		}
		if(!flag || current == dfa.get_ERROR()){
			if(sub1.size() != 0) {
				substr.push_back(sub1);
				sub1 = "";
				sub = "";
				current = dfa.get_START();
			}
		}
	}
	std::cout << "Finding strings: ";
	for(auto s: substr) std::cout << "<" << s << ">";
	std::cout << std::endl;
}


DFA& REgex::make_intersection(){
	std::string a;
	std::string b;
	std::cout << "1-st re -> ";
	std::cin >> a;
	std::cout << "2-nd re -> ";
	std::cin >> b;
        Synt_Tree re1(a);
        Synt_Tree re2(b);
        NFA nfa1(re1);
        NFA nfa2(re2);
        DFA dfa1(nfa1);
        DFA dfa2(nfa2);
        DFA result(dfa1, dfa2, 2);
        return result;
}


DFA& REgex::make_difference(){
	std::string a;
	std::string b;
	std::cout << "1-st re -> ";
        std::cin >> a;
        std::cout << "2-nd re -> ";
        std::cin >> b;
        Synt_Tree re1(a);
        Synt_Tree re2(b);
        NFA nfa1(re1);
        NFA nfa2(re2);
        DFA dfa1(nfa1);
        DFA dfa2(nfa2);
        DFA result(dfa1, dfa2, 1);
        return result;
}


*/
