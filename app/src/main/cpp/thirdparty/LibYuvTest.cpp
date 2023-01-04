#include <android/log.h>
#include "LibYuvTest.h"
//
// Created by ZaneWang on 2023/1/1.
//

const int PIXEL_FORMAT_I420 = 1;
const int PIXEL_FORMAT_ABGR = 2;

extern "C" JNIEXPORT jlong JNICALL Java_com_example_mycxxapplication_libyuv_LibYuvTest_nativeInitialize(JNIEnv *env, jobject thiz) {
    auto *p_myLibYuv = new MyLibYuv();
    jclass jniPixelFormatBeanClass = env->FindClass("com/example/mycxxapplication/libyuv/JNIPixelFormatBean");
    if (jniPixelFormatBeanClass == nullptr) {
        return 0;
    }

    jclass jniPixelOptionBeanClass = env->FindClass("com/example/mycxxapplication/libyuv/JNIPixelOptionBean");
    if (jniPixelOptionBeanClass == nullptr) {
        return 0;
    }
    p_myLibYuv->m_jniPixelFormatST.srcPixelFormatFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mSrcPixelFormat", "I");
    p_myLibYuv->m_jniPixelFormatST.destPixelFormatFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mDestPixelFormat", "I");
    p_myLibYuv->m_jniPixelFormatST.srcPixelByteArrayFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mSrcPixelByteArray", "[B");
    p_myLibYuv->m_jniPixelFormatST.destPixelByteArrayFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mDestPixelByteArray", "[B");
    p_myLibYuv->m_jniPixelFormatST.widthFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mWidth", "I");
    p_myLibYuv->m_jniPixelFormatST.heightFieldId = env->GetFieldID(jniPixelFormatBeanClass, "mHeight", "I");
    p_myLibYuv->m_jniOptionFormatST.cropXFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mCropX", "I");
    p_myLibYuv->m_jniOptionFormatST.cropYFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mCropY", "I");
    p_myLibYuv->m_jniOptionFormatST.cropWidthFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mCropWidth", "I");
    p_myLibYuv->m_jniOptionFormatST.cropHeightFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mCropHeight", "I");
    p_myLibYuv->m_jniOptionFormatST.scaleWidthFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mScaleWidth", "I");
    p_myLibYuv->m_jniOptionFormatST.scaleHeightFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mScaleHeight", "I");
    p_myLibYuv->m_jniOptionFormatST.rotateFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mRotate", "I");
    p_myLibYuv->m_jniOptionFormatST.isMirrorFieldId = env->GetFieldID(jniPixelOptionBeanClass, "mIsMirrored", "Z");
    return (jlong) p_myLibYuv;
}

extern "C" JNIEXPORT jlong JNICALL Java_com_example_mycxxapplication_libyuv_LibYuvTest_nativeUnInitialize(JNIEnv *env, jobject thiz, jlong pointer) {
    if (pointer == 0) {
        return 0;
    }
    auto *p_myLibYuv = (MyLibYuv *) pointer;
    if (p_myLibYuv != nullptr) {
        delete p_myLibYuv;
        p_myLibYuv = nullptr;
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_example_mycxxapplication_libyuv_LibYuvTest_nativeTransferToABGR(JNIEnv *env, jobject thiz, jlong pointer, jobject jniPixelFormatBeanObj, jobject jniPixelOptionBeanObj) {
    if (pointer == 0 || jniPixelFormatBeanObj == nullptr) {
        return -1000;
    }
    int ret = 0;
    auto *p_MyLibYuv = (MyLibYuv *) pointer;
    MyLibYuv::JNIPixelFormatST jniPixelFormatST = p_MyLibYuv->m_jniPixelFormatST;
    int srcPixelFormat = env->GetIntField(jniPixelFormatBeanObj, jniPixelFormatST.srcPixelFormatFieldId);
    int destPixelFormat = env->GetIntField(jniPixelFormatBeanObj, jniPixelFormatST.destPixelFormatFieldId);
    int width = env->GetIntField(jniPixelFormatBeanObj, jniPixelFormatST.widthFieldId);
    int height = env->GetIntField(jniPixelFormatBeanObj, jniPixelFormatST.heightFieldId);
    uint32 srcLibYuvFourcc = MyLibYuv::transformPixelFormatToLibYuvFormat(srcPixelFormat);
    uint32 destLibYuvFourcc = MyLibYuv::transformPixelFormatToLibYuvFormat(destPixelFormat);
    uint8 *p_srcByteArray;
    auto srcPixelByteArrayObj = (jbyteArray) env->GetObjectField(jniPixelFormatBeanObj, jniPixelFormatST.srcPixelByteArrayFieldId);
    if (srcPixelByteArrayObj != nullptr) {
        p_srcByteArray = (uint8 *) env->GetByteArrayElements(srcPixelByteArrayObj, nullptr);
    }
    uint8 *p_destByteArray;
    auto destPixelByteArrayObj = (jbyteArray) env->GetObjectField(jniPixelFormatBeanObj, jniPixelFormatST.destPixelByteArrayFieldId);
    if (destPixelByteArrayObj != nullptr) {
        p_destByteArray = (uint8 *) env->GetByteArrayElements(destPixelByteArrayObj, nullptr);
    }
    int cropX = 0;
    int cropY = 0;
    int cropWidth = 0;
    int cropHeight = 0;
    int scaleWidth = 0;
    int scaleHeight = 0;
    int rotate = 0;
    bool isMirror = false;
    if (jniPixelOptionBeanObj != nullptr) {
        MyLibYuv::JNIPixelFormatST jniOptionFormatST = p_MyLibYuv->m_jniOptionFormatST;
        cropX = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.cropXFieldId);
        cropY = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.cropYFieldId);
        cropWidth = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.cropWidthFieldId);
        cropHeight = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.cropHeightFieldId);
        scaleWidth = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.scaleWidthFieldId);
        scaleHeight = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.scaleHeightFieldId);
        rotate = env->GetIntField(jniPixelOptionBeanObj, jniOptionFormatST.rotateFieldId);
        isMirror = env->GetBooleanField(jniPixelOptionBeanObj, jniOptionFormatST.isMirrorFieldId);
    }
    libyuv::RotationMode libYuvRotate = MyLibYuv::transformPixelRotateToLibYuvRotate(rotate);
    // 如果没传递裁剪的宽和高，则代表不裁剪，将源宽高的值赋给 cropWidth 和 cropHeight
    if (cropWidth == 0 || cropHeight == 0) {
        cropWidth = width;
        cropHeight = height;
    }
    // 处理横竖屏切换
    int rotateCropWidth = cropWidth;
    int rotateCropHeight = cropHeight;
    int rotateScaleWidth = scaleWidth;
    int rotateScaleHeight = scaleHeight;
    if (rotate == 90 || rotate == 270) {
        rotateCropWidth = cropHeight;
        rotateCropHeight = cropWidth;
        rotateScaleWidth = scaleHeight;
        rotateScaleHeight = scaleWidth;
    }
    bool isNeedScaleMirror = false;
    bool isNeedTransformDestColorFormat = false;
    if ((scaleWidth != 0 && scaleHeight != 0) || isMirror) {
        isNeedScaleMirror = true;
    }

    if (destLibYuvFourcc != libyuv::FOURCC_I420) {
        isNeedTransformDestColorFormat = true;
    }
    int ySize = cropWidth * cropHeight;
    uint8 *dest_y = nullptr;
    uint8 *dest_u = nullptr;
    uint8 *dest_v = nullptr;
    // 源数组大小
    int srcByteArraySize = width * height * 3 / 2;
    if (!isNeedScaleMirror && !isNeedTransformDestColorFormat) {
        dest_y = p_destByteArray;
    } else {
        if (p_MyLibYuv->m_transformI420BufferLen < srcByteArraySize) {
            if (p_MyLibYuv->m_transformI420Buffer != nullptr) {
                free(p_MyLibYuv->m_transformI420Buffer);
            }
            p_MyLibYuv->m_transformI420Buffer = (uint8 *) malloc(srcByteArraySize);
            p_MyLibYuv->m_transformI420BufferLen = srcByteArraySize;
        }
        dest_y = p_MyLibYuv->m_transformI420Buffer;
    }
    dest_u = dest_y + ySize;
    dest_v = dest_u + ySize / 4;
    // 做格式转换、裁剪和旋转
    int transformResult = libyuv::ConvertToI420(p_srcByteArray, srcByteArraySize,
                                                dest_y, rotateCropWidth,
                                                dest_u, rotateCropWidth >> 1,
                                                dest_v, rotateCropWidth >> 1,
                                                cropX, cropY,
                                                width, height,
                                                cropWidth, cropHeight,
                                                libYuvRotate, srcLibYuvFourcc);
    // 做缩放和镜像
    if (isNeedScaleMirror && transformResult == 0) {
        if (rotateScaleWidth == 0 || rotateScaleHeight == 0) {
            rotateScaleWidth = rotateCropWidth;
            rotateScaleHeight = rotateCropHeight;
        }
        ySize = cropWidth * cropHeight;
        uint8 *src_y = p_MyLibYuv->m_transformI420Buffer;
        uint8 *src_u = src_y + ySize;
        uint8 *src_v = src_u + ySize / 4;
        ySize = rotateScaleWidth * rotateScaleHeight;
        if (isNeedTransformDestColorFormat) {
            int scaleI420BufferLen = ySize * 3 / 2;
            if (p_MyLibYuv->m_I420ScaleBufferLen < scaleI420BufferLen) {
                if (p_MyLibYuv->m_I420ScaleBuffer != nullptr) {
                    free(p_MyLibYuv->m_I420ScaleBuffer);
                }
                p_MyLibYuv->m_I420ScaleBuffer = (uint8 *) malloc(scaleI420BufferLen);
                p_MyLibYuv->m_I420ScaleBufferLen = scaleI420BufferLen;
            }
            dest_y = p_MyLibYuv->m_I420ScaleBuffer;
        } else {
            dest_y = p_destByteArray;
        }
        dest_u = dest_y + ySize;
        dest_v = dest_u + ySize / 4;
        int scaleMirrorResult = libyuv::I420Scale(src_y, rotateCropWidth,
                                                  src_u, rotateCropWidth >> 1,
                                                  src_v, rotateCropWidth >> 1,
                                                  isMirror ? -rotateCropWidth : rotateCropWidth, rotateCropHeight,
                                                  dest_y, rotateScaleWidth,
                                                  dest_u, rotateScaleWidth >> 1,
                                                  dest_v, rotateScaleWidth >> 1,
                                                  rotateScaleWidth, rotateScaleHeight,
                                                  libyuv::kFilterNone);
        ret = scaleMirrorResult;
    } else {
        ret = transformResult;
    }

    // 如果目标格式不是 I420，则再从 I420 转换到目标格式
    if (isNeedTransformDestColorFormat && ret == 0) {
        uint8 *src_y;
        int destWidth;
        int destHeight;
        if (isNeedScaleMirror) {
            src_y = p_MyLibYuv->m_I420ScaleBuffer;
            destWidth = rotateScaleWidth;
            destHeight = rotateScaleHeight;
        } else {
            src_y = p_MyLibYuv->m_transformI420Buffer;
            destWidth = rotateCropWidth;
            destHeight = rotateCropHeight;
        }
        ySize = destWidth * destHeight;
        uint8 *src_u = src_y + ySize;
        uint8 *src_v = src_u + ySize / 4;
        int destSampleStride = destWidth;
        if (destLibYuvFourcc == libyuv::FOURCC_RGBA || destLibYuvFourcc == libyuv::FOURCC_ABGR || destLibYuvFourcc == libyuv::FOURCC_ARGB) {
            destSampleStride = destWidth * 4;
        }
        ret = libyuv::ConvertFromI420(src_y, destWidth,
                                      src_u, destWidth >> 1,
                                      src_v, destWidth >> 1,
                                      p_destByteArray, destSampleStride,
                                      destWidth, destHeight,
                                      destLibYuvFourcc);
    }
    // 释放 byteArray 数组
    if (srcPixelByteArrayObj != nullptr && p_srcByteArray != nullptr) {
        env->ReleaseByteArrayElements(srcPixelByteArrayObj, (jbyte *) p_srcByteArray, JNI_ABORT);
    }

    if (destPixelByteArrayObj != nullptr && p_destByteArray != nullptr) {
        env->ReleaseByteArrayElements(destPixelByteArrayObj, (jbyte *) p_destByteArray, JNI_ABORT);
    }
    return ret;
}

uint32 MyLibYuv::transformPixelFormatToLibYuvFormat(int pixelFormat) {
    uint32 libYuvFourcc;
    switch (pixelFormat) {
        case PIXEL_FORMAT_I420:
            libYuvFourcc = libyuv::FOURCC_I420;
            break;
        case PIXEL_FORMAT_ABGR:
            libYuvFourcc = libyuv::FOURCC_ARGB;
            break;
        default:
            libYuvFourcc = 0;
    }
    return libYuvFourcc;
}

libyuv::RotationMode MyLibYuv::transformPixelRotateToLibYuvRotate(int rotate) {
    if (rotate == 90) {
        return libyuv::kRotate90;
    } else if (rotate == 180) {
        return libyuv::kRotate180;
    } else if (rotate == 270) {
        return libyuv::kRotate270;
    }
    return libyuv::kRotate0;
}