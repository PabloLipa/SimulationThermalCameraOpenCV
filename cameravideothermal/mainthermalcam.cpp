#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

cv::Mat converteparacinza(const cv::Mat& imagemmatORIGEM) {
    cv::Mat becameGRAY;
    if (imagemmatORIGEM.channels() == 3) {
        cv::cvtColor(imagemmatORIGEM, becameGRAY, cv::COLOR_BGR2GRAY);
    }
    else {
        becameGRAY = imagemmatORIGEM;
    }
    return becameGRAY;
}

int main(int argc, char** argv) {
    // Abrir a webcam (índice 0)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a webcam!" << std::endl;
        return -1;
    }

    cv::Mat frame, gray_img, c_i;

    while (true) {
        // Capturar frame da webcam
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Erro ao capturar frame!" << std::endl;
            break;
        }

        // Converter frame para escala de cinza
        gray_img = converteparacinza(frame);

        // Certificar-se de que a imagem está no formato CV_8UC1
        if (gray_img.type() != CV_8UC1) {
            gray_img.convertTo(gray_img, CV_8UC1);
        }

        // Aplicar o mapa de cores
        cv::applyColorMap(gray_img, c_i, cv::COLORMAP_JET);

        // Mostrar o frame com o mapa de cores aplicado
        cv::imshow("Imagem com Mapa de Cores", c_i);

        // Sair do loop se a tecla 'q' for pressionada
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Liberar a webcam e destruir todas as janelas
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
