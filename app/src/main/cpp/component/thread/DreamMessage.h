//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAMMESSAGE_H
#define MYCXXAPPLICATION_DREAMMESSAGE_H

#include "DreamLooper.h"

class DreamMessage : public std::enable_shared_from_this<DreamMessage>{

public:
    DreamMessage(uint32_t what = 0, DreamLooper::HandlerId target = 0);

    enum Type {
        kTypeInt32,
        kTypeInt64,
        kTypeSize,
        kTypeFloat,
        kTypeDouble,
        kTypePointer,
        kTypeString,
        kTypeObject,
        kTypeMessage,
        kTypeRect,
        kTypeBuffer,
    };

    void SetWhat(uint32_t what);

    void SetTarget(DreamLooper::HandlerId target);

    void SetInt32(const char *name, int32_t value);

    void SetPointer(const char *name, void *value);

    template<typename T>
    void SetObject(const char *name, const sp<T> &obj);

    DreamLooper::HandlerId GetHandlerId();

    uint32_t GetWhat();

    bool FindInt32(const char *name, int32_t *value) const;

    bool FindPointer(const char *name, void **value) const;

    void post(int64_t delayUs = 0);

private:
    struct Item {
        union {
            int32_t int32Value;
            int64_t int64Value;
            size_t sizeValue;
            float floatValue;
            double doubleValue;
            void *ptrValue;
        } u;
        const char *m_name;
        size_t m_name_length;
        Type m_type;

        void setName(const char *name, size_t len);
    };

    enum {
        kMaxNumItems = 64
    };

    /**
     * 消息类型
     */
    uint32_t m_what_;
    /**
     * 绑定的消息处理对象
     */
    DreamLooper::HandlerId m_target_handler_;
    Item mItems[kMaxNumItems];
    size_t mNumItems;

    Item *allocateItem(const char *name);

    void DreamMessage::freeItemValue(Item *item);

    const Item *findItem(const char *name, Type type) const;

    size_t findItemIndex(const char *name, size_t len) const;

    template<typename T>
    void setObjectInternal(const char *name, const sp<T> &obj, Type type);
};


#endif //MYCXXAPPLICATION_DREAMMESSAGE_H
