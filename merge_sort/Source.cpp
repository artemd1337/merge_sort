#include <cstdio>

template <typename T, typename TCompare = std::less<T>>
stats merge_sort(std::vector<T>& vec) {
	TCompare less;
	stats stat;
	std::vector<T> res(vec.size());
	while (true) {
		size_t resl = 0; // Ћева€ граница неотсортированной последовательности в res
		size_t resr = res.size() - 1; // ѕрава€ граница неотсортированной последовательности в res
		bool left = true;
		size_t vecl = 0; // »ндекс левой границы неотсортированной последовательности в vec
		size_t vecr = vec.size() - 1; // »ндекс правой границы неотсортированной последовательности в vec
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
				vecr--; // ”меньшает vecr пока находитс€ увеличивающа€с€ подпоследовательность справа налево от правой границы
				podsize++;
			}
			for (size_t p = 0; p < podsize; ++p) {
				if (i <= vecl) {
					if (j < vecr) { // ≈сли вс€ права€ подпоследовательность уже перебрана, то поочередно записываем левую последовательность
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
						i++; //ћб не всегда делать инкремент
						continue;
					}
					else if (less(vec[i], vec[j])) { //≈сли права€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
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
						i++; //ћб не всегда делать инкремент
						continue;
					}
					else if (i == j) {
						res[resl] = vec[i];
						stat.copy_count++;
						break;
					}
				}
				if (j >= vecr) {
					if (i > vecl) { // ¬с€ лева€ подпоследовательность рассмотрена
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
						j--; //ћб не всегда делать декремент
						continue;
					}
					else if (less(vec[j], vec[i])) { //≈сли лева€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
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
						j--; //ћб не всегда делать декремент
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
}  // —тыдно показывать :(
