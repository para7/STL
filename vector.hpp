#pragma once
#include <algorithm>
namespace my
{
    template<class T>
    class vector
    {
    private:

        T* m_data;

        int32_t m_size;//実際に使っているサイズ

        int32_t m_capacity;//確保したメモリサイズ
        //配列サイズの変更にはコストが大きくかかるため余裕を持って確保する

    public:

        vector() : m_data(nullptr)
            , m_size(0)
            , m_capacity(0) {};

        vector(int32_t n) : m_data(nullptr)
            , m_size(0)
            , m_capacity(0)
        {
            resize(n);
        }

        ~vector()
        {
            delete[] m_data;//deleteに[]をつけないと確か配列として開放されなくてメモリリークする
        }

        T& operator[] (int32_t n) { return m_data[n]; }

        T& at(int32_t n)
        {
            if (n < m_size)
            {
                throw std::out_of_range();
            }

            return m_data[n];
        }

        void reserve(const int32_t _capacity)
        {
            //既に確保されている領域の方が大きい場合
            if (_capacity < m_capacity)
            {
                return;
            }

            //新しい領域を確保
            T* newdata = (T*)malloc(sizeof(T) * _capacity);

            const int32_t nextsize = std::min(m_capacity, _capacity);

            //データを新領域にコピー
            for (size_t i = 0; i < m_size; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //空のデータで埋める
            //for (int32_t i = m_size; i < _capacity; ++i)
            //{
            //    newdata[i] = T();
            //}

            if (m_capacity > 0)
            {
                //今まで使っていた領域を開放
                ReleaseMemory();

                free(m_data);
            }

            //配列を差し替え
            m_data = newdata;

            //キャパシティを更新
            m_capacity = _capacity;

            //配列サイズを修正
            //m_size = capacity;
        }

        void resize(const int32_t _size)
        {
            if (_size < 0)
            {
                return;
            }

            //新しい領域を確保
            T* newdata = (T*)malloc(sizeof(T) * _size);

            const int32_t nextsize = std::min(m_capacity, _size);

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
                ReleaseMemory();

                free(m_data);
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

        int32_t size()
        {
            return m_size;
        }

        int32_t capacity()
        {
            return m_capacity;
        }

    private:

        void ReleaseMemory()
        {
            if (0 > m_size)
            {
                return;
            }

            for (int32_t i = 0; i < m_size; ++i)
            {
                m_data[i].~T();
            }
        }
    };
}