#pragma once
#include <algorithm>
namespace my
{
    template<class T>
    class vector
    {
    private:

        T* m_data;

        int m_size;//���ۂɎg���Ă���T�C�Y

        int m_capacity;//�m�ۂ����������T�C�Y
        //�z��T�C�Y�̕ύX�ɂ̓R�X�g���傫�������邽�ߗ]�T�������Ċm�ۂ���

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
            delete[] m_data;//delete��[]�����Ȃ��Ɗm���z��Ƃ��ĊJ������Ȃ��ă��������[�N����
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
            //���Ɋm�ۂ���Ă���̈�̕����傫���ꍇ
            if (_capacity < m_capacity)
            {
                return;
            }

            //�V�����̈���m��
            auto newdata = new T[_capacity];

            const int nextsize = std::min(m_capacity, _capacity);

            //�f�[�^��V�̈�ɃR�s�[
            for (size_t i = 0; i < m_size; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //��̃f�[�^�Ŗ��߂�
            //for (int i = m_size; i < _capacity; ++i)
            //{
            //    newdata[i] = T();
            //}

            if (m_capacity > 0)
            {
                //���܂Ŏg���Ă����̈���J��
                delete[] m_data;
            }

            //�z��������ւ�
            m_data = newdata;

            //�L���p�V�e�B���X�V
            m_capacity = _capacity;

            //�z��T�C�Y���C��
            //m_size = capacity;
        }

        void resize(int _size)
        {
            if (_size < 0)
            {
                return;
            }

            //�V�����̈���m��
            auto newdata = new T[_size];

            const int nextsize = std::min(m_capacity, _size);

            //�f�[�^��V�̈�ɃR�s�[
            for (size_t i = 0; i < nextsize; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //��̃f�[�^�Ŗ��߂�
            for (size_t i = nextsize; i < _size; ++i)
            {
                newdata[i] = T();
            }

            if (m_capacity > 0)
            {
                //���܂Ŏg���Ă����̈���J��
                delete[] m_data;
            }

            //�z��������ւ�
            m_data = newdata;

            //�L���p�V�e�B���X�V
            m_capacity = _size;

            //�z��T�C�Y���C��
            m_size = _size;
        }

        void push_back(const T& value)
        {
            //�̈悪����Ȃ���
            if (m_capacity < m_size + 1)
            {
                reserve(m_size * 2 + 1);
            }

            m_data[m_size] = move(value);
            m_size++;
        }

        void push_back(T&& value)
        {
            //�̈悪����Ȃ���
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