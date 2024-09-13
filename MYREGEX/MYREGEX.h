#pragma once
#ifndef _MYREGEX_H_
#define _MYREGEX_H_

#include "../DFA/DFA.h"
#include "../Tree/STree.h"
#include "../NFA/NFA.h"
#include <string>
#include <iostream>
#include <sstream>

class REgex{
public:
	REgex() = default;
	DFA* dfa = nullptr;
	DFA* make_difference();
	DFA* make_intersection();
	void findall();
	void compile();
	void start();
	~REgex(){};
};


void REgex::start(){
        std::cout<< "==============================START==============================\n";
        std::cout<< "#                    ENTER NUM TO RUN METHOD                    #\n";
        std::cout<< "#  1) Compile DFA from RE                                       #\n";
        std::cout<< "#  2) Find all substrung from a string                          #\n";
        std::cout<< "#  3) Restore RE from DFA via K-path                            #\n";
        std::cout<< "#  4) difference between languages ​​defined by RE                #\n";
        std::cout<< "#  5) intersection of languages ​​defined by RE                   #\n";
        std::cout<< "#  6-...) Close program                                         #\n";
        std::cout<< "=================================================================\n";
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
                                std::cout << "  <regular expession> \n";
                                if(dfa == nullptr){std::cout << "No DFA\n"; break;}
                                std::cout << dfa->get_regex() << std::endl;
                                break;
                        case 4:
				//delete dfa;
                                dfa = make_difference();
                                dfa->show();
                                break;
                        case 5:
				//delete dfa;
                                dfa = make_intersection();
                                dfa->show();
                                break;
                        default:
                                break;
                }
		std::cout<< "==============================START==============================\n";
        	std::cout<< "#                    ENTER NUM TO RUN METHOD                    #\n";
        	std::cout<< "#  1) Compile DFA from RE                                       #\n";
        	std::cout<< "#  2) Find all substrung from a string                          #\n";
        	std::cout<< "#  3) Restore RE from DFA via K-path                            #\n";
        	std::cout<< "#  4) difference between languages ​​defined by RE                #\n";
	        std::cout<< "#  5) intersection of languages ​​defined by RE                   #\n";
        	std::cout<< "#  6-...) Close program                                         #\n";
        	std::cout<< "=================================================================\n";
                std::cin >> num;
        }
        std::cout << "                     PROGRAM IS CLOSING                         \n";
}


void REgex::findall(){
        if (dfa == nullptr || dfa->states_dfa.size() == 0){
                std::cout << "No RE was compiled. Try to compile some RE first.\n";
                return;
        }
        std::string str;
        std::cout << "Enter the string -> ";
	std::cin.ignore();
        std::getline(std::cin, str);
        if(std::cin.eof()){
                std::cout << "close program. you enter eof\n";
                return;
        }
        std::vector<std::string> substr;
        std::string sub = "", sub1 = "";
        std::shared_ptr<State_dfa> current = dfa->get_START();

        for(int i = 0; i < str.size(); ++i){
                bool flag = false;
                for(auto tr : current->traces){
                        if(tr->let == str[i] || tr->let == '.'){
                                sub+=str[i];
                                flag = true;
                                current = tr->out;
                                break;
                        }
                }
                if(current->is_final){
                        sub1 = sub;
                }
                if(!flag || current == dfa->get_ERROR()){
                        if(sub1.size() != 0) {
                                substr.push_back(sub1);
                                sub1 = "";
                                sub = "";
                                current = dfa->get_START();
                                --i;
                        }
                }
        }
	if(sub1!= "") substr.push_back(sub1);
        std::cout << "Finding strings: ";
        for(auto s: substr) std::cout << "<" << s << ">";
        std::cout << std::endl;
}

void REgex::compile(){
        std::string a;
        std::cout << "Enter the string -> ";
        std::cin >> a;
        Synt_Tree re(a);
        //re.show();
        NFA nfa(re);
        //nfa.show();
	//std::cout << "we hear\n";
        if(dfa != nullptr) delete dfa;
        dfa = new DFA(nfa);
        //dfa->show();
        std::cout<<"    if you want to see Synt. Tree enter 1\n"
                << "    else if you want to see NFA enter 2\n"
                << "    else if you want to see DFA enter 3\n"
                << "    else enter any num\n";
        int num;
        std::cin >> num;
        while(num < 4 && std::cin.good() && !std::cin.eof()){
                switch(num){
                        case 1:
                                re.show();
                                break;
                        case 2:
                                nfa.show();
                                break;
                        case 3:
                                dfa->show();
                        default:
                                break;
                }
		std::cout<<"    if you want to see Synt. Tree enter 1\n"
	                << "    else if you want to see NFA enter 2\n"
        	        << "    else enter any num\n";
                std::cin >> num;
        }
}



DFA* REgex::make_intersection(){
        std::string a;
        std::string b;
        std::cout << "1-st re -> ";
        std::cin >> a;
        std::cout << "2-nd re -> ";
        std::cin >> b;
        Synt_Tree re1(a);
        //re1.show();
        Synt_Tree re2(b);
        //re2.show();
        NFA nfa1(re1);
        //nfa1.show();
        NFA nfa2(re2);
        //nfa2.show();
        DFA *dfa1 = new DFA(nfa1);
        DFA *dfa2 = new DFA(nfa2);
        DFA* result = new DFA(*dfa1, *dfa2, 2);
        delete dfa1;
        delete dfa2;
        return result;
}


DFA* REgex::make_difference(){
        std::string a;
        std::string b;
        std::cout << "1-st re -> ";
        std::cin >> a;
        std::cout << "2-nd re -> ";
        std::cin >> b;
         Synt_Tree re1(a);
        //re1.show();
        Synt_Tree re2(b);
        //re2.show();
        NFA nfa1(re1);
        //nfa1.show();
        NFA nfa2(re2);
        //nfa2.show();
        DFA *dfa1 = new DFA(nfa1);
        DFA *dfa2 = new DFA(nfa2);
        DFA* result = new DFA(*dfa1, *dfa2, 1);
        delete dfa1;
        delete dfa2;
        return result;
}




#endif
