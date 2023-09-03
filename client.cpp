/*reference
https://stackoverflow.com/questions/47881656/how-to-transfer-cvvideocapture-frames-through-socket-in-client-server-model-o
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    int bbytee;
    cout << "before open the cam" << endl;

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Could not open the camera" << endl;
        close(sock);
        return -1;
    }

    Mat frame;
    frame = Mat::zeros(480, 640, CV_8UC3);
    int imgSize = frame.cols * frame.rows * 3;

    int cnt = 0;
    // Mat frame;
    while (1)
    {
        cap >> frame;
        if (frame.empty())
        {
            cerr << "[client] VideoCapture(0) error!" << endl;
        }

        cout << ++cnt << ":" << frame.isContinuous() << "," << frame.size() << endl;
        ;

        if ((bbytee = send(sock, frame.data, imgSize, 0)) < 0)
        {
            cerr << "bytes = " << bbytee << endl;
            break;
        }

        cv::imshow("client", frame);
        if (cv::waitKey(100) == 'q')
        {
            break;
        }
    }
    close(sock);
    return 0;
}