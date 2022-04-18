#include <cstdio>

template <typename T, typename TCompare = std::less<T>>
stats merge_sort(std::vector<T>& vec) {
	TCompare less;
	stats stat;
	std::vector<T> res(vec.size());
	while (true) {
		size_t resl = 0; // ����� ������� ����������������� ������������������ � res
		size_t resr = res.size() - 1; // ������ ������� ����������������� ������������������ � res
		bool left = true;
		size_t vecl = 0; // ������ ����� ������� ����������������� ������������������ � vec
		size_t vecr = vec.size() - 1; // ������ ������ ������� ����������������� ������������������ � vec
		while (vecl < vecr) {
			size_t i = vecl;
			size_t j = vecr;
			size_t podsize = 2;
			stat.comparison_count++;
			while (vecl <= vecr && !less(vec[vecl + 1], vec[vecl])) {
				stat.comparison_count++;
				vecl++;
				podsize++;
				if (vecl == vec.size() - 1) return stat;
			}
			stat.comparison_count++;
			while (vecl <= vecr && !less(vec[vecr - 1], vec[vecr])) {
				stat.comparison_count++;
				vecr--; // ��������� vecr ���� ��������� ��������������� ��������������������� ������ ������ �� ������ �������
				podsize++;
			}
			for (size_t p = 0; p < podsize; ++p) {
				if (i <= vecl) {
					if (j < vecr) { // ���� ��� ������ ��������������������� ��� ���������, �� ���������� ���������� ����� ������������������
						if (left) {
							res[resl] = vec[i];
							stat.copy_count++;
							resl++;
						}
						else {
							res[resr] = vec[i];
							stat.copy_count++;
							resr--;
						}
						i++; //�� �� ������ ������ ���������
						continue;
					}
					else if (less(vec[i], vec[j])) { //���� ������ ��������������������� �� ������� �����������, �� ����� ����������
						stat.comparison_count++;
						if (left) {
							res[resl] = vec[i];
							stat.copy_count++;
							resl++;
						}
						else {
							res[resr] = vec[i];
							stat.copy_count++;
							resr--;
						}
						i++; //�� �� ������ ������ ���������
						continue;
					}
					else if (i == j) {
						res[resl] = vec[i];
						stat.copy_count++;
						break;
					}
				}
				if (j >= vecr) {
					if (i > vecl) { // ��� ����� ��������������������� �����������
						if (left) {
							res[resl] = vec[j];
							stat.copy_count++;
							resl++;
						}
						else {
							res[resr] = vec[j];
							stat.copy_count++;
							resr--;
						}
						j--; //�� �� ������ ������ ���������
						continue;
					}
					else if (less(vec[j], vec[i])) { //���� ����� ��������������������� �� ������� �����������, �� ����� ����������
						stat.comparison_count++;
						if (left) {
							res[resl] = vec[j];
							stat.copy_count++;
							resl++;
						}
						else {
							res[resr] = vec[j];
							stat.copy_count++;
							resr--;
						}
						j--; //�� �� ������ ������ ���������
						continue;
					}
				}
			}
			left = !left;
			vecl++;
			vecr--;
		}
		vec = res;
		stat.copy_count += res.size();
	}
}  // ������ ���������� :(
