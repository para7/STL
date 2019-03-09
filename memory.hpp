#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace my
{
    template<class T>
    class shared_ptr
    {
    private:

        T* value;
        int* cnt;

    public:

        shared_ptr()
        {
            cout << "�f�t�H���g�R���X�g���N�^" << endl;

            value = nullptr;
            cnt = nullptr;
        }

        shared_ptr(T* _ptr)
        {
            cout << "�l����R���X�g���N�^" << endl;

            value = _ptr;
            cnt = new int(1);
        }

        shared_ptr(const shared_ptr &obj)
        {
            cout << "�R�s�[�R���X�g���N�^" << endl;

            if (value != nullptr)
            {
                ReleasePointer();
            }

            value = obj.value;
            cnt = obj.cnt;
            ++*cnt;
        }

        shared_ptr& operator= (const shared_ptr& obj)
        {
            cout << "���" << endl;
        }

        ~shared_ptr()
        {
            cout << "�f�X�g���N�^" << endl;

            ReleasePointer();
        }

        void Print()
        {
            if (value == nullptr)
            {
                cout << "���g�p�ł�" << endl;
                return;
            }

            cout << "value : " << *value << '\n';
            cout << "cnt : " << *cnt << "\n\n";
        }

    private:

        //�Q�Ɛ��ύX����Ƃ��ɌĂяo��
        void ChangeReference(const shared_ptr& obj)
        {
            if (value != nullptr)
            {
                ReleasePointer();
            }

            value = obj.value;
            cnt = obj.cnt;
            ++*cnt;
        }

        //�Q�Ƃ���������ɌĂяo��
        void ReleasePointer()
        {
            cout << "ReleasePointer" << endl;

            --*cnt;

            Print();

            if (*cnt == 0)
            {
                cout << "delete" << endl;
                delete value;
                delete cnt;
            }
        }
    };
}