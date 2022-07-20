#pragma once
#ifndef __MATRIX_CLL_H__
#define __MATRIX_CLL_H__

#include "pch.h"

class Matrix{
private:
	int row_size;//行数
	int col_size;//列数
	double** p;//用于申请空间
	void init();//初始化函数

public:
	Matrix(int, int);//构造0矩阵
	Matrix(int, int, double);//构造值皆为value的矩阵
	Matrix(const Matrix&);//拷贝构造函数
	Matrix(Matrix&&)noexcept;//移动构造函数
	virtual ~Matrix();//析构函数

public:
	Matrix& operator=(const Matrix&);//重载等号，赋值
	Matrix& operator=(Matrix&&)noexcept;//重载等号，用于计算
	Matrix& operator+=(const Matrix&);//重载+=
	Matrix& operator-=(const Matrix&);//重载-=
	Matrix& operator*=(const Matrix&);//重载*=
	Matrix& operator*=(const double&);//数乘
	Matrix operator+(const Matrix&)const;//重载+
	Matrix operator-(const Matrix&)const;//重载-
	Matrix operator*(const Matrix&)const;//重载*，实现矩阵乘法
	Matrix operator*(const double&)const;//右端数乘
	Matrix operator/(const double&)const;
	friend Matrix operator*(const double&, const Matrix&);//左端数乘
	friend std::istream& operator>>(std::istream&, Matrix&);//流输入

public:
	int row()const;//返回行数
	int col()const;//返回列数
	double point(int, int);//返回点的值
	void swapRows(int, int);//交换两行
	double det();//求行列式
	Matrix GaussSlove();//高斯消元解线性方程组
	static Matrix inv(const Matrix&);//求逆矩阵
	static Matrix T(const Matrix&);//求转置矩阵
	static Matrix E(int);//单位阵
	void print()const;//打印矩阵

};

#endif 