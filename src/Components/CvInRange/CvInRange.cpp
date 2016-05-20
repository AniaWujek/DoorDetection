/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "CvInRange.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace CvInRange {

CvInRange::CvInRange(const std::string & name) :
		Base::Component(name) ,
		prop_H_min("prop_H_min", 0, "range"),
		prop_H_max("prop_H_max", 255, "range"),
		prop_S_min("prop_S_min", 0, "range"),
		prop_S_max("prop_S_max", 255, "range"),
		prop_V_min("prop_V_min", 0, "range"),
		prop_V_max("prop_V_max", 255, "range") {

    prop_H_min.addConstraint("0");
	prop_H_min.addConstraint("255");
	prop_H_max.addConstraint("0");
	prop_H_max.addConstraint("255");
	prop_S_min.addConstraint("0");
	prop_S_min.addConstraint("255");
	prop_S_max.addConstraint("0");
	prop_S_max.addConstraint("255");
	prop_V_min.addConstraint("0");
	prop_V_min.addConstraint("255");
	prop_V_max.addConstraint("0");
	prop_V_max.addConstraint("255");

	registerProperty(prop_H_min);
	registerProperty(prop_H_max);
	registerProperty(prop_S_min);
	registerProperty(prop_S_max);
	registerProperty(prop_V_min);
	registerProperty(prop_V_max);

}

CvInRange::~CvInRange() {
}

void CvInRange::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	registerHandler("OnNewImage", boost::bind(&CvInRange::OnNewImage, this));
	addDependency("OnNewImage", &in_img);

}

bool CvInRange::onInit() {

	return true;
}

bool CvInRange::onFinish() {
	return true;
}

bool CvInRange::onStop() {
	return true;
}

bool CvInRange::onStart() {
	return true;
}

void CvInRange::OnNewImage() {

    cv::Mat in_image = (in_img.read()).clone();
    cv::Mat mask;
    cv::Mat hsv;
    cv::Mat out;
    cv::cvtColor(in_image, hsv, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(hsv, hsv, cv::Size(7,7), 2.0, 2.0);
    cv::inRange(hsv, cv::Scalar(prop_H_min, prop_S_min, prop_V_min), cv::Scalar(prop_H_max, prop_S_max, prop_V_max), mask);
    cv::bitwise_and(in_image, in_image, out, mask);
    out_img.write(out);
}



} //: namespace CvInRange
} //: namespace Processors
