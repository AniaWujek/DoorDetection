/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef CVINRANGE_HPP_
#define CVINRANGE_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace CvInRange {

/*!
 * \class CvInRange
 * \brief CvInRange processor class.
 *
 *
 */
class CvInRange: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	CvInRange(const std::string & name = "CvInRange");

	/*!
	 * Destructor
	 */
	virtual ~CvInRange();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<cv::Mat, Base::DataStreamBuffer::Newest,Base::Synchronization::Mutex> in_img;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers

	// Properties
	Base::Property<int> prop_H_min;
	Base::Property<int> prop_H_max;
	Base::Property<int> prop_S_min;
	Base::Property<int> prop_S_max;
	Base::Property<int> prop_V_min;
	Base::Property<int> prop_V_max;


	// Handlers
	void OnNewImage();

};

} //: namespace CvInRange
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("CvInRange", Processors::CvInRange::CvInRange)

#endif /* CVINRANGE_HPP_ */
