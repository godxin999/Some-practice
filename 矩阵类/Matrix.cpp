#include "pch.h"
#include "Matrix.h"

const double eps = 1e-8;

void Matrix::init() {
	p = new double*[row_size];
	for (int i = 0; i < row_size; i++) {
		p[i] = new double[col_size];
	}
}

Matrix::Matrix(int row, int col):row_size(row),col_size(col) {
	init();
	for (int i = 0; i < row_size; i++) {
		for(int j = 0; j < col_size; j++) {
			p[i][j] = 0;
		}
	}
}

Matrix::Matrix(int row, int col, double value) :row_size(row), col_size(col) {
	init();
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] = value;
		}
	}
}

Matrix::Matrix(const Matrix& m):row_size(m.row_size), col_size(m.col_size) {
	init();
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] = m.p[i][j];
		}
	}
}

Matrix::Matrix(Matrix&& m)noexcept{
	row_size = m.row_size;
	col_size = m.col_size;
	p = m.p;
	m.p = nullptr;
}

Matrix::~Matrix() {
	if (p != NULL) {
		for (int i = 0; i < row_size; i++) {
			delete[] p[i];
		}
		delete[] p;
	}
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m)return *this;
	if (row_size != m.row_size || col_size != m.col_size) {
		this->~Matrix();
		row_size = m.row_size;
		col_size = m.col_size;
		init();
	}
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] = m.p[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& m)noexcept{
	if (this == &m)return *this;
	row_size = m.row_size;
	col_size = m.col_size;
	p = m.p;
	m.p = nullptr;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	Matrix temp(row_size, m.col_size,0.0);
	for (int i = 0; i < row_size; i++) {
		for (int k = 0; k < col_size; k++) {
			double s = p[i][k];
			for (int j = 0; j < m.col_size; j++) {
				temp.p[i][j] += (s * m.p[k][j]);
			}
		}
	}
	*this = temp;
	return *this;
}

Matrix& Matrix::operator*=(const double& num) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			p[i][j] = p[i][j] * num;
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& m)const {
	Matrix temp(row_size, col_size, 0.0);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			temp.p[i][j] = p[i][j] + m.p[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& m)const {
	Matrix temp(row_size, col_size, 0.0);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			temp.p[i][j] = p[i][j] - m.p[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& m)const {
	Matrix temp(row_size, m.col_size, 0.0);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < m.col_size; j++) {
			for (int k = 0; k < col_size; k++) {
				temp.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	return temp;
}

Matrix Matrix::operator*(const double& num)const {
	Matrix temp(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			temp.p[i][j] = p[i][j] * num;
		}
	}
	return temp;
}

Matrix Matrix::operator/(const double& num)const {
	Matrix temp(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			temp.p[i][j] = p[i][j] / num;
		}
	}
	return temp;
}

Matrix operator*(const double& num, const Matrix& m) {
	Matrix temp(m.row_size, m.col_size);
	temp = m * num;
	return temp;
}

std::istream& operator >>(std::istream& is, Matrix& m) {
	for (int i = 0; i < m.row_size; i++) {
		for (int j = 0; j < m.col_size; j++) {
			is >> m.p[i][j];
		}
	}
	return is;
}

inline double Matrix::point(int i, int j) {
	return this->p[i][j];
}

inline int Matrix::row()const {
	return row_size;
}

inline int Matrix::col()const {
	return col_size;
}

void Matrix::swapRows(int a, int b) {
	a--;
	b--;
	double* temp = p[a];
	p[a] = p[b];
	p[b] = temp;
}

double Matrix::det() {
	double ans = 1.0;
	if (col() != row()) {
		std::cout <<"Can't calculate." << std::endl;
		std::abort();
	}
	Matrix temp(*this);
	for(int i = 0; i < row(); i++){
		for (int j = i + 1; j < row(); j++) {
			while (fabs(temp.p[i][i])>eps) {
				double x = temp.p[j][i] / temp.p[i][i];
				for (int k = 0; k < row(); k++) {
					temp.p[j][k] -= x * temp.p[i][k];
					if (fabs(temp.p[j][k]) < eps) {
						temp.p[j][k] = 0;
					}
				}
				temp.swapRows(i+1, j+1);
				ans *= -1;
			}
			temp.p[i][i] = 0;
			temp.swapRows(i+1, j+1);
			ans *= -1;
		}
	}
	for (int i = 0; i < row(); i++) {
		ans *= temp.p[i][i];
	}
	if (fabs(ans) < eps)ans = 0;
	return ans;
}

Matrix Matrix::GaussSlove() {
	Matrix ans(row(), 1);
	if (col() != row()+1) {
		std::cout << "Can't calculate." << std::endl;
		return ans;
	}
	Matrix temp(*this);
	int r, c;
	for (r = 0, c = 0; c < row(); c++) {
		int t = r;
		for (int i = r; i < row(); i++) {
			if (fabs(temp.p[i][c]) > fabs(temp.p[t][c])) {
				t = i;
			}
		}
		if (fabs(temp.p[t][c]) < eps)continue;
		temp.swapRows(t+1,r+1);
		for (int i = row(); i >= c; i--) {
			temp.p[r][i] /= temp.p[r][c];
		}
		for (int i = r + 1; i < row(); i++) {
			if (fabs(temp.p[i][c]) > eps) {
				for (int j = row(); j >= c; j--) {
					temp.p[i][j] -= temp.p[r][j] * temp.p[i][c];
				}
			}
		}
		r++;
	}
	if (r < row()) {
		for (int i = r; i < row(); i++) {
			if (fabs(temp.p[i][row()]) > eps) {
				std::cout << "Have no solution." << std::endl;
				return ans;
			}
		}
		std::cout << "Have countless solutions." << std::endl;
		return ans;
	}
	for (int i = row() - 1; ~i; i--) {
		for (int j = i + 1; j < row(); j++) {
			temp.p[i][row()] -= temp.p[i][j] * temp.p[j][row()];
		}
		ans.p[i][0] = temp.p[i][row()];
		if (fabs(ans.p[i][0]) < eps) {
			ans.p[i][0] = 0;
		}
	}
	return ans;
}

Matrix Matrix::inv(const Matrix& m) {
	if (m.col() != m.row()) {
		std::cout << "Don't have inverse matrix." << std::endl;
		std::abort();
	}
	Matrix temp(m.row(),2*m.col());
	Matrix inv(m.row(), m.col());
	for (int i = 0; i < m.row(); i++) {
		for (int j = 0; j < m.col(); j++) {
			temp.p[i][j] = m.p[i][j];
		}
		temp.p[i][i+m.col()] = 1;
	}
	int c;
	for (c = 0; c <temp.row(); c++) {
		int r = c;
		for (int i = c+1; i < temp.row(); i++) {
			if (fabs(temp.p[i][c]) > fabs(temp.p[r][c])) {
				r = i;
			}
		}
		if (r != c)temp.swapRows(r+1, c+1);
		if (fabs(temp.p[c][c])<eps) {
			std::cout << "Don't have inverse matrix." << std::endl;
			std::abort();
		}
		for (int i = 0; i < temp.row(); i++) {
			if (i == c)continue;
			double x = temp.p[i][c] / temp.p[c][c];
			for (int j = c; j < temp.col(); j++) {
				temp.p[i][j] -= x * temp.p[c][j];
			}
		}
		for (int i = temp.col()-1; ~i; i--) {
			temp.p[c][i] /= temp.p[c][c];
		}
	}
	for (int i = 0; i < temp.row(); i++) {
		for (int j = m.col(); j < temp.col(); j++) {
			inv.p[i][j - m.col()] = temp.p[i][j];
			if (fabs(inv.p[i][j - m.col()]) < eps) {
				inv.p[i][j - m.col()] = 0;
			}
		}
	}
	return inv;
}

Matrix Matrix::T(const Matrix& m) {
	Matrix temp(m.col(), m.row());
	for (int i = 0; i < temp.row(); i++) {
		for (int j = 0; j < temp.col(); j++) {
			temp.p[i][j] = m.p[j][i];
		}
	}
	return temp;
}

Matrix Matrix::E(int size) {
	Matrix temp(size, size);
	for (int i = 0; i < size; i++) {
		temp.p[i][i] = 1;
	}
	return temp;
}

void Matrix::print()const {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			std::cout << p[i][j] << " ";
		}
		std::cout <<std:: endl;
	}
	std::cout << std::endl;
}
