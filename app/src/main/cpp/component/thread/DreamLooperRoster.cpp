//
// Created by ZaneWang on 2023/6/12.
//

#include "DreamLooperRoster.h"

DreamLooperRoster::DreamLooperRoster()
        : m_next_handler_id_(1) {
}

DreamLooper::HandlerId DreamLooperRoster::registerHandler(const sp<DreamLooper> &looper, const sp<DreamHandler> &handler) {
    auto_lock autoLock(m_lock_);
    auto p_dream_handler = handler.get();
    if (p_dream_handler == nullptr) {
        return -1;
    }

    if (p_dream_handler->GetId() != 0) {
        return -2;
    }
    DreamHandlerInfo handler_info;
    handler_info.wp_looper = looper;
    handler_info.wp_handler = handler;
    DreamLooper::HandlerId handlerID = m_next_handler_id_++;
    p_dream_handler->SetId(handlerID);
    m_handler_map_.insert(std::make_pair(handlerID, handler_info));
    LOGI("Succeed in adding a handler. id: %d", handlerID);
    return 0;
}

void DreamLooperRoster::unregisterHandler(DreamLooper::HandlerId handlerID) {

}

void DreamLooperRoster::unregisterStaleHandlers() {

}

int DreamLooperRoster::postMessage(const sp<DreamMessage> &msg, int64_t delayUs) {
    DreamMessage *p_message = msg.get();
    if (p_message == nullptr) {
        return -1;
    }
    DreamLooper::HandlerId handler_id = p_message->GetHandlerId();
    if (handler_id == 0) {
        return -2;
    }
    sp<DreamLooper> sp_looper = findLooper(handler_id);
    if (sp_looper == nullptr || sp_looper.get()) {
        return -ENOENT;
    }
    DreamLooper *p_looper = sp_looper.get();
    if (p_looper == nullptr) {
        return -ENOENT;
    }
    p_looper->PostEvent(msg);
    return 0;
}

sp<DreamLooper> DreamLooperRoster::findLooper(DreamLooper::HandlerId handlerID) {
    auto_lock autoLock(m_lock_);
    auto iterator = m_handler_map_.find(handlerID);
    if (iterator == m_handler_map_.end()) {
        return nullptr;
    }
    sp<DreamLooper> looper = iterator->second.wp_looper.lock();
    if (looper == nullptr) {
        m_handler_map_.erase(iterator);
        return nullptr;
    }
    return looper;
}

void DreamLooperRoster::deliverMessage(const sp<DreamMessage> &message) {
    sp<DreamHandler> handler;
    {
        auto_lock autoLock(m_lock_);
        auto iterator = m_handler_map_.find(message->GetHandlerId());
        if (iterator == m_handler_map_.end()) {
            return;
        }
        const DreamHandlerInfo &info = iterator->second;
        handler = info.wp_handler.lock();
        if (handler == nullptr) {
            LOGI("failed to deliver message. Target handler %d registered, but object gone.", message->GetHandlerId());
            m_handler_map_.erase(iterator);
            return;
        }
    }
    handler->OnMessageReceived(message);
}
