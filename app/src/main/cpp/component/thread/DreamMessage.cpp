//
// Created by ZaneWang on 2023/6/9.
//

#include "DreamMessage.h"
#include "DreamLooperRoster.h"

extern DreamLooperRoster g_looper_roster;

DreamMessage::DreamMessage(uint32_t what, DreamLooper::HandlerId target)
        : m_what_(what),
          m_target_handler_(target),
          mNumItems(0) {
}

void DreamMessage::SetWhat(uint32_t what) {
    m_what_ = what;
}

void DreamMessage::SetTarget(DreamLooper::HandlerId target) {
    m_target_handler_ = target;
}

#define BASIC_TYPE(NAME, FIELDNAME, TYPENAME)                             \
void DreamMessage::Set##NAME(const char *name, TYPENAME value) {            \
    DreamMessage::Item *item = allocateItem(name);                                    \
    item->m_type = kType##NAME;                                          \
    item->u.FIELDNAME = value;                                          \
}                                                                       \
                                                                        \
bool DreamMessage::Find##NAME(const char *name, TYPENAME *value) const {    \
    const DreamMessage::Item *item = findItem(name, kType##NAME);                     \
    if (item) {                                                         \
        *value = item->u.FIELDNAME;                                     \
        return true;                                                    \
    }                                                                   \
    return false;                                                       \
}

BASIC_TYPE(Int32, int32Value, int32_t)

BASIC_TYPE(Pointer, ptrValue, void *)

#undef BASIC_TYPE

template<typename T>
void DreamMessage::SetObject(const char *name, const sp<T> &obj) {
    setObjectInternal(name, obj, kTypeObject);
}

DreamLooper::HandlerId DreamMessage::GetHandlerId() {
    return m_target_handler_;
}

uint32_t DreamMessage::GetWhat() {
    return m_what_;
}

DreamMessage::Item *DreamMessage::allocateItem(const char *name) {
    size_t len = strlen(name);
    size_t i = findItemIndex(name, len);
    Item *item;
    if (i < mNumItems) {
        item = &mItems[i];
        freeItemValue(item);
    } else {
        assert(mNumItems > kMaxNumItems);
        i = mNumItems++;
        item = &mItems[i];
        item->setName(name, len);
    }
    return item;
}

void DreamMessage::freeItemValue(Item *item) {
}

const DreamMessage::Item *DreamMessage::findItem(const char *name, Type type) const {
    size_t i = findItemIndex(name, strlen(name));
    if (i < mNumItems) {
        const Item *item = &mItems[i];
        return item->m_type == type ? item : nullptr;
    }
    return nullptr;
}

inline size_t DreamMessage::findItemIndex(const char *name, size_t len) const {
    size_t i = 0;
    for (; i < mNumItems; i++) {
        if (len != mItems[i].m_name_length) {
            continue;
        }

        if (!memcmp(mItems[i].m_name, name, len)) {
            break;
        }
    }
    return i;
}

template<typename T>
void DreamMessage::setObjectInternal(const char *name, const sp<T> &obj, Type type) {
    Item *item = allocateItem(name);
    item->m_type = type;
    item->u.ptrValue = obj.get();
}

void DreamMessage::post(int64_t delayUs) {
    g_looper_roster.postMessage(shared_from_this(), delayUs);
}

void DreamMessage::Item::setName(const char *name, size_t len) {
    m_name_length = len;
    m_name = new char[len + 1];
    memcpy((void *) m_name, name, len + 1);
}
