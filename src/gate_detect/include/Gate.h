//
// Created by da-cam on 20/02/18.
//

#ifndef PROJECT_GATE_H
#define PROJECT_GATE_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ros/ros.h>

class Gate {
    cv::Mat detected_edges, dst;
    int lowVertThresh, lowHorThresh, cannyLow, cannyHigh, poleMax;
    float fiveMetreWidthofPole;
    std::vector<int> vertLines, horLines;
    std::vector<std::vector<float> > vertPoles,horPoles;
    std::vector<float> poleVector;

public:
    Gate();

    /*
     * Function to be called on cv::Mat to find vertical poles and horizontal poles
     *
     * mat : cv::Mat potentially containing a gate
     *
     */

    std::vector<float> initialize(const cv::Mat matin);

    /*
     * Function to check if Gate object has been initialized
     */

    bool checkMat();

    void vertLineCheck();

    void horLineCheck();

private:

    double vectorAngle(cv::Vec4i vector);

    /*
     * Function to filter through vector of cv::Vector4i objects and filter out the horizontal lines
     *
     * allLines : Vector of cv::Vector4i objects in which the Vector4i represents a lines such that [xo , yo , xf, yf]
     *
     * xo = x coordinate of start of line
     *
     * yo = y coordinate of start of line
     *
     * xf = end coordinate of end of line
     *
     * yf = end coordinate of end of line
     *
     */

    std::vector<int> filterHorLines(std::vector<cv::Vec4i> allLines);

    /*
     * Function to filter through vector of cv::Vector4i objects and filter out the Vertical lines
     *
     * allLines : Vector of cv::Vector4i objects in which the Vector4i represents a lines such that [xo , yo , xf, yf]
     *
     * xo = x coordinate of start of line
     *
     * yo = y coordinate of start of line
     *
     * xf = end coordinate of end of line
     *
     * yf = end coordinate of end of line
     *
     */

    std::vector<int> filterVertLines(std::vector<cv::Vec4i> allLines);

    /*
    * Function to filter through set of horizontal lines to determine which lines constitute a pole
    *
    * int poleMax : maximum distance between two horizontal lines that function will call a pole
    *
    */

    std::vector<std::vector<float> > findHorPoles(std::vector<int> horLines);

    /*
     * Function to filter through set of vertical lines to determine which lines constitute a pole
     *
     * int poleMax : maximum distance between two vertical lines that function will call a pole
     *
     */

    std::vector<std::vector<float> > findVertPoles(std::vector<int> vertLines);


    /*
     * Function to filter through set of vertical and horizontal poles to determine which poles constitute a gate
     *
     * int poleMax : maximum distance between two vertical lines that function will call a pole
     *
     */
    std::vector<float> gateVector(std::vector<std::vector<float> > vertPoles, std::vector<std::vector<float> > horPoles);


};

#endif //PROJECT_GATE_H
