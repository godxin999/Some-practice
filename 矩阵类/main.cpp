#include "pch.h"
#include "Matrix.h"
using std::cin;
using std::cout;
using std::endl;
void test() {
	int r, c;
	cout << "输入矩阵A的行数，列数"<<endl;
	cin >> r >> c;
	Matrix A(r, c);
	cout << "输入矩阵A"<<endl;
	cin >> A;
	cout << "输入矩阵B的行数，列数" << endl;
	cin >> r >> c;
	Matrix B(r, c);
	cout << "输入矩阵B" << endl;
	cin >> B;
	cout << "A+B的结果是" << endl;
	Matrix D = A + B;
	D.print();
	cout << "A-B的结果是" << endl;
	D = A - B;
	D.print();
	cout << "A*B的结果是" << endl;
	D = A * B;
	D.print();
	cout << "输入一个数" << endl;
	double x;
	cin >> x;
	cout << "和矩阵A数乘的结果是" << endl;
	D = x * A;
	D.print();
	cout << "A的行列式的值为" << endl;
	double a = A.det();
	cout << a << endl;
	cout << "A的转置矩阵为" << endl;
	Matrix::T(A).print();
	cout << "A的逆矩阵为" << endl;
	Matrix::inv(A).print();
	cout << "输入想要交换的两行" << endl;
	int d, f;
	cin >> d >> f;
	A.swapRows(d, f);
	cout << "交换后的结果是" << endl;
	A.print();
	cout << "输入矩阵C的行数，列数" << endl;
	cin >> r >> c;
	Matrix C(r, c);
	cout << "输入线性方程组的矩阵C" << endl;
	cin >> C;
	cout << "线性方程组C的解为" << endl;
	Matrix E = C.GaussSlove();
	E.print();
}

int main() {
	test();
	system("pause");
	return 0;
}