//
// Created by vasan on 9/28/2019.
//
#ifndef VLIB_OBJECTPOOL_H
#define VLIB_OBJECTPOOL_H

#include <vector>
#include <stack>
#include <stdint.h>
#include <cstdlib>

using namespace std;

namespace VObjectPool {

    template <int SIZE>
    class ObjectPool {
    private:
        static const int MAX_OBJECTS  = SIZE;
        //static const int MAX_OBJECTS  = 5;

        using CollectionObjPool = vector<ObjectPool>;
        static CollectionObjPool vec_ObjPool;
        static stack<uint32_t> st_Free;
        uint32_t ui_val;

    public:
        //ObjectPool() = default;
        ObjectPool(uint32_t val) : ui_val(val){};

        void* operator new(size_t num_bytes) {
            void* objMemory = NULL;
            if (vec_ObjPool.capacity() < MAX_OBJECTS)
                vec_ObjPool.reserve(MAX_OBJECTS);

            if (num_bytes == sizeof(ObjectPool) &&
                vec_ObjPool.size() < vec_ObjPool.capacity()) {
                int index;
                if (st_Free.size()) {
                    index = st_Free.top();
                    st_Free.pop();
                }
                else {
                    vec_ObjPool.emplace_back(NULL);
                    index = vec_ObjPool.size() - 1;
                    //cout << "size is " << vec_ObjPool.size() << endl;
                    //for (int x = 0; x < vec_ObjPool.size(); ++x)
                    //    cout << "value in [" << x <<"] = " << vec_ObjPool[x].ui_val << endl;
                }

                objMemory = vec_ObjPool.data() + index;
            }
            else {
                objMemory = malloc(num_bytes);
            }
            return objMemory;
        }
        void operator delete(void* mem) {
            const intptr_t index = ((intptr_t)static_cast<ObjectPool*>(mem) - (intptr_t)vec_ObjPool.data() ) / ((intptr_t)sizeof(ObjectPool));
            if (index >= 0 && index < static_cast<intptr_t >(vec_ObjPool.size())) {
                st_Free.push(static_cast<uint32_t >(index));
            }
            else {
                free(mem);
            }
        }
        int get() {
            return ui_val;
        };
    };

    template<int SIZE>
    vector<ObjectPool<SIZE>> ObjectPool<SIZE>::vec_ObjPool;

    template<int SIZE>
    stack<uint32_t> ObjectPool<SIZE>::st_Free;

}
#endif //VLIB_OBJECTPOOL_H
