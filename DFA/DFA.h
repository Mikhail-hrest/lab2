#pragma once
#ifndef _DFA_H_
#define _DFA_H_

#include "../NFA/NFA.h"
#include <set>
#include <vector>
#include <string>
#include <utility>

struct State_dfa;

struct trace{
	char let;
	std::shared_ptr<State_dfa> out;
	trace(): let(char(0)), out(nullptr){};
	trace(char s, std::shared_ptr<State_dfa> ptr) : let(s), out(std::move(ptr)){};
};

struct State_dfa{
	int name;
	bool is_final;
	bool is_checked;
	std::set<State*> lasts;
	std::vector<std::shared_ptr<trace>> traces;//first trace is always ERROR
	State_dfa(bool a = false, bool b = false, int nm = 0) : is_final(a), is_checked(b), name(nm) {traces.reserve(1);};
	std::shared_ptr<State_dfa> find_state_by_symb(char symb){
		std::shared_ptr<State_dfa> result = nullptr;
		for(auto i : traces){
			if(i->let == symb) result = i->out;
		}
		return result;
	}
};

//======================================================================================












class DFA{
private:
	std::shared_ptr<State_dfa> START;
	std::shared_ptr<State_dfa> ERROR;
	//alfabet is all symbol -> default have alfabet
	void add_in_set(State* state, std::set<State*>& set, std::set<State*>& lasts);
	bool is_all_checked();
	std::shared_ptr<State_dfa> find(std::set<State*> set, std::vector<std::pair<std::set<State*>, std::shared_ptr<State_dfa>>> map);
	void minimization();
	std::set<std::pair<std::pair<int, std::pair<int, int>>, std::string>> cash;
	std::string get_cash(int k, int i, int j){
		std::string result = "";
		std::pair<int, int> ij = {i, j};
		std::pair<int,std::pair<int, int>> k_ij = {k, ij};
		for(auto s: cash){
			if(s.first == k_ij) result = s.second;
		}
		return result;
	};

	std::string get_R(int k, int i, int j);
public:
	DFA(): ERROR(std::make_shared<State_dfa>(false, true)), is_empty(true) {states_dfa.push_back(ERROR);};
	DFA(NFA& nfa);
	DFA(DFA dfa1, DFA dfa2, int var);
	~DFA(){};
	bool is_empty;
	std::shared_ptr<State_dfa> get_ERROR() {return ERROR;}
	std::shared_ptr<State_dfa> get_START() {return START;}

	std::set<char> alfabet;
	std::vector<std::pair<std::set<State*>, std::shared_ptr<State_dfa>>> map;
	std::vector<std::shared_ptr<State_dfa>> states_dfa;
	void show();
	std::string get_regex();
};












//======================================================================================

std::string DFA::get_R(int k, int i, int j){
	std::string result = get_cash(k, i, j);
    if(result != "") return result;
	if(k == 0){
		if(i != j){
			for(auto state : states_dfa) {
				if(state->name != i) continue;
				else {
					for(auto tr : state->traces){
						if(tr->out->name == j){
							if(result != "") result=result + "|";
							result = result + tr->let;
						}
					}
					if(result == "") result=result + "0";
					break;
				}
			}
		} else {
			for(auto state: states_dfa){
				if(state->name != i) continue;
				else{
					for(auto tr : state->traces){
						if(tr->out->name == j){
							if(result != "") result+= "|";
							result=result + tr->let;
							//result=result + "@";
							break;
						}
					}
					if(result == ""){
						result+= '@';
					}
					break;
				}
			}
		}
	} else {
		std::string r1 = get_R(k-1, i, k), r2 = get_R(k-1, k, k), r3 = get_R(k-1, k, j), r = get_R(k-1, i, j);
		result =result + "(" + r;
		if(r1 != "0" && r2 != "0" && r3 != "0"){
			r2 = r2 != "@" ? r2 + "*" : "";
			r1 = r1 != "@" ? r1 : "";
			r3 = r3 != "@" ? r3 : "";

			if(r1 != "" || r2 != "" || r3 != "") result = result + "|"; 
			result= result + r1 + r2 + r3 ;
		}
		result = result + ")";
	}
	//std::pair<int, int> ij = {i, j};
	std::pair<int,std::pair<int, int>> k_ij = {k, {i, j}};
	std::pair<std::pair<int, std::pair<int,int>>, std::string> n_cash = {k_ij, result};
	cash.insert(n_cash);
	return result;
}


std::string DFA::get_regex(){
	std::cout << "\nEmpty set is '0', epsilon is '@'\n";
	int i = 1;
	std::string result = "";
	std::vector<int> receiving;
	for(auto a : states_dfa){
		if(a != ERROR){
			a->name = i;
			if(a->is_final == 1) receiving.push_back(i);
			++i;
		}
	}
	for(auto s : states_dfa) if(s == ERROR) s->name = i;
	// for(auto i: states_dfa) std::cout << i->name << " ";
	// std::cout << std::endl;
	int k = states_dfa.size()-1;//тк есть ошибочное состояние и оно всегда последнее
	for(auto j : receiving){
		if(result == "") result= result + get_R(k, START->name, j);
		else{
			result = result + "|";
			result = result + get_R(k, START->name, j);
		}
	}
	//std::cout << result << std::endl;
	return result;
}




void DFA::add_in_set(State* state, std::set<State*>& set, std::set<State*>& lasts){
	set.insert(state);
	if(state->out1 != nullptr){
		if(state->out1->lit == '_'){
			if(!set.contains(state->out1->out)) add_in_set(state->out1->out, set,lasts);
		}else lasts.insert(state);
	}
	if(state->out2 != nullptr){
		if(state->out2->lit == '_'){
			if(!set.contains(state->out2->out)) add_in_set(state->out2->out, set, lasts);
		}else lasts.insert(state);
	}
}

bool DFA::is_all_checked(){
	bool fl = true;
	for(auto a: states_dfa){
		fl = fl && a->is_checked;
	}
	return fl;
}

std::shared_ptr<State_dfa> DFA::find(std::set<State*> set, std::vector<std::pair<std::set<State*>, std::shared_ptr<State_dfa>>> map){
	std::shared_ptr<State_dfa> result = nullptr;
	for(auto i: map){
		if(i.first == set){
			result = i.second;
			break;
		}
	}
	return result;
}

DFA::DFA(NFA& nfa){
	//Алгоритм создания дфа
	State* start = nfa.graph->start;
	std::set<State*> set;
	std::set<State*> lasts;
	add_in_set(start, set, lasts);
	std::shared_ptr<State_dfa> st_dfa = std::make_shared<State_dfa>();
	st_dfa->lasts = lasts;
	START = st_dfa;
	//std::cout << "\nset.size() = " << set.size() << "\n";
	//std::cout << "\nlasts.size() = " << lasts.size() << "\n";
	states_dfa.push_back(st_dfa);
	map.push_back({set, st_dfa});
	std::vector<std::pair<std::set<State*>, std::shared_ptr<State_dfa>>>::iterator step = map.begin();
	std::vector<std::pair<std::set<State*>, std::shared_ptr<State_dfa>>>::iterator ending = map.end();
	//std::cout << (step)->second->traces.size() << std::endl;
	int step_int = 0;
	while(!is_all_checked() && step != ending){
		//std::cout << (step)->second->traces.size() << std::endl;
		std::set<char> symb_trans;
		for(auto a: step->second->lasts){
			if(a->out1 != nullptr){
				if(a->out1->lit!= '_')symb_trans.insert(a->out1->lit);
			}
			if(a->out2 != nullptr){
				if(a->out2->lit!= '_')symb_trans.insert(a->out2->lit);
			}
		}
		//std::cout << (step)->second->traces.size() << std::endl;
		//std::cout << "symb count = " << symb_trans.size();
		for(auto l : symb_trans){
			alfabet.insert(l);
			std::set<State*> set1;
			std::set<State*> lasts1;
			for(auto it : step->second->lasts){
				//std::cout << "we are here0\n";
				if(it->out1->lit == l){
					add_in_set(it->out1->out, set1, lasts1);
				}
				else if(it->out2!= nullptr) if(it->out2->lit == l){
					add_in_set(it->out2->out, set1, lasts1);
				}
			}
			//std::cout << (step)->second->traces.size() << std::endl;
			//std::cout <<"we are here1\n";
			if(find(set1, map) == nullptr){
				//std::cout <<"we are here1,5\n";
				std::shared_ptr<State_dfa> new_st_dfa = std::make_shared<State_dfa>();
				new_st_dfa->lasts = lasts1;
				states_dfa.push_back(new_st_dfa);
				//std::cout << map.size() << std::endl;

				//std::shared_ptr<State_dfa> check = step->second;
				map.push_back({set1, new_st_dfa});
				step = map.begin();
				ending = map.end();
				step+=step_int;
				//std::cout << (check == step->second)<< std::endl;
			}
			//std::cout << (step)->second->lasts.size() << std::endl;
			//std::cout <<"we are here2\n";
			std::shared_ptr<State_dfa> new_st_dfa = find(set1, map);
			std::shared_ptr<trace> tr = std::make_shared<trace>(l, new_st_dfa);
			//std::cout << tr->let << std::endl;
			//std::cout << (step)->second->traces.size() << std::endl;
			std::cout << tr->let <<"\n";
			step->second->traces.push_back(tr);
			//std::cout <<"we are here4\n";
			set1.clear();
			lasts1.clear();
		}
		//std::cout << "\ncode 1\n";

		step->second->is_checked = true;
		step = map.begin();
		ending = map.end();
		step_int++;
		step+=step_int;
	}
	//std::cout << "\ncode 2 \n";
	//назначаем вершины финальными если в них есть финальная вершина нка
	for(auto i : map){
		if(i.first.count(nfa.graph->finish)) i.second->is_final = true;
	}
	//show();
	//std::cout << "\ncode 3\n";
	//добавляем ошибочное состояние
	ERROR= std::make_shared<State_dfa>(false, true);
	states_dfa.push_back(ERROR);
	for(auto x : states_dfa){
		std::set<char> use;
		for(auto tr : x->traces){
			use.insert(tr->let);
		}
		//std::cout << use.size() << std::endl;
		for(auto l : alfabet){
			if(!use.contains(l)){
				std::shared_ptr<trace> n_tr = std::make_shared<trace>(l, ERROR);
				x->traces.push_back(n_tr);
			}
		}
		use.clear();
	}
	//std::cout << "\ncode 4 \n";
	for(auto a:map) a.first.clear();
	map.clear();
	is_empty = false;
	//show();
	minimization();
	//show();
}


void DFA::minimization(){
	//удаление недоступных со старта вершин
	std::set<std::shared_ptr<State_dfa>> available1;
	available1.insert(START);
	bool have_final = false;
	/*
	for(auto st : states_dfa){
		for(auto x : st->traces){
			if(st!= ERROR)available1.insert(x->out);
			have_final = have_final || x->out->is_final;
		}
	}*/
	for(auto st : available1){
		for(auto x : st->traces){
			available1.insert(x->out);
			have_final = have_final || x->out->is_final; 
		}
	}
	if(!have_final){
		available1.clear();
		is_empty = true;
		states_dfa.clear();
		for(auto a: map) a.first.clear();
		map.clear();
		alfabet.clear();
		START = nullptr;
		ERROR = nullptr;
		return;
	}
	
	//std::cout << "\navailable1.size() = " << available1.size() << std::endl;

	std::set<std::shared_ptr<State_dfa>> available2;
	for(auto st:available1){
		if(!st->is_final && st!=ERROR){
			bool flag = false;
			for(auto x : st->traces){
				if(x->out != st){
					flag = true;
					break;
				}
			}
			if(flag) available2.insert(st);
		}else available2.insert(st);
	}
	available1.clear();
	//std::cout << "\navailable2.size() = " << available2.size() << std::endl;
	//for(auto x : available2) std::cout << x->name << " ";
	//std::cout << std::endl;
	//int k = 0;
	std::set<std::shared_ptr<State_dfa>> fin;
	std::set<std::shared_ptr<State_dfa>> unfin;
	std::set<std::shared_ptr<State_dfa>> ers;
	//std::cout << "\n <fin, unfin> : <" << fin.size() << " , " << unfin.size() << ">\n";
	for(auto s : available2){
		if(s == ERROR) ers.insert(s);
		else if(s->is_final) fin.insert(s);
		else unfin.insert(s);
	}
	//std::cout << "\n <fin, unfin> : <" << fin.size() << " , " << unfin.size() << ">\n";
	
	//std::cout << std::endl;
	std::set<std::set<std::shared_ptr<State_dfa>>> divide;
	divide.insert(fin);
	if(unfin.size()!=0)divide.insert(unfin);
	if(ers.size()){
		divide.insert(ers);
		//std::cout << "\nAdding error\n";
	}
	//std::cout << "size of divide = " << divide.size() << std::endl;
	std::set<std::set<std::shared_ptr<State_dfa>>> prev;
	do{
		//std::cout << "\ncode1\n";
		prev = divide;
		// for(auto x: divide){
		// 	std::cout << x.size() << ", ";
		// }
		//std::cout << std::endl;
		for(auto s : prev){
			//std::cout << "\ncode 2";
			std::set<std::shared_ptr<State_dfa>> new_group;
			if(s == ers) continue;
			//std::cout << " code 3\n";
			for(auto l : alfabet){
				std::set<std::shared_ptr<State_dfa>> symb_gr;
				auto beg = s.begin();
				std::shared_ptr<State_dfa> ptr = (*beg)->find_state_by_symb(l);
				for(auto k : divide) if(k.contains(ptr)) symb_gr = k;
				for(auto s1 : s){
					std::shared_ptr<State_dfa> need= s1->find_state_by_symb(l);
					if(!symb_gr.contains(need)) new_group.insert(s1);
				}
				symb_gr.clear();
			}
			if(new_group.size() != 0){
				std::set<std::shared_ptr<State_dfa>> srm = s;
				divide.erase(divide.find(s));
				for(auto rm : new_group){
					srm.erase(srm.find(rm));
				}
				divide.insert(srm);
				divide.insert(new_group);
				break;
			}
			new_group.clear();
		}
	}while(prev != divide);
	
	//std::cout << "\n\n";
	std::set<std::pair<std::set<std::shared_ptr<State_dfa>>,std::shared_ptr<State_dfa>>> new_map;
	for(auto s: divide){
		if(s.size()!= 0)new_map.insert({s, std::make_shared<State_dfa>(false, true)});
	}
	for(auto s: new_map){
		std::shared_ptr<State_dfa> nodes = *(s.first.begin());
		for(auto it: nodes->traces){
			for(auto s1: new_map){
				if(s1.first.contains(it->out)){
					s.second->traces.push_back(std::make_shared<trace>(it->let, s1.second));
					break;
				}
			}
		}
	}
	for(auto s: new_map){
        if(s.first.count(START)) START = s.second;
        if(s.first.count(ERROR)) ERROR = s.second;
        for(auto s1: s.first){
            if(s1->is_final){
                s.second->is_final = true;
                break;
            }
	    }
	}
	
	states_dfa.clear();
	for(auto a: new_map) states_dfa.push_back(a.second);
	for(auto a : divide) a.clear();
	divide.clear();
	for(auto a : prev) a.clear();
	prev.clear();
}




void DFA::show(){
	std::cout << "\n                 <===  DFA  ===>";
	if(is_empty){
		std::cout << "\nDFA IS EMPTY\n";
		return;
	}
	int i = 1;
	std::cout << std::endl;
	for(auto s: states_dfa){
		auto traces = s->traces;
		for(auto t : traces){
			int y = 1;
			for(auto s1: states_dfa){
				if(t->out == s1){
					std::cout << i << " " << t->let << " " << y << ";\n";
					break;
				}
				++y;
			}
		}
		++i;
	}
	int ind = 0;
	std::cout << "Start state: ";
	for(auto i :states_dfa){
                if(i == START) std::cout << ind+1 << std::endl;
                ++ind;
        }
	ind = 0;
	std::cout << "Final states: ";
	for(auto i : states_dfa){
		if(i->is_final) std::cout << ind+1 << " ";
		++ind;
	}
	ind = 0;
	std::cout << "\nERROR state: ";
	for(auto i :states_dfa){
		if(i == ERROR) std::cout << ind+1 << std::endl;
		++ind;
	}
	std::cout << std::endl;
	std::cout << "alfabet is :";
	for(auto l : alfabet) std::cout << " " << l;
	std::cout << std::endl;
	//std::cout << states_dfa[2]->traces.size() << std::endl;
}





// if var = 1  -> it is difference, все строки из dfa1 которых нет в dfa2
//из dfa1 принимающее, а из dfa2 непринимающее
// if var = 2  -> it is intersection, слова входящие и в первый язык и во второй
//принимающее состояние - где оба состояния из dfa1 и dfa2 принимающие
DFA::DFA(DFA dfa1, DFA dfa2, int var){
	std::cout << "\n\n<=======    DFA 1    =======>\n";
	dfa1.show();
	std::cout << "\n\n<=======    DFA 2    =======>\n";
	dfa2.show();
	alfabet = dfa1.alfabet;
    std::set<std::pair<std::pair<std::shared_ptr<State_dfa>, std::shared_ptr<State_dfa>> , std::shared_ptr<State_dfa>>> map1;
    int size1 = 1 , size2 = 1;
	//назначение имен для вершине графов dfa1 и dfa2, кроме error state
    for(auto a : dfa1.states_dfa){
        if(a == dfa1.ERROR) continue;
		a->name = size1;
        ++size1;
    }
    for(auto a : dfa2.states_dfa){
        if(a == dfa2.ERROR) continue;
        a->name = size2;
        ++size2;
    }
    int sz = (size1-1)*(size2-1);
	//std::cout << sz << std::endl;
    //заполняю вершины
	//удалю ошибочные состояния
    //заполняю вершины
    for(auto x : dfa1.states_dfa){
        if(x == dfa1.ERROR) continue;
        for(auto y : dfa2.states_dfa){
            if(y == dfa2.ERROR) continue;
			bool final = false;
            if(var == 1 && !x->is_final && y->is_final) final = true;
            if(var == 2 && x->is_final && y->is_final) final = true;
            map1.insert({{x,y},std::make_shared<State_dfa>(final, 1)});
			//std::cout << "<" << x->name << "," << y->name << "> ";
        }
    }
	//std::cout << map1.size() <<std::endl;

    //заполняю узлы
    for(auto x : map1){
        for(auto tr1 : x.first.first->traces){
			if(tr1->out == dfa1.ERROR) continue;
            for(auto tr2 : x.first.second->traces){
				if(tr1->out == dfa2.ERROR) continue;
				if(tr1->let == tr2->let){
					for(auto fnd : map1){
						std::pair<std::shared_ptr<State_dfa>, std::shared_ptr<State_dfa>> pair = {tr1->out, tr2->out};
						std::pair<std::shared_ptr<State_dfa>, std::shared_ptr<State_dfa>> pair_rev = {tr2->out, tr1->out};
						if(fnd.first == pair || fnd.first == pair_rev){
							std::shared_ptr<trace> n_tr = std::make_shared<trace>(tr1->let, fnd.second);
							x.second->traces.push_back(n_tr);
						}
					}
				}
            }
        }
    }
	std::pair<std::shared_ptr<State_dfa>, std::shared_ptr<State_dfa>> strt = {dfa1.START, dfa2.START};
	std::pair<std::shared_ptr<State_dfa>, std::shared_ptr<State_dfa>> strt_rev = {dfa2.START, dfa1.START};
    for(auto x : map1){
		if(x.first == strt || x.first == strt_rev) START = x.second;
        states_dfa.push_back(x.second);
    }
	map1.clear();
	ERROR = std::make_shared<State_dfa>(false, true);
	states_dfa.push_back(ERROR);
	for(auto x : states_dfa){
		std::set<char> use;
		for(auto tr : x->traces){
			use.insert(tr->let);
		}
		//std::cout << use.size() << std::endl;
		for(auto l : alfabet){
			if(!use.contains(l)){
				std::shared_ptr<trace> n_tr = std::make_shared<trace>(l, ERROR);
				x->traces.push_back(n_tr);
			}
		}
		use.clear();
	}
	show();
	minimization();
	if(states_dfa.size()!=0) is_empty = false;
	//show();
	//std::cout << "final\n";
}


#endif