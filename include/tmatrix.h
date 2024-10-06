// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор на динамической памяти

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0 ||sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      if (v.sz == 0) {
          throw "Null vector";
      }
      this -> sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem [i];
      }
  }

  TDynamicVector(TDynamicVector&& v) {
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this -> sz = v.sz;
      v.sz = 0;

  }
  ~TDynamicVector()
  {
      delete [] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }

      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v)
  {
      this->sz = v.sz;
      delete[] pMem;
      this->pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }

  size_t size() const { return sz; }

  T* get_pMem() {
      return this->pMem;
  }

  // индексация
  T& operator[](size_t ind)
  { 
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Index out of range");
      }
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Index out of range");
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind < 0 || ind >= sz) {
        throw out_of_range("Index out of range");
    }
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Index out of range");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const
  {
      if (this->sz != v.sz) { return false; }
      for (int i = 0; i < sz; i++) {
          if (this->pMem[i] != v.pMem[i]) { return false; }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const
  {
      if (this->sz != v.sz) { return true; }
      for (int i = 0; i < sz; i++) {
          if (this->pMem[i] != v.pMem[i]) { return true; }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (v.sz != this->sz) {
          throw "Sizes not equal";
      }
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] + v.pMem[i];
      }
      return result;


  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (v.sz != this->sz) {
          throw "Sizes not equal";
      }
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (v.sz != this->sz) {
          throw "Sizes not equal";
      }
      T result(sz);
      result = 0;
      for (int i = 0; i < sz; i++) {
          result += this->pMem[i] * v[i];
      }
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs)
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T> >
{
  using TDynamicVector<TDynamicVector<T> >::pMem;
  using TDynamicVector<TDynamicVector<T> >::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
  {
    if (s > MAX_MATRIX_SIZE) {
        throw out_of_range("Cant instantiate a matrix larger than 10000");
    }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T> >::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const
  {
      if (this->sz != m.sz) { return false; }
      for (int i = 0; i < sz; i++) {
          if (this->pMem[i] != m.pMem[i]) { return false; }
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {

      TDynamicVector<T> res(sz);

      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              res[i] += pMem[i][j] * val;
          }
      }

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<int> result (sz);

      for (int i = 0; i < sz; i++) {
          result[i] = 0;
          for (int j = 0; j < sz; j++) {
              result[i] += pMem[i][j] * v[j];
          }
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw out_of_range("Matrices must be the same size!");
      }
      TDynamicMatrix result (sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] + m[i];
      }
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw out_of_range("Matrices must be the same size!");
      }
      TDynamicMatrix result (sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = this->pMem[i] - m[i];
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (m.size() != sz) {
          throw "Can't multiply matrices of non-equal sizes!";
      }
      TDynamicMatrix<T> result(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              result[i][j] = 0;
              for (int k = 0; k < sz; k++) {
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return result;

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          for (size_t i = 0; i < pMem[i].sz; i++)
              istr >> v.pMem[i].pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i][j] << ' ';
      }

      return ostr;
  }

  T get_size() {
      return this->sz;
  }

  TDynamicVector<T>* get_pMem() {
      return this->pMem;
  }
};

#endif
