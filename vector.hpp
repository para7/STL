#pragma once
#include <algorithm>
namespace my
{
    template<class T>
    class vector
    {
    private:

        T* m_data;

        int m_size;//実際に使っているサイズ

        int m_capacity;//確保したメモリサイズ
        //配列サイズの変更にはコストが大きくかかるため余裕を持って確保する

    public:

        vector() : m_data(nullptr)
            , m_size(0)
            , m_capacity(0) {};

        vector(int n) : m_data(nullptr)
            , m_size(0)
            , m_capacity(0)
        {
            resize(n);
        }

        ~vector()
        {
            delete[] m_data;//deleteに[]をつけないと確か配列として開放されなくてメモリリークする
        }

        T& operator[] (int n) { return m_data[n]; }

        T& at(int n)
        {
            if (n < m_size)
            {
                throw std::out_of_range();
            }

            return m_data[n];
        }

        void reserve(int _capacity)
        {
            //既に確保されている領域の方が大きい場合
            if (_capacity < m_capacity)
            {
                return;
            }

            //新しい領域を確保
            auto newdata = new T[_capacity];

            const int nextsize = std::min(m_capacity, _capacity);

            //データを新領域にコピー
            for (size_t i = 0; i < m_size; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //空のデータで埋める
            //for (int i = m_size; i < _capacity; ++i)
            //{
            //    newdata[i] = T();
            //}

            if (m_capacity > 0)
            {
                //今まで使っていた領域を開放
                delete[] m_data;
            }

            //配列を差し替え
            m_data = newdata;

            //キャパシティを更新
            m_capacity = _capacity;

            //配列サイズを修正
            //m_size = capacity;
        }

        void resize(int _size)
        {
            if (_size < 0)
            {
                return;
            }

            //新しい領域を確保
            auto newdata = new T[_size];

            const int nextsize = std::min(m_capacity, _size);

            //データを新領域にコピー
            for (size_t i = 0; i < nextsize; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //空のデータで埋める
            for (size_t i = nextsize; i < _size; ++i)
            {
                newdata[i] = T();
            }

            if (m_capacity > 0)
            {
                //今まで使っていた領域を開放
                delete[] m_data;
            }

            //配列を差し替え
            m_data = newdata;

            //キャパシティを更新
            m_capacity = _size;

            //配列サイズを修正
            m_size = _size;
        }

        void push_back(const T& value)
        {
            //領域が足りない時
            if (m_capacity < m_size + 1)
            {
                reserve(m_size * 2 + 1);
            }

            m_data[m_size] = move(value);
            m_size++;
        }

        void push_back(T&& value)
        {
            //領域が足りない時
            if (m_capacity < m_size + 1)
            {
                reserve(m_size * 2 + 1);
            }

            m_data[m_size] = std::move(value);
            m_size++;
        }

        int size()
        {
            return m_size;
        }

        int capacity()
        {
            return m_capacity;
        }

    private:

    };
}