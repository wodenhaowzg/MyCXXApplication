//
// Created by ZaneWang on 2022/12/30.
//

#ifndef MYCXXAPPLICATION_JNIYUVDATATRANSFER_H
#define MYCXXAPPLICATION_JNIYUVDATATRANSFER_H

class YuvDataTransfer {

public:
    struct VideoDataScaleST {
        jfieldID formatFieldId;
        jfieldID srcDataArrayFieldId;
        jfieldID destDataArrayFieldId;
        jfieldID srcBufferFieldId;
        jfieldID cropBufferFieldId;
        jfieldID destBufferFieldId;
        jfieldID widthFieldId, heightFieldId;
        jfieldID cropXFieldId, cropYFieldId;
        jfieldID cropWidthFieldId, cropHeightFieldId;
        jfieldID scaleWidthFieldId, scaleHeightFieldId;
        jfieldID rotate;
        jfieldID mirrored;
    };

    YuvDataTransfer() {
    }

    ~YuvDataTransfer() {
    }

    VideoDataScaleST m_videoYuvDataST;
};

#endif //MYCXXAPPLICATION_JNIYUVDATATRANSFER_H
