此工程是为验证 android JNI 一些特性。或者进行一些较为独立、轻量的优化方案。



LibYuvTestActivity
该界面主要测试 libyuv 库，封装该库提供格式转换、裁剪、缩放、镜像、旋转等功能。
testMemoryLeak：测试频繁创建/销毁 libyuv 封装对象，是否存在内存泄露。
testSrcDataLenChanged：测试不同分辨率之间切换，比如分辨率从小到大、从大到小是否有问题。
testCropScale：测试 libyuv 封装对象的裁剪、缩放功能是否正常，主要看画面裁剪的是否居中，缩放比例是否正常。


包结构
Thread：测试线程相关功能





性能测试
1、字符串拼接
测试类：StringTestJni.java -> StringTestJni.cpp
测试结果：snprintf > string.append > stringstream