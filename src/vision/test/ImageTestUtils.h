/*
 * Created By: reidoliveira
 * Created On: January 27, 2018
 * Description:
 */
#ifndef PROJECT_IMAGETESTUTILS_H
#define PROJECT_IMAGETESTUTILS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageTestUtils {
  public:
    static bool compareMat(cv::Mat& first, cv::Mat& second);
    static void compareImg(cv::Mat& expected, cv::Mat& actual);
};

#endif // PROJECT_IMAGETESTUTILS_H
