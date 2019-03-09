#pragma once
#include <algorithm>
namespace my
{
    template<class T>
    class vector
    {
    private:

        T* m_data;

        int32_t m_size;//���ۂɎg���Ă���T�C�Y

        int32_t m_capacity;//�m�ۂ����������T�C�Y
        //�z��T�C�Y�̕ύX�ɂ̓R�X�g���傫�������邽�ߗ]�T�������Ċm�ۂ���

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
            ReleaseMemory();//delete��[]�����Ȃ��Ɗm���z��Ƃ��ĊJ������Ȃ��ă��������[�N����
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
            std::cout << "reserve:" << _capacity << std::endl;

            //���Ɋm�ۂ���Ă���̈�̕����傫���ꍇ
            if (_capacity < m_capacity)
            {
                return;
            }

            //�V�����̈���m��
            T* newdata = (T*)malloc(sizeof(T) * _capacity);

            const int32_t nextsize = std::min(m_capacity, _capacity);

            //�f�[�^��V�̈�ɃR�s�[
            for (size_t i = 0; i < m_size; ++i)
            {
                newdata[i] = std::move(m_data[i]);
            }

            //��̃f�[�^�Ŗ��߂�
            //for (int32_t i = m_size; i < _capacity; ++i)
            //{
            //    newdata[i] = T();
            //}

            ReleaseMemory();

            //�z��������ւ�
            m_data = newdata;

            //�L���p�V�e�B���X�V
            m_capacity = _capacity;

            //�z��T�C�Y���C��
            //m_size = capacity;
        }

        void resize(const int32_t _size)
        {
            std::cout << "resize:" << _size  << std::endl;

            if (_size < 0)
            {
                return;
            }

            //�V�����̈���m��
            T* newdata = (T*)malloc(sizeof(T) * _size);

            const int32_t nextsize = std::min(m_capacity, _size);

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

            ReleaseMemory();

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
            if (m_capacity <= 0)
            {
                return;
            }

            if (0 > m_size)
            {
                return;
            }

            for (int32_t i = 0; i < m_size; ++i)
            {
                m_data[i].~T();
            }

            free(m_data);

            m_data = nullptr;
        }
    };
}