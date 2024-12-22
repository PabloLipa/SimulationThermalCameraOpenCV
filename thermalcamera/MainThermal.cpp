#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat converteparacinza(const cv::Mat& imagemmatORIGEM) {
	cv::Mat becameGRAY;
	if (imagemmatORIGEM.channels() == 3) {
		cv::cvtColor(imagemmatORIGEM, becameGRAY, cv::COLOR_BGR2GRAY);
	}
	else
	{
		becameGRAY = imagemmatORIGEM;
	}
	return becameGRAY;

}




int main(int argc, char** argv) {
	try {
		cv::Mat thermal_img = cv::imread("man.jpg", cv::IMREAD_UNCHANGED);
		if (thermal_img.empty()) { std::cerr << "Erro ao carregar a imagem!" << std::endl; return -1; }


		cv::Mat gray_img = converteparacinza(thermal_img);
		if (gray_img.type() != CV_8UC1)
		{ 
			gray_img.convertTo(gray_img, CV_8UC1);
		}

		cv::Mat c_i;
		if (gray_img.type() == CV_8UC1 || gray_img.type() == CV_8UC3) 
		{ 
			cv::applyColorMap(gray_img, c_i, cv::COLORMAP_JET);
		}else { 
			std::cerr << "Tipo de imagem incompatível para cv::applyColorMap!" << std::endl; 
			return -1; 
		}


		cv::imshow("NOME DO ARQUIVO DA IMAGEM", c_i);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
	catch (const cv::Exception& e) {
		std::cerr << "Erro da OpenCV: " << e.what() << std::endl; return -1;
	}
	catch (const std::exception& e) {
		std::cerr << "Erro: " << e.what() << std::endl; return -1;
	}
	return 0;
}



