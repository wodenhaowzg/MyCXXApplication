//
// Created by ZaneWang on 2023/6/12.
//

#include <vector>
#include "dream_looper_roster.h"
#include "dream_handler.h"

DreamLooperRoster::DreamLooperRoster()
        : m_next_handler_id_(1) {
}

DreamLooper::HandlerId DreamLooperRoster::RegisterHandler(const sp<DreamLooper> &looper, const sp<DreamHandler> &handler) {
    AutoLock autoLock(m_lock_);
    DreamHandler *p_dream_handler = handler.get();
    if (p_dream_handler == nullptr) {
        LOGE("Failed to register handler, the DreamHandler is empty!");
        return -1;
    }

    if (p_dream_handler->GetId() != 0) {
        LOGE("Failed to register handler, the DreamHandler ID is empty!");
        return -2;
    }
    DreamHandlerInfo handler_info;
    handler_info.wp_looper = looper;
    handler_info.wp_handler = handler;
    DreamLooper::HandlerId handlerID = m_next_handler_id_++;
    p_dream_handler->SetId(handlerID);
    m_handler_map_.insert(std::make_pair(handlerID, handler_info));
    LOGI("Succeed in adding a handler. id: %d, size: %d", handlerID, m_handler_map_.size());
    return 0;
}

void DreamLooperRoster::UnregisterHandler(DreamLooper::HandlerId handlerId) {
    AutoLock autoLock(m_lock_);
    auto handler_info = m_handler_map_.find(handlerId);
    if (handler_info == m_handler_map_.end()) {
        return;
    }
    DreamHandler *p_dream_handler = handler_info->second.wp_handler.lock().get();
    if (p_dream_handler != nullptr) { // 这一步没想到，参考源码的，但是～如果不设置为0有什么风险？
        p_dream_handler->SetId(0);
    }
    m_handler_map_.erase(handler_info);
    LOGI("Succeed in removing a handler. id: %d, size: %d", handlerId, m_handler_map_.size());
}

void DreamLooperRoster::UnregisterHandlers() {
    AutoLock autoLock(m_lock_);
    std::vector<sp<DreamLooper> > activeLoopers;
    for (const auto &item: m_handler_map_) {
        auto handler_info = item.second;
        DreamLooper* looper = handler_info.wp_looper.lock().get();
        if (looper == nullptr) {
            m_handler_map_.erase(item);
        } else {
            activeLoopers.push_back(looper);
        }
    }

    for (auto it = m_handler_map_.begin(); it != m_handler_map_.end();) {
        const auto& item = *it;
        auto handler_info = item.second;
        DreamLooper* looper = handler_info.wp_looper.lock().get();
        if (looper == nullptr) {
            it = m_handler_map_.erase(it);
        } else {
            ++it;
        }
    }
}

int DreamLooperRoster::PostMessage(const sp<DreamMessage> &msg, int64_t delayUs) {
    DreamMessage *p_message = msg.get();
    if (p_message == nullptr) {
        return -1;
    }
    DreamLooper::HandlerId handler_id = p_message->GetHandlerId();
    if (handler_id == 0) {
        return -2;
    }
    sp<DreamLooper> sp_looper = FindLooper(handler_id);
    if (sp_looper == nullptr) {
        return -ENOENT;
    }
    DreamLooper *p_looper = sp_looper.get();
    if (p_looper == nullptr) {
        return -ENOENT;
    }
    p_looper->PostEvent(msg);
    LOGI("Succeed in PostMessage message. what: %d", msg->GetWhat());
    return 0;
}

sp<DreamLooper> DreamLooperRoster::FindLooper(DreamLooper::HandlerId handlerID) {
    AutoLock autoLock(m_lock_);
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

void DreamLooperRoster::DeliverMessage(const sp<DreamMessage> &message) {
    sp<DreamHandler> handler;
    {
        AutoLock autoLock(m_lock_);
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
