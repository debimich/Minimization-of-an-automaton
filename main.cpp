#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int st_num;
	int sign_num;
	std::cout << "Input number of states: ";
	std::cin >> st_num;
	std::cout << "Input input signals: ";
	std::cin >> sign_num;
	std::vector<std::vector<int>> Table(st_num, std::vector<int>(sign_num * 2));
	std::cout << "Input table: " << std::endl;;
	for (int i = 0; i < st_num; i++) {
		for (int j = 0; j < sign_num * 2; j++) {
			std::cin >> Table[i][j];
		}
	}
	std::vector<std::vector<int>> Partition(st_num, std::vector<int>(st_num + 1));
	int part_i = 0;
	int part_j = 0;
	for (int i = 0; i < st_num - 1; i++) {
		int temp = 1;
		for (int l = 0; l < part_i; l++) {
				if (std::find(Partition[l].begin(), Partition[l].end(), i + 1) != Partition[l].end())
					temp = 0;
			}
		if (temp == 1) {
			Partition[part_i][part_j] = i + 1;
			part_j++;
			for (int k = i + 1; k < st_num; k++) {
					int flag = 1;
					for (int j = sign_num; j < sign_num * 2; j++) {
						if (Table[i][j] != Table[k][j])
							flag = 0;
					}
					if (flag == 1) {
						Partition[part_i][part_j] = k + 1;
						part_j++;
					}
					//std::cout << i << ' ' << k << ' ' << part_i << ' ' << part_j << ' ' << std::endl;
			}
		}
		part_i++;
		part_j = 0;
	}
	std::cout << "GOVNO: " << std::endl;;
	for (int i = 0; i < part_i; i++) {
		for (int j = 0; j < st_num; j++) {
			std::cout << Partition[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}