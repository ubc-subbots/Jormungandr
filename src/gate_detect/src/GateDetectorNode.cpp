/*
 * Created By: Cameron Newton
 * Created On: February 27th, 2018
 * Set up environment for GateDetectorNode
 */

#include "GateDetectorNode.h"

GateDetectorNode::GateDetectorNode(int argc, char** argv) {
    ros::NodeHandle nh;
    ros::NodeHandle nh_;
    image_transport::ImageTransport it(nh);

    dynamic_reconfigure::Server<gate_detect::gatedetectConfig> server;
    dynamic_reconfigure::Server<gate_detect::gatedetectConfig>::CallbackType f;

    subscribeTopic = "/vision/output";
    publishTopic   = "/gate_detect/output";

    int cannyLow, houghLinesThreshold, houghLinesMinLength, poleMax,
    lowVertThresh, lowHorThresh, houghLinesMaxLineGap;
    double interpolationConstant1, interpolationConstant2;

    nh.getParam("/gate_detect_node/width", width_);
    nh.getParam("/gate_detect_node/height", height_);
    nh.getParam("/gate_detect_node/cannyLow", cannyLow);
    nh.getParam("/gate_detect_node/houghLinesThreshold", houghLinesThreshold);
    nh.getParam("/gate_detect_node/houghLinesMinLength", houghLinesMinLength);
    nh.getParam("/gate_detect_node/houghLinesMaxLineGap", houghLinesMaxLineGap);
    nh.getParam("/gate_detect_node/poleMax", poleMax);
    nh.getParam("/gate_detect_node/lowVertThresh", lowVertThresh);
    nh.getParam("/gate_detect_node/lowVertThresh", lowHorThresh);
    nh.getParam("/gate_detect_node/interpolationConstant1",
                interpolationConstant1);
    nh.getParam("/gate_detect_node/interpolationConstant2",
                interpolationConstant2);

    gateDetector_ = GateDetector(cannyLow,
                                 houghLinesThreshold,
                                 houghLinesMinLength,
                                 houghLinesMaxLineGap,
                                 poleMax,
                                 interpolationConstant1,
                                 interpolationConstant2,
                                 lowVertThresh,
                                 lowHorThresh);

    subscriber_ = it.subscribe(
    subscribeTopic, 2, &GateDetectorNode::subscriberCallBack, this);

    f = boost::bind(&GateDetectorNode::reconfigCallBack, this, _1, _2);
    server.setCallback(f);

    publisher1_ = nh_.advertise<gate_detect::GateDetectMsg>(publishTopic, 10);
    publisher2_ = it.advertise("gate_image_output", 100);

    ros::spin();
}

void GateDetectorNode::subscriberCallBack(
const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;

    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat image = (cv_ptr->image);

    lineImg = cv::Mat(image,
                      cv::Rect((image.cols / 2) - (width_ / 2),
                               (image.rows / 2) - (height_ / 2),
                               width_,
                               height_));

    GateCoordinates gateCoordinates = gateDetector_.initialize(lineImg);

    publishGateDetectMsg(gateCoordinates);

    // Uncomment if you want to view gate seen by node
    // publishGateImage(gateCoordinates);
}

void GateDetectorNode::publishGateDetectMsg(GateCoordinates gateCoordinates) {
    gate_detect::GateDetectMsg msg;

    if (gateCoordinates.detectedLeftPole == 0.0) {
        msg.detectedLeftPole = 0;
        msg.angleLeftPole    = 0;
        msg.distanceLeftPole = 0;
    } else {
        msg.detectedLeftPole = 1;
        msg.angleLeftPole    = gateCoordinates.angleLeftPole;
        msg.distanceLeftPole = gateCoordinates.distanceLeftPole;
    }
    if (gateCoordinates.angleRightPole == 0.0) {
        msg.detectedRightPole = 0;
        msg.angleRightPole    = 0;
        msg.distanceRightPole = 0;

    } else {
        msg.detectedRightPole = 1;
        msg.angleRightPole    = gateCoordinates.angleRightPole;
        msg.distanceRightPole = gateCoordinates.distanceRightPole;
    }
    if (gateCoordinates.detectedTopPole == 0.0) {
        msg.detectedTopPole = 0;
        msg.angleTopPole    = 0;
        msg.distanceTopPole = 0;

    } else {
        msg.detectedTopPole = 1;
        msg.angleTopPole    = gateCoordinates.angleTopPole;
        msg.distanceTopPole = gateCoordinates.distanceTopPole;
    }

    publisher1_.publish(msg);
}

void GateDetectorNode::publishGateImage(GateCoordinates gateCoordinates) {
    cv::Mat colourMat;

    cv::cvtColor(lineImg, colourMat, CV_GRAY2BGR);

    // colourMat = TestUtils::drawGate(colourMat, gateCoordinates);

    cv_bridge::CvImage out_msg;
    out_msg.header =
    std_msgs::Header(); // Same timestamp and tf frame as input image
    out_msg.encoding = sensor_msgs::image_encodings::BGR8; // Or whatever
    out_msg.image    = colourMat;                          // Your cv::Mat

    publisher2_.publish(out_msg.toImageMsg());
}

void GateDetectorNode::reconfigCallBack(
const gate_detect::gatedetectConfig& config, uint32_t level) {
    ROS_INFO("Reconfigure Request: %i %i %i %i %i",
             config.cannyLow,
             config.houghLinesThreshold,
             config.houghLinesMinLength,
             config.houghLinesMaxLineGap,
             config.poleMax);

    gateDetector_.setParams(config.cannyLow,
                            config.houghLinesThreshold,
                            config.houghLinesMinLength,
                            config.houghLinesMaxLineGap,
                            config.poleMax,
                            config.interpolationConstant1,
                            config.interpolationConstant2,
                            config.lowVertThresh,
                            config.lowHorThresh);
}