/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>

#include "FindManyChessboards.hpp"
#include "Common/Logger.hpp"

#include "Types/Drawable.hpp"
#include "Types/DrawableContainer.hpp"

#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

namespace Processors {
namespace FindManyChessboards {

FindManyChessboards::FindManyChessboards(const std::string & name) :
		Base::Component(name),
		colors_count("colors_count", 1)  {

}

FindManyChessboards::~FindManyChessboards() {
}

void FindManyChessboards::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	for(int i = 0; i < colors_count; ++i) {
        char id = '0' + i;
        out_img.push_back(new Base::DataStreamOut<cv::Mat>);
        registerStream(std::string("out_img")+id, out_img[i]);
	}
	registerStream("out_img", out_img[0]);
	// Register handlers
	registerHandler("onNewImage", boost::bind(&FindManyChessboards::onNewImage, this));
	addDependency("onNewImage", &in_img);

}

bool FindManyChessboards::onInit() {

	return true;
}

bool FindManyChessboards::onFinish() {
	return true;
}

bool FindManyChessboards::onStop() {
	return true;
}

bool FindManyChessboards::onStart() {
	return true;
}

void FindManyChessboards::onNewImage() {
    cv::Mat img = in_img.read().clone();
    for(int i = 0; i < colors_count; ++i){
        out_img[i]->write(img.clone());
    }
}



} //: namespace FindManyChessboards
} //: namespace Processors
