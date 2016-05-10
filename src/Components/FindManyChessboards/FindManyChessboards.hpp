/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef FindManyChessboards_HPP_
#define FindManyChessboards_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace Processors {
namespace FindManyChessboards {

/*!
 * \class FindManyChessboards
 * \brief FindManyChessboards processor class.
 *
 *
 */
class FindManyChessboards: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	FindManyChessboards(const std::string & name = "FindManyChessboards");

	/*!
	 * Destructor
	 */
	virtual ~FindManyChessboards();

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
	Base::DataStreamIn<cv::Mat, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_img;

	// Output data streams
	std::vector<Base::DataStreamOut<cv::Mat> *> out_img;

	// Handlers

	// Properties
	Base::Property<int> colors_count;


	// Handlers
	void onNewImage();

};

} //: namespace FindManyChessboards
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("FindManyChessboards", Processors::FindManyChessboards::FindManyChessboards)

#endif /* FindManyChessboards_HPP_ */
