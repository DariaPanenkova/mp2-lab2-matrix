﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() const    { return Size;       } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos) const;             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
template <class ValType>
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
template <class ValType>
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if(s > MAX_VECTOR_SIZE)
		throw invalid_argument("Uncorrectly size, s<MAX_VECTOR_SIZE");
	if(s < 0)
		throw invalid_argument("Uncorrectly size, s<0");
	if(si < 0)
		throw invalid_argument("Uncorrectly startindex, si<0");
	Size=s;
	StartIndex=si;
	pVector=new ValType[Size];
	for(int i=StartIndex; i < Size+StartIndex; i++)
	{
		(*this)[i]=ValType();
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size=v.Size;
	StartIndex=v.StartIndex;
	pVector=new ValType[Size];
	for( int i=0; i < Size+StartIndex; i++)
	{
		(*this)[i]= v[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	if(pVector != NULL)
		delete []pVector;

} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) const
{
	if(pos > Size+StartIndex)
		throw invalid_argument("Uncorrectly position, pos > Size");
	if(pos < 0)
		throw invalid_argument("Uncorrectly position, pos<0");
	if(pos > MAX_VECTOR_SIZE)
		throw invalid_argument("Uncorrectly position, pos<MAX_VECTOR_SIZE");
	/*if (pos < StartIndex) 
		throw invalid_argument("Uncorrectly position, pos<StartIndex");*/
	if(pos<StartIndex){
		return *new ValType();
	}

	return pVector[pos-StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if(this==&v)
		return true;
	if( Size!=v.Size)
		return false;
	for( int i=StartIndex; i < Size+StartIndex; i++)
	{
		if ((*this)[i]!=v[i])
			return false;
	}
	return true;
	 
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if(this==&v)
		return false;
	if( Size!=v.Size )
		return true;
	for( int i=StartIndex; i < Size+StartIndex; i++)
		if ((*this)[i]!=v[i])
			return true;
	return false;

} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if(this==&v)
		return *this;

	if (Size != v.Size)
	{
		Size=v.Size;
		delete []pVector;
		pVector=new ValType[Size];
	}
	StartIndex=v.StartIndex; 
	for( int i=StartIndex; i < Size+StartIndex; i++)
		(*this)[i] = v[i]; 
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res(Size,StartIndex);
	for( int i=StartIndex; i < Size+StartIndex; i++)
		res[i] = (*this)[i] + val; 

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{

	TVector<ValType> res(Size,StartIndex);
	for( int i=StartIndex; i < Size+StartIndex; i++)
		res[i] = (*this)[i] - val; 

	return res;


} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res(Size,StartIndex);
	for( int i=StartIndex; i < Size+StartIndex; i++)
		res[i] = (*this)[i] * val; 

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if(Size != v.Size)
		throw "Not equal size";

	else 
		if(StartIndex != v.StartIndex)
			throw "Not equal start index";
		else
			{
				TVector<ValType> res(Size,StartIndex);

				for(int i=StartIndex; i < Size+StartIndex; i++)
					res[i]= (*this)[i] + v[i];

				return res;
			}

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if(Size != v.Size)
		throw "Not equal size";

	else 
		if(StartIndex != v.StartIndex)
			throw "Not equal start index";
		else
			{
				TVector<ValType> res(Size,StartIndex);

				for(int i=StartIndex; i < Size+StartIndex; i++)
					res[i]= (*this)[i] - v[i];

				return res;
			}

} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw "Not equal size";

	else 
		if(StartIndex != v.StartIndex)

			throw "Not equal start index";
	else
	{
		ValType res=0;
		for (int i=StartIndex; i < Size+StartIndex;i++)
			res  = res + ((*this)[i] * v[i]);
		return res;
	}

} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
template <class ValType>

  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
template <class ValType>

  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if(s<0)
		throw invalid_argument("s<0");
	if(s > MAX_MATRIX_SIZE)
		throw invalid_argument("Size more than MAX_MATRIX_SIZE(Matrix)");
	
	Size = s;

	for(int i=0; i < Size; i++)
			pVector[i] = TVector<ValType>(Size-i ,i);

	for (int i=0; i < Size; i++)
		for (int j=(*this)[i].GetStartIndex(); j < (*this)[i].GetStartIndex() + (*this)[i].GetSize(); j++)
			pVector[i][j] = 0;

	
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) 
		return true;
	

	if (Size != mt.Size) {
		return false;
	}

	for (int i = 0; i < Size; i++) {
		if (pVector[i] != mt.pVector[i])
			return false;
	}

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	/*if (this != &mt)
		return true;

	else
		if (StartIndex != mt.StartIndex)
			return true;

		else
		{
			for (int i = StartIndex; i < Size; i++)

				if (pVector[i]!= mt.pVector[i])

					return true;
					
				else
					return false;
		}*/
	return !(*this==mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt)
	{
		if (Size != mt.Size) 
		{
			delete[] pVector;
			pVector = new TVector<ValType>[mt.Size];
		}
		Size = mt.Size;
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size!=(mt.Size))
	{
		throw invalid_argument("Not equal size");
	}
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] + mt.pVector[i];
		
	}
	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size!=(mt.Size))
	{
		throw invalid_argument("Not equal size");
	}
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - mt.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
