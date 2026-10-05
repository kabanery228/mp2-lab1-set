// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 1)
        len = 0;
    else if (len < 31) {
        BitLen = len;
        MemLen = 1;
        //pMem = new TELEM[1]{};
    }
    else {
        BitLen = len;
        MemLen = (len + 31) >> 5;
        pMem = new TELEM[MemLen]{};
    }
    pMem = new TELEM[MemLen]{};
}

TBitField::TBitField(const TBitField &bf):BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
    pMem = new TELEM[MemLen]{};
    for (int i{}; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n>>5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1<<(n&31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) return;
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) return;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)]&GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen; MemLen = bf.MemLen;
        pMem = new TELEM[MemLen]{};
        for (int i{};i < BitLen; pMem[i] = bf.pMem[i++]);
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return false;
    else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int mx_bitlen = max(this->BitLen, bf.BitLen);
    TBitField tmp(mx_bitlen);
    for (int i = 0;i < mx_bitlen;i++) {
        if (i < min(this->BitLen, bf.BitLen)) tmp.pMem[i] = this->pMem[i] | bf.pMem[i];
        else tmp.pMem[i] = ((BitLen > bf.BitLen) ? this->pMem[i] : bf.pMem[i]);
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int mx_bitlen = max(this->BitLen, bf.BitLen);
    TBitField tmp(mx_bitlen);
    for (int i = 0;i < mx_bitlen;i++) {
        if (i < min(this->BitLen, bf.BitLen)) tmp.pMem[i] = this->pMem[i] & bf.pMem[i];
        else tmp.pMem[i] = ((BitLen > bf.BitLen) ? this->pMem[i] : bf.pMem[i]);
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);
    for (int i{}; i < tmp.MemLen; i++) {
        tmp.pMem[i] = ~tmp.pMem[i];
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
    char ch;
    while (i < bf.GetLength() && istr.get(ch)) {
        //istr >> ch;
        if (ch == '0') bf.ClrBit(i++);
        else if (ch == '1') bf.SetBit(i++);
        else {
            istr.putback(ch);
            break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0;i < bf.GetLength();(bf.GetBit(i++)) ? ostr << '1' : ostr << '0');
    return ostr;
}
