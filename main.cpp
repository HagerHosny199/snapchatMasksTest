#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include "opencv2/imgproc/imgproc.hpp"

using namespace dlib;
using namespace std;
void noseMouthMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &img)
{
	int  x1, y1, x2, y2;
	cv::Mat  nose, dst, rNose, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 

	x1 = shapes.part(27)(0) - 90;
	x2 = shapes.part(54)(0) + 70;
	y1 = shapes.part(27)(1);
	y2 = shapes.part(54)(1) + 15;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	cout << "x1= " << x1 << " y1= " << y1 << endl << " x2= " << x2 << " y2=" << y2 << endl;
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
		//	cv::cvtColor(temp, temp, CV_BGR2BGRA);
		temp(rowRange, colRange).copyTo(nose);

		cv::resize(rgba[3], rNose, cv::Size(nose.cols, nose.rows));
		cv::resize(img, img, cv::Size(nose.cols, nose.rows));

		nose.copyTo(dst);
		for (int i = 1; i < nose.rows - 3; i++)
		{
			for (int j = 1; j < nose.cols - 3; j++)
			{
				//cout << rNose.ptr<int>(i, j)[0] << " ";

				if (rNose.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}

		}

		//now i will work on applying mask

		cout << "nose.rows =" << nose.rows << " nose.cols= " << nose.cols << " numb= " << nose.channels() << endl
			<< "rnose.rows=" << rNose.rows << " rnose.cols =" << rNose.cols << " numb= " << rNose.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
	else
		cout << "something went wrong" << endl;
}
void noseMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &img)
{
	int  x1, y1, x2, y2;
	cv::Mat  nose, dst, rNose, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 
	
	x1 = shapes.part(27)(0)-90;
	x2 = shapes.part(35)(0)+70;
	y1 = shapes.part(27)(1);
	y2 = shapes.part(35)(1)+15;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	cout << "x1= " << x1 << " y1= " << y1 << endl << " x2= " << x2 << " y2=" << y2 << endl;
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
		//	cv::cvtColor(temp, temp, CV_BGR2BGRA);
		temp(rowRange, colRange).copyTo(nose);

		cv::resize(rgba[3], rNose, cv::Size(nose.cols, nose.rows));
		cv::resize(img, img, cv::Size(nose.cols, nose.rows));

		nose.copyTo(dst);
		for (int i = 1; i < nose.rows - 3; i++)
		{
			for (int j = 1; j < nose.cols - 3; j++)
			{
				//cout << rNose.ptr<int>(i, j)[0] << " ";

				if (rNose.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}

		}

		//now i will work on applying mask

		cout << "nose.rows =" << nose.rows << " nose.cols= " << nose.cols << " numb= " << nose.channels() << endl
			<< "rnose.rows=" << rNose.rows << " rnose.cols =" << rNose.cols << " numb= " << rNose.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
	else
		cout << "something went wrong" << endl;
}
void earMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &img)
{
	int r, x1, y1, x2, y2;
	cv::Mat  head, dst, rEar, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 
	r = (shapes.part(0)(0) + shapes.part(16)(0)) / 2;
	x1 = shapes.part(0)(0) - 20;
	x2 = shapes.part(16)(0) + 25;
	y1 = shapes.part(0)(1) - 2 * r;
	y2 = shapes.part(0)(1) - 20;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	if (x2 > temp.rows)
		x2 = temp.rows - 1;
	if (y2 > temp.cols)
		y2 = temp.cols - 1;
	if (x1 < 0)
		x1 = 1;
	if (y1 < 0)
		y1 = 1;
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
		//	cv::cvtColor(temp, temp, CV_BGR2BGRA);
		temp(rowRange, colRange).copyTo(head);

		cv::resize(rgba[3], rEar, cv::Size(head.cols, head.rows));
		cv::resize(img, img, cv::Size(head.cols, head.rows));

		head.copyTo(dst);
		for (int i = 1; i < head.rows - 3; i++)
		{
			for (int j = 1; j < head.cols - 3; j++)
			{
				

				if (rEar.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}

		}

		//now i will work on applying mask

		cout << "head.rows =" << head.rows << " head.cols= " << head.cols << " numb= " << head.channels() << endl
			<< "ear.rows=" << rEar.rows << " ear.cols =" << rEar.cols << " numb= " << rEar.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
	else
		cout << "something went wrong" << endl;
}
void catMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &ear, cv::Mat &nose)
{
	noseMask(temp, shapes, nose);
	earMask(temp, shapes, ear);
}
void heartMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &img)
{
	int r, x1, y1, x2, y2;
	cv::Mat  head, dst, rEar, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 
	r = (shapes.part(0)(0) + shapes.part(16)(0)) / 2;
	x1 = shapes.part(0)(0) - 70;
	x2 = shapes.part(16)(0) + 80;
	y1 = shapes.part(0)(1) - 2 * r-30;
	y2 = shapes.part(0)(1) - 30;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	if (x2 > temp.rows)
		x2 = temp.rows - 1;
	if (y2 > temp.cols)
		y2 = temp.cols - 1;
	if (x1 < 0)
		x1 = 1;
	if (y1 < 0)
		y1 = 1;
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
		//	cv::cvtColor(temp, temp, CV_BGR2BGRA);
		temp(rowRange, colRange).copyTo(head);

		cv::resize(rgba[3], rEar, cv::Size(head.cols, head.rows));
		cv::resize(img, img, cv::Size(head.cols, head.rows));

		head.copyTo(dst);
		for (int i = 1; i < head.rows - 3; i++)
		{
			for (int j = 1; j < head.cols - 3; j++)
			{


				if (rEar.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}

		}

		//now i will work on applying mask

		cout << "head.rows =" << head.rows << " head.cols= " << head.cols << " numb= " << head.channels() << endl
			<< "ear.rows=" << rEar.rows << " ear.cols =" << rEar.cols << " numb= " << rEar.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
	else
		cout << "something went wrong" << endl;
}
void hatMask(cv::Mat &temp, full_object_detection shapes, cv::Mat &img)
{
	int r,x1, y1, x2, y2;
	cv::Mat  head, dst, rHat, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 
	r  = (shapes.part(0)(0) + shapes.part(16)(0))/2;
	x1 = shapes.part(0)(0) - 100;
	x2 = shapes.part(16)(0) + 25;
	y1 = shapes.part(0)(1) - 2 * r;
	y2 = shapes.part(0)(1)-20 ;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	if (x2 > temp.rows)
		x2 = temp.rows - 1;
	if (y2 > temp.cols)
		y2 = temp.cols - 1;
	if (x1 < 0)
		x1 = 1;
	if (y1 < 0)
		y1 = 1;
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
	//	cv::cvtColor(temp, temp, CV_BGR2BGRA);
		temp(rowRange, colRange).copyTo(head);

		cv::resize(rgba[3], rHat, cv::Size(head.cols, head.rows));
		cv::resize(img, img, cv::Size(head.cols, head.rows));

		head.copyTo(dst);
		for (int i = 1; i < head.rows - 3; i++)
		{
			for (int j = 1; j < head.cols - 3; j++)
			{
				cout<<rHat.ptr<int>(i, j)[0] << " ";

				if (rHat.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}

		}

		//now i will work on applying mask

		cout << "head.rows =" << head.rows << " head.cols= " << head.cols << " numb= " << head.channels() << endl
			<< "hat.rows=" << rHat.rows << " hat.cols =" << rHat.cols << " numb= " << rHat.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
	else
		cout << "something went wrong" << endl;
}
void glassesMask(cv::Mat &temp, full_object_detection shapes,cv::Mat &img)
{
	int x1, y1, x2, y2;
	cv::Mat  eye, dst, rGlasses, rgba[4];
	split(img, rgba);
	//getting th rect of the eye 
	x1 = shapes.part(36)(0) - 60;
	x2 = shapes.part(45)(0) + 60;
	y1 = shapes.part(37)(1) - 50;
	y2 = shapes.part(47)(0) - 60;
	//crop eyes to add glasses mask 
	if (y1 > y2)
		swap(y1, y2);
	if (x1 > x2)
		swap(x1, x2);
	if (y1 > 0 && x1 > 0 && x2 <= temp.rows && y2 <= temp.cols)
	{
		cv::Range colRange = cv::Range(x1, x2);
		cv::Range rowRange = cv::Range(y1, y2);
		
		temp(rowRange, colRange).copyTo(eye);

		cv::resize(rgba[3], rGlasses, cv::Size(eye.cols, eye.rows));
		cv::resize(img, img, cv::Size(eye.cols, eye.rows));

		eye.copyTo(dst);
		for (int i = 1; i < eye.rows - 3; i++)
		{
			for (int j = 1; j < eye.cols - 3; j++)
			{
				
				if (rGlasses.ptr<int>(i, j)[0] < 0)
				{
					dst.at<cv::Vec4b>(i, j)[0] = img.at<cv::Vec4b>(i, j)[0];
					dst.at<cv::Vec4b>(i, j)[1] = img.at<cv::Vec4b>(i, j)[1];
					dst.at<cv::Vec4b>(i, j)[2] = img.at<cv::Vec4b>(i, j)[2];
					dst.at<cv::Vec4b>(i, j)[3] = img.at<cv::Vec4b>(i, j)[3];
				}

			}
	
		}

		//now i will work on applying mask

		cout << "eye.rows =" << eye.rows << " eye.cols= " << eye.cols << " numb= " << eye.channels() << endl
			<< "glasses.rows=" << rGlasses.rows << " glasses.cols =" << rGlasses.cols << " numb= " << rGlasses.channels() << endl;


		dst.copyTo(temp(rowRange, colRange));


	}
}
int check(cv::Mat img, cv::Mat temp,cv::Mat hat)
{
	if (!img.data || !temp.data || !hat.data )
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	else
	{
		cout << "i found ittttttttttttttttttttttt \n";

	}

}
int main()
{

	try
	{
		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

		//read images 
		cv::Mat img = cv::imread("glasses4.png", cv::IMREAD_UNCHANGED);
		cv::Mat hat = cv::imread("hat2.png", cv::IMREAD_UNCHANGED);
		cv::Mat nose = cv::imread("nose.png", cv::IMREAD_UNCHANGED);
		cv::Mat ear = cv::imread("ear.png", cv::IMREAD_UNCHANGED);
		cv::Mat nose2 = cv::imread("nose2.png", cv::IMREAD_UNCHANGED);
		cv::Mat ear2 = cv::imread("ear2.png", cv::IMREAD_UNCHANGED);
		cv::Mat heart = cv::imread("hearts.png", cv::IMREAD_UNCHANGED);
		cv::Mat temp = cv::imread("hager3.jpg", cv::IMREAD_UNCHANGED);
		cv::Mat temp2, temp3;
		temp.copyTo(temp2);
		temp.copyTo(temp3);


		//resize to deal with suitable size
		cv::resize(temp, temp, cv::Size(500, 500));
		cv::resize(temp2, temp2, cv::Size(500, 500));
		cv::resize(temp3, temp3, cv::Size(500, 500));
		// Check for invalid input
		check(img, temp,hat);
		//convert img to something that dlb can deal with 
		cv_image<bgr_pixel> cimg(temp);
		// Detect faces 
		std::vector<rectangle> faces = detector(cimg);
		// Find the pose of each face.
		std::vector<full_object_detection> shapes;

		cout << "number of detected faces = " << faces.size() << endl;

		for (unsigned long i = 0; i < faces.size(); ++i)
		{
			shapes.push_back(pose_model(cimg, faces[i]));
			cv::cvtColor(temp, temp, CV_BGR2BGRA);
			cv::cvtColor(temp2, temp2, CV_BGR2BGRA);
			cv::cvtColor(temp3, temp3, CV_BGR2BGRA);
			glassesMask(temp, shapes[i], img);
		//	hatMask(temp, shapes[i], hat);
		    catMask(temp2, shapes[i], ear, nose);
			//rabbitMask(temp, shapes[i], ear2, nose2);
			heartMask(temp3, shapes[i], heart);
		}

		cv::namedWindow("temp", cv::WINDOW_AUTOSIZE);// Create a window for display.
		cv::imshow("temp", temp);                   // Show our image inside it.

		cv::namedWindow("temp2", cv::WINDOW_AUTOSIZE);// Create a window for display.
		cv::imshow("temp2", temp2);                   // Show our image inside it.

		cv::namedWindow("temp3", cv::WINDOW_AUTOSIZE);// Create a window for display.
		cv::imshow("temp3", temp3);                   // Show our image inside it.

		//cv::namedWindow("glasses", cv::WINDOW_AUTOSIZE);// Create a window for display.
		//cv::imshow("glasses",img);	
		cv::waitKey(0);
			
		
	}
	catch (serialization_error& e)
	{
		cout << endl << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

