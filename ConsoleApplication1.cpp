#include <iostream>
#include <cmath>
#include <vector>

//Функция нахождения определителя матрицы 3 на 3
double determinant3(double product[3][3]) {
	return product[0][0] * product[1][1] * product[2][2] - product[0][0] * product[1][2] * product[2][1]
		- product[0][1] * product[1][0] * product[2][2] + product[0][1] * product[1][2] * product[2][0]
		+ product[0][2] * product[1][0] * product[2][1] - product[0][2] * product[1][1] * product[2][0];

}

//Функция нахождения расстояния между плоскостями без свободных членов
//В каждом члене выражения содержится определитель i,j,k
double lenght(std::vector<double> d1, std::vector<double> d2) {
	return sqrt(pow((d1[1] * d2[2] - d2[1] * d1[2]), 2) + pow((d1[0] * d2[2] - d2[0] * d1[2]), 2) + pow((d1[0] * d2[1] - d2[0] * d1[1]), 2));
}

//Функция создания двумерного массива с точками, где точка представляет собой массив из значений x,y,z
void make_array(double points[2][3], int i) {
	std::cout << "Введите координаты двух точек в трехмерном пространстве для прямой " << i << ":\n";
	std::vector<char> coor = { 'x','y','z' };
	for (int j = 0; j < 2; ++j) {
		for (int l = 0; l < 3; ++l) {
			std::cout << coor[l] << j+1 << ": ";
			std::cin >> points[j][l];
		}
	}
}

//Функция подсчета направляющего вектора для перевода векторов в декартову систему
std::vector<double> direction(double matrix[2][3]) {
	std::vector<double> d;
	for (int i = 0; i < 3; i++) {
		d.push_back(matrix[1][i] - matrix[0][i]); //по формуле значения направляющего вектора x2-x1, y2-y1, z2-z1
	}
	return d;
}

//Функция проверки линейной зависимости векторов (являются параллельными или пересекаются)
bool check_dependence(std::vector<double> d1, std::vector<double> d2) {
	bool check = true;
	for (int i = 0; i < 2; i++) {
		if (d1[i] / d2[i] != d1[i+1] / d2[i + 1]) { //сравниваем совпадает ли коэффициент разницы между значениями векторов на протяжении всего вектора
			check = false;
			break;
		}
	}
	return check;
}

//Функция нахождения вектора, который соединяет 2 точки введеных векторов
std::vector<double> connect(double first[2][3], double second[2][3]) {
	std::vector<double> con;
	for (int i = 0; i < 3; i++) {
		con.push_back(second[0][i] - first[0][i]);
	}
	return con;
}

//Функция нахождения расстояния между линейно НЕЗАВИСИМЫМИ векторами
void find_distance_independence(double first[2][3], double second[3][3], std::vector<double> d1, std::vector<double> d2) {
	//найдем вектор, соединяющий линии
	std::vector<double> connection = connect(first, second);
	//Найдем смешанное произведение векторов. Построим матрицу
	//Для этого подсчитаем определитель матрицы направляющих векторов d1 и d2 и общего connection
	double product[3][3];
	for (int i = 0; i < 3; i++) {
		std::vector<double> temp;
		if (i == 0) {
			temp = d1;
		}
		else if (i == 1) {
			temp = d2;
		}
		else {
			temp = connection;
		}
		for (int j = 0; j < 3; j++) {
			product[i][j] = temp[j];
			}
	}
	//Найдем определитель получившейся матрицы
	double det = determinant3(product);
	std::cout << "Минимальная длина между заданными линиями равна: " << abs(det) / lenght(d1, d2) << std::endl;
}

//Функция нахождения расстояния между линейно ЗАВИСИМЫМИ векторами
void find_distance_dependence(double first[2][3], double second[3][3], std::vector<double> d1, std::vector<double> d2) {
	std::vector<double> connection = connect(first, second);
	double l = lenght(connection, d1);
	//Произведение с направляющим вектором для первой прямой (тк они парралельны, то возьмем любой из них, здесь: 1-й) 
	double l2 = sqrt(pow(d1[0], 2) + pow(d1[1], 2) + pow(d1[2], 2));
	std::cout << "Минимальная длина между заданными линиями равна: " << l / l2 << std::endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double first[2][3], second[2][3];
	//Попросим пользователя ввести x,y,z координаты 2-х точек для каждой из прямой
	make_array(first, 1);
	make_array(second, 2);
	//Подсчитаем направляющий вектор для каждой из прямой
	std::vector<double> d1 = direction(first);
	std::vector<double> d2 = direction(second);
	//Выбор функции для подсчета расстояния исходя из того, являются ли прямые линейно зависимыми
	if (check_dependence(d1,d2) == true) {
		find_distance_dependence(first, second, d1, d2);
	}
	else {
		find_distance_independence(first, second, d1, d2);
	}
	system("pause");
}

