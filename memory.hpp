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
            cout << "デフォルトコンストラクタ" << endl;

            value = nullptr;
            cnt = nullptr;
        }

        shared_ptr(T* _ptr)
        {
            cout << "値ありコンストラクタ" << endl;

            value = _ptr;
            cnt = new int(1);
        }

        shared_ptr(const shared_ptr &obj)
        {
            cout << "コピーコンストラクタ" << endl;

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
            cout << "代入" << endl;
        }

        ~shared_ptr()
        {
            cout << "デストラクタ" << endl;

            ReleasePointer();
        }

        void Print()
        {
            if (value == nullptr)
            {
                cout << "未使用です" << endl;
                return;
            }

            cout << "value : " << *value << '\n';
            cout << "cnt : " << *cnt << "\n\n";
        }

    private:

        //参照先を変更するときに呼び出す
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

        //参照を手放す時に呼び出す
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