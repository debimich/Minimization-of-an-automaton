#include <iostream>
#include <string>
#include <vector>
#include <set>

void printPart(std::vector<std::set<std::string>> CurPartSet, int PartNum);

int main() {

	int st_num;
	int inSig_num;
	std::cout << "Enter number of states: ";
	std::cin >> st_num;
	std::cout << "Enter input signals: ";
	std::cin >> inSig_num;
	std::vector<std::vector<std::string>> TransTable(st_num, std::vector<std::string>(inSig_num + 1));
	std::cout << "Enter transition table:" << std::endl;
	for (int i = 0; i < st_num; i++) {
		for (int j = 0; j < inSig_num + 1; j++) {
			if (j == inSig_num)
				getline(std::cin, TransTable[i][j]);
			else 
				std::cin >> TransTable[i][j];
		}
	}

	std::vector<std::vector<std::string>> SaveTransTable(st_num, std::vector<std::string>(inSig_num + 1));
	SaveTransTable = TransTable;

	int PartNum = 0;
	std::vector<std::set<std::string>> PrePartSet;
	std::vector<std::set<std::string>> CurPartSet;
	CurPartSet.push_back(std::set<std::string>{"1"});
	for (int i = 1; i < st_num; i++)
		CurPartSet[0].insert(std::to_string(i + 1));
	printPart(CurPartSet, PartNum);
	while (PrePartSet != CurPartSet) {
		PrePartSet = CurPartSet;
		CurPartSet.clear();
		for (int i = 0; i < st_num - 1; i++) {
			if (TransTable[i][inSig_num] != "") {
				CurPartSet.push_back(std::set<std::string>{std::to_string(i + 1)});
				for (int j = i + 1; j < st_num; j++) {
					if (TransTable[i][inSig_num] == TransTable[j][inSig_num]) {
						for (int k = 0; k < PrePartSet.size(); k++) {
							if ((PrePartSet[k].count(std::to_string(i + 1)) != 0) && (PrePartSet[k].count(std::to_string(j + 1)) != 0)) {
								CurPartSet[CurPartSet.size() - 1].insert(std::to_string(j + 1));
								TransTable[j][inSig_num] = "";
							}
						}
					}
				}
			}
		}
		if (TransTable[st_num - 1][inSig_num] != "")
			CurPartSet.push_back(std::set<std::string>{std::to_string(st_num)});
		
		for (int i = 0; i < st_num; i++) {
			TransTable[i][inSig_num] = "";
			for (int j = 0; j < inSig_num; j++) {
				for (int k = 0; k < CurPartSet.size(); k++) {
					if (CurPartSet[k].count(TransTable[i][j]) != 0) {
						TransTable[i][inSig_num] += std::to_string(k + 1);
						TransTable[i][inSig_num] += " ";
					}
				}
			}
		}

		PartNum++;
		printPart(CurPartSet, PartNum);

		for (int i = 0; i < st_num; i++) {
		for (int j = 0; j < inSig_num + 1; j++)
			std::cout << TransTable[i][j] << " ";
		std::cout << std::endl;
		}

	}

	if (CurPartSet.size() == st_num)
		std::cout << "Automaton is not minimized" << std::endl;
	else {
		std::cout << "Automaton is minimized" << std::endl;
		std::cout << "New automaton" << std::endl;
		for (int i = 0; i < CurPartSet.size(); i++) {
			std::string element = *(CurPartSet[i].begin());
			int index = std::stoi(element);
			std::cout << i + 1 << "  " << TransTable[index - 1][inSig_num] << SaveTransTable[index - 1][inSig_num] << std::endl;
		}
	}


	return 0;
}

void printPart(std::vector<std::set<std::string>> CurPartSet, int PartNum) {
	char ch = 'A';
	std::cout << "pi" << PartNum << " = {";
	for (const auto& mySet : CurPartSet) {
		std::cout << " " << ch << PartNum << " = < ";
		for (const auto& element : mySet) {
			std::cout << element << " ";
		}
		std::cout << "> ";
		ch++;
	}
	std::cout << "}" << std::endl;
}