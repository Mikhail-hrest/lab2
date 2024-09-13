#include "DFA.h"
#include <set>
/*
// if var = 1  -> it is difference
// if var = 2  -> it is intersection
DFA::DFA(DFA dfa1, DFA dfa2, int var){
	std::set<std::pair<std::pair<State_dfa*, State_dfa*> , State_dfa*>> map;
	int size1 = 1 , size2 = 1;
	for(auto a : dfa1.states_dfa){
                if(a != dfa1.ERROR){
                        a->name = size1;
                        ++size1;
                }
        }
	for(auto a : dfa2.states_dfa){
                if(a != dfa2.ERROR){
                        a->name = size2;
                        ++size2;
                }
        }
	int sz = size1*size2;
	//заполняю вершины
	for(auto x : dfa1.states_dfa){
		bool final = false;
		if(x == dfa1.ERROR) continue;
		for(auto y : dfa2.states){
			if(y = dfa2.ERROR) continue;
			if(var == 1 && x->is_final && !y->is_final) final = true;
			if(var == 2 && x->is_final && y->is_final) final = true;
			map.insert({{x,y},new State_dfa(final, 1)});
		}
	}
	//заполняю узлы
	for(auto x : map){
		for(auto tr1 : x.first.first->traces){
			for(auto tr2 : x.first.secons->traces){
				for(auto y : map){
					if(tr1.let == tr2.let){
						for(auto fnd : map){
							if(fnd.first == {tr1->out, tr2->out}){
								x.second.traces.push_back(fnd.second);
							}
						}
					}
				}
			}
		}
	}
	for(auto x : map){
		states_dfa.push_back(x.second);
	}
};
*/
